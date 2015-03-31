/*
 *  LL.h
 *
 *  COSC 052 Summer 2014
 *  Project #4
 *  Author: Leslie Kim
 *  NetID : lk584
 *
 *  Due on: AUG 06, 2014
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
//#define DEBUG_LL

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
 *                class LL_iterator definition                *
 *                                                            *
 **************************************************************/
template <typename T>
class LL_iterator {
 private:
  Node<T> *current;// Pointer to point to current node in LL
 public:
  LL_iterator();// Default constrcutor
  LL_iterator(Node<T> *ptr);// Convert constructor
  
  // Overloaded dereferncing operator
  // Returns info contained in node
  T& operator*();
  
  // Overloaded pre-increment operator
  // Iterator is advanced to next node in LL
  LL_iterator operator++();
  
  // Overloaded equality operator
  // Returns true if this iterator is equal to iterator
  // specified on RHS and false otherwise
  bool operator==(const LL_iterator &rhsObj) const;
  
  // Overloaded equality operator
  // Returns true if this iterator is not equal to iterator
  // specified on RHS and false otherwise
  bool operator!=(const LL_iterator &rhsObj) const;
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
  
  // Private function caleld by copy constructor and
  // overloaded = operator (deep copy)
  void copyList(const LL<T> &listToCopy);
 public:
  LL();
  LL(const LL<T> &otherLL);// Copy constructor
  ~LL();// Destructor, must ensure memory is deallocated
  
  int size() const { return count; }
  
  // Results in a Node<T> object being added to the end of the linked list
  void push_back(T);
  
  // Results in a Node<T> object being added to the front of the linked list
  void push_front(T);

  // Removes the last object from the linked list - deallocates memory
  void pop_back();
  
  // Removes all objects from the list (Hint: consider a loop that calls pop_back())
  void clear();
  
  // Overloaded = operator
  const LL& operator=(const LL <T> &rhsObj);

  // Same as at() function of vector class
  T& at(int ndx) const;

  // Same as subscript operator for vectors and arrays
  T& operator[](int ndx);
  
  LL_iterator<T> begin();
  LL_iterator<T> end();
  
  void bubbleSort();
  void selectionSort();
  int linearSearch(std::string) const;
  int binarySearch(std::string) const;
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
    else {
      if (ndx == 0) {
	return head->info;
      }
      else {
	current = head;
	for (int i = 0; i < ndx; i++) {
	  current = current->next;
	}
      }
    }
  }
  catch (std::string e) {
    std::cout << e << std::endl;
  }
  
  return current->info;
}

template <typename T>
T& LL<T>::operator[](int ndx) {
  return this->at(ndx);
}

template <typename T>
LL_iterator<T> LL<T>::begin() {
  LL_iterator<T> temp(head);
  return temp;
}

template <typename T>
LL_iterator<T> LL<T>::end() {
  LL_iterator<T> temp(NULL);
  return temp;
}

template <typename T>
void LL<T>::bubbleSort() {
  T temp;
  bool swap;

  do {
    swap = false;
    for (int i = 0; i < (count - 1); i++) {
      if (this->at(i) > this->at(i + 1)) {
	temp = this->at(i);
	this->at(i) = this->at(i + 1);
	this->at(i + 1) = temp;
	swap = true;
      }
    }
  } while (swap);
}

template <typename T>
void LL<T>::selectionSort() {
  int startScan, minIndex;
  T minValue;
  
  for (startScan = 0; startScan < (count - 1); startScan++) {
    minIndex = startScan;
    minValue = this->at(startScan);
    
    for (int index = startScan + 1; index < count; index++) {
      if (this->at(index) < minValue) {
	minValue = this->at(index);
	minIndex = index;
      }
    }
    this->at(minIndex) = this->at(startScan);
    this->at(startScan) = minValue;
  }
}

template <typename T>
int LL<T>::linearSearch(std::string target) const {
  int index = 0;
  int position = -1;
  bool found = false;
  
  while (index < count && !found) {
    if (this->at(index) == target) {
      found = true;
      position = index;
    }
    index++;
  }

  /*
    Node<T> *current = head;
    Node<T> *position = NULL;
    int index = 0;
    bool found = false;
    
    while (current != NULL && !found) {
    
    if (current->info == target) {
    found = true;
    position = current;
    }
    current = current->next;
    index++;
    }*/
  
  return ((found) ? (index - 1) : -1);
}

template <typename T>
int LL<T>::binarySearch(std::string target) const {
  int first = 0;
  int last = count - 1;
  int middle = 0;
  int position = -1;
  bool found = false;
  
  while (!found && first <= last) {
    middle = (first + last) / 2;
    
    if (this->at(middle) == target) {
      found = true;
      position = middle;
    }
    else if (this->at(middle) > target) {
      last = middle - 1;
    }
    else {
      first = middle + 1;
    }
  }
  return ((found) ? position : -1);
}

/**************************************************************
 *                                                            *
 *              class LL_iterator implementation              *
 *                                                            *
 **************************************************************/

template <typename T>
LL_iterator<T>::LL_iterator() {
  current = NULL;
}

template <typename T>
LL_iterator<T>::LL_iterator(Node<T> *ptr) {
  current = ptr;
}

template <typename T>
T& LL_iterator<T>::operator*() {
  return current->info;
}

template <typename T>
LL_iterator<T> LL_iterator<T>::operator++() {
  current = current->next;
    
  return *this;
}

template <typename T>
bool LL_iterator<T>::operator==(const LL_iterator &rhsObj) const {
  return current == rhsObj.current;

}

template <typename T>
bool LL_iterator<T>::operator!=(const LL_iterator &rhsObj) const {
  return current != rhsObj.current;
}
#endif
