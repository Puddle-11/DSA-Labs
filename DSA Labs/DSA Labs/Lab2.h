/*
File:			Lab2.h
Author(s):
	Base:		Justin Tackett
				jtackett@fullsail.com
	Student:

Purpose:		Usage of the std::vector class
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
#define LAB_2	1

// Individual unit test toggles
#define LAB2_PALINDROME_NUMBER		1
#define LAB2_FILL_FILE				1
#define LAB2_FILL_ARRAY				1
#define LAB2_CLEAR					1
#define LAB2_SORT_ASCENDING			1
#define LAB2_SORT_DESCENDING		1
#define LAB2_BRACKETS				1
#define LAB2_CONTAINS_TRUE			1
#define LAB2_CONTAINS_FALSE			1
#define LAB2_MOVE_PALINDROMES		1

/************/
/* Includes */
/************/
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>


inline int IsPalindromeNumber(unsigned int _num) {
	// TODO: Implement this function	
	std::string reverseNum = std::to_string(_num);
	std::string wholeNum = reverseNum;
	std::reverse(reverseNum.begin(), reverseNum.end());
	return wholeNum == reverseNum ? true : false;
}

class DSA_Lab2
{
	friend class UnitTests_Lab2;	// Giving access to test code

private:

	std::vector<int> mValues;		// contains all of the values
	std::vector<int> mPalindromes;	// contains just the numbers that are palindromes (only used in MovePalindromes method)

public:

	void Fill(const char* _inputFilename) {
		// TODO: Implement this method
		mValues.clear();
		std::ifstream fs(_inputFilename, std::ios::binary);
		int arrSize;
		int currentVal;
		fs.read((char*)&arrSize, sizeof(int));
		for (int i = 0; i < arrSize; i++)
		{
			fs.read((char*)&currentVal, sizeof(int));
			mValues.push_back(currentVal);
		}
		fs.close();
	}

	void Fill(const int* _arr, size_t _size) {
		// TODO: Implement this method
		mValues.clear();
		for (size_t i = 0; i < _size; i++)
		{
			mValues.push_back(_arr[i]);
		}
	}

	void Clear() {
		// TODO: Implement this method
		mValues.clear();
		std::vector<int>().swap(mValues);
	}
	void Sort(bool _ascending) {

		// TODO: Implement this method
		if (_ascending) {
			std::sort(mValues.begin(), mValues.end());
		}
		else {
			std::sort(mValues.begin(), mValues.end(), std::greater<>{});
		}

	}

	int operator[](int _index) {
		// TODO: Implement this method
		return mValues[_index];
	}

	bool Contains(int _val) const {
		// TODO: Implement this method
		for (size_t i = 0; i < mValues.size(); i++)
		{
			if (mValues[i] == _val) return true;
		}
		return false;
	}

	void MovePalindromes() {	
		// TODO: Implement this method
		std::vector<int> tempIndex;
		for (size_t i = 0; i < mValues.size(); i++)
		{
			if (IsPalindromeNumber(mValues[i])) {

				mPalindromes.push_back(mValues[i]);

			}
			else {

				tempIndex.push_back(mValues[i]);
			}
		}
		mValues = tempIndex;

	}
};

