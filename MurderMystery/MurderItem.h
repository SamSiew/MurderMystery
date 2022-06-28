/**************************************************
Project: Murder Mystery
Author: Ming Shern Siew
Purpose: Header File
Header file organize all dependency and package which will be used in murderitem file.
The structured file is in order of following:
#include, using
declare global variables
declare user defined functions
**************************************************/
#ifndef MURDERITEM_H
#define MURDERITEM_H
#include "Item.h"
#include "Map.h"

class MurderItem : public Item
{
public:
	MurderItem(string name);
	virtual bool use(Suspect* suspect, Map* map);
};
#endif
