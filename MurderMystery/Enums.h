/**************************************************
Project: Murder Mystery
Author: Ming Shern Siew
Purpose: Enums Header
Defines enum data for use by all classes
**************************************************/
#ifndef ENUMS_H
#define ENUMS_H
// Status Type were used to identify suspect to allow programmer to know in other class which allows polymorphism to just easily figure out status type without switch case everytime.
enum class StatusType {
	SUSPECT,
	MURDERER,
	VICTIM,
	DETECTIVE
};
// Difficulty for game which can change vary number of item and suspect at will to make game more challenging, can be identified along with integer.
enum DifficultyType {
	NOVICE = 2,
	SENIOR = 3,
	ELITE = 4
};
// Status Type were used to identify item to allow programmer to know in other class which allows polymorphism to just easily figure out item type without switch case everytime.
enum class ItemType {
	NONE,
	WEAPON,
	NOTE,
	MISCELLANEOUS
};
// Command which indicate type of command user has provided to process the moveset for game character.
enum class Command {
	GO, 
	SEARCH,
	USE, 
	GET, 
	DROP,
	EXAMINE,
	QUESTION,
	ACCUSE,
	GATHER,
	MAP,
	HELP,
	QUIT,
	INVALID
};
#endif