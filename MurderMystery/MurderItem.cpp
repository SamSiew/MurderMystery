#include "MurderItem.h"

MurderItem::MurderItem(string name) : Item(name,ItemType::WEAPON,true)
{
}

bool MurderItem::use(Suspect* suspect, Map* map)
{
	Suspect* rmvsuspect = map -> findRandomSuspect(suspect->getCurrentLocation());
	if (rmvsuspect != NULL && suspect -> getStatusType() == StatusType::MURDERER)
	{
		map -> murderAction(rmvsuspect);
		map -> dropAction(getItemName(), suspect);
		delete rmvsuspect;
		return true;
	}
	displayInformation("Cannot find target or Cannot be used by you!",true);
	return false;

}
