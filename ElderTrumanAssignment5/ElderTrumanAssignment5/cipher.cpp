/* ---------------------------------------------------------------------------
** I attest that this following code represents my own work and is subject to
** the plagiarism policy found in the course syllabus.
**
** Class: 	CSC 242
** Assignment: 	5
** File: 	cipher.cpp
** Description: Encrypts or decrypts files using a cipher
**
** Author: 	Truman Elder
** Date: 	22 November 2025
** -------------------------------------------------------------------------*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cctype>

using std::string;
using std::vector;

//helper function to generate the cipher key based on the keyword
string generateKey(const string& keyword) {
	string cipher = "";
	bool used[26] = { false }; // keeps track of letters used

	// add unique letters from keyword
	for (char c : keyword) {
		if (isalpha(c)) {
			c = toupper(c);
			int index = c - 'A';
			if (!used[index]) {
				cipher += c;
				used[index] = true;
			}
		}
	}

	// add rest of the letters of alphabet in reverse order
	for (char c = 'Z'; c >= 'A'; c--) {
		int index = c - 'A';
		if (!used[index]) {
			cipher += c;
		}
	}
	return cipher;
}

//function to perform encryption or decryption
void processFile(const string& inputFile, const string& outputFile, const string& cipher, bool decrypt) {
	std::ifstream inFile;
	std::ofstream outFile;

	inFile.open(inputFile); // open input file
	if (!inFile.is_open()) {
		std::cerr << "Error opening file: " << inputFile << std::endl;
		return;
	}

	outFile.open(outputFile); // open output file
	if (!outFile.is_open()) {
		std::cerr << "Error opening file: " << outputFile << std::endl;
		inFile.close();
		return;
	}

	char c;
	// read character by character so we can keep the spaces and such
	while (inFile.get(c)) {
		if (isalpha(c)) {
			char upperC = toupper(c);
			bool isLower = islower(c);
			char transformedChar;

			if (!decrypt) {
				// checking to see which place in the cipher we'll be comparing
				int index = upperC - 'A';
				transformedChar = cipher[index];
			}
			else {
				//find character in cipher and map back to A
				int index = -1;
				for (int i = 0; i < 26; i++) {
					if (cipher[i] == upperC) {
						index = i;
						break;
					}
				}
				transformedChar = 'A' + index;
			}

			// restore case if original was lowercase
			if (isLower) {
				transformedChar = tolower(transformedChar);
			}
			outFile << transformedChar;
		}
		else {
			// not a letter
			outFile << c;
		}
	}

	inFile.close();
	outFile.close();
}

int main(int argc, char* argv[]) {
	bool decrypt = false;
	string keyword = "";
	string inputFile = "";
	string outputFile = "";

	// read user arguments from command line
	for (int i = 1; i < argc; i++) {
		string arg = argv[i];
		if (arg == "-d") {
			decrypt = true;
		}
		else if (arg.substr(0, 2) == "-k") {
			keyword = arg.substr(2); // grab string after -k option
		}
		else {
			if (inputFile == "") {
				inputFile = arg;
			}
			else {
				outputFile = arg;
			}
		}
	}

	// check for errors
	if (keyword == "") {
		std::cerr << "Error: No keyword" << std::endl;
		return 1;
	}
	if (inputFile == "" || outputFile == "") {
		std::cerr << "Error: must supply file names" << std::endl;
		return 1;
	}

	// generate the key map
	string keyMap = generateKey(keyword);

	// run the cipher process
	processFile(inputFile, outputFile, keyMap, decrypt);

	return 0;
}