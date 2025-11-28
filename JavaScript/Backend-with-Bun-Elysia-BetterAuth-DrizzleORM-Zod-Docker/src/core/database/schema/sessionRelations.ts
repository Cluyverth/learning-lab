import { relations } from "drizzle-orm";
import { sessions } from "./sessions";
import { users } from "./users";

export const sessionRelations = relations(sessions, ({ one }) => ({
	users: one(users, {
		fields: [sessions.userId],
		references: [users.id],
	}),
}));
