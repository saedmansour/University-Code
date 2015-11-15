#ifndef _COMPANY_
#define _COMPANY_

//========================================================================================
//	Includes
//========================================================================================



#include "candidate.h"
#include "library1.h"
#include "field.h"



//<summary info="NoData is used to make a node with key only.">
typedef int* NoData;
#define NO_DATA NULL
//</summary>






//========================================================================================
//	Company Class
//========================================================================================
//
//	Summary: The data structure of the homework. Details solution is in the dry.
//

class Company
{
public:

	Company(int numField):numOfFields(numField), bonus(0),midSalary(0),salarySum(0), candidateNums(0),lowestNum(0),highestNum(0)
	{
		this->fieldsArray = new Field[numField];
	};

	StatusType  AddCandidate(int candID, int field, int salary);
	StatusType  HireCandidate(int candID);
	StatusType  HireCheapestCandidate(int field);
	StatusType  HireFirstCandidate(int field);
	StatusType  IncreaseAverageMarketSalary(int update);
	StatusType  GetRequestedSalary(int candID, int* salary);
	StatusType  AverageRequestedSalary(double* average);
	StatusType  MedianRequestedSalary(int* median);
	StatusType  MinimalFieldSalary(int field, int* min);
	StatusType  AverageOfFirstKInField(int field, int k, double* average);
	void		updateMid(Candidate candidate,int flag,int salary);


private:
	int numOfFields;						// save num of Field
	int bonus;								// save the new average different
	int midSalary;							// save the mid salary of all student
	int salarySum;							// calculate all the salary for all the student
	int candidateNums;						// save the number of all student 
	int lowestNum;							// number of the lowest salary
	int highestNum;							// number of the highest salary
	

	//OptimalArray<Field> fieldsArray;		// initialize with O(1)...
	Field* fieldsArray;

	AVLTree<Candidate, int> candidateAVL;

	AVLTree<NoData,Candidate> candidateHighestSalaryAVL;
	AVLTree<NoData, Candidate> candidateLowestSalaryAVL;
};


#endif
