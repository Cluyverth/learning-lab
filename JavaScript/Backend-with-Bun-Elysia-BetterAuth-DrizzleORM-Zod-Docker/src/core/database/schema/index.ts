import { accountRelations } from "./accountRelations";
import { accounts } from "./accounts";
import { sessionRelations } from "./sessionRelations";
import { sessions } from "./sessions";
import { userRelations } from "./userRelations";
import { users } from "./users";
import { verifications } from "./verifications";

export const schema = {
	users,
	userRelations,
	accounts,
	accountRelations,
	sessions,
	sessionRelations,
	verifications,
};
