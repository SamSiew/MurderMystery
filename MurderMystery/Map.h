/**************************************************
Project: Murder Mystery
Author: Ming Shern Siew
Purpose: Header File
Header file organize all dependency and package which will be used in map file.
The structured file is in order of following:
#include, using
declare global variables
declare user defined functions
**************************************************/
#ifndef MAP_H
#define MAP_H
#include "Utility.h"
#include "MiscItem.h"
#include "MurderItem.h"
#include "Location.h"
#include "Murderer.h"
#include "Suspect.h"

using namespace std;

class Map {
private:
	// Class variables
	int *suspectTurnIndex;
	vector<Location*> maps;
	vector<Suspect*> actorLocations;

	int getNumSuspect();
	int getSuspectTurn();
	void setSuspectTurn(int suspectTurn);
	void removeSuspect(Suspect* suspect);
	Suspect* currentSuspectTurn();

public:
	// Constructors
	Map();
	// Destructor
	~Map();
	// Accessor Functions
	int size();
	bool hasFoundMurderer(string token);
	bool hasMurderWeapon();
	Item* getItem(Location* location, string name);
	Location* getLocation(int location_index);
	Location* getLocation(string name);
	Suspect* getSuspect(string suspect);
	Suspect* nextSuspectTurn();
	Suspect* findRandomSuspect(Location* location);

	// Mutator Functions
	Item* removeItem(string item, Location* newlocation);
	Item* removeItem(Item* item, Location* newlocation);
	void dropAction(string item, Suspect* actorlocation);
	void pickAction(string item, Suspect* actorlocation);
	void murderAction(Suspect* target);
	void addSuspect(Suspect* suspect);
	void addSuspect(Suspect* suspect, string newlocation);
	void addSuspect(Suspect* suspect, Location* newlocation);
	void moveSuspect(Suspect* suspect, string newlocation);
	void moveSuspect(Suspect* suspect, Location* newlocation);
	void addItem(Item* item);
	void addItem(Item* item, string newlocation);
	void addItem(Item* item, Location* newlocation);
	void addLocation(Location* newlocation);
	void spawnSuspect(vector<string>& suspects);
	void spawnMurderer(vector<string>& items, string murdername);
	void spawnItem(vector<string>& items);
	void spawnLocation(vector<string>& locations);
	void gatherSuspects(Suspect* suspect);
	void search(string newlocation);
	void displayNumbSuspect();
	void displayMapDetail();
	void displayMap();
};

#endif
