#include "NoteItem.h"

NoteItem::NoteItem() : Item("note", ItemType::NOTE)
{
}

NoteItem::~NoteItem()
{
	ofstream output("note.txt");
}

string NoteItem::getItemDetails()
{
	// Returns a formatted string containing information on the item.
	stringstream itemDetails;
	itemDetails << Item::getItemDetails();
	loadData("note.txt", itemDetails);
	return itemDetails.str();
}

bool NoteItem::use(Suspect* suspect, Map* map)
{
	string userinput = askForString("Type what you want, press enter to exit: ");
	saveData("note.txt", userinput);
	return true;
}
