/**************************************************
Project: Murder Mystery
Author: Ming Shern Siew
Purpose: Header File
Header file organize all dependency and package which will be used in miscellous file.
The structured file is in order of following:
#include, using
declare global variables
declare user defined functions
**************************************************/
#ifndef MISCITEM_H
#define MISCITEM_H
#include "Item.h"
class MiscItem : public Item
{
public:
	MiscItem(string name);
};
#endif
