/**************************************************
Project: Murder Mystery
Assignment 3
Author: Ming Shern Siew
Purpose: Murder Mystery Driver Class File
**************************************************/
#include "Application.h"

int main() {
	runMenu();
	displayInformation("Thank you for playing this game!", true);
	return 0;
}

void runMenu() {
	/******************************************************************************
	 * Display and run menu options which allow user to different kind of service.
	 ******************************************************************************/
	 // declare and initialise local variables
	vector<string> token;
	vector<string> txt_list;
	
	int random_murderer;
	string murderer_name;
	Command command;
	Suspect* suspect;
	
	bool isGameStillRunning = true;
	Map* maps = new Map();
	
	displayText("rule_help.txt");
	system("pause");

	displayText("command_help.txt");
	system("pause");

	createLists("room.txt", txt_list);
	maps -> spawnLocation(txt_list);

	createLists("suspect.txt", txt_list);
	random_murderer = rand() % txt_list.size();
	murderer_name = txt_list[random_murderer];
	swap(txt_list[random_murderer], txt_list.back());
	txt_list.pop_back();
	maps -> spawnSuspect(txt_list);

	createLists("murder_item.txt", txt_list);
	maps -> spawnMurderer(txt_list, murderer_name);

	createLists("misc_item.txt", txt_list);
	maps -> spawnItem(txt_list);

	maps -> addSuspect(new Detective("ming"));
	
	suspect = maps -> nextSuspectTurn();

	//for all actor location
	while (isGameStillRunning) {
		system("cls");
		suspect -> displayCurrentLocation();
		maps -> displayNumbSuspect();
		suspect -> displayDescription();
		suspect -> move(token, maps);
		command = resolveOption(token[0]);
		if (token.size() == 1) {
			runOneWordCmd(maps, suspect, command, isGameStillRunning);
		}
		else if(token.size() == 2)
		{
			runTwoWordCmd(maps, suspect, &command, token[1], isGameStillRunning);
		}
		else
		{
			command = Command::INVALID;
			displayInformation("Command is not valid!", true);
		}
		if (suspect -> getStatusType() == StatusType::DETECTIVE) {
			system("pause");
		}
		if (token.size() == 2 && command != Command::INVALID) {
			suspect = maps -> nextSuspectTurn();
		}
		token.clear();
	}
	murderer_name.clear();
	delete maps;
}

void runOneWordCmd(Map* map, Suspect* actorlocation, Command cmd, bool& isGameRunning)
{
	switch (cmd)
	{
		case Command::GATHER:
			map -> gatherSuspects(actorlocation);
			displayInformation("Detective have gather all suspect here.", true);
			break;
		case Command::MAP:
			displayText("map.txt");
			break;
		case Command::HELP:
			displayText("help.txt");
			break;
		case Command::QUIT:
			displayInformation("Thank you for playing this game", true);
			isGameRunning = false;
			break;
		default:
			/*Invalid handling*/
			displayInformation("Command is not valid!", true);
			break;
	}
}

void runTwoWordCmd(Map* map, Suspect* actorlocation, Command* command, string token, bool& isGameRunning)
{
	bool isSafetoContinue = true;
	Command cmd = *command;
	 if ( cmd == Command::GO || cmd == Command::SEARCH)
	 {
		 if (map->getLocation(token) == NULL) {
			 displayInformation("Location cannot be found! Please try again!", true);
			 isSafetoContinue = false;
		 }
	 }
	 else if (cmd == Command::ACCUSE || cmd == Command::QUESTION) 
	 {
		 if (map -> getSuspect(token) == NULL) {
			 displayInformation("Suspect cannot be found! Please try again!", true);
			 isSafetoContinue = false;
		 }
	 }
	 else
	 {
		 if ((map->getItem(actorlocation -> getCurrentLocation(), token) == NULL && actorlocation -> getItem(token) == NULL) || cmd == Command::INVALID) {
			 displayInformation("Either invalid command or location,suspect or item cannot be found! Please try again!", true);
			 isSafetoContinue = false;
		 }
	 }
	 if (isSafetoContinue) {
		 switch (cmd)
		 {
			 case Command::GO:
				 map->moveSuspect(actorlocation, token);
				 displayInformation("Fast travel to " + token, true);
				 break;
			 case Command::GET:
				 map->pickAction(token, actorlocation);
				 displayInformation("Detective managed to get " + token, true);
				 break;
			 case Command::DROP:
				 map->dropAction(token, actorlocation);
				 displayInformation("Detective managed to drop " + token, true);
				 break;
			 case Command::SEARCH:
				 map->search(token);
				 displayInformation("Detective have search location here.", true);
				 break;
			 case Command::EXAMINE:
				 actorlocation->examine(token);
				 displayInformation("Detective have examined " + token, true);
				 break;
			 case Command::QUESTION:
				 map->getSuspect(token)->displayDescription(actorlocation);
				 displayInformation("Detective managed to asked question " + token, true);
				 break;
			 case Command::ACCUSE:
				 displayInformation("This is your feedback: ", true);
				 displayResult(actorlocation, map, token);
				 if (actorlocation->hasMurderWeapon() && actorlocation ->getHasRecvMotive() && map->hasFoundMurderer(token) && map -> hasMurderWeapon() == false) {
					 displayInformation("You won!", true);
				 }
				 else {
					 displayInformation("You lost!", true);
				 }
				 isGameRunning = false;
				 break;
			 case Command::USE:
				 actorlocation->useItem(token, map);
				 break;
		 }
	 }
	 else
	 {
		 *command = Command::INVALID;
		 displayInformation("Command is not valid!", true);
	}
}

void displayResult(Suspect* actorlocation, Map* map, string token) {
	stringstream gameDetails;
	gameDetails << "Did you have murder weapon: " << boolalpha << actorlocation->hasMurderWeapon() << endl;
	gameDetails << "Did you found motive: " << boolalpha << actorlocation->getHasRecvMotive() << endl;
	gameDetails << "Did you found all murder weapon: " << boolalpha << (map->hasMurderWeapon()== false) << endl;
	gameDetails << "Did you found murderer: " << boolalpha << map->hasFoundMurderer(token) << endl;
	displayInformation(gameDetails.str(), true);
}

Command resolveOption(string input) {
	to_lower(input);
	if (input == "go") return Command::GO;
	if (input == "search") return Command::SEARCH;
	if (input == "use") return Command::USE;
	if (input == "get") return Command::GET;
	if (input == "drop") return Command::DROP;
	if (input == "examine") return Command::EXAMINE;
	if (input == "question") return Command::QUESTION;
	if (input == "accuse") return Command::ACCUSE;
	if (input == "gather") return Command::GATHER;
	if (input == "map") return Command::MAP;
	if (input == "help") return Command::HELP;
	if (input == "quit") return Command::QUIT;
	return Command::INVALID;
}