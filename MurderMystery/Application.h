/**************************************************
Project: Murder Mystery
Author: Ming Shern Siew
Purpose: Header File
Header file organize all dependency and package which will be used in application file.
The structured file is in order of following:
#include, using
declare global variables
declare user defined functions
**************************************************/
#ifndef APPLICATION_H
#define APPLICATION_H

// #include, using
#include "Utility.h"
#include "Enums.h"
#include "MiscItem.h"
#include "MurderItem.h"
#include "NoteItem.h"
#include "Map.h"
#include "Item.h"
#include "Detective.h"
#include "Suspect.h"
#include "Murderer.h"
#include "Location.h"

using namespace std;

// declare global variables
const unsigned MAX_PLACE = 20;

// declare functions
void runMenu();
void runOneWordCmd(Map* map, Suspect* actorlocation, Command cmd, bool& isGameRunning);
void runTwoWordCmd(Map* map, Suspect* actorlocation, Command* cmd, string token, bool& isGameRunning);
void displayResult(Suspect* actorlocation, Map* map, string token);
Command resolveOption(string input);

// main functions
int main();
#endif