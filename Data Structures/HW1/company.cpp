
//========================================================================================
//	Includes
//========================================================================================

#include "company.h"
#include "avl_tree.h"
#include "field.h"




//========================================================================================
//	Company Class Implmentation
//========================================================================================




//  flag=1 , for remove candidate from the tree
//	flag=0 , enter candidate it
 void Company::updateMid(Candidate candidate,int flag, int salary)
{
	Candidate highestCandTemp;
	Candidate lowestCandTemp;

	if(highestNum>0)
	{
		 highestCandTemp= candidateHighestSalaryAVL.MinKey();
	}
	if(lowestNum>0)
	{
		 lowestCandTemp = candidateLowestSalaryAVL.MaxKey();
	}
	
	if(flag==0)
	{
		if(lowestNum ==0)
		{
			lowestNum++;
			candidateLowestSalaryAVL.AddByKey(candidate,NULL);
			midSalary=salary;
			return;
		}
		if(lowestNum >highestNum  )
		{
			highestNum++;
			if(salary>midSalary ||   candidate > lowestCandTemp )
			{
				candidateHighestSalaryAVL.AddByKey(candidate, NULL); //need change
			}
			else
			{
				Candidate tempCand=candidateLowestSalaryAVL.MaxKey();
				candidateHighestSalaryAVL.AddByKey(tempCand, NULL);
				candidateLowestSalaryAVL.RemoveByKey(tempCand);
				candidateLowestSalaryAVL.AddByKey(candidate, NULL);
			}
		}
		else
		{
			//assert(lowestNum==highestNum);
			Candidate tempCand=candidateHighestSalaryAVL.MinKey();
			int minSalary=tempCand.getSalary();
			lowestNum++;
			if(salary<minSalary ||  candidate < highestCandTemp )
			{
				candidateLowestSalaryAVL.AddByKey(candidate, NULL); //need change
			}
			else
			{
				candidateLowestSalaryAVL.AddByKey(tempCand, NULL);
				candidateHighestSalaryAVL.RemoveByKey(tempCand);
				candidateHighestSalaryAVL.AddByKey(candidate, NULL);
			}

		}
		Candidate MaxSalaryId = candidateLowestSalaryAVL.MaxKey();
		midSalary= MaxSalaryId.getSalary();
		return ;

	}
	/************** for delete element*********/
	else
	{
		if(lowestNum ==0)
		{
			return;
		}
		if(lowestNum > highestNum && lowestNum==1)	//only 1 candidate and is in the lowest
		{
			midSalary=-bonus;
			lowestNum--;
			Candidate tempOnlyCand = candidateLowestSalaryAVL.MinKey();
			candidateLowestSalaryAVL.RemoveByKey(candidate);
			return;
		}
		if(lowestNum >highestNum)
		{
			lowestNum--;
			if(salary<=midSalary || candidate<=lowestCandTemp)
			{
				candidateLowestSalaryAVL.RemoveByKey(candidate); //need change
			}
			else
			{
				candidateHighestSalaryAVL.RemoveByKey(candidate); //need change
				Candidate tempCand=candidateLowestSalaryAVL.MaxKey();
				candidateHighestSalaryAVL.AddByKey(tempCand, NULL);
				candidateLowestSalaryAVL.RemoveByKey(tempCand);
			}
		}
		else
		{
			Candidate tempCand=candidateHighestSalaryAVL.MinKey();
			int minSalary=tempCand.getSalary();
			highestNum--;
			if(salary>=minSalary || candidate>=highestCandTemp)
			{
				candidateHighestSalaryAVL.RemoveByKey(candidate); //need change
			}
			else
			{
				candidateLowestSalaryAVL.RemoveByKey(candidate); //need change
				Candidate tempCand=candidateHighestSalaryAVL.MinKey();
				candidateLowestSalaryAVL.AddByKey(tempCand, NULL);
				candidateHighestSalaryAVL.RemoveByKey(tempCand);
			}
		}
		Candidate MaxSalaryId= candidateLowestSalaryAVL.MaxKey();
		midSalary= MaxSalaryId.getSalary();
		return ;

	}
}

StatusType  Company::AddCandidate(int candID, int field, int salary) 
{
 if(candID<0 || salary<0|| field<0 || field>= numOfFields)
 {
	 return INVALID_INPUT;
 }

 Candidate candidate(candID,salary-bonus, field);
 if(!candidateAVL.FindByKey(candID))
 {
	 Node<Candidate> *ptrNode=fieldsArray[field].AddCandidate(candidate);
	 candidate.updatePtrNodeList(ptrNode);
	 candidateAVL.AddByKey(candID ,candidate);
	 candidateNums++;
	 salarySum+=salary-bonus;
	 updateMid(candidate,0,salary-bonus);
	 return SUCCESS;
 }
 return FAILURE;
}


StatusType  Company::HireCandidate(int candID)
{ 
	if(candID<0 )
	{
		return INVALID_INPUT;
	}
	
	TreeNode<Candidate, int>* treeNode = candidateAVL.FindByKey(candID);
	if(treeNode == NULL)
	{
		return FAILURE;
	}
	Candidate tempCandidate = treeNode->GetData();

	int salary=tempCandidate.getSalary();
		candidateNums--;
		salarySum-=salary;
		updateMid(tempCandidate,1,salary);
		candidateAVL.RemoveByKey(candID);
		(fieldsArray[(tempCandidate.getField())]).HireCandidate(tempCandidate);
		return SUCCESS;
}
StatusType  Company::HireCheapestCandidate(int field)
{
	if(field >=numOfFields || field < 0)
	{
		return INVALID_INPUT;
	}
	
	//TOdo:.... return candidate contains not the riight node

	
	if(fieldsArray[field].isEmpty())
	{
		return FAILURE;
	}

	Candidate tmpCand = fieldsArray[field].getMinSalaryCandidate();
	if((fieldsArray[field].HireCandidate(tmpCand))==SUCCESS)
	{
		HireCandidate(tmpCand.getId());
		return SUCCESS;
	}
	return FAILURE;  
}


StatusType  Company::HireFirstCandidate(int field) 
{
	if(field >=numOfFields || field < 0)
	{
		return INVALID_INPUT;
	}

	if(fieldsArray[field].isEmpty())
	{
		return FAILURE;
	}

	Candidate tmpCand = fieldsArray[field].getFirstCandidate();
	if((fieldsArray[field].HireFirstCandidate())==SUCCESS)
	{
		HireCandidate(tmpCand.getId());
		return SUCCESS;
	}
	return FAILURE;  
}


StatusType  Company::IncreaseAverageMarketSalary(int update) 
{
	if(update <=0 )
	{
		return FAILURE;
	}
	bonus+=update;
	return SUCCESS; 
}
StatusType  Company::GetRequestedSalary(int candID, int* salary) 
{
	if(candID<0|| salary==NULL)
	{
		return INVALID_INPUT;
	}

	TreeNode<Candidate,int> *Cand= candidateAVL.FindByKey(candID);
	if(Cand == NULL)
	{
		return FAILURE;
	}
	Candidate tmpCand= candidateAVL.FindByKey(candID)->GetData();
	*salary=tmpCand.getSalary()+bonus;
	return SUCCESS;
}
StatusType  Company::AverageRequestedSalary(double* average) 
{
	if(average == NULL)
	{
		return INVALID_INPUT;
	}
	if(candidateNums==0)
	{
		return FAILURE;
	}
	*average=((double)salarySum)/candidateNums+bonus;
	return SUCCESS; 
}
StatusType  Company::MedianRequestedSalary(int* median)
{
	if(median==NULL)
	{
		return INVALID_INPUT;
	}
	if(midSalary==0)
	{
		return FAILURE;
	}
	*median=midSalary+bonus;
	return SUCCESS; 
}
StatusType  Company::MinimalFieldSalary(int field, int* min)
{
	if(field<0 || field >=numOfFields || min == NULL)
	{
		return INVALID_INPUT;
	}
	
	if(fieldsArray[field].isEmpty())
	{
		return FAILURE;
	}
	*min=fieldsArray[field].getMinSalary()+bonus;

	return SUCCESS; 
}



StatusType  Company::AverageOfFirstKInField(int field, int k, double* average) 
{
	if(field<0 || field >=numOfFields || k <= 0 || average == NULL)
	{
		return INVALID_INPUT;
	}
	StatusType tempState = fieldsArray[field].getAverageFirstK(k, average); 

	*average += bonus; 

	return tempState;
}
