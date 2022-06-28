#include "Suspect.h"
#include "Item.h"
#include "Location.h"
#include "Map.h"

Suspect::Suspect() {
	// Default constructor
	setInitialStats("Anon","",StatusType::SUSPECT,NULL);
}
Suspect::Suspect(string newName) {
	// Usual creation constructor
	setInitialStats(newName, "", StatusType::SUSPECT, NULL);
}
Suspect::Suspect(string newName, StatusType status) {
	// Usual creation constructor
	setInitialStats(newName, "", status, NULL);
}
Suspect::Suspect(string newName, Location* baselocation) {
	// Usual creation constructor
	setInitialStats(newName, "", StatusType::SUSPECT, baselocation);
}
Suspect::Suspect(string newName,Location* baselocation,StatusType status) {
	// Usual creation constructor
	setInitialStats(newName, "", status, baselocation);
}
// Destructor
Suspect::~Suspect()
{
	delete numberOfTurn;
	delete hasSendMotive;
	delete hasRecvMotive;
	delete alibi;
	delete suspectName;
	delete suspectType;
	for (size_t i = 0; i < inventory.size(); i++) {
		delete inventory[i];
		inventory[i] = NULL;
	}
}

bool Suspect::operator==(Suspect suspect)
{
	if (getSuspectName() != suspect.getSuspectName())
	{
		return false;
	}
	if (getStatusType() != suspect.getStatusType())
	{
		return false;
	}
	return true;
}

bool Suspect::operator==(Suspect* suspect)
{
	return *this == *suspect;
}

int Suspect::getNumOfTurn()
{
	return *numberOfTurn;
}

string Suspect::getAlibi()
{
	// returns a formatted string
	stringstream suspectDetails;
	if (alibi -> empty()) {
		suspectDetails << "I was alone at " << getBaseLocation() -> getLocationName() << endl;
	}
	else
	{
		suspectDetails << "I was with " << *alibi << " at " << getBaseLocation()->getLocationName() << endl;
	}
	return suspectDetails.str();
}

Location* Suspect::getBaseLocation()
{
	return baselocation;
}

Location* Suspect::getCurrentLocation()
{
	return currentlocation;
}

// ACCESSOR FUNCTIONS
// Written like this to reduce space in this document
StatusType Suspect::getStatusType() { return *suspectType; }

string Suspect::getSuspectName() { return *suspectName; }

string Suspect::getSuspectDetails() {
	// returns a formatted string
	stringstream suspectDetails;
	suspectDetails << "Hi, My name is : " << getSuspectName() << endl;
	suspectDetails << "Currently, I am at : " << getCurrentLocation() -> getLocationName() << endl;
	if (getStatusType() == StatusType::DETECTIVE) {
		suspectDetails << "My inventory: " << getInventoryContents();
	}
	else {
		suspectDetails << getAlibi();
	}
	suspectDetails << endl;
	return suspectDetails.str();
}
void Suspect::setNumOfTurn(int turn)
{
	*numberOfTurn = turn;
}
void Suspect::setBaseLocation(Location* location)
{
	baselocation = location;
}
void Suspect::setCurrentLocation(Location* location)
{
	currentlocation = location;
}
void Suspect::setAlibi(Suspect* newalibi)
{
	*alibi = newalibi -> getSuspectName();
}
// MUTATOR FUNCTIONS
void Suspect::setSuspectName(string newName) {
	if (newName.length() > 0) {
		*suspectName = newName;
	}
}
void Suspect::setSuspectType(StatusType newSuspectType)
{
	*suspectType = newSuspectType;
}

void Suspect::addInventory(Item* newItem) {
	inventory.push_back(newItem);
}
Item* Suspect::removeInventory(Item* newItem) {
	inventory.erase(remove(inventory.begin(), inventory.end(), newItem), inventory.end());
	return newItem;
}
Item* Suspect::removeInventory(string newItem)
{
	Item* item = getItem(newItem);
	removeInventory(item);
	return item;
}
void Suspect::move(vector<string>& token, Map* map)
{
	token.push_back("Go");
	if (*numberOfTurn == MAX_WAITING_TURN) {
		int place_pos = rand() % map->size();
		token.push_back(map->getLocation(place_pos)->getLocationName());
		setNumOfTurn(0);
	}
	else
	{
		token.push_back(getCurrentLocation() -> getLocationName());
		setNumOfTurn(getNumOfTurn() + 1);
	}
}
void Suspect::examine(string item)
{
	Item* items = getItem(item);
	items -> displayDescription();
}

void Suspect::displayCurrentLocation()
{
	getCurrentLocation()->displayLocation();
}

void Suspect::displayDescription()
{
	cout << getSuspectDetails();
}

void Suspect::displayDescription(Suspect* suspect)
{
	displayDescription();
	if (getStatusType() != StatusType::DETECTIVE) {
		if (getHasSendMotive()) {
			displayInformation("Rumor says that revenge was the motive because organization here killed john wick's pet, he's comming for us!", true);
			suspect->setHasRecvMotive(true);
		}
		else
		{
			setHasSendMotive(true);
		}
	}
}
void Suspect::useItem(string target, Map* map)
{
	Item* item = getItem(target);
	item -> use(this, map);
}
// PRIVATE FUNCTIONS
string Suspect::getInventoryContents() {
	// Return string of the character’s inventory
	string contents = "";
	vector<Item*>::iterator iter;
	for (iter = inventory.begin(); iter != inventory.end(); iter++) {
		contents += (*iter) -> getItemName() + ", ";
	}
	return contents;
}

bool Suspect::hasMurderWeapon() {
	vector<Item*>::iterator iter;
	for (iter = inventory.begin(); iter != inventory.end(); iter++) {
		if ((*iter) -> getIsMurderItem()) {
			return true;
		};
	}
	return false;
}

bool Suspect::hasAlibi()
{
	return alibi -> empty() == false;
}

bool Suspect::getHasSendMotive()
{
	return *hasSendMotive;
}

bool Suspect::getHasRecvMotive()
{
	return *hasRecvMotive;
}

void Suspect::setHasSendMotive(bool sendMotive)
{
	*hasSendMotive = sendMotive;
}

void Suspect::setHasRecvMotive(bool recvMotive)
{
	*hasRecvMotive = recvMotive;
}

void Suspect::setInitialStats(string initName,string initAlibi,StatusType status, Location* newbaselocation) {
	// Generate random values for each character attributes using defaults
	suspectName = new string(initName);
	alibi = new string(initAlibi);
	suspectType = new StatusType(status);
	numberOfTurn = new int(0);
	hasSendMotive = new bool(false);
	hasRecvMotive = new bool(false);
	baselocation = newbaselocation;
	currentlocation = newbaselocation;
}

Item* Suspect::getItem(string name)
{
	for (size_t i = 0; i < inventory.size(); i++)
	{
		if (*inventory[i] == name) {
			return inventory[i];
		}
	}
	return NULL;
}
