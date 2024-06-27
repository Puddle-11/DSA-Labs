/*
File:			BST.h
Author(s):
	Base:		Justin Tackett
				jtackett@fullsail.com
	Student:

Purpose:		A binary search tree
Notes:			Property of Full Sail University 2406
*/

// Header protection
#pragma once

/************/
/* Includes */
/************/
#include <string>

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
#define LAB_7	1

// Individual unit test toggles
#define BST_CTOR								1
#define BST_NODE_CTOR							1
#define BST_PUSH_EMPTY							1
#define BST_PUSH_LEFT							1
#define BST_PUSH_RIGHT							1
#define BST_CLEAR								0
#define BST_DTOR								0
#define BST_CONTAINS_FOUND						1
#define BST_CONTAINS_NOTFOUND					1
#define BST_REMOVE_CASE0_ROOT					1
#define BST_REMOVE_CASE0_LEFT					1
#define BST_REMOVE_CASE0_RIGHT					1
#define BST_REMOVE_CASE1_ROOT_LEFT				1
#define BST_REMOVE_CASE1_ROOT_RIGHT				1
#define BST_REMOVE_CASE1_LEFT_LEFT				1
#define BST_REMOVE_CASE1_LEFT_RIGHT				1
#define BST_REMOVE_CASE1_RIGHT_LEFT				1
#define BST_REMOVE_CASE1_RIGHT_RIGHT			1
#define BST_REMOVE_CASE2_CASE0					1
#define BST_REMOVE_CASE2_CASE1					1
#define BST_REMOVE_CASE0						0
#define BST_REMOVE_CASE1						0
#define BST_REMOVE_CASE2						0
#define BST_REMOVE_NOT_FOUND					0
#define BST_IN_ORDER_TRAVERSAL					0
#define BST_ASSIGNMENT_OP						0
#define BST_COPY_CTOR							0


// Templated binary search tree
template<typename Type>
class BST {

	friend class UnitTests_Lab7;	// Giving access to test code

	struct Node {
		Type data;					
		Node* left, * right;		
		Node* parent;				

		Node(const Type& _data, Node* _parent = nullptr) {
			// TODO: Implement this method
			data = _data;
			
			parent = _parent;
			left = nullptr;
			right = nullptr;
		}
	};

	// Data members
	// NOTE: All values set to -1 for unit test purposes
	Node* mRoot = reinterpret_cast<Node*>(-1);	

public:

	BST() {

		mRoot = nullptr;
		// TODO: Implement this method

	}

	~BST() {
		// TODO: Implement this method

	}

	BST(const BST& _copy) {
		// TODO: Implement this method

	}

	BST& operator=(const BST& _assign) {
		// TODO: Implement this method
		
	}

private:
	// Recursive helper method for use with Rule of 3
	void Copy(const Node* _curr) {
		// TODO: Implement this method

	}

public:

	void Clear() {
		// TODO: Implement this method

	}

private:

	// Recursive helper method for use with Clear
	void Clear(Node* _curr) {
		// TODO: Implement this method

	}

public:

	void Push(const Type& _val) {
		// TODO: Implement this method
		Node* newNode = new Node(_val);
		if (mRoot == nullptr) {
			mRoot = newNode;
			return;
		}
		else {
			Node* temp = mRoot;
			while (true)
			{
				if (newNode->data < temp->data) {
					if (temp->left == nullptr) {
						temp->left = newNode;
						newNode->parent = temp;
						break;
					}
					else {
						temp = temp->left;
					}
				}
				else {
					if (temp->right == nullptr) {
						temp->right = newNode;
						newNode->parent = temp;
						break;
					}
					else {
						temp = temp->right;
					}
				}
			}


		}
	}

	bool Contains(const Type& _val) {
		// TODO: Implement this method

		return FindNode(_val) != nullptr ? true : false;
	}

private:

	Node* FindNode(const Type& _val) {
		Node* temp = mRoot;
		if (temp == nullptr) return nullptr;
		while (true)
		{
			if (temp->data > _val)
			{
				//go left
				if (temp->left == nullptr) return nullptr; //no value found

				temp = temp->left;

			}
			else if (temp->data < _val)
			{

				//go right
				if (temp->right == nullptr) return nullptr; //no value found

				temp = temp->right;
			}
			else {
				//found
				return temp;
			}
		}

	}

	void RemoveCase0(Node* _node) {
		// TODO: Implement this method
		if (_node->parent == nullptr) {

			mRoot = nullptr;
		}
		else if (_node->parent->left == _node) {
			//left
			_node->parent->left = nullptr;
		}
		else if (_node->parent->right == _node) {
			//right
			_node->parent->right = nullptr;

		}

		delete _node;
	}

	void RemoveCase1(Node* _node) {
		// TODO: Implement this method
		if (_node->parent == nullptr) {
			//root
			if (_node->left != nullptr) {
				//move left
				mRoot = _node->left;
				_node->left->parent = nullptr;
			}
			else if (_node->right != nullptr)
			{
				mRoot = _node->right;
				_node->right->parent = nullptr;
				//move right
			}

		}
		else if (_node->parent->left == _node) {
			//left
			if (_node->left != nullptr) {
				//move left
				_node->parent->left = _node->left;
				_node->left->parent = _node->parent;
			}
			else if(_node->right != nullptr)
			{
				_node->parent->left = _node->right;
				_node->right->parent = _node->parent;
				//move right
			}

		}
		else if (_node->parent->right == _node) {
			//right
			if (_node->left != nullptr) {
				//move left
				_node->parent->right = _node->left;
				_node->left->parent = _node->parent;
			}
			else if (_node->right != nullptr)
			{
				_node->parent->right = _node->right;
				_node->right->parent = _node->parent;

				//move right
			}
		}

		delete _node;
	}

	void RemoveCase2(Node* _node) {
		// TODO: Implement this method

	}

public:

	bool Remove(const Type& _val) {
		// TODO: Implement this method

	}

	std::string InOrder() {
		// TODO: Implement this method

	}

private:

	// Recursive helper method to help with InOrder
	void InOrder(Node* _curr, std::string& _str) {
		// TODO: Implement this method

	}
};

