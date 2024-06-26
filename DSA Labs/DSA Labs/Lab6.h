/*
File:			DSA_Lab6.h
Author(s):
	Base:		Justin Tackett
				jtackett@fullsail.com
	Student:

Purpose:		Usage of the std::unordered_map class
Notes:			Property of Full Sail University 2406
*/

// Header protection
#pragma once

/***********/
/* Defines */
/***********/

/*
How to use:

	When working on a lab, turn that lab's #define from 0 to 1

		Example:	#define LAB_1	1

	When working on an individual unit test, turn that #define from 0 to 1

		Example:	#define DYNARRAY_DEFAULT_CTOR	1

NOTE: If the unit test is not on, that code will not be compiled!
*/


// Main toggle
#define LAB_6	1

// Individual unit test toggles
#define LAB6_POPULATE_LETTER_VALUES	1
#define LAB6_GET_LETTER_VALUE		1
#define LAB6_GET_WORD_VALUE			1
#define LAB6_CREATE_PAIR			1
#define LAB6_LOAD_FILE				1
#define LAB6_FIND_WORD_SCORE		1

/************/
/* Includes */
/************/
#include <string>
#include <fstream>
#include <unordered_map>

class DSA_Lab6 {

	friend class UnitTests_Lab6;	// Giving access to test code

	// Data members
	int mLetterValues[26] = { -1 };
	std::unordered_map<std::string, int> mScrabbleMap;

public:

	void PopulateLetterValues(const int* _letterValues) {
		// TODO: Implement this method
		for (size_t i = 0; i < 26; i++)
		{
			mLetterValues[i] = _letterValues[i];
		}
	}

	int GetLetterValue(char _letter) const {
		// TODO: Implement this method
		_letter = _letter - 'A';
		return mLetterValues[_letter];
	}

	int GetWordValue(const std::string& _word) const {
		// TODO: Implement this method
		int total = 0;
		for (size_t i = 0; i < _word.size(); i++)
		{
		total+=	GetLetterValue(std::toupper(_word[i]));
		}
		return total;
	}

	std::pair<std::string, int> CreatePair(const std::string& _word) const {
		// TODO: Implement this method
		return std::pair(_word, GetWordValue(_word));
	}

	void LoadWords(const char* _filename) {
		// TODO: Implement this method
		std::ifstream fs(_filename);

		if (fs.is_open()) {
			while (!fs.eof())
			{
				std::string word;
				std::getline(fs, word);
				std::pair<std::string, int> pair = CreatePair(word);
				mScrabbleMap.insert(pair);

			}


			fs.close();
		}

	}

	int FindValueInMap(const std::string& _word) {
		// TODO: Implement this method
		//ternary statement, checks to see if _word is invalid, if not return word value, otherwise return -1
			return mScrabbleMap.find(_word) != mScrabbleMap.end() ? mScrabbleMap.at(_word) : - 1;
	}
};
