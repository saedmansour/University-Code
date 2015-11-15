#ifndef _LINKEDLIST_
#define _LINKEDLIST_


//========================================================================================
//	Includes
//========================================================================================

#include "node.h"
#include "candidate.h"
#include <iostream>





//========================================================================================
//	LinkedList Class
//========================================================================================
//
//	Summary: LinkedList is used in the Field as a queue of candidates.
//

template<class T>
class LinkedList
{
public:
	LinkedList()
	{
		firstNode		= new Node<T>();
		firstNode->prev = NULL;
		firstNode->next = NULL;
		last			= firstNode;
	}

	~LinkedList()
	{
		while(removeFirst());
		delete firstNode;
	}


	bool isEmpty()
	{
		return firstNode->next == NULL;
	}


	Node<T>* returnFirst()
	{
		if(last == firstNode)
		{
			return NULL;
		}
		return last;
	}


	bool averageFirstK(int k,double *average)
	{
		Node<T>* current = last;
		
		int i=0;
		*average=0;
		for( i = 0; i < k && current != firstNode; i++, current = current->prev)
		{
			*average += (current->candidate).getSalary();		
		}
		if(i!=k)
		{
			return false;
		}
		*average = (*average/(double)k);

		return true;
	}


	///<summary>Adds node at the start of the list</summary>
	Node<T>*	addFirst(Candidate* candidate)
	{
		Node<T> *tmp;
		Node<T> *candidateNode = new Node<T>(*candidate);

		tmp	= firstNode->next;
		if (tmp == NULL)
		{
			candidateNode->next = NULL;
			candidateNode->prev = firstNode;
			firstNode->next		= candidateNode;
			last				= candidateNode;
		}
		else
		{	
			firstNode->next		= candidateNode;
			candidateNode->next	= tmp;
			candidateNode->prev	= firstNode;
			tmp->prev			= candidateNode;
		}
		return candidateNode;
	}


	///<summary>First here means the first that was entered. (remove last in the list)</summary>
	bool removeFirst()
	{
		Node<T> *tmp;
		tmp	= firstNode->next;
		if(tmp == NULL)	//ListIsEmpty (only dummy node)
		{
			return false;
		}

		tmp = last->prev;
		delete last;
		tmp->next = NULL;
		last = tmp;

		return true;
	}


	///<summary>Remove node from list</summary>
	void remove(Node<T>* node)
	{
		if(node->next == NULL)	//if node is last
		{
			node->prev->next	 = NULL;
			last				 = node->prev;
		}
		else
		{
			node->prev->next	= node->next; 
			node->next->prev	= node->prev;
		}
		delete node;
	}


	///<summary>Prints the list from the first node to the last node.</summary>
	void printList()
	{
		Node<T>* temp = firstNode;

		std::cout << "****Printing List**************************" << std::endl;
		while(temp->next != NULL)
		{
			temp = temp->next;
			std::cout << "Candidate ID = " <<(temp->candidate).getId()<< " " << 
				" Salary = " << (temp->candidate).getSalary() << std::endl;
		}
		std::cout << "*******************************************" << std::endl << std::endl;
	}



private:

	Node<T>* firstNode;
	Node<T>* last;
};

#endif
