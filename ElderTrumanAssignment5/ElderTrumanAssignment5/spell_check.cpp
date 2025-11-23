/* ---------------------------------------------------------------------------
** I attest that this following code represents my own work and is subject to
** the plagiarism policy found in the course syllabus.
**
** Class: 	CSC 242
** Assignment: 	5
** File: 	spell_check.cpp
** Description: Checks the spelling of words in a text file
**
** Author: 	Truman Elder
** Date: 	22 November 2025
** -------------------------------------------------------------------------*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using std::string;
using std::vector;

//helper function to load words to be spell checked from a file
vector<string> loadWords(const string& filename) {
	vector<string> words;
	std::ifstream inFile;
	inFile.open(filename);// open file for reading

	// check if file opened successfully
	if (!inFile.is_open()) {
		std::cerr << "Error opening file: " << filename << std::endl;
		return words;
	}

	string word;
	while (inFile >> word) {
		words.push_back(word);
	}
	inFile.close(); // close the file
	return words;
}

//helper function to load dictionary words from a file
vector<string> loadDictionary(const string& filename) {
	vector<string> dictionary;
	std::ifstream inFile;
	inFile.open(filename);// open file for reading

	// check if file opened successfully
	if (!inFile.is_open()) {
		std::cerr << "Error opening file: " << filename << std::endl;
		return dictionary;
	}
	string word;
	while (inFile >> word) {
		dictionary.push_back(word);
	}
	inFile.close(); // close the file
	return dictionary;
}

//function to perform spell checking
vector<string> spellCheck(const vector<string>& words, const vector<string>& dictionary) {
	vector<string> misspelledWords;

	// check each word against the dictionary
	for (const auto& word : words) {
		bool found = false;
		for (const auto& dictWord : dictionary) {
			if (word == dictWord) {
				found = true;
				break;
			}
		}
		if (!found) {
			misspelledWords.push_back(word);
		}
	}
	return misspelledWords;
}

int main() {
	//load words to be checked
	vector<string> wordsToCheck = loadWords("words.txt");
	//load dictionary
	vector<string> dictionary = loadDictionary("dict.txt");
	//run spell check
	vector<string> misspelledWords = spellCheck(wordsToCheck, dictionary);
	//check to see if any misspelled words were found
	if (misspelledWords.empty()) {
		std::cout << "No misspelled words found." << std::endl;
	} else {
		//print misspelled words
		std::cout << "Misspelled words:" << std::endl;
		for (const auto& word : misspelledWords) {
			std::cout << word << std::endl;
		}
	}
	return 0;
}