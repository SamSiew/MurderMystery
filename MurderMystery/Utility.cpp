#include "Utility.h"

void to_lower(string& input) {
	transform(input.begin(), input.end(), input.begin(), tolower);
}

string& trim(string& str)
{
	const string& chars = "\t\n\v\f\r ";
	str.erase(str.find_last_not_of(chars) + 1);
	str.erase(0, str.find_first_not_of(chars));
	return str;
}

void processInput(vector<string>& token) {
	string userInput = askForString("Command:");
	trim(userInput);
	to_lower(userInput);
	getToken(userInput, token);
}

void createLists(string filename, vector<string>& selectedVector) {
	/***************************************************************************
	 * Loads data from a file and returns this data as a vector.
	 *
	 * @param   filename          Name of the text file to be displayed.
	 * @param   selectedVector    String vector containing data from each line of
	 *                            file. Empty if file does not exist or is empty.
	 **************************************************************************/
	 // declare local variables
	string currData;
	ifstream file;

	// Open file.
	file.open(filename);

	// Validate if file found and not empty.
	if (isValidFile(file)) {
		// clear vector to store brand new data.
		selectedVector.clear();
		// Read file into vector.
		while (getline(file, currData, ';')) {
			to_lower(currData);
			selectedVector.push_back(currData);
		}
		// Display succession of data loading from file.
		displayInformation("Data loading from " + filename, true);
	}
	else {
		// print error file is not found
		displayInformation(filename + " not Found or is empty. Unable to update information in this system", true);
	}
}

void saveData(string filename, string stringToWrite) {
	/***************************************************************************
	 * Write a single line of text into a file.
	 *
	 * @param   cryptogramFilename       Name of the cryptogram file to be edited.
	 * @param   cryptogramString         Cryptogram String to be written on to file.
	 **************************************************************************/
	 // declare and initialise local variables
	string iscryptosaved;
	ofstream fileToWrite(filename, ios::app);
	
	// validate if fileToWrite can be written
	if (fileToWrite.is_open()) {
		// save the content into file 
		fileToWrite << stringToWrite << ';';
		displayInformation("This Note is now saved.", true);
	}
	else {
		// print error unable to write to file
		displayInformation("Unable to write to " + filename + ".", true);
	}
	// close the file
	fileToWrite.close();
}

void loadData(string filename, stringstream& details) {
	/***************************************************************************
	 * Read and displays cryptograms data stored in a savedCryptograms.txt.
	 *
	 * @param   cryptogramFilename       Name of the cryptogram file to be edited.
	 **************************************************************************/
	 // declare and initialise local variables
	string line = "";
	ifstream fileToRead(filename);

	// validate if fileToRead can be read before proceeds.
	if (isValidFile(fileToRead)) {
		// clear up cryptogram to update
		details << "All Saved Note:" << endl;
		// reading from a file and print it into console
		while (getline(fileToRead, line, ';')) {
			// add one cryptogram at a time to update
			details << line << endl;
		}

	}
	else {
		// print error file is not found
		details << filename + " not Found or is empty." << endl;
	}
	// close the file
	fileToRead.close();

}


bool isValidFile(ifstream& file) {
	/***************************************************************************
	 * validate if file exist and not empty.
	 *
	 * @param   file:             Text file which will need to validate if it exist and not empty.
	 * @return  boolean value     True: File can be read; False: File can't be read
	 **************************************************************************/
	 // is_open() check if file exist and peek() will check if file is not end of file which indicate empty file if it is end of file.
	return file.is_open() && file.peek() != EOF;
}

void getToken(string line, vector <string>& tokens) {
	string intermediate;
	stringstream stream_line(line);
	tokens.clear();
	while (getline(stream_line, intermediate, ' '))
	{
		tokens.push_back(intermediate);
	}
}

string askForString(string question) {
	/******************************************************************************
	 * Asks user for valid string input.
	 *
	 * @param   question      Prompt to be displayed to the user.
	 * @return  userInput     Appropriate string entered by user.
	 ******************************************************************************/
	 // Initialise empty string to prompt user with question later.
	string userInput = "";

	// Keep asking for string input until it is not empty.
	while (userInput.empty()) {
		displayInformation(question, false);
		getline(cin, userInput);
		// let user knows thier response should not be empty.
		if (userInput.empty()) {
			displayInformation("Your response should not be empty, Try again!", true);
		}
	}
	return userInput;
}

int askForNumber(string question, int minimumRange, int maximumRange) {
	/***************************************************************************
	* Asks user for valid integer input.
	*
	* @param   question        Prompt to be displayed to the user.
	* @param   minimumRange    Lowest integer user can input.
	* @param   maximumRange    Highest integer user can input.
	* @return  num             Appropriate integer entered by user.
	**************************************************************************/
	// Initialise num to -1 because postive value is expected.
	int num = -1;
	// Keep asking for input until it is within range specified.
	while (num < minimumRange || num > maximumRange) {
		num = stoi(askForString(question + " (" + to_string(minimumRange) + "-" + to_string(maximumRange) + "): "));
	}
	return num;
}

void displayText(string filename) {
	/***************************************************************************
	 * Prints out every new line of a file into the console.
	 *
	 * @param filename: Name of the text file to be displayed.
	 **************************************************************************/
	 // declare local variables
	string textline;
	ifstream file;

	// clear all console.
	file.open(filename);

	// Validate if file found and not empty.
	if (isValidFile(file)) {
		// Clear system for new information.
		system("cls");
		// Display all line in file.
		while (getline(file, textline)) {
			displayInformation(textline, true);
		}
		displayInformation("", true);
	}
	else {
		// print error file is not found
		displayInformation(filename + " not Found or is empty.", true);
	}
	file.close();
}


void displayInformation(string information, bool isEndOfLine) {
	/***************************************************************************
	 * Prints out contents of a file into the console exactly the way it was
	 * formatted.
	 *
	 * @param information:     String value which will need to be displayed to user.
	 * @param isEndOfLine:     Boolean value which indicate whether it is end of a line
	 **************************************************************************/
	 // print string into console
	cout << information;
	// when isEndOfLine = True, console will have new line for next consecutive string.
	if (isEndOfLine) {
		cout << endl;
	}
}