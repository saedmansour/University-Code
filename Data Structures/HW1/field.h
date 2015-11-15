#ifndef _Field_
#define _Field_

//========================================================================================
//	Includes
//========================================================================================

#include "avl_tree.h"
#include "library1.h"
#include "candidate.h"
#include "linked_list.h"





//========================================================================================
//	Field Class
//========================================================================================
//
//	Summary: Data structures for each field. Add to field remove etc. Details in dry part.
//
class Field
{
public:
	
	Field(){}


	Candidate getMinSalaryCandidate()
	{
		return candidatesSalaryAVL.MinKey();
	}


	bool isEmpty()
	{
		return candidatesSalaryAVL.IsEmpty();
	}


	Node<Candidate>*  AddCandidate(Candidate candidate)
	{
		Node<Candidate>* tempNode = candidatesQueue.addFirst(&candidate);
		
		candidate.updatePtrNodeList(tempNode);
		candidatesSalaryAVL.AddByKey(candidate, NULL);
		
		return tempNode;
	}


	StatusType  HireCandidate(Candidate candidate)
	{
		Node<Candidate> *tempNode = candidate.getLinkListPtrNode();
		
		if(!candidatesSalaryAVL.RemoveByKey(candidate))
		{
			return FAILURE;
		}
		candidatesQueue.remove(tempNode);

		return SUCCESS;
	}


	StatusType HireFirstCandidate()
	{
		if(candidatesQueue.isEmpty())
		{
			return FAILURE;
		}

		Candidate tempCand = candidatesQueue.returnFirst()->candidate;
		candidatesSalaryAVL.RemoveByKey(tempCand);
		candidatesQueue.removeFirst();
		
		return SUCCESS;
	}


	Candidate getFirstCandidate()
	{
		return (candidatesQueue.returnFirst()->candidate);
	}


	int	getMinSalary()
	{
		return getMinSalaryCandidate().getSalary();
	}


	StatusType getAverageFirstK(int k, double* average)
	{
		if(candidatesQueue.averageFirstK(k,average))
		{
			return SUCCESS;
		}
		return FAILURE;
	}




private:
	AVLTree<NoData,Candidate> candidatesSalaryAVL;
	LinkedList<Candidate> candidatesQueue;
};
#endif
