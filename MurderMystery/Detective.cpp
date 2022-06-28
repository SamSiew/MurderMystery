#include "Detective.h"

Detective::Detective() : Suspect("anon", StatusType::DETECTIVE)
{
	addInventory(new NoteItem());
}

Detective::Detective(string name) : Suspect(name, StatusType::DETECTIVE)
{
	addInventory(new NoteItem());
}

void Detective::move(vector<string>& token, Map* map)
{
	processInput(token);
	if (token.size() > 2) {
		displayInformation("Only accept either one or two words command and single whitespace between two words!", true);
		move(token, map);
	}
}