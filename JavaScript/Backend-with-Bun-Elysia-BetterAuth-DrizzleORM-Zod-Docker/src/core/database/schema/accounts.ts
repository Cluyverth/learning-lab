import { randomUUIDv7 } from "bun";
import { index, pgTable, text, timestamp } from "drizzle-orm/pg-core";
import { users } from "./users";

export const accounts = pgTable(
	"accounts",
	{
		id: text("id")
			.primaryKey()
			.$defaultFn(() => randomUUIDv7()),
		accountId: text("accountId").notNull(),
		providerId: text("providerId").notNull(),
		userId: text("userId")
			.notNull()
			.references(() => users.id, { onDelete: "cascade" }),
		scope: text("scope"),
		password: text("password"),
		idToken: text("idToken"),
		accessToken: text("accessToken"),
		refreshToken: text("refreshToken"),
		accessTokenExpiresAt: timestamp("accessTokenExpiresAt"),
		refreshTokenExpiresAt: timestamp("refreshTokenExpiresAt"),
		createdAt: timestamp("createdAt").notNull(),
		updatedAt: timestamp("updatedAt")
			.$onUpdate(() => new Date())
			.notNull(),
	},
	(table) => [index("accounts_userId_idx").on(table.userId)],
);
