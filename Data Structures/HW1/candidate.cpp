
//==================================================================================
//	Includes
//==================================================================================

#include "candidate.h"




//==================================================================================
//	Operators of Candidate implementation
//==================================================================================

bool operator<(const Candidate& leftCandidate, const Candidate& rightCandidate)
{
	if(leftCandidate.salary == rightCandidate.salary)
	{
		return leftCandidate.id < rightCandidate.id;		
	}
	return leftCandidate.salary < rightCandidate.salary;
}

bool operator>=(Candidate& leftCandidate, Candidate& rightCandidate)
{
	return !(leftCandidate < rightCandidate);
}

bool operator==(Candidate& leftCandidate,	Candidate& rightCandidate)
{
	return leftCandidate.id == rightCandidate.id;
}

bool operator>(Candidate& leftCandidate,	Candidate& rightCandidate)
{
	return  rightCandidate < leftCandidate;
}

bool operator<=(Candidate& leftCandidate, Candidate& rightCandidate)
{
	return !(leftCandidate > rightCandidate);
}
