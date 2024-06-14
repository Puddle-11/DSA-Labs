/*
File:			DList.h\
Author(s):
	Base:		Justin Tackett
				jtackett@fullsail.com
	Student:

Purpose:		A doubly-linked list (similar to std::list)
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
#define LAB_3	1

// Individual unit test toggles			
#define LAB3_CTOR						1
#define LAB3_NODE_CTOR_DEFAULT			1
#define LAB3_NODE_CTOR					1
#define LAB3_ADDHEAD_EMPTY				1
#define LAB3_ADDHEAD					1
#define LAB3_ADDTAIL_EMPTY				1
#define LAB3_ADDTAIL					1
#define LAB3_CLEAR						1
#define LAB3_DTOR						0
#define LAB3_ITER_BEGIN					1
#define LAB3_ITER_END					1
#define LAB3_ITER_INCREMENT_PRE			0
#define LAB3_ITER_INCREMENT_POST		0
#define LAB3_ITER_DECREMENT_PRE			0
#define LAB3_ITER_DECREMENT_POST		0
#define LAB3_ITER_DEREFERENCE			0
#define LAB3_INSERT_EMPTY				0
#define LAB3_INSERT_HEAD				0
#define LAB3_INSERT_MIDDLE				0
#define LAB3_ERASE_EMPTY				1
#define LAB3_ERASE_HEAD					1
#define LAB3_ERASE_TAIL					1
#define LAB3_ERASE_MIDDLE				1
#define LAB3_ASSIGNMENT_OP				0
#define LAB3_COPY_CTOR					1

template<typename Type>
class DList {

	friend class UnitTests_Lab3;	// Giving access to test code

	struct Node {
		// NOTE: Values set to -1 for unit test purposes
		Type data;
		Node* next = reinterpret_cast<Node*>(-1);
		Node* prev = reinterpret_cast<Node*>(-1);

	
		Node(const Type& _data, Node* _next = nullptr, Node* _prev = nullptr) {
			// TODO: Implement this method
			data = _data;
			next = _next;
			prev = _prev;
		}
	};

public:

	class Iterator {
	public:

		Node* mCurr = reinterpret_cast<Node*>(-1);

		Iterator& operator++() {
			// TODO: Implement this method
		
		}

		Iterator operator++(int) {
			// TODO: Implement this method
			
		}

		Iterator& operator--() {
			// TODO: Implement this method
			
		}

		Iterator operator--(int) {
			// TODO: Implement this method
			
		}

		Type& operator*() {
			// TODO: Implement this method
			
		}

	
		bool operator != (const Iterator& _iter) const {
			return mCurr != _iter.mCurr;
		}
	};

	// Data members
	// NOTE: All values set to -1 for unit test purposes
	Node* mHead = reinterpret_cast<Node*>(-1);
	Node* mTail = reinterpret_cast<Node*>(-1);
	size_t mSize = -1;

public:

	DList() {
		mHead = nullptr;
		mTail = nullptr;
			mSize = 0;
		// TODO: Implement this method
		
	}

	~DList() {
		// TODO: Implement this method
		
	}

	DList(const DList& _copy)  {

	
		// TODO: Implement this method
		
	}

	DList& operator=(const DList& _assign) {
		// TODO: Implement this method
		
	}

	void AddHead(const Type& _data) {
		Node* temp = mHead;

		mHead = new Node(_data, temp, nullptr);
		
		if (temp != nullptr) temp->prev = mHead;
		if (mTail == nullptr) mTail = mHead;


		mSize++;
	}

	void AddTail(const Type& _data) {
		// TODO: Implement this method
		Node* temp = mTail;

		mTail = new Node(_data, nullptr, temp);

		if (temp != nullptr) temp->next = mTail;
		if (mHead == nullptr) mHead = mTail;

		mSize++;

	}

	void Clear() {
		// TODO: Implement this method
		if (mHead != nullptr) {


			Node* next = nullptr;
			while (true)
			{
				next = mHead->next;

				delete mHead;
				mHead = next;
				if (mHead->next == nullptr) 
				{
					delete mHead;
					break;
				}
			}
			mHead = mTail = nullptr;
			mSize = 0;
		}
	}

	Iterator Insert(Iterator& _iter, const Type& _data) {
	
	}

	Iterator Erase(Iterator& _iter) {
		// TODO: Implement this method
		if (mHead == nullptr) return _iter;
		Node* current = mHead;
		while (current != _iter.mCurr)
		{
			if (current->next == nullptr) { 
				
				break;
			}


			if (current = _iter.mCurr) {
				if (current->prev != nullptr) {
					current->prev->next = current->next;
				}
				if (current->next != nullptr) {
					current->next->prev = current->prev;
				}
				if (_iter.mCurr->next == nullptr) {
					_iter.mCurr = _iter.mCurr->prev;

				}
				else {

				_iter.mCurr = _iter.mCurr->next;
				}
				delete current;
				
				break;
			}
			current = current->next;
		}
		mSize--;
		return _iter;
	}

	Iterator Begin() const {
		// TODO: Implement this method
		Iterator i;
		i.mCurr = mHead;
		return i;
	}

	Iterator End() const {
		// TODO: Implement this method
		Iterator i;
		i.mCurr = mTail->next;

		return i;
	}
};