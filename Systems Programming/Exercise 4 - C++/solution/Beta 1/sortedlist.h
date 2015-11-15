#ifndef SORTED_LIST_H
#define SORTED_LIST_H

#include <iostream>

using std::cout;
using std::endl;
using std::ostream;


template <typename S>
class node
{
public:
	node():data(NULL), next(NULL), previous(NULL){}

	S data;
	node<S>* next;
	node<S>* previous;
};



template <typename T>
class SortedList
{
public:
	SortedList(): first(NULL), last(NULL), current(NULL){}
	~SortedList();

	bool add(const T newData);
	bool empty() const;
	void printAll() const;

	//<functions type="iteration">
	void start();
	void next();
	bool end();
	T* getCurrent();
	bool removeCurrent();
	//<functions>

	template <typename Type>
	friend bool operator==(const SortedList<Type>& leftList, const SortedList<Type>& rightList);

	//to calculat the average
	node<T>* first;
	node<T>* last;
	node<T>* current;
};




template <typename T>
SortedList<T>::~SortedList()
{
	start();
	while(!end())
	{
		removeCurrent();
		if(current != NULL)
		{
			next();
		}
	}
}



template <typename T>
bool SortedList<T>::add(const T newData)
{
	node<T>* newNode = new node<T>;
	if(newNode == NULL)
	{
		return false;
	}
	newNode->data = newData;


	start();
	while(!end())
	{
		if(*(current->data) == *(newNode->data))	
		{
			delete newNode;
			return false;
		}
		next();
	}

	// --Algorithm:
	// Find the node that should be ahead of the new node, and put the new one before it.

	start();
	//<edge_checks>
	if(current != NULL)	//list is not empty
	{
		if(*(newNode->data) < *(current->data))			
		{
			newNode->next = current;
			newNode->previous = NULL;
			current->previous = newNode;
			first = newNode;

			current = first;	//a convention
			return true;
		}
	}
	else	//list is empty
	{
		newNode->next = NULL;
		newNode->previous = NULL;
		first = newNode;
		last = newNode;

		current = first;
		return true;
	}
	//</edge_checks>

	next();
	while(!end())
	{
		if(*(newNode->data) < *(current->data))
		{
			newNode->next = current;
			newNode->previous = current->previous;
			//<update_neighbours>
			current->previous->next = newNode;
			current->previous = newNode;
			//</update_neighbours>
			current = first;
			return true;
		}
		next();
	}

	//else if didn't add, then it should be added at the end
	newNode->next = NULL;
	newNode->previous = last;
	last->next = newNode;
	last = newNode;

	current = first;
	return true;
}



template <typename T>
bool SortedList<T>::empty() const
{
	if(first == NULL)	//if empty
	{
		return true;
	}
	return false;
}


template <typename T>
void SortedList<T>::printAll() const
{
	node<T>* currentNode;
	currentNode = first;
	while(currentNode != NULL)
	{
		cout << currentNode->data << endl;
		currentNode = currentNode->next;
	}
}



template <typename T>
void SortedList<T>::start()
{
	current = first;
}


template <typename T>
void SortedList<T>::next() 
{
	current = current->next;
}


template <typename T>
bool SortedList<T>::end()
{
	if(current == NULL)
	{
		return true;
	}
	return false;
}


template <typename T>
T* SortedList<T>::getCurrent()
{
	return &(current->data);
}



template <typename T>
bool SortedList<T>::removeCurrent() 
{
	if(empty())
	{
		return false;
	}
	if(current->previous != NULL)	//if not first element
	{
		current->previous->next = current->next;
	}
	else	//if first
	{
		first = current->next;
	}

	if(current->next != NULL)		//if not last element
	{
		current->next->previous = current->previous;
	}
	else	//if last
	{
		last = current->previous;
	}

	//delete current; because it is deleted from where it came from

	current = first;	//a convention
	return true;
}



template <typename T>
bool operator==(const SortedList<T>& leftList, const SortedList<T>& rightList)
{
	node<T>* currentLeftNode;
	node<T>* currentRightNode;
	currentLeftNode = leftList.first;
	currentRightNode = rightList.first;

	while(!(currentLeftNode == NULL || currentRightNode == NULL ))
	{
		if(*(currentLeftNode->data) != *(currentRightNode->data))
		{
			return false;				
		}
		currentLeftNode = currentLeftNode->next;
		currentRightNode = currentRightNode->next;
	}

	if(currentLeftNode != NULL || currentRightNode != NULL )
	{
		return false;
	}
	return true;
}



#endif //#ifndef SORTED_LIST_H


