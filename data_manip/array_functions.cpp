/*
 * author: jackanderson12
 * date: 10/10/2020
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <locale>
#include <algorithm>
#include "../includes/array_functions.h"
#include "../includes/utilities.h"

//zero out vector that tracks words and their occurrences
void KP::clear(std::vector<constants::entry> &entries) {
	entries.clear();
}

//how many unique words are in the vector
int KP::getSize(std::vector<constants::entry> &entries) {
	return entries.size();
}

//get data at a particular location, if i>size() then get the last value in the vector
//(this is lazy, should throw an exception instead)
std::string KP::getWordAt(std::vector<constants::entry> &entries, int i) {
	return entries[i].word;
}
int KP::getNumbOccurAt(std::vector<constants::entry> &entries, int i) {
	return entries[i].number_occurences;
}

/*loop through whole file, one line at a time
 * call processLine on each line from the file
 * returns false: myfstream is not open
 *         true: otherwise*/
bool KP::processFile(std::vector<constants::entry> &entries,
		std::fstream &myfstream) {
	if (!myfstream.is_open()) {
		return false;
	}
	std::string myString;
	while (getline(myfstream, myString)) {
		processLine(entries, myString);
	}
	return true;
}

/*take 1 line and extract all the tokens from it
 feed each token to processToken for recording*/
void KP::processLine(std::vector<constants::entry> &entries,
		std::string &myString) {
	//given on project description
	std::string holder;
	std::stringstream myStringStream(myString);
	while (getline(myStringStream, holder, constants::CHAR_TO_SEARCH_FOR)) {
		processToken(entries, holder);
	}
}

/*NOTE: first call strip_unwanted_chars from utilities to get rid of rubbish chars in the token
 * if the token is an empty string after this then return since we are not tracking empty strings
 *
 * Keep track of how many times each token seen, in other words look thru the entries vector to
 * see if there is a entry struct that has entry.word==token,
 * if so increment entry.number_occurences, otherwise create a new entry struct for the token,
 * set entry.number_occurences=1 and add it to the entries vector*/
void KP::processToken(std::vector<constants::entry> &entries,
		std::string &token) {
	if (strip_unwanted_chars(token) == false) {
		return;
	}
	std::string uToken = token;
	toUpper(uToken);
	int a = -1;
	for (int i = 0; i < entries.size(); i++) {
		std::string holder = entries[i].word_uppercase;
		if (holder == uToken) {
			a = i;
			break;
		}
	}
	if (a != -1) {
		entries[a].number_occurences++;
	} else {
		constants::entry myEntry { token, uToken, 1 };
		entries.push_back(myEntry);
	}
}
bool orderA(constants::entry &holder, constants::entry &holder2) {
	return holder.word_uppercase < holder2.word_uppercase;
}
bool orderD(constants::entry &holder, constants::entry &holder2) {
	return holder.word_uppercase > holder2.word_uppercase;
}
bool orderN(constants::entry &holder, constants::entry &holder2) {
	return holder.number_occurences > holder2.number_occurences;
}

/*
 * Sort entries based on so enum value.
 * Please provide a solution that sorts according to the enum
 * The presence of the enum implies a switch statement based on its value
 * See the course lectures and demo project for how to sort a vector of structs
 */
void KP::sort(std::vector<constants::entry> &entries, constants::sortOrder so) {
	switch (so) {
	case constants::NONE:
		break;
	case constants::ASCENDING:
		std::sort(entries.begin(), entries.end(), orderA);
		break;
	case constants::DESCENDING:
		std::sort(entries.begin(), entries.end(), orderD);
		break;
	case constants::NUMBER_OCCURRENCES:
		std::sort(entries.begin(), entries.end(), orderN);
		break;
	default:
		break;
	}
}
