/*
 * author: jackanderson12
 * date: 10/10/2020
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ios>
#include "../includes/fileio.h"
#include "../includes/utilities.h"
#include "../includes/constants.h"

/*if you are debugging the file must be in the project parent directory
 in this case Project2 with the .project and .cProject files*/
bool openFile(std::fstream &myfile, const std::string &myFileName,
		std::ios_base::openmode mode) {
	myfile.open(myFileName, mode);
	return myfile.is_open();
}

/*iff myfile is open then close it*/
void closeFile(std::fstream &myfile) {
	if (myfile.is_open()) {
		myfile.close();
	}
}

/* serializes all content in entries to file outputfilename
 * check out utils for helpful type conversion functions
 * BTW serialize means the process of translating a data structure
 * into a format that can be stored in a file
 * returns  FAIL_FILE_DID_NOT_OPEN if cannot open outputfilename
 * 			FAIL_NO_ARRAY_DATA if there are 0 entries in the vector entries
 * 			SUCCESS if all data is written and outputfilename closes OK
 * */
int writetoFile(std::vector<constants::entry> &entries,
		const std::string &outputfilename) {
	std::ofstream myFile;
	myFile.open(outputfilename);
	if (!myFile.is_open()) {
		return constants::FAIL_FILE_DID_NOT_OPEN;
	}
	for (int i = 0; i < entries.size(); i++) {
		myFile << entries[i].word << " " << entries[i].number_occurences
				<< std::endl;
	}
	if (entries.empty()) {
		return constants::FAIL_NO_ARRAY_DATA;
	}
	return constants::SUCCESS;
}
