//========================================================================================
//	Includes
//========================================================================================

#include "library1.h"
#include "company.h"




//========================================================================================
//	Library1.h Implementation
//========================================================================================


void*	Init(int numFields)
{
	return (new Company(numFields));
}

StatusType  AddCandidate(void* DS, int candID, int field, int salary)
{
	return (((Company*)DS)->AddCandidate(candID, field, salary));
}



StatusType  HireCandidate(void* DS, int candID)
{
	return (((Company*)DS)->HireCandidate(candID));
}


StatusType  HireCheapestCandidate(void* DS, int field)
{
	return (((Company*)DS)->HireCheapestCandidate(field));
}


StatusType  HireFirstCandidate(void* DS, int field)
{
	return (((Company*)DS)->HireFirstCandidate(field));
}


StatusType  IncreaseAverageMarketSalary(void* DS, int update)
{
	return (((Company*)DS)->IncreaseAverageMarketSalary(update));
}


StatusType  GetRequestedSalary(void* DS, int candID, int* salary)
{
	return (((Company*)DS)->GetRequestedSalary(candID, salary));
}



StatusType  AverageRequestedSalary(void* DS, double* average)
{
	return (((Company*)DS)->AverageRequestedSalary(average));
}


StatusType  MedianRequestedSalary(void* DS, int* median)
{
	return (((Company*)DS)->MedianRequestedSalary(median));
}


StatusType  MinimalFieldSalary(void* DS, int field, int* min)
{
	return (((Company*)DS)->MinimalFieldSalary(field, min));
}


StatusType  AverageOfFirstKInField(void* DS, int field, int k, double* average)
{
	return (((Company*)DS)->AverageOfFirstKInField(field, k, average));
}


void Quit(void** DS)
{
	delete *((Company**)DS);

	*DS = NULL;
}

