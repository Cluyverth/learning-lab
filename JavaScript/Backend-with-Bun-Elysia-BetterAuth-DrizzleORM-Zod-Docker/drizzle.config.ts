import { env } from "@/env";
import { defineConfig } from "drizzle-kit";

export default defineConfig({
	schema: "./src/core/database/schema/**",
	out: "./src/core/database/migrations",
	dialect: "postgresql",
	dbCredentials: {
		url: env.DATABASE_URL,
	},
	casing: "camelCase",
});
