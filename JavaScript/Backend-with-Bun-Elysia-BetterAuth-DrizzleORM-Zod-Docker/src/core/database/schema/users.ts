import { randomUUIDv7 } from "bun";
import { boolean, pgTable, text, timestamp } from "drizzle-orm/pg-core";

export const users = pgTable("users", {
	id: text("id")
		.primaryKey()
		.$defaultFn(() => randomUUIDv7()),
	name: text("name").notNull(),
	email: text("email").notNull().unique(),
	emailVerified: boolean("emailVerified").default(false).notNull(),
	image: text("image"),
	createdAt: timestamp("createdAt").notNull(),
	updatedAt: timestamp("updatedAt")
		.$onUpdate(() => new Date())
		.notNull(),
});
