import { openapi } from "@elysiajs/openapi";
import { Elysia } from "elysia";
import { z } from "zod";
import {
	betterAuthPlugin,
	OpenAPI,
} from "./core/server/http/plugins/betterAuth";

const app = new Elysia()
	.use(
		openapi({
			documentation: {
				components: await OpenAPI.components,
				paths: await OpenAPI.getPaths(),
			},
		}),
	)
	.use(betterAuthPlugin)
	.get("/", () => "Hello Elysia")
	.get(
		"/users/:id",
		({ params, user }) => {
			const userId = params.id;
			const authenticatedUserName = user.name;
			console.log(
				`Authenticated user ${authenticatedUserName} is accessing user ${userId}`,
			);
			return {
				id: userId,
				name: authenticatedUserName,
			};
		},
		{
			auth: true,
			detail: {
				summary: "Get User by ID",
				description: "Fetches a user object based on the provided user ID.",
				tags: ["User"],
			},
			params: z.object({
				id: z.string(),
			}),
			response: {
				200: z.object({
					id: z.string(),
					name: z.string(),
				}),
			},
		},
	)
	.listen(3333);

console.log(
	`🦊 Elysia is running at ${app.server?.hostname}:${app.server?.port}`,
);
