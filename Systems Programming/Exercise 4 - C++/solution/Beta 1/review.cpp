#include "review.h"
 


//this operator is used so sortedList would work right because if it was undefined it
//wouldn't find what to call

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

