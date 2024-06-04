/*
File:			DynArray.h
Author(s):
	Base:		Justin Tackett
				jtackett@fullsail.com
	Student:

Purpose:		A dynamically-allocated resizeable array (similar to std::vector)
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
#define LAB_1	1

// Individual unit test toggles
#define LAB1_DEFAULT_CONSTRUCTOR_NO_ARGS			1
#define LAB1_DEFAULT_CONSTRUCTOR_WITH_ARGS			1
#define LAB1_BRACKET_OPERATOR						1
#define LAB1_SIZE_ACCESSOR							1
#define LAB1_CAPACITY_ACCESSOR						1
#define LAB1_RESERVE_EMPTY							1
#define LAB1_RESERVE_DOUBLE_CAPACITY				1
#define LAB1_RESERVE_LARGER_CAPACITY				1
#define LAB1_RESERVE_SMALLER_CAPACITY				1
#define LAB1_APPEND_NO_RESIZE						1
#define LAB1_APPEND_RESIZE							1
#define LAB1_CLEAR									1
#define LAB1_DESTRUCTOR								1
#define LAB1_ASSIGNMENT_OPERATOR					1
#define LAB1_COPY_CONSTRUCTOR						1

// Our implementation of a vector (simplified)
template<typename Type>
class DynArray {

	// Gives access to test code
	friend class UnitTests_Lab1;

	// Data members
	// NOTE: All values set to -1 for unit test purposes
	Type* mArray = reinterpret_cast<Type*>(-1);

	size_t mSize = -1;

	size_t mCapacity = -1;

public:




	//Constructor w/ args
	DynArray(size_t _startingCap = 0) {
		if (_startingCap == 0)
			mArray = nullptr;
		else
			mArray = new Type[_startingCap];

		mSize = 0;
		mCapacity = _startingCap;

	};

	~DynArray() {
		// TODO: Implement this method
		if (mArray != nullptr) {
			delete[] mArray;
		}
		mArray = nullptr;
	}

	//Copy constructor
	DynArray(const DynArray& _copy) {
		if (this != &_copy) {
			this->mSize = _copy.mSize;
			this->mCapacity = _copy.mCapacity;
		}
		this->mArray = new Type[mCapacity];
		for (size_t i = 0; i < mSize; i++)
		{
			this->mArray[i] = _copy.mArray[i];
		}
	}

	DynArray& operator=(const DynArray& _assign) {
		// TODO: Implement this method
		if (this != &_assign) {

			//shallow copy data from _assign object
			this->mCapacity = _assign.mCapacity;
			this->mSize = _assign.mSize;


			if (this->mArray != nullptr) delete[] this->mArray;

			this->mArray = new Type[this->mCapacity];
			for (size_t i = 0; i < mSize; i++)
			{
				this->mArray[i] = _assign.mArray[i];
			}
		}
			return *this;
	}

	void Clear() {
		// TODO: Implement this method
		if (mArray != nullptr) {
			delete[] mArray;
		}
		mArray = nullptr;
		mSize = 0;
		mCapacity = 0;

	}

	Type& operator[](size_t _index) {
		// TODO: Implement this method
		return mArray[_index];
	}

	size_t Size() const {
		// TODO: Implement this method
		return mSize;
	}

	size_t Capacity() const {
		// TODO: Implement this method
		return mCapacity;
	}

	void Append(const Type& _data) {
	
		if (mSize >= mCapacity)
		{
			Reserve();
		}
			mArray[mSize] = _data;
			mSize++;
		// TODO: Implement this method
	
	}

	void Reserve(size_t _newCapacity = 0) {
		
		// TODO: Implement this method
		if (_newCapacity == 0) {
			mCapacity = mCapacity == 0 ? 1 : mCapacity * 2;
		}
		else if(_newCapacity > mCapacity){
			mCapacity = _newCapacity;
		}
		else {
			return;
		}

		Type* tempArr = new Type[mCapacity];
		for (size_t i = 0; i < mSize; i++)
		{
			tempArr[i] = mArray[i];
		}
		delete[] mArray;
		mArray = tempArr;
		tempArr = nullptr;
	}
};