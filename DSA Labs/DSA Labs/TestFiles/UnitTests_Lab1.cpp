/*
File:			UnitTests_Lab1.cpp
Author(s):
	Base:		Justin Tackett
				jtackett@fullsail.com
Created:		08.15.2021
Last Modified:	10.20.2021
Purpose:		Definitions of Lab1 Unit Tests for DynArray
Notes:			Property of Full Sail University
*/

/************/
/* Includes */
/************/
#include "UnitTests_Lab1.h"
#include "Memory_Management.h"
#include <fstream>
#include <iostream>


#pragma warning(disable:6386)
#pragma warning(disable:6385)

// Maximum points for each test
#define POINTS_LAB1_DEFAULT_CONSTRUCTOR_NO_ARGS		3
#define POINTS_LAB1_DEFAULT_CONSTRUCTOR_WITH_ARGS	7
#define POINTS_LAB1_BRACKET_OPERATOR				5
#define POINTS_LAB1_SIZE_ACCESSOR					1
#define POINTS_LAB1_CAPACITY_ACCESSOR				1
#define POINTS_LAB1_RESERVE_EMPTY					5
#define POINTS_LAB1_RESERVE_DOUBLE_CAPACITY			10
#define POINTS_LAB1_RESERVE_LARGER_CAPACITY			10
#define POINTS_LAB1_RESERVE_SMALLER_CAPACITY		3
#define POINTS_LAB1_APPEND_NO_RESIZE				5
#define POINTS_LAB1_APPEND_RESIZE					10
#define POINTS_LAB1_CLEAR							10
#define POINTS_LAB1_DESTRUCTOR						5
#define POINTS_LAB1_ASSIGNMENT_OPERATOR				15
#define POINTS_LAB1_COPY_CONSTRUCTOR				10

#if LAB_1
void UnitTests_Lab1::FullBattery() {

#ifndef _GRADING
	results::Log("DynArray.log", { "DynArray.h" });
	// results::WriteResults("DynArray.h", "DynArray.results"); 
#endif
	int totalScore = 0;

#if LAB1_DEFAULT_CONSTRUCTOR_NO_ARGS
	totalScore += Battery_DefaultConstructorNoArgs();
#endif
#if LAB1_DEFAULT_CONSTRUCTOR_WITH_ARGS
	totalScore += Battery_DefaultConstructorWithArgs();
#endif
#if LAB1_BRACKET_OPERATOR
	totalScore += Battery_BracketOperator();
#endif
#if LAB1_SIZE_ACCESSOR
	totalScore += Battery_SizeAccessor();
#endif
#if LAB1_CAPACITY_ACCESSOR
	totalScore += Battery_CapacityAccessor();
#endif
#if LAB1_RESERVE_EMPTY
	totalScore += Battery_ReserveEmpty();
#endif
#if LAB1_RESERVE_DOUBLE_CAPACITY
	totalScore += Battery_ReserveDoubleCapacity();
#endif
#if LAB1_RESERVE_LARGER_CAPACITY
	totalScore += Battery_ReserveLargerCapacity();
#endif
#if LAB1_RESERVE_SMALLER_CAPACITY
	totalScore += Battery_ReserveSmallerCapacity();
#endif
#if LAB1_APPEND_NO_RESIZE
	totalScore += Battery_AppendNoResize();
#endif
#if LAB1_APPEND_RESIZE
	totalScore += Battery_AppendResize();
#endif
#if LAB1_CLEAR
	totalScore += Battery_Clear();
#endif
#if LAB1_DESTRUCTOR
	totalScore += Battery_Destructor();
#endif
#if LAB1_ASSIGNMENT_OPERATOR
	totalScore += Battery_AssignmentOperator();
#endif
#if LAB1_COPY_CONSTRUCTOR
	totalScore += Battery_CopyConstructor();
#endif

	PrintTotalScore(totalScore);
}

// Fills in a DynArray object with valid values
//
// In:	_object				The DynArray to populate
//		_array				A pre-allocated array of values
//		_size				Number of elements in _array (and also the size of the DynArray)
//		_capacity			Capacity of DynArray (must be >= _size)
void UnitTests_Lab1::PopulateDynArray(DynArray<int>& _object, int* _array, size_t _size, size_t _capacity) {
	_object.mArray = _array;
	_object.mSize = _size;
	_object.mCapacity = _capacity;
}

// Protection in case that array is still set to -1
void UnitTests_Lab1::ArrayNegativeOneProtection(DynArray<int>& _da) {
	if (_da.mArray == reinterpret_cast<int*>(-1))
		_da.mArray = nullptr;
}

#pragma region Test - Default Constructor (No Arguments)
#if LAB1_DEFAULT_CONSTRUCTOR_NO_ARGS
int UnitTests_Lab1::Battery_DefaultConstructorNoArgs() {
	FailVector failVec;
	failVec.push_back(Fail_DefaultConstructorNoArgs_MemoryIsAllocated);
	failVec.push_back(Fail_DefaultConstructorNoArgs_Array_IsNotNullPointer);
	failVec.push_back(Fail_DefaultConstructorNoArgs_Capacity_IsNotZero);
	failVec.push_back(Fail_DefaultConstructorNoArgs_Size_IsNotZero);

	PassVector passVec;
	passVec.push_back(Pass_DefaultConstructorNoArgs_NoMemoryAllocated);
	passVec.push_back(Pass_DefaultConstructorNoArgs_Array_IsNullPointer);
	passVec.push_back(Pass_DefaultConstructorNoArgs_Capacity_IsZero);
	passVec.push_back(Pass_DefaultConstructorNoArgs_Size_IsZero);

	int totalDeductions = UnitTestBattery("Testing default constructor (with no arguments)", POINTS_LAB1_DEFAULT_CONSTRUCTOR_NO_ARGS, failVec, passVec);
	int scoreForTest = CalculatePointsForTest(POINTS_LAB1_DEFAULT_CONSTRUCTOR_NO_ARGS, totalDeductions);
	
	return scoreForTest;
}

#pragma region Fail Tests
FailResult UnitTests_Lab1::Fail_DefaultConstructorNoArgs_MemoryIsAllocated() {
	size_t memoryDeltaStart = inUse;
	DynArray<int> object;
	size_t memoryDeltaEnd = inUse;
	size_t memoryAllocated = memoryDeltaEnd - memoryDeltaStart;

	FailResult result;
	result.check = memoryAllocated > 0;
	result.deduction = 3;
	result.msg = "No memory should be allocated";

	// Error-protection in case of Clear/destructor
	ArrayNegativeOneProtection(object);

	return result;
}

FailResult UnitTests_Lab1::Fail_DefaultConstructorNoArgs_Array_IsNotNullPointer() {
	DynArray<int> object;

	FailResult result;
	result.check = object.mArray != nullptr;
	result.deduction = 3;
	result.msg = "Array should be nullptr";

	// Error-protection in case of Clear/destructor
	ArrayNegativeOneProtection(object);

	return result;
}

FailResult UnitTests_Lab1::Fail_DefaultConstructorNoArgs_Capacity_IsNotZero() {
	DynArray<int> object;

	FailResult result;
	result.check = object.mCapacity != 0;
	result.deduction = 1;
	result.msg = "Capacity should be zero";

	// Error-protection in case of Clear/destructor
	ArrayNegativeOneProtection(object);

	return result;
}

FailResult UnitTests_Lab1::Fail_DefaultConstructorNoArgs_Size_IsNotZero() {
	DynArray<int> object;

	FailResult result;
	result.check = object.mSize != 0;
	result.deduction = 1;
	result.msg = "Size should be zero";

	// Error-protection in case of Clear/destructor
	ArrayNegativeOneProtection(object);

	return result;
}
#pragma endregion

#pragma region Pass Tests
bool UnitTests_Lab1::Pass_DefaultConstructorNoArgs_NoMemoryAllocated() {
	size_t memoryDeltaStart = inUse;
	DynArray<int> object;

	bool result = memoryDeltaStart == inUse;

	// Error-protection in case of Clear/destructor
	ArrayNegativeOneProtection(object);

	return result;
}

bool UnitTests_Lab1::Pass_DefaultConstructorNoArgs_Array_IsNullPointer() {
	DynArray<int>object;

	bool result = nullptr == object.mArray;

	// Error-protection in case of Clear/destructor
	ArrayNegativeOneProtection(object);

	return result;
}

bool UnitTests_Lab1::Pass_DefaultConstructorNoArgs_Capacity_IsZero() {
	DynArray<int> object;
	bool result = 0 == object.mCapacity;
	
	// Error-protection in case of Clear/destructor
	ArrayNegativeOneProtection(object);

	return result;
}

bool UnitTests_Lab1::Pass_DefaultConstructorNoArgs_Size_IsZero() {
	DynArray<int> object;
	bool result = 0 == object.mSize;

	// Error-protection in case of Clear/destructor
	ArrayNegativeOneProtection(object);

	return result;
}
#pragma endregion
#endif
#pragma endregion

#pragma region Test - Default Constructor (With Arguments)
#if LAB1_DEFAULT_CONSTRUCTOR_WITH_ARGS
int UnitTests_Lab1::Battery_DefaultConstructorWithArgs() {
	FailVector failVec;
	failVec.push_back(Fail_DefaultConstructorWithArgs_Array_IncorrectAmountOfMemoryAllocated);
	failVec.push_back(Fail_DefaultConstructorNoArgs_Array_IsNullPointer);
	failVec.push_back(Fail_DefaultConstructorWithArgs_Array_AllocatedToValidAddress);
	failVec.push_back(Fail_DefaultConstructorWithArgs_Capacity_IncorrectValue);
	failVec.push_back(Fail_DefaultConstructorWithArgs_Size_IsNotZero);

	PassVector passVec;
	passVec.push_back(Pass_DefaultConstructorWithArgs_Array_IsDynamicallyAllocated);
	passVec.push_back(Pass_DefaultConstructorWithArgs_Array_CorrectAmountOfMemoryAllocated);
	passVec.push_back(Pass_DefaultConstructorWithArgs_Capacity_IsCorrectValue);
	passVec.push_back(Pass_DefaultConstructorWithArgs_Size_IsZero);

	int totalDeductions = UnitTestBattery("Testing default constructor (with arguments)", POINTS_LAB1_DEFAULT_CONSTRUCTOR_WITH_ARGS, failVec, passVec);
	int scoreForTest = CalculatePointsForTest(POINTS_LAB1_DEFAULT_CONSTRUCTOR_WITH_ARGS, totalDeductions);

	return scoreForTest;
}

#pragma region Fail Tests
FailResult UnitTests_Lab1::Fail_DefaultConstructorWithArgs_Array_IncorrectAmountOfMemoryAllocated() {
	int randomCapacity = size_t(RandomInt(5, 25));
	size_t memoryDeltaStart = inUse;
	DynArray<int> object(randomCapacity);
	size_t memoryDeltaEnd = inUse;
	size_t memoryAllocated = memoryDeltaEnd - memoryDeltaStart;

	FailResult result;
	result.check = memoryAllocated != sizeof(int)*randomCapacity;
	result.deduction = 6;
	result.msg = "Incorrect amount of memory allocated (or not at all)";

	// Error-protection in case of Clear/destructor
	ArrayNegativeOneProtection(object);

	return result;
}

FailResult UnitTests_Lab1::Fail_DefaultConstructorNoArgs_Array_IsNullPointer() {
	int randomCapacity = size_t(RandomInt(5, 25));
	DynArray<int> object(randomCapacity);
	
	FailResult result;
	result.check = object.mArray == nullptr;
	result.deduction = 6;
	result.msg = "Memory was not allocated, or is leaked";

	// Error-protection in case of Clear/destructor
	ArrayNegativeOneProtection(object);

	return result;
}

FailResult UnitTests_Lab1::Fail_DefaultConstructorWithArgs_Array_AllocatedToValidAddress() {
	int randomCapacity = size_t(RandomInt(5, 25));
	size_t memoryDeltaStart = inUse;
	DynArray<int> object(randomCapacity);

	FailResult result;
	result.check = object.mArray == reinterpret_cast<int*>(-1) || nullptr;
	result.deduction = 6;
	result.msg = "Array was not dynamically allocated correctly";

	// Error-protection in case of Clear/destructor
	ArrayNegativeOneProtection(object);

	return result;
}


FailResult UnitTests_Lab1::Fail_DefaultConstructorWithArgs_Capacity_IncorrectValue() {
	int randomCapacity = size_t(RandomInt(5, 25));
	DynArray<int> object(randomCapacity);

	FailResult result;
	result.check = object.mCapacity != randomCapacity;
	result.deduction = 1;
	result.msg = "Capacity has incorrect value";

	// Error-protection in case of Clear/destructor
	ArrayNegativeOneProtection(object);

	return result;
}

FailResult UnitTests_Lab1::Fail_DefaultConstructorWithArgs_Size_IsNotZero() {
	int randomCapacity = size_t(RandomInt(5, 25));
	DynArray<int> object(randomCapacity);

	FailResult result;
	result.check = object.mSize != 0;
	result.deduction = 1;
	result.msg = "Size has incorrect value";

	// Error-protection in case of Clear/destructor
	ArrayNegativeOneProtection(object);

	return result;
}
#pragma endregion

#pragma region Pass Tests
bool UnitTests_Lab1::Pass_DefaultConstructorWithArgs_Array_IsDynamicallyAllocated() {
	int randomCapacity = size_t(RandomInt(5, 25));
	DynArray<int> object(randomCapacity);

	bool result = object.mArray != nullptr;

	// Error-protection in case of Clear/destructor
	ArrayNegativeOneProtection(object);

	return result;
}

bool UnitTests_Lab1::Pass_DefaultConstructorWithArgs_Array_CorrectAmountOfMemoryAllocated() {
	int randomCapacity = size_t(RandomInt(5, 25));
	size_t memoryDeltaStart = inUse;
	DynArray<int> object(randomCapacity);
	size_t memoryDeltaEnd = inUse;
	size_t memoryAllocated = memoryDeltaEnd - memoryDeltaStart;

	bool result = memoryAllocated == sizeof(int) * randomCapacity;

	// Error-protection in case of Clear/destructor
	ArrayNegativeOneProtection(object);

	return result;
}

bool UnitTests_Lab1::Pass_DefaultConstructorWithArgs_Capacity_IsCorrectValue() {
	int randomCapacity = size_t(RandomInt(5, 25));
	DynArray<int> object(randomCapacity);
	
	bool result = object.mCapacity == randomCapacity;

	// Error-protection in case of Clear/destructor
	ArrayNegativeOneProtection(object);

	return result;
}

bool UnitTests_Lab1::Pass_DefaultConstructorWithArgs_Size_IsZero() {
	int randomCapacity = size_t(RandomInt(5, 25));
	DynArray<int> object(randomCapacity);

	bool result = object.mSize == 0;

	// Error-protection in case of Clear/destructor
	ArrayNegativeOneProtection(object);

	return result;
}
#pragma endregion
#endif
#pragma endregion

#pragma region Test - [] Operator (Read-Only)
#if LAB1_BRACKET_OPERATOR
int UnitTests_Lab1::Battery_BracketOperator() {
	FailVector failVec;
	failVec.push_back(Fail_BracketOperator_UsesLoop);
	failVec.push_back(Fail_BracketOperator_ValueAtIndex_ReturnsIncorrectValue);
	failVec.push_back(Fail_BracketOperator_ValueAtIndex_WritesIncorrectValue);

	PassVector passVec;
	passVec.push_back(Pass_BracketOperator_ValueAtIndex_ReturnsCorrectValue);
	passVec.push_back(Pass_BracketOperator_ValueAtIndex_WritesCorrectValue);

	int totalDeductions = UnitTestBattery("Testing [] operator", POINTS_LAB1_BRACKET_OPERATOR, failVec, passVec);
	int scoreForTest = CalculatePointsForTest(POINTS_LAB1_BRACKET_OPERATOR, totalDeductions);

	return scoreForTest;
}

#pragma region Fail Tests
FailResult UnitTests_Lab1::Fail_BracketOperator_UsesLoop() {
	bool usesLoop = SearchFile("DynArray.h", "operator[](size_t", "size_t Size(", "for(") ||
		SearchFile("DynArray.h", "operator[](size_t", "size_t Size(", "while(");

	FailResult result;
	result.check = usesLoop;
	result.deduction = 5;
	result.msg = "This method should not use a loop";

	return result;
}


FailResult UnitTests_Lab1::Fail_BracketOperator_ValueAtIndex_ReturnsIncorrectValue() {
	// Generating an array of random values
	int randomCapacity = RandomInt(10, 100);
	int* randomVals = CreateRandomArray(randomCapacity);
	int randomIndex = (int)RandomInt(1, randomCapacity - 1);	// Not including [0] to account for *mArray

	// Creating object
	DynArray<int> object;
	PopulateDynArray(object, randomVals, randomCapacity, randomCapacity);

	FailResult result;
	result.check = object[randomIndex] != randomVals[randomIndex];
	result.deduction = 5;
	result.msg = "Returned incorrect value";

	return result;
}

FailResult UnitTests_Lab1::Fail_BracketOperator_ValueAtIndex_WritesIncorrectValue() {
	// Generating an array of random values
	int randomCapacity = RandomInt(10, 100);
	int* randomVals = CreateRandomArray(randomCapacity);
	int randomIndex = (int)RandomInt(1, randomCapacity - 1);	// Not including [0] to account for *mArray
	const int randomVal = (int)RandomInt(101, 200);

	// Creating object
	DynArray<int> object;
	PopulateDynArray(object, randomVals, randomCapacity, randomCapacity);

	object[randomIndex] = randomVal;
	int retFromArray = object[randomIndex];

	FailResult result;
	result.check = retFromArray != randomVal;
	result.deduction = 5;
	result.msg = "Did not set value at correct index";

	return result;
}
#pragma endregion

#pragma region Pass Tests
bool UnitTests_Lab1::Pass_BracketOperator_ValueAtIndex_ReturnsCorrectValue() {
	// Generating an array of random values
	int randomSize = RandomInt(10, 100);
	int* randomVals = CreateRandomArray(randomSize);
	int randomIndex = (int)RandomInt(1, randomSize - 1);	// Not including [0] to account for *mArray

	// Creating object
	DynArray<int> object;
	PopulateDynArray(object, randomVals, randomSize, randomSize);

	bool result = object[randomIndex] == randomVals[randomIndex];

	return result;
}

bool UnitTests_Lab1::Pass_BracketOperator_ValueAtIndex_WritesCorrectValue() {
	// Generating an array of random values
	int randomSize = RandomInt(10, 100);
	int* randomVals = CreateRandomArray(randomSize);
	int randomIndex = (int)RandomInt(1, randomSize - 1);	// Not including [0] to account for *mArray
	const int randomVal = (int)RandomInt(101, 200);

	// Creating object
	DynArray<int> object;
	PopulateDynArray(object, randomVals, randomSize, randomSize);

	object.mArray[randomIndex] = randomVal;
	const int retFromArray = object[randomIndex];

	bool result = retFromArray == randomVal;

	return result;
}
#pragma endregion
#endif
#pragma endregion

#pragma region Test - Size Accessor
#if LAB1_SIZE_ACCESSOR
int UnitTests_Lab1::Battery_SizeAccessor() {
	FailVector failVec;
	failVec.push_back(Fail_SizeAccessor_Size_ReturnsIncorrectValue);

	PassVector passVec;
	passVec.push_back(Pass_SizeAccessor_Size_ReturnsCorrectValue);

	int totalDeductions = UnitTestBattery("Testing Size accessor", POINTS_LAB1_SIZE_ACCESSOR, failVec, passVec);
	int scoreForTest = CalculatePointsForTest(POINTS_LAB1_SIZE_ACCESSOR, totalDeductions);

	return scoreForTest;
}

#pragma region Fail Tests
FailResult UnitTests_Lab1::Fail_SizeAccessor_Size_ReturnsIncorrectValue() {
	int randomSize = RandomInt(1, 100);
	DynArray<int> object;
	PopulateDynArray(object, nullptr, randomSize);

	FailResult result;
	result.check = object.Size() != randomSize;
	result.deduction = 1;
	result.msg = "Returned incorrect value";

	return result;
}
#pragma endregion

#pragma region Pass Tests
bool UnitTests_Lab1::Pass_SizeAccessor_Size_ReturnsCorrectValue() {
	int randomSize = RandomInt(1, 100);
	DynArray<int> object;
	PopulateDynArray(object, nullptr, randomSize);

	bool result = object.Size() == randomSize;

	return result;
}
#pragma endregion
#endif
#pragma endregion

#pragma region Test - Capacity Accessor
#if LAB1_CAPACITY_ACCESSOR
int UnitTests_Lab1::Battery_CapacityAccessor() {
	FailVector failVec;
	failVec.push_back(Fail_CapacityAccessor_Capacity_ReturnsIncorrectValue);

	PassVector passVec;
	passVec.push_back(Pass_CapacityAccessor_Capacity_ReturnsCorrectValue);

	int totalDeductions = UnitTestBattery("Testing Capacity accessor", POINTS_LAB1_CAPACITY_ACCESSOR, failVec, passVec);
	int scoreForTest = CalculatePointsForTest(POINTS_LAB1_CAPACITY_ACCESSOR, totalDeductions);

	return scoreForTest;
}

#pragma region Fail Tests
FailResult UnitTests_Lab1::Fail_CapacityAccessor_Capacity_ReturnsIncorrectValue() {
	int randomCapacity = RandomInt(1, 100);
	DynArray<int> object;
	PopulateDynArray(object, nullptr, 0, randomCapacity);

	FailResult result;
	result.check = object.Capacity() != randomCapacity;
	result.deduction = 1;
	result.msg = "Returned incorrect value";

	return result;
}
#pragma endregion

#pragma region Pass Tests
bool UnitTests_Lab1::Pass_CapacityAccessor_Capacity_ReturnsCorrectValue() {
	int randomCapacity = RandomInt(1, 100);
	DynArray<int> object;
	PopulateDynArray(object, nullptr, 0, randomCapacity);

	bool result = object.Capacity() == randomCapacity;

	return result;
}
#pragma endregion
#endif
#pragma endregion

#pragma region Test - Reserve (Empty)
#if LAB1_RESERVE_EMPTY
int UnitTests_Lab1::Battery_ReserveEmpty() {
	FailVector failVec;
	failVec.push_back(Fail_ReserveEmpty_Array_IncorrectAmountOfMemoryAllocated);
	failVec.push_back(Fail_ReserveEmpty_Capacity_IsNotOne);
	failVec.push_back(Fail_ReserveEmpty_Size_IsNotOne);

	PassVector passVec;
	passVec.push_back(Pass_ReserveArray_Array_IsDynamicallyAllocated);
	passVec.push_back(Pass_ReserveArray_Array_CorrectAmountOfMemoryAllocated);
	passVec.push_back(Pass_ReserveArray_Capacity_IsOne);
	passVec.push_back(Pass_ReserveArray_Size_IsZero);

	int totalDeductions = UnitTestBattery("Testing Reserve from empty DynArray", POINTS_LAB1_RESERVE_EMPTY, failVec, passVec);
	int scoreForTest = CalculatePointsForTest(POINTS_LAB1_RESERVE_EMPTY,totalDeductions);

	return scoreForTest;
}

#pragma region Fail Tests


FailResult UnitTests_Lab1::Fail_ReserveEmpty_Array_IncorrectAmountOfMemoryAllocated() {
	DynArray<int> object;
	PopulateDynArray(object);

	size_t memoryDeltaStart = inUse;
	object.Reserve();
	size_t memoryDeltaEnd = inUse;
	size_t memoryAllocated = memoryDeltaEnd - memoryDeltaStart;
	
	FailResult result;
	result.check = memoryAllocated != sizeof(int) && object.mArray != reinterpret_cast<int*>(-1);
	result.deduction = 5;
	result.msg = "Incorrect amount of memory allocated (or not at all)";
	
	return result;
}

FailResult UnitTests_Lab1::Fail_ReserveEmpty_Capacity_IsNotOne() {
	DynArray<int> object;
	PopulateDynArray(object);

	object.Reserve();

	FailResult result;
	result.check = object.mCapacity != 1;
	result.deduction = 1;
	result.msg = "Capacity was not incremented";

	return result;
}

FailResult UnitTests_Lab1::Fail_ReserveEmpty_Size_IsNotOne() {
	DynArray<int> object;
	PopulateDynArray(object);

	object.Reserve();

	FailResult result;
	result.check = object.mSize != 0;
	result.deduction = 1;
	result.msg = "Size should not be incremented";

	return result;
}

#pragma endregion

#pragma region Pass Tests
bool UnitTests_Lab1::Pass_ReserveArray_Array_IsDynamicallyAllocated() {
	DynArray<int> object;
	PopulateDynArray(object);

	object.Reserve();

	bool result = object.mArray != nullptr && object.mArray != reinterpret_cast<int*>(-1);

	return result;
}

bool UnitTests_Lab1::Pass_ReserveArray_Array_CorrectAmountOfMemoryAllocated() {
	DynArray<int> object;
	PopulateDynArray(object);

	size_t memoryDeltaStart = inUse;
	object.Reserve();
	size_t memoryDeltaEnd = inUse;
	size_t memoryAllocated = memoryDeltaEnd - memoryDeltaStart;

	bool result = memoryAllocated == sizeof(int);

	return result;
}

bool UnitTests_Lab1::Pass_ReserveArray_Capacity_IsOne() {
	DynArray<int> object;
	PopulateDynArray(object);

	object.Reserve();

	bool result = object.mCapacity == 1;

	return result;
}

bool UnitTests_Lab1::Pass_ReserveArray_Size_IsZero() {
	DynArray<int> object;
	PopulateDynArray(object);

	object.Reserve();

	bool result = object.mSize == 0;

	return result;
}
#pragma endregion
#endif
#pragma endregion

#pragma region Test - Reserve (Double Capacity) 
#if LAB1_RESERVE_DOUBLE_CAPACITY
int UnitTests_Lab1::Battery_ReserveDoubleCapacity() {
	FailVector failVec;
	failVec.push_back(Fail_ReserveDoubleCapacity_Array_IsNotDynamicallyAllocated);
	failVec.push_back(Fail_ReserveDoubleCapacity_Array_SameMemoryAddressAsOriginal);
	failVec.push_back(Fail_ReserveDoubleCapacity_Array_IncorrectAmountOfMemoryAllocated);
	failVec.push_back(Fail_ReserveDoubleCapacity_Array_DidntDeleteOldArray);
	failVec.push_back(Fail_ReserveDoubleCapacity_Array_DataNotCopiedToNewArray);
	failVec.push_back(Fail_ReserveDoubleCapacity_Array_Capacity_NotDoubled);
	failVec.push_back(Fail_ReserveDoubleCapacity_Array_Size_WasChanged);

	PassVector passVec;
	passVec.push_back(Pass_ReserveDoubleCapacity_Array_IsDynamicallyAllocated);
	passVec.push_back(Pass_ReserveDoubleCapacity_Array_DifferentMemoryAddressThanOriginal);
	passVec.push_back(Pass_ReserveDoubleCapacity_Array_CorrectAmoutnOfMemoryAllocated);
	passVec.push_back(Pass_ReserveDoubleCapacity_Array_DeletedOldArray);
	passVec.push_back(Pass_ReserveDoubleCapacity_Array_DataCopiedToNewArray);
	passVec.push_back(Pass_ReserveDoubleCapacity_Capacity_ShouldBeDoubled);
	passVec.push_back(Pass_ReserveDoubleCapacity_Size_WasNotChanged);

	int totalDeductions = UnitTestBattery("Testing Reserve with default doubling capacity", POINTS_LAB1_RESERVE_DOUBLE_CAPACITY, failVec, passVec);
	int scoreForTest = CalculatePointsForTest(POINTS_LAB1_RESERVE_DOUBLE_CAPACITY, totalDeductions);

	return scoreForTest;
}

#pragma region Fail Tests
FailResult UnitTests_Lab1::Fail_ReserveDoubleCapacity_Array_IsNotDynamicallyAllocated() {
	DynArray<int> object;
	int randomCapacity = RandomInt(2, 10);
	PopulateDynArray(object, nullptr, 0, randomCapacity);
	
	object.Reserve();

	FailResult result;
	result.check = object.mArray == nullptr || object.mArray == reinterpret_cast<int*>(-1);
	result.deduction = 10;
	result.msg = "Array was not dynamically allocated";

	return result;
}

FailResult UnitTests_Lab1::Fail_ReserveDoubleCapacity_Array_SameMemoryAddressAsOriginal() {
	int randomCapacity = RandomInt(2, 10);
	int* randomVals = CreateRandomArray(randomCapacity);
	DynArray<int> object;
	PopulateDynArray(object, randomVals, randomCapacity, randomCapacity);

	object.Reserve();

	FailResult result;
	result.check = object.mArray == randomVals;
	result.deduction = 10;
	result.msg = "Array was not allocated at different address";

	return result;
}

FailResult UnitTests_Lab1::Fail_ReserveDoubleCapacity_Array_IncorrectAmountOfMemoryAllocated() {
	int randomCapacity = RandomInt(2, 10);
	int* randomVals = CreateRandomArray(randomCapacity);
	DynArray<int> object;
	PopulateDynArray(object, randomVals, randomCapacity, randomCapacity);

	size_t memoryDeltaStart = inUse;
	object.Reserve();
	size_t memoryDeltaEnd = inUse;
	size_t memoryAllocated = memoryDeltaEnd - memoryDeltaStart;

	size_t correctAmountOfMemory = sizeof(int) * randomCapacity; // Doubled

	FailResult result;
	result.check = memoryAllocated != correctAmountOfMemory;
	result.deduction = 6;
	result.msg = "Incorrect amount of memory allocated";

	return result;
}

FailResult UnitTests_Lab1::Fail_ReserveDoubleCapacity_Array_DidntDeleteOldArray() {
	size_t memoryDeltaStart = inUse;
	int randomCapacity = RandomInt(2, 10);
	int* randomVals = CreateRandomArray(randomCapacity);
	DynArray<int> object;
	PopulateDynArray(object, randomVals, randomCapacity, randomCapacity);

	object.Reserve();
	size_t memoryDeltaEnd = inUse;
	size_t memoryAllocated = memoryDeltaEnd - memoryDeltaStart;

	size_t correctAmountOfMemory = sizeof(int) * randomCapacity * 2;

	FailResult result;
	result.check = memoryAllocated > correctAmountOfMemory;
	result.deduction = 4;
	result.msg = "Too much memory allocated (forgot to delete old array?)";

	return result;
}

FailResult UnitTests_Lab1::Fail_ReserveDoubleCapacity_Array_DataNotCopiedToNewArray() {
	int randomCapacity = RandomInt(2, 10);
	int* randomVals = CreateRandomArray(randomCapacity, 1, 100);
	DynArray<int> object;
	object.mArray = new int[randomCapacity];
	memcpy(object.mArray, randomVals, sizeof(int) * randomCapacity);
	object.mCapacity = object.mSize = randomCapacity;

	object.Reserve();

	bool correctData = 0 == memcmp(randomVals, object.mArray, sizeof(int) * randomCapacity);

	FailResult result;
	result.check = correctData == false;
	result.deduction = 10;
	result.msg = "Data in array was not copied over correctly";

	delete[] randomVals;

	return result;
}

FailResult UnitTests_Lab1::Fail_ReserveDoubleCapacity_Array_Capacity_NotDoubled() {
	int randomCapacity = RandomInt(2, 10);
	DynArray<int> object;
	PopulateDynArray(object, nullptr, 0, randomCapacity);

	object.Reserve();

	FailResult result;
	result.check = object.mCapacity != (int64_t)randomCapacity * 2;
	result.deduction = 2;
	result.msg = "Capacity was not doubled";

	return result;
}

FailResult UnitTests_Lab1::Fail_ReserveDoubleCapacity_Array_Size_WasChanged() {
	int randomCapacity = RandomInt(2, 10);
	DynArray<int> object;
	PopulateDynArray(object, CreateRandomArray(randomCapacity), randomCapacity, randomCapacity);

	object.Reserve();

	FailResult result;
	result.check = object.mSize != randomCapacity;
	result.deduction = 2;
	result.msg = "Size should not change";

	return result;
}

#pragma endregion

#pragma region Pass Tests
bool UnitTests_Lab1::Pass_ReserveDoubleCapacity_Array_IsDynamicallyAllocated() {
	DynArray<int> object;
	int randomCapacity = RandomInt(2, 10);
	PopulateDynArray(object, nullptr, 0, randomCapacity);

	object.Reserve();

	bool result = object.mArray != nullptr && object.mArray != reinterpret_cast<int*>(-1);
	
	return result;
}

bool UnitTests_Lab1::Pass_ReserveDoubleCapacity_Array_DifferentMemoryAddressThanOriginal() {
	int randomCapacity = RandomInt(2, 10);
	int* randomVals = CreateRandomArray(randomCapacity);
	DynArray<int> object;
	PopulateDynArray(object, randomVals, randomCapacity, randomCapacity);

	object.Reserve();

	bool result = object.mArray != randomVals;

	return result;
}

bool UnitTests_Lab1::Pass_ReserveDoubleCapacity_Array_CorrectAmoutnOfMemoryAllocated() {
	size_t memoryDeltaStart = inUse;
	int randomCapacity = RandomInt(2, 10);
	int* randomVals = CreateRandomArray(randomCapacity);
	DynArray<int> object;
	PopulateDynArray(object, randomVals, randomCapacity, randomCapacity);


	object.Reserve();
	size_t memoryDeltaEnd = inUse;
	size_t memoryAllocated = memoryDeltaEnd - memoryDeltaStart;

	size_t correctAmountOfMemory = sizeof(int) * randomCapacity * 2;

	bool result = memoryAllocated == correctAmountOfMemory;

	return result;
}

bool UnitTests_Lab1::Pass_ReserveDoubleCapacity_Array_DeletedOldArray() {
	size_t memoryDeltaStart = inUse;
	int randomCapacity = RandomInt(2, 10);
	int* randomVals = CreateRandomArray(randomCapacity);
	DynArray<int> object;
	PopulateDynArray(object, randomVals, randomCapacity, randomCapacity);

	object.Reserve();
	size_t memoryDeltaEnd = inUse;
	size_t memoryAllocated = memoryDeltaEnd - memoryDeltaStart;

	size_t correctAmountOfMemory = sizeof(int) * randomCapacity * 2;

	bool result = memoryAllocated == correctAmountOfMemory;

	return result;
}

bool UnitTests_Lab1::Pass_ReserveDoubleCapacity_Array_DataCopiedToNewArray() {
	int randomCapacity = RandomInt(2, 10);
	int* randomVals = CreateRandomArray(randomCapacity);
	DynArray<int> object;
	object.mArray = new int[randomCapacity];
	memcpy(object.mArray, randomVals, sizeof(int) * randomCapacity);
	object.mCapacity = object.mSize = randomCapacity;

	object.Reserve();

	bool correctData = 0 == memcmp(randomVals, object.mArray, sizeof(int) * randomCapacity);

	bool result = correctData == true;

	delete[] randomVals;

	return result;
}

bool UnitTests_Lab1::Pass_ReserveDoubleCapacity_Capacity_ShouldBeDoubled() {
	int randomCapacity = RandomInt(2, 10);
	DynArray<int> object;
	PopulateDynArray(object, nullptr, 0, randomCapacity);

	object.Reserve();

	bool result = object.mCapacity == (int64_t)randomCapacity * 2;

	return result;
}

bool UnitTests_Lab1::Pass_ReserveDoubleCapacity_Size_WasNotChanged() {
	int randomCapacity = RandomInt(2, 10);
	DynArray<int> object;
	PopulateDynArray(object, CreateRandomArray(randomCapacity), randomCapacity, randomCapacity);

	object.Reserve();

	bool result = object.mSize == randomCapacity;

	return result;
}
#pragma endregion
#endif
#pragma endregion

#pragma region Test - Reserve (Larger Capacity)
#if LAB1_RESERVE_LARGER_CAPACITY
int UnitTests_Lab1::Battery_ReserveLargerCapacity() {
	FailVector failVec;
	failVec.push_back(Fail_ReserveLargerCapacity_Array_IsNotDynamicallyAllocated);
	failVec.push_back(Fail_ReserveLargerCapacity_Array_SameMemoryAddressThanOriginal);
	failVec.push_back(Fail_ReserveLargerCapacity_Array_IncorrectAmountOfMemoryAllocated);
	failVec.push_back(Fail_ReserveLargerCapacity_Array_DidntDeleteOldArray);
	failVec.push_back(Fail_ReserveLargerCapacity_Array_DataNotCopiedToNewArray);
	failVec.push_back(Fail_ReserveLargerCapacity_Capacity_NotChanged);
	failVec.push_back(Fail_ReserveLargerCapacity_Size_WasChanged);

	PassVector passVec;
	passVec.push_back(Pass_ReserveLargerCapacity_Array_IsDynamicallyAllocated);
	passVec.push_back(Pass_ReserveLargerCapacity_Array_DifferentMemoryAddressThanOriginal);
	passVec.push_back(Pass_ReserveLargerCapacity_Array_CorrectAmountOfMemoryAllocated);
	passVec.push_back(Pass_ReserveLargerCapacity_Array_DeletedOldArray);
	passVec.push_back(Pass_ReserveLargerCapacity_Array_DataCopiedToNewArray);
	passVec.push_back(Pass_ReserveLargerCapacity_Capacity_ShouldBeUpdated);
	passVec.push_back(Pass_ReserveLargerCapacity_Size_WasNotChanged);

	int totalDeductions = UnitTestBattery("Testing Reserve with larger capacity", POINTS_LAB1_RESERVE_LARGER_CAPACITY, failVec, passVec);
	int scoreForTest = CalculatePointsForTest(POINTS_LAB1_RESERVE_LARGER_CAPACITY, totalDeductions);

	return scoreForTest;
}
#pragma region Fail Tests
FailResult UnitTests_Lab1::Fail_ReserveLargerCapacity_Array_IsNotDynamicallyAllocated() {
	int randomNewCapacity = (2, 10);
	DynArray<int> object;
	PopulateDynArray(object);

	object.Reserve(randomNewCapacity);

	FailResult result;
	result.check = object.mArray == nullptr;
	result.deduction = 10;
	result.msg = "Array was not dynamically allocated";

	return result;
}

FailResult UnitTests_Lab1::Fail_ReserveLargerCapacity_Array_SameMemoryAddressThanOriginal() {
	int randomStartingCapacity = RandomInt(2, 10);
	int randomLargerCapacity = RandomInt(randomStartingCapacity * 10, randomStartingCapacity * 10);
	int* randomVals = CreateRandomArray(randomStartingCapacity);
	DynArray<int> object;
	PopulateDynArray(object, randomVals, randomStartingCapacity, randomStartingCapacity);

	object.Reserve(randomLargerCapacity);

	FailResult result;
	result.check = object.mArray == randomVals;
	result.deduction = 10;
	result.msg = "Array was not allocated at different address (possibly double-copying data)";

	return result;
}

FailResult UnitTests_Lab1::Fail_ReserveLargerCapacity_Array_IncorrectAmountOfMemoryAllocated() {
	size_t memoryDeltaStart = inUse;
	int randomStartingCapacity = RandomInt(2, 10);
	int randomLargerCapacity = RandomInt(randomStartingCapacity*10, randomStartingCapacity*10);
	int* randomVals = CreateRandomArray(randomStartingCapacity);
	DynArray<int> object;
	PopulateDynArray(object, randomVals, randomStartingCapacity, randomStartingCapacity);

	object.Reserve(randomLargerCapacity);
	size_t memoryDeltaEnd = inUse;
	size_t memoryAllocated = memoryDeltaEnd - memoryDeltaStart;

	size_t correctAmountOfMemory = sizeof(int) * randomLargerCapacity;

	FailResult result;
	result.check = memoryAllocated != correctAmountOfMemory;
	result.deduction = 6;
	result.msg = "Incorrect amount of memory allocated";

	return result;
}

FailResult UnitTests_Lab1::Fail_ReserveLargerCapacity_Array_DidntDeleteOldArray() {
	size_t memoryDeltaStart = inUse;
	int randomStartingCapacity = RandomInt(2, 10);
	int randomLargerCapacity = RandomInt(randomStartingCapacity + 1, 20);
	int* randomVals = CreateRandomArray(randomStartingCapacity);
	DynArray<int> object;
	PopulateDynArray(object, randomVals, randomStartingCapacity, randomStartingCapacity);

	object.Reserve(randomLargerCapacity);

	size_t memoryDeltaEnd = inUse;
	size_t memoryAllocated = memoryDeltaEnd - memoryDeltaStart;

	size_t correctAmountOfMemory = sizeof(int) * randomLargerCapacity;

	FailResult result;
	result.check = memoryAllocated > correctAmountOfMemory;
	result.deduction = 4;
	result.msg = "Too much memory allocated (forgot to delete old array?)";

	return result;
}

FailResult UnitTests_Lab1::Fail_ReserveLargerCapacity_Array_DataNotCopiedToNewArray() {
	int randomStartingCapacity = RandomInt(2, 10);
	int randomLargerCapacity = RandomInt(randomStartingCapacity + 1, 20);
	int* randomVals = CreateRandomArray(randomStartingCapacity);
	DynArray<int> object;
	PopulateDynArray(object, nullptr, randomStartingCapacity, randomStartingCapacity);
	object.mArray = new int[randomStartingCapacity];
	memcpy(object.mArray, randomVals, sizeof(int) * randomStartingCapacity);

	object.Reserve(randomLargerCapacity);

	bool correctData = memcmp(object.mArray, randomVals, sizeof(int) * randomStartingCapacity) == 0;
	
	FailResult result;
	result.check = correctData == false;
	result.deduction = 10;
	result.msg = "Data in array was not copied over correctly";

	delete[] randomVals;

	return result;
}

FailResult UnitTests_Lab1::Fail_ReserveLargerCapacity_Capacity_NotChanged() {
	int randomCapacity = RandomInt(2, 10);
	DynArray<int> object;
	PopulateDynArray(object, nullptr, 0, 0);

	object.Reserve(randomCapacity);

	FailResult result;
	result.check = object.mCapacity != (int64_t)randomCapacity;
	result.deduction = 2;
	result.msg = "Capacity was not increased to specified size";

	return result;
}

FailResult UnitTests_Lab1::Fail_ReserveLargerCapacity_Size_WasChanged() {
	int randomSize = RandomInt(2, 10);
	DynArray<int> object;
	PopulateDynArray(object, CreateRandomArray(randomSize), randomSize, randomSize);

	object.Reserve(randomSize);

	FailResult result;
	result.check = object.mSize != randomSize;
	result.deduction = 2;
	result.msg = "Size should not change";

	return result;
}
#pragma endregion

#pragma region Pass Tests
bool UnitTests_Lab1::Pass_ReserveLargerCapacity_Array_IsDynamicallyAllocated() {
	DynArray<int> object;
	PopulateDynArray(object);

	object.Reserve(RandomInt(2,20));

	bool result = object.mArray != nullptr && object.mArray != reinterpret_cast<int*>(-1);

	return result;
}

bool UnitTests_Lab1::Pass_ReserveLargerCapacity_Array_DifferentMemoryAddressThanOriginal() {
	int randomStartingCapacity = RandomInt(2, 10);
	int randomLargerCapacity = RandomInt(randomStartingCapacity*10, randomStartingCapacity * 10);
	int* randomVals = CreateRandomArray(randomStartingCapacity);
	DynArray<int> object;
	PopulateDynArray(object, randomVals, randomStartingCapacity, randomStartingCapacity);

	object.Reserve(randomLargerCapacity);

	bool result = object.mArray != randomVals;

	return result;
}

bool UnitTests_Lab1::Pass_ReserveLargerCapacity_Array_CorrectAmountOfMemoryAllocated() {
	size_t memoryDeltaStart = inUse;
	int randomStartingCapacity = RandomInt(2, 10);
	int randomLargerCapacity = RandomInt(randomStartingCapacity + 1, 20);
	int* randomVals = CreateRandomArray(randomStartingCapacity);
	DynArray<int> object;
	PopulateDynArray(object, randomVals, randomStartingCapacity, randomStartingCapacity);

	object.Reserve(randomLargerCapacity);
	size_t memoryDeltaEnd = inUse;
	size_t memoryAllocated = memoryDeltaEnd - memoryDeltaStart;

	size_t correctAmountOfMemory = sizeof(int) * randomLargerCapacity;

	bool result = memoryAllocated == correctAmountOfMemory;

	return result;
}

bool UnitTests_Lab1::Pass_ReserveLargerCapacity_Array_DeletedOldArray() {
	size_t memoryDeltaStart = inUse;
	int randomStartingCapacity = RandomInt(2, 10);
	int randomLargerCapacity = RandomInt(randomStartingCapacity + 1, 20);
	int* randomVals = CreateRandomArray(randomStartingCapacity);
	DynArray<int> object;
	PopulateDynArray(object, randomVals, randomStartingCapacity, randomStartingCapacity);

	object.Reserve(randomLargerCapacity);

	size_t memoryDeltaEnd = inUse;
	size_t memoryAllocated = memoryDeltaEnd - memoryDeltaStart;

	size_t correctAmountOfMemory = sizeof(int) * randomLargerCapacity;

	bool result = memoryAllocated == correctAmountOfMemory;

	return result;
}

bool UnitTests_Lab1::Pass_ReserveLargerCapacity_Array_DataCopiedToNewArray() {
	int randomStartingCapacity = RandomInt(2, 10);
	int randomLargerCapacity = RandomInt(randomStartingCapacity + 1, 20);
	int* randomVals = CreateRandomArray(randomStartingCapacity);
	
	DynArray<int> object;
	object.mArray = new int[randomStartingCapacity];
	memcpy(object.mArray, randomVals, sizeof(int) * randomStartingCapacity);
	object.mCapacity = object.mSize = randomStartingCapacity;

	object.Reserve(randomLargerCapacity);

	bool correctData = memcmp(object.mArray, randomVals, sizeof(int)*randomStartingCapacity) == 0;
	
	bool result = correctData == true;

	delete[] randomVals;

	return result;
}

bool UnitTests_Lab1::Pass_ReserveLargerCapacity_Capacity_ShouldBeUpdated() {
	int randomStartingCapacity = RandomInt(2, 10);
	int randomNewCapacity = RandomInt(randomStartingCapacity + 1, 20);
	DynArray<int> da;
	PopulateDynArray(da, nullptr, 0, randomStartingCapacity);

	da.Reserve(randomNewCapacity);

	bool result = da.mCapacity == randomNewCapacity;

	return result;
}

bool UnitTests_Lab1::Pass_ReserveLargerCapacity_Size_WasNotChanged() {
	int randomSize = RandomInt(2, 10);
	int randomCapacity = RandomInt(11, 20);
	DynArray<int> object;
	PopulateDynArray(object, CreateRandomArray(randomSize), randomSize, randomSize);

	object.Reserve(randomCapacity);

	bool result = object.mSize == randomSize;

	return result;
}
#pragma endregion
#endif
#pragma endregion

#pragma region Test - Reserve (Smaller Capacity) 
#if LAB1_RESERVE_SMALLER_CAPACITY
int UnitTests_Lab1::Battery_ReserveSmallerCapacity() {
	FailVector failVec;
	failVec.push_back(Fail_ReserveSmallerCapacity_Array_AddressWasChanged);
	failVec.push_back(Fail_ReserveSmallerCapacity_Capacity_WasChanged);

	PassVector passVec;
	passVec.push_back(Pass_ReserveSmallerCapacity_Array_DidNotChange);
	passVec.push_back(Pass_ReserveSmallerCapacity_Capacity_ShouldNotChange);

	int totalDeductions = UnitTestBattery("Testing Reserve with a smaller capacity", POINTS_LAB1_RESERVE_SMALLER_CAPACITY, failVec, passVec);
	int scoreForTest = CalculatePointsForTest(POINTS_LAB1_RESERVE_SMALLER_CAPACITY, totalDeductions);

	return scoreForTest;
}

#pragma region Fail Tests
FailResult UnitTests_Lab1::Fail_ReserveSmallerCapacity_Array_AddressWasChanged() {
	int randomCapacity = RandomInt(10, 20);
	size_t smallerCapacity = RandomInt(1, randomCapacity - 1);
	int* randomVals = CreateRandomArray(randomCapacity);

	DynArray<int> da;
	PopulateDynArray(da, randomVals, randomCapacity, randomCapacity);

	da.Reserve(smallerCapacity);

	FailResult result;
	result.check = da.mArray != randomVals;
	result.deduction = 3;
	result.msg = "Array should not be changed";

	return result;
}

FailResult UnitTests_Lab1::Fail_ReserveSmallerCapacity_Capacity_WasChanged() {
	int randomCapacity = RandomInt(10, 20);
	size_t smallerCapacity = RandomInt(1, randomCapacity-1);
	int* randomVals = CreateRandomArray(randomCapacity);

	DynArray<int> da;
	PopulateDynArray(da, randomVals, randomCapacity, randomCapacity);

	da.Reserve(smallerCapacity);

	FailResult result;
	result.check = da.mCapacity < randomCapacity;
	result.deduction = 3;
	result.msg = "Capacity should not change";

	return result;
}
#pragma endregion

#pragma region Pass Tests
bool UnitTests_Lab1::Pass_ReserveSmallerCapacity_Array_DidNotChange() {
	int randomCapacity = RandomInt(10, 20);
	size_t smallerCapacity = RandomInt(1, randomCapacity - 1);
	int* randomVals = CreateRandomArray(randomCapacity);

	DynArray<int> da;
	PopulateDynArray(da, randomVals, randomCapacity, randomCapacity);

	da.Reserve(smallerCapacity);

	bool result = da.mArray == randomVals;

	return result;
}

bool UnitTests_Lab1::Pass_ReserveSmallerCapacity_Capacity_ShouldNotChange() {
	int randomCapacity = RandomInt(10,20);
	size_t smallerCapacity = RandomInt(1, randomCapacity-1);
	int* randomVals = CreateRandomArray(randomCapacity);

	DynArray<int> da;
	PopulateDynArray(da, randomVals, randomCapacity, randomCapacity);

	da.Reserve(smallerCapacity);

	bool result = da.mCapacity == randomCapacity;
	
	return result;
}
#pragma endregion
#endif
#pragma endregion

#pragma region Test - Append (No Resize)
#if LAB1_APPEND_NO_RESIZE
int UnitTests_Lab1::Battery_AppendNoResize() {
	FailVector failVec;
	failVec.push_back(Fail_AppendNoResize_Array_DynamicMemoryWasAllocated);
	failVec.push_back(Fail_AppendNoResize_Array_ValueWasNotAddedToNextAvailableElement);
	failVec.push_back(Fail_AppendNoResize_Array_ValueWasAddedToMultipleIndices);
	failVec.push_back(Fail_AppendNoResize_Size_WasNotIncremented);
	failVec.push_back(Fail_AppendNoResize_Capacity_WasChanged);

	PassVector passVec;
	passVec.push_back(AppendNoResize_Array_NoDynamicMemoryWasAllocated);
	passVec.push_back(AppendNoResize_Array_ValueAddedToNextAvailableElement);
	passVec.push_back(AppendNoResize_Size_WasIncremented);
	passVec.push_back(AppendNoResize_Capacity_DidNotChange);

	int totalDeductions = UnitTestBattery("Testing Append with no resize necessary", POINTS_LAB1_APPEND_NO_RESIZE, failVec, passVec);
	int scoreForTest = CalculatePointsForTest(POINTS_LAB1_APPEND_NO_RESIZE, totalDeductions);

	return scoreForTest;
}

#pragma region Fail Tests
FailResult UnitTests_Lab1::Fail_AppendNoResize_Array_DynamicMemoryWasAllocated() {
	int randomCapacity = RandomInt(2, 10);
	int* randomVals = CreateRandomArray(randomCapacity);

	DynArray<int> object;
	object.mArray = randomVals;
	object.mSize = 0;
	object.mCapacity = randomCapacity;

	size_t memoryDeltaStart = inUse;
	object.Append(1);
	size_t memoryDeltaEnd = inUse;
	size_t memoryAllocated = memoryDeltaEnd - memoryDeltaStart;

	FailResult result;
	result.check = memoryAllocated != 0;
	result.deduction = 5;
	result.msg = "No memory should be allocated when array is not full";

	return result;
}

FailResult UnitTests_Lab1::Fail_AppendNoResize_Array_ValueWasNotAddedToNextAvailableElement() {
	int randomSize = RandomInt(2, 10);
	int randomCapacity = RandomInt(randomSize+1, randomSize * 2);
	int* randomVals = CreateRandomArray(randomCapacity);
	int randomVal = (int)RandomInt(101, 500);

	DynArray<int> object;
	object.mArray = randomVals;
	object.mSize = randomSize;
	object.mCapacity = randomCapacity;

	object.Append(randomVal);

	FailResult result;
	result.check = object.mArray[randomSize] != randomVal;
	result.deduction = 5;
	result.msg = "Value was not stored in next available element of array";

	return result;
}

FailResult UnitTests_Lab1::Fail_AppendNoResize_Array_ValueWasAddedToMultipleIndices() {
	int randomSize = RandomInt(2, 10);
	int randomCapacity = RandomInt(randomSize+1, randomSize * 2);
	int* randomVals = CreateRandomArray(randomCapacity);
	int randomVal = (int)RandomInt(101, 500);

	DynArray<int> object;
	object.mArray = randomVals;
	object.mSize = randomSize;
	object.mCapacity = randomCapacity;

	object.Append(randomVal);

	int numFound = 0;
	for (int i = 0; i < randomSize + 1; ++i)
		if (object.mArray && object.mArray[i] == randomVal)
			numFound++;

	FailResult result;
	result.check = numFound != 1;
	result.deduction = 5;
	result.msg = "Value was stored in multiple indices";

	return result;
}

FailResult UnitTests_Lab1::Fail_AppendNoResize_Size_WasNotIncremented() {
	int randomSize = RandomInt(2, 10);
	int* randomVals = CreateRandomArray((int64_t)randomSize * 2);

	DynArray<int> object;
	object.mArray = randomVals;
	object.mSize = randomSize;
	object.mCapacity = (int64_t)randomSize * 2;

	object.Append((int)RandomInt(101, 500));

	FailResult result;
	result.check = object.mSize != (int64_t)randomSize + 1;
	result.deduction = 2;
	result.msg = "Size was not incremented";

	return result;
}

FailResult UnitTests_Lab1::Fail_AppendNoResize_Capacity_WasChanged() {
	int randomSize = RandomInt(2, 10);
	int* randomVals = CreateRandomArray((int64_t)randomSize * 2);

	DynArray<int> object;
	object.mArray = randomVals;
	object.mSize = randomSize;
	object.mCapacity = (int64_t)randomSize * 2;

	object.Append((int)RandomInt(101, 500));

	FailResult result;
	result.check = object.mCapacity != (int64_t)randomSize * 2;
	result.deduction = 2;
	result.msg = "Capacity should not be changed";

	return result;
}
#pragma endregion

#pragma region Pass Tests
bool UnitTests_Lab1::AppendNoResize_Array_NoDynamicMemoryWasAllocated() {
	int randomCapacity = RandomInt(2, 10);
	int* randomVals = CreateRandomArray(randomCapacity);

	DynArray<int> object;
	object.mArray = randomVals;
	object.mSize = 0;
	object.mCapacity = randomCapacity;

	size_t memoryDeltaStart = inUse;
	object.Append(1);
	size_t memoryDeltaEnd = inUse;
	size_t memoryAllocated = memoryDeltaEnd - memoryDeltaStart;

	bool result = memoryAllocated == 0;

	return result;
}

bool UnitTests_Lab1::AppendNoResize_Array_ValueAddedToNextAvailableElement() {
	int randomSize = RandomInt(2, 10);
	int randomCapacity = RandomInt(randomSize+1, randomSize * 2);
	int* randomVals = CreateRandomArray(randomCapacity);
	int randomVal = (int)RandomInt(101, 500);

	DynArray<int> object;
	object.mArray = randomVals;
	object.mSize = randomSize;
	object.mCapacity = randomCapacity;

	object.Append(randomVal);

	bool result = object.mArray[randomSize] == randomVal;

	return result;
}

bool UnitTests_Lab1::AppendNoResize_Size_WasIncremented() {
	int randomSize = RandomInt(2, 10);
	int* randomVals = CreateRandomArray((int64_t)randomSize * 2);

	DynArray<int> object;
	object.mArray = randomVals;
	object.mSize = randomSize;
	object.mCapacity = (int64_t)randomSize * 2;

	object.Append((int)RandomInt(101, 500));

	bool result = object.mSize == (int64_t)randomSize + 1;

	return result;
}

bool UnitTests_Lab1::AppendNoResize_Capacity_DidNotChange() {
	int randomSize = RandomInt(2, 10);
	int* randomVals = CreateRandomArray((int64_t)randomSize * 2);

	DynArray<int> object;
	object.mArray = randomVals;
	object.mSize = randomSize;
	object.mCapacity = (int64_t)randomSize * 2;

	object.Append((int)RandomInt(101, 500));

	bool result = object.mCapacity == (int64_t)randomSize * 2;

	return result;
}
#pragma endregion
#endif
#pragma endregion

#pragma region Test - Append (Resize)
#if LAB1_APPEND_RESIZE
int UnitTests_Lab1::Battery_AppendResize() {
	FailVector failVec;
	failVec.push_back(Fail_AppendResize_Array_ArrayIsNotDoubled);
	failVec.push_back(Fail_AppendResize_Array_DataIsNotCopiedToNewArray);
	failVec.push_back(Fail_AppendResize_Array_ValueNotAddedToNextAvailableElement);
	failVec.push_back(Fail_AppendResize_Array_ValueWasAddedToMultipleIndices);
	failVec.push_back(Fail_AppendResize_Size_WasNotIncremented);
	failVec.push_back(Fail_AppendResize_Capacity_WasNotDoubled);

	PassVector passVec;
	passVec.push_back(Pass_AppendResize_Array_CapacityIsDoubled);
	passVec.push_back(Pass_AppendResize_Array_DataCopiedToNewArray);
	passVec.push_back(Pass_AppendResize_Array_ValueAddedToNextAvailableElement);
	passVec.push_back(Pass_AppendResize_Size_WasBeIncremented);
	passVec.push_back(Pass_AppendResize_Capacity_WasDoubled);

	int totalDeductions = UnitTestBattery("Testing Append with resize", POINTS_LAB1_APPEND_RESIZE, failVec, passVec);
	int scoreForTest = CalculatePointsForTest(POINTS_LAB1_APPEND_RESIZE, totalDeductions);

	return scoreForTest;
}

#pragma region Fail Tests
FailResult UnitTests_Lab1::Fail_AppendResize_Array_ArrayIsNotDoubled() {
	int randomStartingCapacity = RandomInt(2, 10);
	int* randomVals = CreateRandomArray(randomStartingCapacity);

	DynArray<int> object;
	object.mArray = randomVals;
	object.mCapacity = randomStartingCapacity;
	object.mSize = randomStartingCapacity;

	size_t memoryDeltaStart = inUse;
	object.Append((int)RandomInt(101, 500));
	size_t memoryDeltaEnd = inUse;

	size_t memoryAllocated = memoryDeltaEnd - memoryDeltaStart;

	FailResult result;
	result.check = memoryAllocated != sizeof(int) * randomStartingCapacity;
	result.deduction = 10;
	result.msg = "Incorrect amount of memory allocated (should be doubled)";

	return result;
}

FailResult UnitTests_Lab1::Fail_AppendResize_Array_DataIsNotCopiedToNewArray() {
	int randomStartingCapacity = RandomInt(2, 10);
	int* randomVals = CreateRandomArray(randomStartingCapacity);
	int randomVal = (int)RandomInt(101, 500);

	DynArray<int> object;
	object.mArray = new int[randomStartingCapacity];
	memcpy(object.mArray, randomVals, sizeof(int) * randomStartingCapacity);
	object.mCapacity = object.mSize = randomStartingCapacity;

	object.Append(randomVal);

	bool correctDataOldArray = 0 == memcmp(randomVals, object.mArray, sizeof(int) * randomStartingCapacity);

	FailResult result;
	result.check = !correctDataOldArray;
	result.deduction = 10;
	result.msg = "Data in array was not copied over correctly";

	delete[] randomVals;

	return result;
}

FailResult UnitTests_Lab1::Fail_AppendResize_Array_ValueNotAddedToNextAvailableElement() {
	int randomStartingCapacity = RandomInt(2, 10);
	int* randomVals = CreateRandomArray(randomStartingCapacity);
	int randomVal = (int)RandomInt(101, 500);

	DynArray<int> object;
	object.mArray = new int[randomStartingCapacity];
	memcpy(object.mArray, randomVals, sizeof(int) * randomStartingCapacity);
	object.mCapacity = object.mSize = randomStartingCapacity;

	object.Append(randomVal);

	FailResult result;
	result.check = object.mArray[randomStartingCapacity] != randomVal;
	result.deduction = 5;
	result.msg = "Value was not stored in next available element of array";

	delete[] randomVals;

	return result;
}

FailResult UnitTests_Lab1::Fail_AppendResize_Array_ValueWasAddedToMultipleIndices() {
	int randomStartingCapacity = RandomInt(2, 10);
	int* randomVals = CreateRandomArray(randomStartingCapacity);
	int randomVal = (int)RandomInt(101, 500);

	DynArray<int> object;
	object.mArray = new int[randomStartingCapacity];
	memcpy(object.mArray, randomVals, sizeof(int) * randomStartingCapacity);
	object.mCapacity = object.mSize = randomStartingCapacity;

	object.Append(randomVal);

	int numFound = 0;
	for (int i = 0; i < randomStartingCapacity + 1; ++i)
		if (object.mArray && object.mArray[i] == randomVal)
			numFound++;

	FailResult result;
	result.check = numFound != 1;
	result.deduction = 5;
	result.msg = "Value was stored in multiple indices";

	delete[] randomVals;

	return result;
}

FailResult UnitTests_Lab1::Fail_AppendResize_Size_WasNotIncremented() {
	int randomStartingCapacity = RandomInt(2, 10);
	int* randomVals = CreateRandomArray(randomStartingCapacity);

	DynArray<int> object;
	object.mArray = randomVals;
	object.mCapacity = object.mSize = randomStartingCapacity;

	object.Append((int)RandomInt(101, 500));

	FailResult result;
	result.check = object.mSize != (int64_t)randomStartingCapacity + 1;
	result.deduction = 2;
	result.msg = "Size was not incremented";

	return result;
}

FailResult UnitTests_Lab1::Fail_AppendResize_Capacity_WasNotDoubled() {
	int randomStartingCapacity = RandomInt(2, 10);
	int* randomVals = CreateRandomArray(randomStartingCapacity);

	DynArray<int> object;
	object.mArray = randomVals;
	object.mCapacity = object.mSize = randomStartingCapacity;

	object.Append((int)RandomInt(101, 500));

	FailResult result;
	result.check = object.mCapacity != (int64_t)randomStartingCapacity * 2;
	result.deduction = 2;
	result.msg = "Capacity was not doubled";

	return result;
}

#pragma endregion

#pragma region Pass Tests
bool UnitTests_Lab1::Pass_AppendResize_Array_CapacityIsDoubled() {
	int randomStartingCapacity = RandomInt(2, 10);
	int* randomVals = CreateRandomArray(randomStartingCapacity);

	DynArray<int> object;
	object.mArray = randomVals;
	object.mCapacity = randomStartingCapacity;
	object.mSize = randomStartingCapacity;

	size_t memoryDeltaStart = inUse;
	object.Append((int)RandomInt(101, 500));
	size_t memoryDeltaEnd = inUse;
	size_t memoryAllocated = memoryDeltaEnd - memoryDeltaStart;

	bool result = memoryAllocated == sizeof(int) * randomStartingCapacity;

	return result;
}

bool UnitTests_Lab1::Pass_AppendResize_Array_DataCopiedToNewArray() {
	int randomStartingCapacity = RandomInt(2, 10);
	int* randomVals = CreateRandomArray(randomStartingCapacity);
	int randomVal = (int)RandomInt(101, 500);

	DynArray<int> object;
	object.mArray = new int[randomStartingCapacity];
	memcpy(object.mArray, randomVals, sizeof(int) * randomStartingCapacity);
	object.mCapacity = object.mSize = randomStartingCapacity;

	object.Append(randomVal);

	bool correctDataOldArray = 0 == memcmp(randomVals, object.mArray, sizeof(int) * randomStartingCapacity);

	bool result = correctDataOldArray;

	delete[] randomVals;

	return result;
}

bool UnitTests_Lab1::Pass_AppendResize_Array_ValueAddedToNextAvailableElement() {
	int randomStartingCapacity = RandomInt(2, 10);
	int* randomVals = CreateRandomArray(randomStartingCapacity);
	int randomVal = (int)RandomInt(101, 500);

	DynArray<int> object;
	object.mArray = new int[randomStartingCapacity];
	memcpy(object.mArray, randomVals, sizeof(int) * randomStartingCapacity);
	object.mCapacity = object.mSize = randomStartingCapacity;

	object.Append(randomVal);

	bool result = object.mArray[randomStartingCapacity] == randomVal;

	delete[] randomVals;

	return result;
}

bool UnitTests_Lab1::Pass_AppendResize_Size_WasBeIncremented() {
	int randomStartingCapacity = RandomInt(2, 10);
	int* randomVals = CreateRandomArray(randomStartingCapacity);

	DynArray<int> object;
	object.mArray = randomVals;
	object.mCapacity = object.mSize = randomStartingCapacity;

	object.Append((int)RandomInt(101, 500));

	bool result = object.mSize == (int64_t)randomStartingCapacity + 1;

	return result;
}

bool UnitTests_Lab1::Pass_AppendResize_Capacity_WasDoubled() {
	int randomStartingCapacity = RandomInt(2, 10);
	int* randomVals = CreateRandomArray(randomStartingCapacity);

	DynArray<int> object;
	object.mArray = randomVals;
	object.mCapacity = object.mSize = randomStartingCapacity;

	object.Append((int)RandomInt(101, 500));

	bool result = object.mCapacity == (int64_t)randomStartingCapacity * 2;

	return result;
}
#pragma endregion
#endif
#pragma endregion

#pragma region Test - Clear
#if LAB1_CLEAR
int UnitTests_Lab1::Battery_Clear() {
	FailVector failVec;
	failVec.push_back(Fail_Clear_Array_IsNotNullPointer);
	failVec.push_back(Fail_Clear_Array_MemoryIsNotDeleted);
	failVec.push_back(Fail_Clear_Array_NotDeletedWithBrackets);
	failVec.push_back(Fail_Clear_Capacity_IsNotZero);
	failVec.push_back(Fail_Clear_Size_IsNotZero);

	PassVector passVec;
	passVec.push_back(Pass_Clear_Array_IsNullPointer);
	passVec.push_back(Pass_Clear_Array_MemoryIsDeleted);
	passVec.push_back(Pass_Clear_Capacity_IsZero);
	passVec.push_back(Pass_Clear_Size_IsZero);

	int totalDeductions = UnitTestBattery("Testing Clear", POINTS_LAB1_CLEAR, failVec, passVec);
	int scoreForTest = CalculatePointsForTest(POINTS_LAB1_CLEAR, totalDeductions);

	return scoreForTest;
}

#pragma region Fail Tests
FailResult UnitTests_Lab1::Fail_Clear_Array_IsNotNullPointer() {
	DynArray<int> object;
	object.mArray = CreateRandomArray(RandomInt(5, 10));

	object.Clear();

	FailResult result;
	result.check = object.mArray != nullptr;
	result.deduction = 3;
	result.msg = "Array should be nullptr";

	return result;
}

FailResult UnitTests_Lab1::Fail_Clear_Array_MemoryIsNotDeleted() {
	size_t memoryDeltaStart = inUse;

	DynArray<int> object;
	object.mArray = CreateRandomArray(RandomInt(5, 10));

	object.Clear();
	size_t memoryDeltaEnd = inUse;
	size_t memoryAllocated = memoryDeltaEnd - memoryDeltaStart;

	FailResult result;
	result.check = memoryAllocated > 0;
	result.deduction = 10;
	result.msg = "Memory was not correctly delected";

	return result;
}

FailResult UnitTests_Lab1::Fail_Clear_Array_NotDeletedWithBrackets() {
	bool deletedWithBrackets = SearchFile("DynArray.h", "void Clear()", "// Overloaded [] operator", "delete[] mArray");

	FailResult result;
	result.check = deletedWithBrackets == false;
	result.deduction = 3;
	result.msg = "Array was not deleted with brackets";

	return result;
}


FailResult UnitTests_Lab1::Fail_Clear_Capacity_IsNotZero() {
	DynArray<int> object;
	PopulateDynArray(object, nullptr, 0, RandomInt(1, 100));

	object.Clear();

	FailResult result;
	result.check = object.mCapacity != 0;
	result.deduction = 2;
	result.msg = "Capacity should be 0";

	return result;
}

FailResult UnitTests_Lab1::Fail_Clear_Size_IsNotZero() {
	DynArray<int> object;
	PopulateDynArray(object, nullptr, RandomInt(1, 100));

	object.Clear();

	FailResult result;
	result.check = object.mSize != 0;
	result.deduction = 2;
	result.msg = "Size should be 0";

	return result;
}

#pragma endregion

#pragma region Pass Tests
bool UnitTests_Lab1::Pass_Clear_Array_IsNullPointer() {
	DynArray<int> object;
	object.mArray = CreateRandomArray(RandomInt(5, 10));

	object.Clear();

	bool result = object.mArray == nullptr;

	return result;
}

bool UnitTests_Lab1::Pass_Clear_Array_MemoryIsDeleted() {
	size_t memoryDeltaStart = inUse;

	DynArray<int> object;
	object.mArray = CreateRandomArray(RandomInt(5, 10));

	object.Clear();
	size_t memoryDeltaEnd = inUse;
	size_t memoryAllocated = memoryDeltaEnd - memoryDeltaStart;

	bool result = memoryAllocated == 0;

	return result;
}

bool UnitTests_Lab1::Pass_Clear_Capacity_IsZero() {
	DynArray<int> object;
	PopulateDynArray(object, nullptr, 0, RandomInt(1, 100));

	object.Clear();

	bool result = object.mCapacity == 0;

	return result;
}

bool UnitTests_Lab1::Pass_Clear_Size_IsZero() {
	DynArray<int> object;
	PopulateDynArray(object, nullptr, RandomInt(1, 100));

	object.Clear();

	bool result = object.mSize == 0;

	return result;
}
#pragma endregion
#endif
#pragma endregion

#pragma region Test - Destructor
#if LAB1_DESTRUCTOR
int UnitTests_Lab1::Battery_Destructor() {
	FailVector failVec;
	failVec.push_back(Fail_Destructor_DoesNotDeleteOrCallClear);
	failVec.push_back(Fail_Destructor_MemoryIsNotDeleted);

	PassVector passVec;
	passVec.push_back(Pass_Destructor_MemoryIsDeleted);

	int totalDeductions = UnitTestBattery("Testing destructor", POINTS_LAB1_DESTRUCTOR, failVec, passVec);
	int scoreForTest = CalculatePointsForTest(POINTS_LAB1_DESTRUCTOR, totalDeductions);

	return scoreForTest;
}

#pragma region Fail Tests
FailResult UnitTests_Lab1::Fail_Destructor_DoesNotDeleteOrCallClear() {
	// bool deletedWithBrackets = SearchFile("DynArray.h", "void Clear()", "// Overloaded [] operator", "delete[] mArray");
	bool clearsMemory = SearchFile("DynArray.h", "~DynArray()", "DynArray(const DynArray&", "delete[] mArray") ||
		SearchFile("DynArray.h", "~DynArray()", "DynArray(const DynArray&", "Clear()") ||
		SearchFile("DynArray.h", "~DynArray()", "DynArray(const DynArray&", "this->Clear()");

	FailResult result;
	result.check = clearsMemory == false;
	result.deduction = 5;
	result.msg = "Array was not deleted properly";

	return result;
}


FailResult UnitTests_Lab1::Fail_Destructor_MemoryIsNotDeleted() {
	size_t memoryDeltaStart = inUse;

	DynArray<int>* object = new DynArray<int>;
	PopulateDynArray(*object, CreateRandomArray(RandomInt(5, 10)));

	delete object;
	size_t memoryDeltaEnd = inUse;
	size_t memoryAllocated = memoryDeltaEnd - memoryDeltaStart;

	FailResult result;
	result.check = memoryAllocated > 0;
	result.deduction = 5;
	result.msg = "Not all memory was freed";

	return result;
}
#pragma endregion

#pragma region Pass Tests
bool UnitTests_Lab1::Pass_Destructor_MemoryIsDeleted() {
	size_t memoryDeltaStart = inUse;

	DynArray<int>* object = new DynArray<int>;
	PopulateDynArray(*object, CreateRandomArray(RandomInt(5, 10)));

	delete object;
	size_t memoryDeltaEnd = inUse;
	size_t memoryAllocated = memoryDeltaEnd - memoryDeltaStart;

	bool result = memoryAllocated == 0;

	return result;
}
#pragma endregion
#endif
#pragma endregion

#pragma region Test - Assignment Operator
#if LAB1_ASSIGNMENT_OPERATOR
int UnitTests_Lab1::Battery_AssignmentOperator() {
	FailVector failVec;
	failVec.push_back(Fail_AssignmentOperator_Argument_NoSelfAssignmentCheck);
	failVec.push_back(Fail_AssignmentOperator_Array_SameAddressAsArgument);
	failVec.push_back(Fail_AssignmentOperator_Array_IncorrectAmountOfMemoryAllocated);
	failVec.push_back(Fail_AssignmentOperator_Array_DataChangedInOriginalObject);
	failVec.push_back(Fail_AssignmentOperator_Array_DataNotCopiedToNewArray);
	failVec.push_back(Fail_AssignmentOperator_Capacity_IsNotCorrectValue);
	failVec.push_back(Fail_AssignmentOperator_Size_IsNotCorrectValue);

	PassVector passVec;
	passVec.push_back(Pass_AssignmentOperator_Argument_HasSelfAssignmentCheck);
	passVec.push_back(Pass_AssignmentOperator_Array_DifferentMemoryAddressThanArgument);
	passVec.push_back(Pass_AssignmentOperator_Array_CorrectAmountOfMemoryAllocated);
	passVec.push_back(Pass_AssignmentOperator_Array_DataCopiedToNewArray);
	passVec.push_back(Pass_AssignmentOperator_Capacity_IsCorrectValue);
	passVec.push_back(Pass_AssignmentOperator_Size_IsCorrectValue);

	int totalDeductions = UnitTestBattery("Testing assignment operator", POINTS_LAB1_ASSIGNMENT_OPERATOR, failVec, passVec);
	int scoreForTest = CalculatePointsForTest(POINTS_LAB1_ASSIGNMENT_OPERATOR, totalDeductions);

	return scoreForTest;
}

#pragma region Fail Tests
FailResult UnitTests_Lab1::Fail_AssignmentOperator_Argument_NoSelfAssignmentCheck() {
	bool selfAssignmentFound = SearchFile("DynArray.h", "DynArray& operator=(const DynArray& _assign)", "void Clear()", "if(this != &_assign)") ||
							   SearchFile("DynArray.h", "DynArray& operator=(const DynArray& _assign)", "void Clear()", "if(this == &_assign)") ||
							   SearchFile("DynArray.h", "DynArray& operator=(const DynArray& _assign)", "void Clear()", "if(&_assign != this)") ||
							   SearchFile("DynArray.h", "DynArray& operator=(const DynArray& _assign)", "void Clear()", "if(&_assign == this)");

	FailResult result;
	result.check = selfAssignmentFound == false;
	result.deduction = 2;
	result.msg = "Self-assignment check not found";

	return result;
}

FailResult UnitTests_Lab1::Fail_AssignmentOperator_Array_SameAddressAsArgument() {
	int* randomVals = CreateRandomArray(RandomInt(2, 10));

	DynArray<int> assignFrom;
	PopulateDynArray(assignFrom, randomVals);
	DynArray<int> assignTo;
	PopulateDynArray(assignTo);

	assignTo = assignFrom;

	FailResult result;
	result.check = assignTo.mArray == assignFrom.mArray;
	result.deduction = 10;
	result.msg = "Array was shallow copied";

	// Preventing crash
	if (result.check)
		assignTo.mArray = assignFrom.mArray = nullptr;

	return result;
}

FailResult UnitTests_Lab1::Fail_AssignmentOperator_Array_IncorrectAmountOfMemoryAllocated() {
	int randomAssignFromCapacity = RandomInt(6, 10);
	int randomAssignToCapacity = RandomInt(2, 5);
	int randomAssignFromSize = RandomInt(1, randomAssignFromCapacity);
	int randomAssignToSize = RandomInt(1, randomAssignToCapacity);
	int* randomAssignFromValues = CreateRandomArray(randomAssignFromCapacity);
	int* randomAssignToValues = CreateRandomArray(randomAssignToCapacity);

	DynArray<int> assignFrom;
	assignFrom.mArray = randomAssignFromValues;
	assignFrom.mCapacity = randomAssignFromCapacity;
	assignFrom.mSize = randomAssignFromSize;

	DynArray<int> assignTo;
	assignTo.mArray = randomAssignToValues;
	assignTo.mCapacity = randomAssignToCapacity;
	assignTo.mSize = randomAssignToSize;

	size_t memoryDeltaStart = inUse;

	assignTo = assignFrom;
	size_t memoryDeltaEnd = inUse;
	size_t memoryAllocated = memoryDeltaEnd - memoryDeltaStart;

	size_t correctMemoryUsage = sizeof(int) * ((int64_t)randomAssignFromCapacity - randomAssignToCapacity);

	FailResult result;
	result.check = memoryAllocated != correctMemoryUsage;
	result.deduction = 10;
	result.msg = "Incorrect amount of memory allocated";

	return result;
}

FailResult UnitTests_Lab1::Fail_AssignmentOperator_Array_DataChangedInOriginalObject() {
	int randomAssignFromCapacity = RandomInt(6, 10);
	int randomAssignToCapacity = RandomInt(2, 5);
	int randomAssignFromSize = RandomInt(1, randomAssignFromCapacity);
	int randomAssignToSize = RandomInt(1, randomAssignToCapacity);
	int* randomAssignFromValues = CreateRandomArray(randomAssignFromCapacity, 1, 100);
	int* randomAssignToValues = CreateRandomArray(randomAssignToCapacity, 1, 100);

	// Creating a duplicate array to store assignFrom values
	int* assignFromCopyOfArray = new int[randomAssignFromCapacity];
	memcpy(assignFromCopyOfArray, randomAssignFromValues, sizeof(int) * randomAssignFromCapacity);

	DynArray<int> assignFrom;
	assignFrom.mArray = randomAssignFromValues;
	assignFrom.mCapacity = randomAssignFromCapacity;
	assignFrom.mSize = randomAssignFromSize;

	DynArray<int> assignTo;
	assignTo.mArray = randomAssignToValues;
	assignTo.mCapacity = randomAssignToCapacity;
	assignTo.mSize = randomAssignToSize;

	assignTo = assignFrom;

	bool correctData = false;
	if (assignFrom.mArray)
		correctData = 0 == memcmp(assignFrom.mArray, assignFromCopyOfArray, sizeof(int) * randomAssignFromSize);

	FailResult result;
	result.check = correctData == false;
	result.deduction = 10;
	result.msg = "Values in _assign should not be changed";

	// Clean up additional array
	delete[] assignFromCopyOfArray;

	return result;
}

FailResult UnitTests_Lab1::Fail_AssignmentOperator_Array_DataNotCopiedToNewArray() {
	int randomAssignFromCapacity = RandomInt(6, 10);
	int randomAssignToCapacity = RandomInt(2, 5);
	int randomAssignFromSize = RandomInt(1, randomAssignFromCapacity);
	int randomAssignToSize = RandomInt(1, randomAssignToCapacity);
	int* randomAssignFromValues = CreateRandomArray(randomAssignFromCapacity);
	int* randomAssignToValues = CreateRandomArray(randomAssignToCapacity);

	DynArray<int> assignFrom;
	assignFrom.mArray = randomAssignFromValues;
	assignFrom.mCapacity = randomAssignFromCapacity;
	assignFrom.mSize = randomAssignFromSize;

	DynArray<int> assignTo;
	assignTo.mArray = randomAssignToValues;
	assignTo.mCapacity = randomAssignToCapacity;
	assignTo.mSize = randomAssignToSize;

	assignTo = assignFrom;

	bool correctData = false;
	if(assignTo.mArray)
		correctData = 0 == memcmp(assignTo.mArray, randomAssignFromValues, sizeof(int) * randomAssignFromSize);

	FailResult result;
	result.check = correctData == false;
	result.deduction = 10;
	result.msg = "Values in array are not equal";

	return result;
}

FailResult UnitTests_Lab1::Fail_AssignmentOperator_Capacity_IsNotCorrectValue() {
	int randomAssignFromCapacity = RandomInt(6, 10);
	int randomAssignToCapacity = RandomInt(2, 5);
	int randomAssignFromSize = RandomInt(1, randomAssignFromCapacity);
	int randomAssignToSize = RandomInt(1, randomAssignToCapacity);
	int* randomAssignFromValues = CreateRandomArray(randomAssignFromCapacity);
	int* randomAssignToValues = CreateRandomArray(randomAssignToCapacity);

	DynArray<int> assignFrom;
	assignFrom.mArray = randomAssignFromValues;
	assignFrom.mCapacity = randomAssignFromCapacity;
	assignFrom.mSize = randomAssignFromSize;

	DynArray<int> assignTo;
	assignTo.mArray = randomAssignToValues;
	assignTo.mCapacity = randomAssignToCapacity;
	assignTo.mSize = randomAssignToSize;

	assignTo = assignFrom;

	FailResult result;
	result.check = assignTo.mCapacity != assignFrom.mCapacity;
	result.deduction = 2;
	result.msg = "Capacity is not correct value";

	return result;
}

FailResult UnitTests_Lab1::Fail_AssignmentOperator_Size_IsNotCorrectValue() {
	int randomAssignFromCapacity = RandomInt(6, 10);
	int randomAssignToCapacity = RandomInt(2, 5);
	int randomAssignFromSize = RandomInt(1, randomAssignFromCapacity);
	int randomAssignToSize = RandomInt(1, randomAssignToCapacity);
	int* randomAssignFromValues = CreateRandomArray(randomAssignFromCapacity);
	int* randomAssignToValues = CreateRandomArray(randomAssignToCapacity);

	DynArray<int> assignFrom;
	assignFrom.mArray = randomAssignFromValues;
	assignFrom.mCapacity = randomAssignFromCapacity;
	assignFrom.mSize = randomAssignFromSize;

	DynArray<int> assignTo;
	assignTo.mArray = randomAssignToValues;
	assignTo.mCapacity = randomAssignToCapacity;
	assignTo.mSize = randomAssignToSize;

	assignTo = assignFrom;

	FailResult result;
	result.check = assignTo.mSize != assignFrom.mSize;
	result.deduction = 2;
	result.msg = "Size is not correct value";

	return result;
}
#pragma endregion

#pragma region Pass Tests
bool UnitTests_Lab1::Pass_AssignmentOperator_Argument_HasSelfAssignmentCheck() {
	bool selfAssignmentFound = SearchFile("DynArray.h", "DynArray& operator=(const DynArray& _assign)", "void Clear()", "if(this != &_assign)") ||
							   SearchFile("DynArray.h", "DynArray& operator=(const DynArray& _assign)", "void Clear()", "if(this == &_assign)") ||
							   SearchFile("DynArray.h", "DynArray& operator=(const DynArray& _assign)", "void Clear()", "if(&_assign != this)") ||
							   SearchFile("DynArray.h", "DynArray& operator=(const DynArray& _assign)", "void Clear()", "if(&_assign == this)");

	bool result = selfAssignmentFound == true;

	return result;
}

bool UnitTests_Lab1::Pass_AssignmentOperator_Array_DifferentMemoryAddressThanArgument() {
	int* randomVals = CreateRandomArray(RandomInt(2, 10));

	DynArray<int> assignFrom;
	PopulateDynArray(assignFrom, randomVals);
	DynArray<int> assignTo;
	PopulateDynArray(assignTo);

	assignTo = assignFrom;

	bool result = assignTo.mArray != assignFrom.mArray;

	return result;
}

bool UnitTests_Lab1::Pass_AssignmentOperator_Array_CorrectAmountOfMemoryAllocated() {
	int randomAssignFromCapacity = RandomInt(6, 10);
	int randomAssignToCapacity = RandomInt(2, 5);
	int randomAssignFromSize = RandomInt(1, randomAssignFromCapacity);
	int randomAssignToSize = RandomInt(1, randomAssignToCapacity);
	int* randomAssignFromValues = CreateRandomArray(randomAssignFromCapacity, 1, 100);
	int* randomAssignToValues = CreateRandomArray(randomAssignToCapacity, 1, 100);

	DynArray<int> assignFrom;
	assignFrom.mArray = randomAssignFromValues;
	assignFrom.mCapacity = randomAssignFromCapacity;
	assignFrom.mSize = randomAssignFromSize;

	DynArray<int> assignTo;
	assignTo.mArray = randomAssignToValues;
	assignTo.mCapacity = randomAssignToCapacity;
	assignTo.mSize = randomAssignToSize;

	size_t memoryDeltaStart = inUse;
	assignTo = assignFrom;
	size_t memoryDeltaEnd = inUse;
	size_t memoryAllocated = memoryDeltaEnd - memoryDeltaStart;

	size_t correctMemoryUsage = sizeof(int) * ((int64_t)randomAssignFromCapacity - randomAssignToCapacity);

	bool result = memoryAllocated == correctMemoryUsage;

	return result;
}

bool UnitTests_Lab1::Pass_AssignmentOperator_Array_DataCopiedToNewArray() {
	int randomAssignFromCapacity = RandomInt(6, 10);
	int randomAssignToCapacity = RandomInt(2, 5);
	int randomAssignFromSize = RandomInt(1, randomAssignFromCapacity);
	int randomAssignToSize = RandomInt(1, randomAssignToCapacity);
	int* randomAssignFromValues = CreateRandomArray(randomAssignFromCapacity, 1, 100);
	int* randomAssignToValues = CreateRandomArray(randomAssignToCapacity, 1, 100);

	DynArray<int> assignFrom;
	assignFrom.mArray = randomAssignFromValues;
	assignFrom.mCapacity = randomAssignFromCapacity;
	assignFrom.mSize = randomAssignFromSize;

	DynArray<int> assignTo;
	assignTo.mArray = randomAssignToValues;
	assignTo.mCapacity = randomAssignToCapacity;
	assignTo.mSize = randomAssignToSize;

	assignTo = assignFrom;

	bool correctData = 0 == memcmp(assignTo.mArray, randomAssignFromValues, sizeof(int) * randomAssignFromSize);

	bool result = correctData == true;

	return result;
}

bool UnitTests_Lab1::Pass_AssignmentOperator_Capacity_IsCorrectValue() {
	int randomAssignFromCapacity = RandomInt(6, 10);
	int randomAssignToCapacity = RandomInt(2, 5);
	int randomAssignFromSize = RandomInt(1, randomAssignFromCapacity);
	int randomAssignToSize = RandomInt(1, randomAssignToCapacity);
	int* randomAssignFromValues = CreateRandomArray(randomAssignFromCapacity, 1, 100);
	int* randomAssignToValues = CreateRandomArray(randomAssignToCapacity, 1, 100);

	DynArray<int> assignFrom;
	assignFrom.mArray = randomAssignFromValues;
	assignFrom.mCapacity = randomAssignFromCapacity;
	assignFrom.mSize = randomAssignFromSize;

	DynArray<int> assignTo;
	assignTo.mArray = randomAssignToValues;
	assignTo.mCapacity = randomAssignToCapacity;
	assignTo.mSize = randomAssignToSize;

	assignTo = assignFrom;

	bool result = assignTo.mCapacity == assignFrom.mCapacity;

	return result;
}

bool UnitTests_Lab1::Pass_AssignmentOperator_Size_IsCorrectValue() {
	int randomAssignFromCapacity = RandomInt(6, 10);
	int randomAssignToCapacity = RandomInt(2, 5);
	int randomAssignFromSize = RandomInt(1, randomAssignFromCapacity);
	int randomAssignToSize = RandomInt(1, randomAssignToCapacity);
	int* randomAssignFromValues = CreateRandomArray(randomAssignFromCapacity, 1, 100);
	int* randomAssignToValues = CreateRandomArray(randomAssignToCapacity, 1, 100);

	DynArray<int> assignFrom;
	assignFrom.mArray = randomAssignFromValues;
	assignFrom.mCapacity = randomAssignFromCapacity;
	assignFrom.mSize = randomAssignFromSize;

	DynArray<int> assignTo;
	assignTo.mArray = randomAssignToValues;
	assignTo.mCapacity = randomAssignToCapacity;
	assignTo.mSize = randomAssignToSize;

	assignTo = assignFrom;

	bool result = assignTo.mSize == assignFrom.mSize;

	return result;
}
#pragma endregion
#endif
#pragma endregion

#pragma region Test - Copy Constructor
#if LAB1_COPY_CONSTRUCTOR
int UnitTests_Lab1::Battery_CopyConstructor() {
	FailVector failVec;
	failVec.push_back(Fail_CopyConstructor_Array_SameMemoryAddressAsArgument);
	failVec.push_back(Fail_CopyConstructor_Array_IncorrectAmountOfMemoryAllocated);
	failVec.push_back(Fail_CopyConstructor_Array_DataNotCopiedToNewArray);
	failVec.push_back(Fail_CopyConstructor_Capacity_IsIncorrectValue);
	failVec.push_back(Fail_CopyConstructor_Size_IsIncorrectValue);

	PassVector passVec;
	passVec.push_back(Pass_CopyConstructor_Array_DifferentMemoryAddressThanArgument);
	passVec.push_back(Pass_CopyConstructor_Array_CorrectAmountOfMemoryAllocated);
	passVec.push_back(Pass_CopyConstructor_Array_DataCopiedToNewArray);
	passVec.push_back(Pass_CopyConstructor_Capacity_IsCorrectValue);
	passVec.push_back(Pass_CopyConstructor_Size_IsCorrectValue);

	int totalDeductions = UnitTestBattery("Testing copy constructor", POINTS_LAB1_COPY_CONSTRUCTOR, failVec, passVec);
	int scoreForTest = CalculatePointsForTest(POINTS_LAB1_COPY_CONSTRUCTOR, totalDeductions);

	return scoreForTest;
}

#pragma region Fail Tests
FailResult UnitTests_Lab1::Fail_CopyConstructor_Array_SameMemoryAddressAsArgument() {
	int* randomVals = CreateRandomArray(RandomInt(2, 10));

	DynArray<int> copyFrom;
	PopulateDynArray(copyFrom, randomVals);

	DynArray<int> copyTo = copyFrom;

	FailResult result;
	result.check = copyTo.mArray == copyFrom.mArray;
	result.deduction = 10;
	result.msg = "Array was shallow copied";

	// Preventing crash
	if (result.check)
		copyTo.mArray = copyFrom.mArray = nullptr;

	ArrayNegativeOneProtection(copyTo);

	return result;
}

FailResult UnitTests_Lab1::Fail_CopyConstructor_Array_IncorrectAmountOfMemoryAllocated() {
	int randomCopyFromCapacity = RandomInt(6, 10);
	int randomCopyFromSize = RandomInt(1, randomCopyFromCapacity-1);
	int* randomCopyFromValues = CreateRandomArray(randomCopyFromCapacity, 1, 100);

	DynArray<int> copyFrom;
	copyFrom.mArray = randomCopyFromValues;
	copyFrom.mCapacity = randomCopyFromCapacity;
	copyFrom.mSize = randomCopyFromSize;
	

	size_t memoryDeltaStart = inUse;
	DynArray<int> copyTo = copyFrom;
	size_t memoryDeltaEnd = inUse;
	size_t memoryAllocated = memoryDeltaEnd - memoryDeltaStart;

	size_t correctMemoryUsage = sizeof(int) * (randomCopyFromCapacity);

	FailResult result;
	result.check = memoryAllocated != correctMemoryUsage;
	result.deduction = 10;
	result.msg = "Incorrect amount of memory allocated";

	ArrayNegativeOneProtection(copyTo);

	return result;
}

FailResult UnitTests_Lab1::Fail_CopyConstructor_Array_DataNotCopiedToNewArray() {
	int randomCopyFromCapacity = RandomInt(6, 10);
	int randomCopyFromSize = RandomInt(1, randomCopyFromCapacity);
	int* randomValues = CreateRandomArray(randomCopyFromSize, 1, 100);
	int* randomCopyFromValues = new int[randomCopyFromCapacity];
	memcpy(randomCopyFromValues, randomValues, sizeof(int) * randomCopyFromSize);

	DynArray<int> copyFrom;
	PopulateDynArray(copyFrom, randomCopyFromValues, randomCopyFromSize, randomCopyFromCapacity);

	DynArray<int> copyTo = copyFrom;

	bool correctData = false;
	if (copyTo.mArray != nullptr && copyTo.mArray != reinterpret_cast<int*>(-1))
		correctData = 0 == memcmp(copyTo.mArray, randomValues, sizeof(int) * randomCopyFromSize);

	FailResult result;
	result.check = correctData == false;
	result.deduction = 10;
	result.msg = "Values in array are not equal";

	delete[] randomValues;

	ArrayNegativeOneProtection(copyTo);

	return result;
}

FailResult UnitTests_Lab1::Fail_CopyConstructor_Capacity_IsIncorrectValue() {
	int randomCopyFromCapacity = RandomInt(6, 10);
	int randomCopyFromSize = RandomInt(1, randomCopyFromCapacity);
	int* randomCopyFromValues = CreateRandomArray(randomCopyFromCapacity, 1, 100);

	DynArray<int> copyFrom;
	copyFrom.mArray = randomCopyFromValues;
	copyFrom.mCapacity = randomCopyFromCapacity;
	copyFrom.mSize = randomCopyFromSize;

	DynArray<int> copyTo = copyFrom;

	FailResult result;
	result.check = copyTo.mCapacity != copyFrom.mCapacity;
	result.deduction = 2;
	result.msg = "Capacity is not correct value";

	ArrayNegativeOneProtection(copyTo);

	return result;
}

FailResult UnitTests_Lab1::Fail_CopyConstructor_Size_IsIncorrectValue() {
	int randomCopyFromCapacity = RandomInt(6, 10);
	int randomCopyFromSize = RandomInt(1, randomCopyFromCapacity);
	int* randomCopyFromValues = CreateRandomArray(randomCopyFromCapacity, 1, 100);

	DynArray<int> copyFrom;
	copyFrom.mArray = randomCopyFromValues;
	copyFrom.mCapacity = randomCopyFromCapacity;
	copyFrom.mSize = randomCopyFromSize;

	DynArray<int> copyTo = copyFrom;

	FailResult result;
	result.check = copyTo.mSize != copyFrom.mSize;
	result.deduction = 2;
	result.msg = "Size is not correct value";

	ArrayNegativeOneProtection(copyTo);

	return result;
}
#pragma endregion

#pragma region Pass Tests
bool UnitTests_Lab1::Pass_CopyConstructor_Array_DifferentMemoryAddressThanArgument() {
	int* randomVals = CreateRandomArray(RandomInt(2, 10));

	DynArray<int> copyFrom;
	PopulateDynArray(copyFrom, randomVals);

	DynArray<int> copyTo = copyFrom;

	bool result = copyTo.mArray != copyFrom.mArray;

	return result;
}

bool UnitTests_Lab1::Pass_CopyConstructor_Array_CorrectAmountOfMemoryAllocated() {
	int randomCopyFromCapacity = RandomInt(6, 10);
	int randomCopyFromSize = RandomInt(1, randomCopyFromCapacity);
	int* randomCopyFromValues = CreateRandomArray(randomCopyFromCapacity, 1, 100);

	DynArray<int> copyFrom;
	copyFrom.mArray = randomCopyFromValues;
	copyFrom.mCapacity = randomCopyFromCapacity;
	copyFrom.mSize = randomCopyFromSize;


	size_t memoryDeltaStart = inUse;
	DynArray<int> copyTo = copyFrom;
	size_t memoryDeltaEnd = inUse;
	size_t memoryAllocated = memoryDeltaEnd - memoryDeltaStart;

	size_t correctMemoryUsage = sizeof(int) * (randomCopyFromCapacity);

	bool result = memoryAllocated == correctMemoryUsage;

	return result;
}

bool UnitTests_Lab1::Pass_CopyConstructor_Array_DataCopiedToNewArray() {
	int randomCopyFromCapacity = RandomInt(6, 10);
	int randomCopyFromSize = RandomInt(1, randomCopyFromCapacity);
	int* randomCopyFromValues = CreateRandomArray(randomCopyFromCapacity, 1, 100);

	DynArray<int> copyFrom;
	PopulateDynArray(copyFrom, randomCopyFromValues, randomCopyFromSize, randomCopyFromCapacity);

	DynArray<int> copyTo = copyFrom;

	bool correctData = false;
	if (copyTo.mArray != nullptr && copyTo.mArray != reinterpret_cast<int*>(-1))
		correctData = 0 == memcmp(copyTo.mArray, randomCopyFromValues, sizeof(int) * randomCopyFromSize);

	bool result = correctData == true;

	return result;
}

bool UnitTests_Lab1::Pass_CopyConstructor_Capacity_IsCorrectValue() {
	int randomCopyFromCapacity = RandomInt(6, 10);
	int randomCopyFromSize = RandomInt(1, randomCopyFromCapacity);
	int* randomCopyFromValues = CreateRandomArray(randomCopyFromCapacity, 1, 100);

	DynArray<int> copyFrom;
	copyFrom.mArray = randomCopyFromValues;
	copyFrom.mCapacity = randomCopyFromCapacity;
	copyFrom.mSize = randomCopyFromSize;

	DynArray<int> copyTo = copyFrom;

	bool result = copyTo.mCapacity == copyFrom.mCapacity;

	return result;
}

bool UnitTests_Lab1::Pass_CopyConstructor_Size_IsCorrectValue() {
	int randomCopyFromCapacity = RandomInt(6, 10);
	int randomCopyFromSize = RandomInt(1, randomCopyFromCapacity);
	int* randomCopyFromValues = CreateRandomArray(randomCopyFromCapacity, 1, 100);

	DynArray<int> copyFrom;
	copyFrom.mArray = randomCopyFromValues;
	copyFrom.mCapacity = randomCopyFromCapacity;
	copyFrom.mSize = randomCopyFromSize;

	DynArray<int> copyTo = copyFrom;

	bool result = copyTo.mSize == copyFrom.mSize;

	return result;
}
#pragma endregion
#endif
#pragma endregion
#endif