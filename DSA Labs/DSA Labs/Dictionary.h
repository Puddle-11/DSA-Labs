/*
File:			Dictionary.h
Author(s):
	Base:		Justin Tackett
				jtackett@fullsail.com
	Student:

Purpose:		A hash-mapped data structure using key/value pairs and separate chaining
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
#define LAB_5	1

// Individual unit test toggles
#define LAB5_PAIR_CTOR				1
#define LAB5_CTOR					1
#define LAB5_DTOR					1
#define LAB5_CLEAR					1
#define LAB5_INSERT_NEW				1
#define LAB5_INSERT_EXISTING		1
#define LAB5_FIND					1
#define LAB5_FIND_NOT_FOUND			1
#define LAB5_REMOVE					1
#define LAB5_REMOVE_NOT_FOUND		1
#define LAB5_ASSIGNMENT_OP			1
#define LAB5_COPY_CTOR				1

/************/
/* Includes */
/************/
#include <list>

template<typename Key, typename Value>
class Dictionary {

	friend class UnitTests_Lab5;	// Giving access to test code

	struct Pair {
		Key key;			
		Value value;		

		Pair(const Key& _key, const Value& _value) {
			// TODO: Implement this method
			key = _key;
			value = _value;
		}

		// For testing
		bool operator==(const Pair& _comp) const {
			return (_comp.key == key &&
				_comp.value == value);
		}
	};

	// Data members
	// NOTE: All values set to -1 for unit test purposes
	std::list<Pair>* mTable = reinterpret_cast<std::list<Pair>*>(-1);							// A dynamic array of lists (these are the buckets)
	size_t mNumBuckets = -1;																	// Number of elements in mTable
	unsigned int(*mHashFunc)(const Key&) = reinterpret_cast<unsigned int(*)(const Key&)>(-1);	// Pointer to the hash function

public:

	Dictionary(size_t _numBuckets, unsigned int (*_hashFunc)(const Key&)) {
		// TODO: Implement this method
		mTable = new std::list<Pair>[_numBuckets];
		mNumBuckets = _numBuckets;
		mHashFunc = _hashFunc;
		//mTable->push_back(temp);
	
	}

	~Dictionary() {
		// TODO: Implement this method
		delete[] mTable;
	}

	Dictionary(const Dictionary& _copy) {
		// TODO: Implement this method
		this->mNumBuckets = _copy.mNumBuckets;
		this->mHashFunc = _copy.mHashFunc;

		this->mTable = new std::list<Pair>[this->mNumBuckets];

		for (size_t i = 0; i < this->mNumBuckets; i++)
		{
			this->mTable[i] = _copy.mTable[i];
		}

	}

	Dictionary& operator=(const Dictionary& _assign) {
		// TODO: Implement this method
		if (this == &_assign) return *this;


		delete[] this->mTable;

		this->mNumBuckets = _assign.mNumBuckets;
		this->mHashFunc = _assign.mHashFunc;

		this->mTable = new std::list<Pair>[this->mNumBuckets];

		for (size_t i = 0; i < this->mNumBuckets; i++)
		{
			this->mTable[i] = _assign.mTable[i];
		}

		return *this;
	}

	void Clear() {
		// TODO: Implement this method
		for (size_t i = 0; i < mNumBuckets; i++)
		{
			mTable[i].clear();
		}
	}

	void Insert(const Key& _key, const Value& _value) {
		// TODO: Implement this method
		int index = mHashFunc(_key);
		for (auto it = mTable[index].begin(); it != mTable[index].end(); ++it) {
			if (it->key == _key) {
				it->value = _value;
				return;
			}	
		}
		Pair newpair(_key, _value);
		mTable[index].push_back(newpair);
	}

	const Value* Find(const Key& _key) {
		// TODO: Implement this method
		int index = mHashFunc(_key);
		for (auto it = mTable[index].begin(); it != mTable[index].end(); ++it) {
			if (it->key == _key) {
				return &it->value;
			}
		}
		return nullptr;
	}

	bool Remove(const Key& _key) {
		// TODO: Implement this method
		int index = mHashFunc(_key);
		for (auto it = mTable[index].begin(); it != mTable[index].end(); ++it) {
			if (it->key == _key) {
				mTable[index].erase(it);
				return true;
			}
		}
		return false;

	}
	
};