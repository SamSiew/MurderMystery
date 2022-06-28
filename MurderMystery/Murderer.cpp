#include "Murderer.h"

Murderer::Murderer() : Suspect("anon", StatusType::MURDERER)
{
}

Murderer::Murderer(string name) : Suspect(name, StatusType::MURDERER)
{
}

void Murderer::move(vector<string>& token, Map* map)
{
	Item* weapon = findMurderWeapon();
	if (weapon != NULL && map -> findRandomSuspect(getCurrentLocation()) != NULL) 
	{
		token.push_back("use");
		token.push_back(weapon -> getItemName());
	}
	else
	{
		Suspect::move(token, map);
	}
}

Item* Murderer::findMurderWeapon() {
	for (size_t i = 0; i < inventory.size(); i++)
	{
		if (inventory[i] -> getIsMurderItem()) {
			return inventory[i];
		}
	}
	return NULL;
}