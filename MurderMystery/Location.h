/**************************************************
Project: Murder Mystery
Author: Ming Shern Siew
Purpose: Header File
Header file organize all dependency and package which will be used in location file.
The structured file is in order of following:
#include, using
declare global variables
declare user defined functions
**************************************************/
#ifndef LOCATION_H
#define LOCATION_H
#include <iostream>
#include <sstream>
#include <string>
#include "Utility.h"
#include "Enums.h"
#include "Suspect.h"
#include "Item.h"

using namespace std;

class Location {
	private:
		// Class variables
		bool *isCrimeScene;
		string *locationName;
		vector<Suspect*> suspects;
		vector<Item*> inventory;
		void setInitialStats(string initName, bool isCrime);
		string getInventoryContents();
		string getSuspectsContents();

	public:
		// Constructors
		Location();
		Location(string newName);
		Location(string locName, bool isCrime);
		// Destructor
		~Location();
		// Accessor Functions
		bool getIsCrimeScene();
		bool hasMurderWeapon();
		string getLocationName();
		string getLocationDetails();
		Suspect* getSuspect(string name);
		Suspect* findRandomSuspect();
		Item* getItem(string name);
		bool operator == (Location location);
		bool operator == (string location);

		// Mutator Functions
		void updateLocationName(string newName);
		void updateCrimeScene(bool isCrime);
		void addItem(Item* newItem);
		void removeItem(Item* newItem);
		void addSuspect(Suspect* suspect);
		void removeSuspect(Suspect* suspect);
		void moveSuspect(Suspect* newSuspect, Location* location);
		void displayLocation();
		void displayDescription();
};
#endif