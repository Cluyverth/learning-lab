import { randomUUIDv7 } from "bun";
import { index, pgTable, text, timestamp } from "drizzle-orm/pg-core";
import { users } from "./users";

export const sessions = pgTable(
	"sessions",
	{
		id: text("id")
			.primaryKey()
			.$defaultFn(() => randomUUIDv7()),
		userId: text("userId")
			.notNull()
			.references(() => users.id, { onDelete: "cascade" }),
		ipAddress: text("ipAddress"),
		userAgent: text("userAgent"),
		token: text("token").notNull().unique(),
		expiresAt: timestamp("expiresAt").notNull(),
		createdAt: timestamp("createdAt").notNull(),
		updatedAt: timestamp("updatedAt")
			.$onUpdate(() => new Date())
			.notNull(),
	},
	(table) => [index("sessions_userId_idx").on(table.userId)],
);
