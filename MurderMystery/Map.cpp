#include "Map.h"

Map::Map()
{
	suspectTurnIndex = new int(-1);
}

Map::~Map()
{
	for (size_t i = 0; i < maps.size(); i++) {
		delete maps[i];
		maps[i] = NULL;
	}
	for (size_t i = 0; i < actorLocations.size(); i++) {
		delete actorLocations[i];
		actorLocations[i] = NULL;
	}
	delete suspectTurnIndex;
}

void Map::setSuspectTurn(int suspectTurn)
{
	*suspectTurnIndex = suspectTurn;
}

int Map::getNumSuspect()
{
	return actorLocations.size() - 1;
}

Suspect* Map::getSuspect(string suspect)
{
	for (size_t i = 0; i < actorLocations.size(); i++)
	{
		if (actorLocations[i] -> getSuspectName() == suspect) {
			return actorLocations[i];
		}
	}
	return NULL;
}

Location* Map::getLocation(int location_index)
{
	return maps[location_index];
}

Location* Map::getLocation(string name)
{
	for (size_t i = 0; i < maps.size(); i++)
	{
		if (*maps[i] == name) {
			return maps[i];
		}
	}
	return NULL;
}

Item* Map::getItem(Location* location, string name)
{
	return location -> getItem(name);
}

int Map::size()
{
	return maps.size();
}

bool Map::hasFoundMurderer(string token)
{
	return getSuspect(token)->getStatusType() == StatusType::MURDERER;
}

bool Map::hasMurderWeapon()
{
	for (vector<Location*>::iterator iter = maps.begin(); iter != maps.end(); iter++) {
		if ((*iter)->hasMurderWeapon()) {
			return true;
		}
	}
	return false;
}

Suspect* Map::nextSuspectTurn()
{
	setSuspectTurn(getSuspectTurn() + 1);
	if (getSuspectTurn() >= actorLocations.size()) {
		setSuspectTurn(0);
	}
	return currentSuspectTurn();
}

Suspect* Map::currentSuspectTurn()
{
	return actorLocations.at(getSuspectTurn());
}

int Map::getSuspectTurn()
{
	return *suspectTurnIndex;
}

void Map::search(string newlocation)
{
	Location* location = getLocation(newlocation);
	location->displayDescription();
}

void Map::displayNumbSuspect()
{
	displayInformation("Number of suspect in game left: " + to_string(getNumSuspect()), true);
}

void Map::addSuspect(Suspect* suspect, string newlocation)
{
	Location* location = getLocation(newlocation);
	addSuspect(suspect, location);
}

void Map::addSuspect(Suspect* suspect, Location* newlocation)
{
	actorLocations.insert(actorLocations.begin(),suspect);
	newlocation->addSuspect(suspect);
	suspect->setBaseLocation(newlocation);
	suspect->setCurrentLocation(newlocation);
}

void Map::removeSuspect(Suspect* suspect)
{
	suspect-> getCurrentLocation() ->removeSuspect(suspect);
	suspect-> setCurrentLocation(NULL);
	actorLocations.erase(remove(actorLocations.begin(), actorLocations.end(), suspect), actorLocations.end());
}

Suspect* Map::findRandomSuspect(Location* location)
{
	return location->findRandomSuspect();
}

void Map::addSuspect(Suspect* suspect)
{
	int rand_place = rand() % maps.size();
	Location* tomovelocation = maps.at(rand_place);
	addSuspect(suspect, tomovelocation);
}

void Map::moveSuspect(Suspect* suspect, string newlocation)
{
	Location* tomovelocation = getLocation(newlocation);
	moveSuspect(suspect, tomovelocation);
}

void Map::moveSuspect(Suspect* suspect, Location* newlocation)
{
	suspect->getCurrentLocation()->removeSuspect(suspect);
	suspect->setCurrentLocation(newlocation);
	newlocation->addSuspect(suspect);
}

void Map::addItem(Item* item)
{
	int rand_place = rand() % maps.size();
	Location* tomovelocation = maps.at(rand_place);
	addItem(item, tomovelocation);
}

void Map::addItem(Item* item, string newlocation)
{
	Location* location = getLocation(newlocation);
	addItem(item,location);
}

void Map::addItem(Item* item, Location* newlocation)
{
	newlocation -> addItem(item);
}

Item* Map::removeItem(string item, Location*  newlocation)
{
	Item* curr_item = getItem(newlocation, item);
	removeItem(curr_item, newlocation);
	return curr_item;
}

Item* Map::removeItem(Item* item, Location* newlocation)
{
	newlocation -> removeItem(item);
	return item;
}

void Map::dropAction(string item, Suspect* actorlocation)
{
	Location* location = actorlocation -> getCurrentLocation();
	Item* curr_item = actorlocation -> removeInventory(item);
	addItem(curr_item, location);
}

void Map::pickAction(string item, Suspect* actorlocation)
{
	Location* location = actorlocation -> getCurrentLocation();
	Item* curr_item = getItem(location, item);
	location->removeItem(curr_item);
	actorlocation->addInventory(curr_item);
}

void Map::murderAction(Suspect* target)
{
	Location* location = target->getCurrentLocation();
	getLocation(location->getLocationName())->updateCrimeScene(true);
	removeSuspect(target);
}

void Map::addLocation(Location* newlocation)
{
	maps.push_back(newlocation);
}

void Map::spawnSuspect(vector<string>& suspects)
{
	for (vector<string>::iterator iterator = suspects.begin(); iterator != suspects.end(); iterator++) {
		Suspect* newSus = new Suspect(*iterator);
		addSuspect(newSus);
	}

	for (size_t index = 0; index < 5; index++) {
		Suspect* suspect = actorLocations.at(index);
		Suspect* newsuspect = actorLocations.at(actorLocations.size() - index - 1);
		suspect -> setAlibi(newsuspect);
		newsuspect -> setAlibi(suspect);
		newsuspect-> setBaseLocation(suspect->getBaseLocation());
	}
	suspects.clear();
}

void Map::spawnMurderer(vector<string>& items, string murdername)
{
	int rand_place = rand() % maps.size();
	Murderer* newMurderer = new Murderer(murdername);
	newMurderer -> setAlibi(actorLocations.at(0));
	maps.at(rand_place)->updateCrimeScene(true);
	addItem(new MurderItem("knife"), maps.at(rand_place));
	addSuspect(newMurderer);
	for (vector<string>::iterator iterator = items.begin(); iterator != items.end(); iterator++) {
		newMurderer->addInventory(new MurderItem(*iterator));
	}
	items.clear();
	murdername.clear();
}


void Map::spawnItem(vector<string>& items)
{
	for (vector<string>::iterator iterator = items.begin(); iterator != items.end(); iterator++) {
		Item* newsuspect = new MiscItem(*iterator);
		addItem(newsuspect);
	}
	items.clear();
}

void Map::spawnLocation(vector<string>& locations)
{
	for (vector<string>::iterator iterator = locations.begin(); iterator != locations.end(); iterator++) {
		Location* newsuspect = new Location(*iterator);
		addLocation(newsuspect);
	}
	locations.clear();
}

void Map::gatherSuspects(Suspect* suspect)
{
	Location* newlocation = suspect -> getCurrentLocation();
	for (size_t i = 0; i < actorLocations.size(); i++)
	{
		moveSuspect(actorLocations[i], newlocation);
	}
}

void Map::displayMapDetail()
{
	for (size_t i = 0; i < maps.size(); i++)
	{
		cout << maps[i] -> getLocationDetails();
	}
}

void Map::displayMap()
{
	displayText("map.txt");
}
