/**************************************************
Project: Murder Mystery
Author: Ming Shern Siew
Purpose: Header File
Header file organize all dependency and package which will be used in suspect file.
The structured file is in order of following:
#include, using
declare global variables
declare user defined functions
**************************************************/
#ifndef SUSPECT_H
#define SUSPECT_H

#include <iostream>
#include <sstream>
#include <string>
#include <ctime>
#include <vector>
#include "Enums.h"

using namespace std;

class Item;
class Map;
class Location;
class Suspect {
	protected:
		// Variables
		static const int MAX_WAITING_TURN = 5;
		int *numberOfTurn;
		bool *hasSendMotive;
		bool *hasRecvMotive;
		string *alibi;
		string *suspectName;
		StatusType *suspectType;
		Location *baselocation;
		Location *currentlocation;
		vector<Item*> inventory;
		
		// Private Functions
		bool getHasSendMotive();
		void setHasSendMotive(bool sendMotive);
		void setHasRecvMotive(bool recvMotive);
		void setInitialStats(string initName, string initAlibi, StatusType status, Location* newbaselocation);

	public:
		// Constructors
		Suspect();
		Suspect(string newName);
		Suspect(string newName, StatusType status);
		Suspect(string newName, Location* baselocation);
		Suspect(string newName, Location* baselocation, StatusType status);
		// Destructor
		~Suspect();
		// Accessor Functions
		bool operator==(Suspect suspect);
		bool operator==(Suspect* suspect);
		int getNumOfTurn();
		bool getHasRecvMotive();
		bool hasMurderWeapon();
		bool hasAlibi();
		string getAlibi();
		Location* getBaseLocation();
		Location* getCurrentLocation();
		StatusType getStatusType();
		Item* getItem(string name);
		string getSuspectName();
		string getSuspectDetails();
		string getInventoryContents();
		
		// Mutator Functions
		void setNumOfTurn(int turn);
		void setBaseLocation(Location* location);
		void setCurrentLocation(Location* location);
		void setAlibi(Suspect* alibi);
		void setSuspectName(string newName);
		void setSuspectType(StatusType newSuspectType);
		void addInventory(Item* newItem);
		Item* removeInventory(Item* newItem);
		Item* removeInventory(string newItem);
		void useItem(string target, Map* map);
		void examine(string item);
		void displayCurrentLocation();
		void displayDescription();
		void displayDescription(Suspect* suspect);
		virtual void move(vector<string>& token, Map* map);
};
#endif