#include "Location.h"

Location::Location()
{
	setInitialStats("", false);
}

Location::Location(string newName)
{
	setInitialStats(newName, false);
}

Location::Location(string newName, bool isCrime)
{
	setInitialStats(newName, isCrime);
}

Location::~Location()
{
	delete locationName;
	delete isCrimeScene;
	for (size_t i = 0; i < inventory.size(); i++) {
		delete inventory[i];
		inventory[i] = NULL;
	}
}

bool Location::getIsCrimeScene()
{
	return *isCrimeScene;
}

bool Location::hasMurderWeapon()
{
	for (vector<Item*>::iterator iter = inventory.begin(); iter != inventory.end(); iter++) {
		bool isMurderWeapon = (*iter)->getIsMurderItem();
		if (isMurderWeapon) {
			return true;
		}
	}
	return false;
}

string Location::getLocationName()
{
	return *locationName;
}


string Location::getLocationDetails()
{
	// returns a formatted string
	stringstream locationDetails;
	locationDetails << "This is " << getLocationName() << endl;
	locationDetails << "The suspect arround here: " << getSuspectsContents() << endl;
	locationDetails << "The item around here: " << getInventoryContents() << endl;
	locationDetails << "Are there blood here ? : " << boolalpha << getIsCrimeScene() << endl;
	locationDetails << endl;
	return locationDetails.str();
}

Suspect* Location::getSuspect(string name)
{
	for (size_t i = 0; i < suspects.size(); i++)
	{
		if (*suspects[i] == name) {
			return suspects[i];
		}
	}
	return NULL;
}

Item* Location::getItem(string name)
{
	for (size_t i = 0; i < inventory.size(); i++)
	{
		if (*inventory[i] == name) {
			return inventory[i];
		}
	}
	return NULL;
}

bool Location::operator==(Location location)
{
	if (getLocationName() != location.getLocationName())
	{
		return false;
	}
	return true;
}

bool Location::operator==(string location)
{
	if (getLocationName().find(location) == string::npos)
	{
		return false;
	}
	return true;
}

void Location::updateLocationName(string newName)
{
	*locationName = newName;
}

void Location::updateCrimeScene(bool isCrime)
{
	*isCrimeScene = isCrime;
}

void Location::addItem(Item* newItem)
{
	inventory.push_back(newItem);
}

void Location::removeItem(Item* newItem)
{
	inventory.erase(remove(inventory.begin(),inventory.end(),newItem),inventory.end());
}

void Location::addSuspect(Suspect* suspect)
{
	suspects.push_back(suspect);
}

Suspect* Location::findRandomSuspect()
{
	int rand_sus = rand() % suspects.size();
	StatusType status = suspects.at(rand_sus)->getStatusType();
	if (status == StatusType::DETECTIVE || status == StatusType::MURDERER)
	{
		return NULL;
	}
	else 
	{
		return suspects.at(rand_sus);
	}
}

void Location::removeSuspect(Suspect* newSuspect)
{
	suspects.erase(remove(suspects.begin(), suspects.end(), newSuspect), suspects.end());
}

void Location::moveSuspect(Suspect* newSuspect, Location* location)
{
	removeSuspect(newSuspect);
	location -> addSuspect(newSuspect);
}

void Location::setInitialStats(string initName, bool isCrime)
{
	locationName = new string(initName);
	isCrimeScene = new bool(isCrime);
}

string Location::getInventoryContents() {
	// Return string of the character’s inventory
	string contents = "";
	for (vector<Item*>::iterator iter = inventory.begin(); iter != inventory.end(); iter++) {
		contents += (*iter) -> getItemName() + ", ";
	}
	return contents;
}

string Location::getSuspectsContents()
{
	// Return string of the character’s inventory
	string contents = "";
	for (vector<Suspect*>::iterator iter = suspects.begin(); iter != suspects.end(); iter++) {
		if ((*iter) -> getStatusType() != StatusType::DETECTIVE) {
			contents += (*iter)->getSuspectName() + ", ";
		}
	}
	return contents;
}

void Location::displayLocation()
{
	displayText(getLocationName() + ".txt");
}

void Location::displayDescription()
{
	cout << getLocationDetails();
}
