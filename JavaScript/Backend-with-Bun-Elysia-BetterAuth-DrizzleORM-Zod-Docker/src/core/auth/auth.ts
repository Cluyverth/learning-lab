import { betterAuth } from "better-auth";
import { drizzleAdapter } from "better-auth/adapters/drizzle";
import { openAPI } from "better-auth/plugins";
import { db } from "../database/client";

export const auth = betterAuth({
	basePath: "/auth",
	plugins: [openAPI()],
	database: drizzleAdapter(db, {
		provider: "pg",
		usePlural: true,
		camelCase: true,
	}),
	advanced: {
		database: {
			generateId: false,
		},
	},
	emailAndPassword: {
		enabled: true,
		autoSignIn: true,
		password: {
			hash: (password: string) => Bun.password.hash(password),
			verify: ({ password, hash }) => Bun.password.verify(password, hash),
		},
	},
	session: {
		expiresIn: 60 * 60 * 24 * 7, // 7 days
		cookieCache: {
			enabled: true,
			maxAge: 60 * 10, // 10 minutes
		},
	},
	// If using scalable architecture, enable secondary storage for caching sessions using Redis.
	// secondaryStorage: {
	// 	type: "redis",
	// 	client: redisClient, // Your Redis client instance
	// 	cacheTTL: 60 * 10, // 10 minutes
	// },
});
