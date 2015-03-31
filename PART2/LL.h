/*
 *  LL.h
 *
 *  COSC 052 Summer 2014
 *  Project #3
 *  Author: Leslie Kim
 *  NetID : lk584
 *
 *  Due on: JUL 29, 2014
 *
 *
 *  In accordance with the class policies and Georgetown's
 *  Honor Code, I certify that, with the exceptin of the
 *  class resources and those items noted below, I have neither
 *  given nor received any assistance on this project.
 */

#ifndef __Templates__LL__
#define __Templates__LL__

#include <iostream>
#include <string>

//#define DEBUG_NODE
#define DEBUG_LL

/**************************************************************
 *                                                            *
 *                    class Node definition                   *
 *                                                            *
 **************************************************************/

template<typename T>
class Node {
public:
	T info;
	Node<T> *next;
	
	Node(T info, Node<T> * = NULL);
};

/**************************************************************
 *                                                            *
 *                     class LL definition                    *
 *                                                            *
 **************************************************************/

template <typename T>
class LL {
private:
	int count;
	Node<T> *head;
	Node<T> *tail;
	
	// copyList is a private function called by
	// both copy constructor and overloaded = operator
	// (must ensure deep copy)
	void copyList(const LL<T> &listToCopy);
	
	// printing backwards - use two pointers
	// store the size of list & iterate through with a for loop
	
public:
	LL();
	LL(const LL<T> &otherLL);	// Copy constructor
	~LL();										// Destructor, must ensure memory is deallocated
	
	int size() const {
	//	return 100;
		return count;
	}
	// Returns number of objects on the linked list
	
	void push_back(T);
	// Results in a Node<T> object being added to the end of the linked list
	// Requires dynamic allocation of memory
	
	void push_front(T);
	// Results in a Node<T> object being added to the front of the linked list
	// Requires dynamic allocation of memory
	
	void pop_back();
	// Removes the last object from the linked list - deallocates memory
	
	void clear();
	// Removes all objects from the list (Hint: consider a loop that calls pop_back())
	
	const LL& operator=(const LL <T> &rhsObj); // Overloaded = operator
	
	T& at(int ndx) const;
	// Same as at() function of vector class
	
	T& operator[](int ndx);
	// Same as subscript operator for vectors and arrays
};

/**************************************************************
 *                                                            *
 *                  class Node implementation                 *
 *                                                            *
 **************************************************************/

template <typename T>
Node<T>::Node(T infoValue, Node<T> *nodePtr) {
#ifdef DEBUG_NODE
	cout << "Entered Node<T>::Node(T, Node<T> *) consructor" << endl;
#endif
	
	info = infoValue;
	next = nodePtr;
	
#ifdef DEBUG_NODE
	cout << "Exiting Node<T>::Node(T, Node<T> *) constructor" << endl;
#endif
}

/**************************************************************
 *                                                            *
 *                   class LL implementation                  *
 *                                                            *
 **************************************************************/

template <typename T>
LL<T>::LL() {
#ifdef DEBUG_NODE
	cout << "Entered LL<T>::LL() consructor" << endl;
#endif
	
	head = NULL;
	tail = NULL;
	count = 0;
	
#ifdef DEBUG_NODE
	cout << "Exiting LL<T>::LL() consructor" << endl;
#endif
}

template <typename T>
LL<T>::LL(const LL<T> &otherLL){
#ifdef DEBUG_NODE
	cout << "Entered LL<T>::LL(const LL<T> &) convert constructor" << endl;
#endif
	
	Node<T> *newList;
	
	count = 0;
	head = NULL;
	tail = NULL;
	
	newList = copyList(otherLL);
	
#ifdef DEBUG_NODE
	cout << "Exiting LL<T>::LL(const LL<T> &) convert constructor" << endl;
#endif
}

template <typename T>
LL<T>::~LL() {
#ifdef DEBUG_NODE
	cout << "Entered LL<T>::~LL() destructor" << endl;
#endif
	
	Node<T> *current = head;
	
	while (current != NULL) {
		head = head->next;
		delete current;
		current = head;
		count--;
	}
	
	head = NULL;
	tail = NULL;
	
#ifdef DEBUG_NODE
	cout << "Exiting LL<T>::~LL() destructor" << endl;
#endif
}

template <typename T>
void LL<T>::copyList(const LL<T> &listToCopy) {
	Node<T> *current;
	current = listToCopy.head;
	
	while (current != NULL) {
		T copy = current->value;
		push_back(copy);
		current = current->next;
	}
}

template <typename T>
void LL<T>::push_back(T infoValue) {
	Node<T> *objectToAdd;
	
	objectToAdd = new Node<T>(infoValue, NULL);
	count++;
	
	if (head == NULL) {
		head = objectToAdd;
		tail = objectToAdd;
	}
	else {
		objectToAdd->next = head;
		head = objectToAdd;
	}
}

template <typename T>
void LL<T>::push_front(T infoValue) {
	Node<T> *objectToAdd;
	
	objectToAdd = new Node<T>(infoValue, NULL);
	count++;
	
	if (head == NULL) {
		head = objectToAdd;
		tail = objectToAdd;
	}
	else {
		objectToAdd->next = head;
		head = objectToAdd;
	}
}

template <typename T>
void LL<T>::pop_back() {
	Node<T> *current = head;
	
	if (head == NULL) {
		throw "Empty list.";
	}
	
	while (current->next != tail) {
		current = current->next;
	}
	
	delete current->next;
	tail = current;
}

template <typename T>
void LL<T>::clear() {
	while (head != NULL) {
		pop_back();
	}
}

template <typename T>
const LL<T>& LL<T>::operator=(const LL<T> &rhsObj) {
	// Not self assignment, okay to proceed
	if (this != rhsObj) {
		clear();
		copyList(rhsObj);
	}
	
	return *this;
}

template <typename T>
T& LL<T>::at(int ndx) const {
	Node<T> *current = head;

	try {
		if (ndx < 0 || ndx >= count) {
		        std::string err = "ERROR: Invalid subscript.";
			throw err;
		}
		for (int i = 0; i < ndx; i++) {
			current = current->next;
		}
	}
	catch (std::string e) {
	         std::cout << e << std::endl;
	}
	
	return current->info;
}

template <typename T>
T& LL<T>::operator[](int ndx) {
	Node<T> *current = head;
	
	current = head;
	while (current) {
		count++;
		current = current->next;
	}
	
	try {
		if (ndx < 0 || ndx >= count) {
			throw "ERROR: Invalid subscript.";
		}

		for (int i = 1; i <= ndx; i++) {
			current = current->next;
		}
	}
	catch (std::string e) {
		std::cout << e << std::endl;
	}
	
	return current->info;
}
#endif
