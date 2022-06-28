#include "Item.h"

Item::Item() {
	// Default constructor
	itemName = new string("Undefined");
	itemType = new ItemType(ItemType::NONE);
	isMurderItem = new bool(false);
}
Item::Item(string newName) {
	// Set values based off input
	itemName = new string(newName);
	itemType = new ItemType(ItemType::NONE);
	isMurderItem = new bool(false);
}

Item::Item(string newName, ItemType type)
{
	itemName = new string(newName);
	itemType = new ItemType(type);
	isMurderItem = new bool(false);
}

Item::Item(string newName, ItemType type, bool isMurder)
{
	itemName = new string(newName);
	itemType = new ItemType(type);
	isMurderItem = new bool(isMurder);
}

Item::~Item() {
	delete itemName;
	delete itemType;
	delete isMurderItem;
	// Nothing for now
}
// ACCESSOR FUNCTIONS
// Written like this to reduce space in this document
bool Item::operator==(Item item)
{
	if (getItemName() == item.getItemName())
	{
		return true;
	}
	return false;
}
bool Item::operator==(Item* item)
{
	return *this == *item;
}
// Written like this to reduce space in this document
bool Item::operator==(string item)
{
	if (getItemName() == item)
	{
		return true;
	}
	return false;
}

bool Item::getIsMurderItem()
{
	return *isMurderItem;
}
ItemType Item::getItemType() { return *itemType; }
string Item::getItemName() { return *itemName; }
string Item::getItemDetails() {
	// Returns a formatted string containing information on the item.
	stringstream itemDetails;
	itemDetails << "This Item is " << *itemName << endl ;
	itemDetails << "Is Weapon filled with blood: " << boolalpha << getIsMurderItem() << endl;
	itemDetails << endl;
	return itemDetails.str();
}

// MUTATOR FUNCTIONS
void Item::setName(string newName) {
	// Make sure that the type is valid
	if (newName.length() > 0) {
		*itemName = newName;
	}
}
void Item::setItemType(ItemType newType) {
	// Make sure that the type is valid
	// Assumption here that none is invalid. Should never be set.
	*itemType = newType;
}

void Item::setIsMurderItem(bool isMurder)
{
	*isMurderItem = isMurder;
}

void Item::displayDescription()
{
	cout << getItemDetails();
}

bool Item:: use(Suspect* suspect, Map* map)
{
	cout << "This item has no use." << endl;
	return true;
}
