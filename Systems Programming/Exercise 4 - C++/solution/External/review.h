#ifndef REVIEW
#define REVIEW

#include <string>


using std::string;



class Review
{
protected: 
	
	string review;
	int grade;
	Reviewer type;	// note: added by me

public:
	
	Review() {}
	Review(const string &rev, const int &gra): review(rev), grade(gra) {}
	Review(const Review& rev): review(rev.review), grade(rev.grade) {}
	virtual ~Review() {}
	

	//////////////
	// parameters:
	// none.
	//
	// the function will print the review.
	//
	// return value:
	// none.
	//////////////
	virtual void print() = 0;

	virtual int getGrade(int *weight) = 0;


};


#endif

