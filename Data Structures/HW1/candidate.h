#ifndef _CANDIDATE_
#define _CANDIDATE_

//========================================================================================
//	Includes
//========================================================================================

#include "node.h"
#include <stdlib.h>





//========================================================================================
//	Candidate Class
//========================================================================================
//
//	Summary: Data for each candidate
//
class Candidate
{
public:
	Candidate(int id, int salary, int field): id(id), salary(salary), field(field), candidateNode(NULL){}
	Candidate():id(-1), salary(-1), field(-1){}

	int getId()
	{
		return id;
	}

	int getSalary()
	{
		return salary;
	}

	int getField()
	{
		return field;
	}

	Node<Candidate>* getLinkListPtrNode()
	{
		return candidateNode;
	}

	void updatePtrNodeList(Node<Candidate> *ptr)
	{
		candidateNode = ptr;
	}
	

	friend bool operator==(Candidate& leftCandidate,	Candidate& rightCandidate);
	friend bool operator<(const Candidate& leftCandidate,		const Candidate& rightCandidate);
	friend bool operator>(Candidate& leftCandidate,		Candidate& rightCandidate);
	friend bool operator>=(Candidate& leftCandidate,	Candidate& rightCandidate);
	friend bool operator<=(Candidate& leftCandidate,	Candidate& rightCandidate);

private:
	int			     id;
	int				 salary;
	int				 field;		
	Node<Candidate>* candidateNode;
};

#endif

