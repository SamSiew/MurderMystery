/**************************************************
Project: Murder Mystery
Author: Ming Shern Siew
Purpose: Header File
Header file organize all dependency and package which will be used in murderer file.
The structured file is in order of following:
#include, using
declare global variables
declare user defined functions
**************************************************/
#pragma once
#ifndef MURDERER_H
#define MURDERER_H
#include "Suspect.h"
#include "Map.h"

class Murderer : public Suspect
{
private:
	Item* findMurderWeapon();
public:
	Murderer();
	Murderer(string name);
	// functions
	virtual void move(vector<string>& token, Map* map);
};
#endif
