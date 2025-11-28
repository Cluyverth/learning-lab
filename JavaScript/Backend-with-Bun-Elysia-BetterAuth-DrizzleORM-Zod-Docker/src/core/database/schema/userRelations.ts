import { relations } from "drizzle-orm";
import { accounts } from "./accounts";
import { sessions } from "./sessions";
import { users } from "./users";

export const userRelations = relations(users, ({ many }) => ({
	sessions: many(sessions),
	accounts: many(accounts),
}));
