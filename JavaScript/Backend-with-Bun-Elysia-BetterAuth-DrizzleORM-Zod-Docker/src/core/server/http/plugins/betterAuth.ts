/**
 * Elysia Plugin for Better Auth: Mounts auth API routes + adds `auth` derive/macro.
 *
 * WHY? Reusable across app: .use(betterAuthPlugin) in index.ts enables:
 * - /auth/* routes (signUp, signIn, etc.).
 * - { auth: true } in routes → auto session check, blocks unauth → provides user/session.
 *
 * Macro 'resolve': Runs BEFORE handler, computes session, returns data or 401.
 * Elysia caches it per-request (perf!).
 */

import { auth } from "@/core/auth/auth";
import Elysia from "elysia";

export const betterAuthPlugin = new Elysia({ name: "betterAuth" })
	.mount(auth.handler)
	.macro({
		/**
		 * Macro: Adds 'auth' to context (like derive/compute).
		 * USAGE: In routes: .get('/protected', ({ auth }) => ..., { auth: true })
		 * WHY MACRO? Global, cached per-request, TypeScript-safe inference.
		 */
		auth: {
			async resolve({ status, request: { headers } }) {
				/**
				 * Runs BEFORE handler if { auth: true }.
				 * 1. Extract headers (cookies w/ session token).
				 * 2. auth.api.getSession({ headers }) → validates DB session.
				 * 3. No session? status(401) → BLOCKS route (short-circuit).
				 * 4. Has session? Return { user, session } → available in handler.
				 */
				// Get session from headers (cookie-based).
				const session = await auth.api.getSession({ headers });

				if (!session) {
					// No session: Return 401 Unauthorized (blocks route).
					return status(401, { message: "Unauthorized" });
				}

				// Return session data (access via { auth } in handlers).
				return {
					user: session.user,
					session: session.session,
				};
			},
		},
	});

/**
 * OpenAPI Schema Generator: Lazy-caches Better Auth's auto-generated OpenAPI spec.
 * WHY? Better Auth exposes .api.generateOpenAPISchema() → full docs for /auth/*.
 * Prefix paths (/auth/api), add tags → integrate w/ Elysia OpenAPI plugin.
 * Lazy: Compute ONCE (expensive), reuse everywhere (perf).
 */
let _schema:
	| Awaited<ReturnType<typeof auth.api.generateOpenAPISchema>>
	| undefined; // Private cache (singleton).

const getSchema = async () => {
	/**
	 * Lazy loader: Check cache, compute if missing (memoization).
	 * WHY ASYNC? Schema gen scans routes → Promise.
	 * WHY IF? Avoid recompute on every call (startup perf!).
	 */
	if (!_schema) {
		_schema = await auth.api.generateOpenAPISchema();
	}
	return _schema;
};

export const OpenAPI = {
	/**
	 * getPaths: Prefixes Better Auth paths (e.g., /signIn → /auth/api/signIn).
	 * WHY? Match your basePath + mount.
	 * Mutates: Adds 'Better Auth' tag to ALL operations → grouped in Swagger UI.
	 */
	getPaths: (prefix = "/auth") =>
		getSchema().then(({ paths }) => {
			const reference: typeof paths = Object.create(null);

			for (const path of Object.keys(paths)) {
				const key = prefix + path;
				reference[key] = paths[path];

				for (const method of Object.keys(paths[path])) {
					/**
					 * For each HTTP method (GET/POST), grab op → add tag.
					 * WHY Record<...>? OpenAPI paths: { '/path': { get: {...}, post: {...} } }
					 * Tags group in docs UI.
					 */
					const operation = (
						reference[key] as Record<string, Record<string, unknown>>
					)[method] as Record<string, unknown>;

					operation.tags = ["Better Auth"];
				}
			}

			return reference;
		}) as Promise<Record<string, Record<string, { tags: string[] }>>>,
	components: getSchema().then(({ components }) => components) as Promise<
		Record<string, unknown>
	>,
} as const;
