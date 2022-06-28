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
#pragma once
#ifndef UTILITY_H
#define UTILITY_H

// #include, using
#include <stdio.h>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include <ctime>
#include <vector>

using namespace std;

// declare functions
void to_lower(string& input);
string& trim(string& str);
string askForString(string question);
int askForNumber(string question, int minimumRange, int maximumRange);
bool isValidFile(ifstream& file);
void saveData(string cryptogramFilename, string stringToWrite);
void loadData(string filename, stringstream& details);
void createLists(string filename, vector<string>& selectedVector);
void processInput(vector<string>& token);
void to_lower(string& input);
void getToken(string line, vector <string>& tokens);
void displayInformation(string information, bool isEndOfLine);
void displayText(string filename);
#endif