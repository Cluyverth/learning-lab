import { randomUUIDv7 } from "bun";
import { index, pgTable, text, timestamp } from "drizzle-orm/pg-core";

export const verifications = pgTable(
	"verifications",
	{
		id: text("id")
			.primaryKey()
			.$defaultFn(() => randomUUIDv7()),
		identifier: text("identifier").notNull(),
		value: text("value").notNull(),
		expiresAt: timestamp("expiresAt").notNull(),
		createdAt: timestamp("createdAt").notNull(),
		updatedAt: timestamp("updatedAt")
			.$onUpdate(() => new Date())
			.notNull(),
	},
	(table) => [index("verifications_identifier_idx").on(table.identifier)],
);
