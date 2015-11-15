#include "review.h"


bool operator==(const Review& leftReview, const Review& rightReview)
{
	//this is a trick to add similar reviews
	return false;
}


bool operator!=(const Review& leftReview, const Review& rightReview)
{
	if(rightReview.grade == leftReview.grade && 
		rightReview.review == leftReview.review)
	{
		return false;
	}
	return true;
}


//returns true if they are equal
bool operator<(const Review& leftReview, const Review& rightReview)
{
	//<edgeCase info="if equal let the leftReview be the first and make sure it is the last review
	//that was inserted whenever this operator is used">
	if(rightReview.grade == leftReview.grade && 
		rightReview.review == leftReview.review)
	{
		return true;
	}
	//</edgeCase>

	if(leftReview.grade > rightReview.grade)
	{
		return true;
	}
	else if(leftReview.grade == rightReview.grade)
	{
		if(leftReview.review < rightReview.review)
		{
			return true;
		}
	}
	return false;
}


ostream& operator<<(ostream& out, const Review* review)
{
	(*review).print();
	return out;
}



void userReview::print() const
{
	cout << grade << " - " << review << ".";
}

int userReview::getGrade(int *weight)
{
	*weight = USER_WEIGHT_GRADE;
	return grade;		
}





void criticReview::print() const
{
	cout << "Critics: \"" << review << "\" (" << grade << ").";
}

int criticReview::getGrade(int *weight)
{
	*weight = CRITIC_WEIGHT_GRADE;
	return grade;		
}
