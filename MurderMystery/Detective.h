/**************************************************
Project: Murder Mystery
Author: Ming Shern Siew
Purpose: Header File
Header file organize all dependency and package which will be used in detective file.
The structured file is in order of following:
#include, using
declare global variables
declare user defined functions
**************************************************/
#ifndef DETECTIVE_H
#define DETECTIVE_H
#include "Suspect.h"
#include "Utility.h"
#include "NoteItem.h"

#pragma once
class Detective : public Suspect {
	public:
		Detective();
		Detective(string name);
		// functions
		virtual void move(vector<string>& token, Map* map);
};
#endif

