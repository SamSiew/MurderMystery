/**************************************************
Project: Murder Mystery
Author: Ming Shern Siew
Purpose: Header File
Header file organize all dependency and package which will be used in noteitem file.
The structured file is in order of following:
#include, using
declare global variables
declare user defined functions
**************************************************/
#ifndef NOTEITEM_H
#define NOTEITEM_H
#include "Item.h"
#include "Utility.h"

class NoteItem : public Item
{
	public:
		NoteItem();
		~NoteItem();
		virtual string getItemDetails();
		virtual bool use(Suspect* suspect, Map* map);
};
#endif
