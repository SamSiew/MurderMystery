/**************************************************
Project: Murder Mystery
Author: Ming Shern Siew
Purpose: Header File
Header file organize all dependency and package which will be used in item file.
The structured file is in order of following:
#include, using
declare global variables
declare user defined functions
**************************************************/
#ifndef ITEM_H
#define ITEM_H
#include <iostream>
#include <sstream>
#include <string>
#include "Enums.h"
#include "Suspect.h"

using namespace std;

class Item {
	protected:
		// Class variables
		bool* isMurderItem;
		ItemType* itemType;
		string* itemName;

		Item();
		Item(string newName);
		Item(string newName, ItemType type);
		Item(string newName, ItemType type, bool isMurderItem);

	public:
		// Destructor
		virtual ~Item();
		// Accessor Functions
		bool operator==(Item item);
		bool operator==(Item* item);
		bool operator==(string item);
		bool getIsMurderItem();
		ItemType getItemType();
		string getItemName();
		// Mutator Functions
		void setName(string newName);
		void setItemType(ItemType newType);
		void setIsMurderItem(bool isMurder);
		void displayDescription();
		virtual string getItemDetails();
		virtual bool use(Suspect* suspect, Map* map);
};
#endif