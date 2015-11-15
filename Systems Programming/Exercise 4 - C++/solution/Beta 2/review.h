#ifndef REVIEW
#define REVIEW

#include <string>
using std::string;

#include <iostream>
using std::cout;
using std::endl;
using std::ostream;


//<constants>
int const USER_WEIGHT_GRADE = 3;
int const CRITIC_WEIGHT_GRADE = 5;
//</constants>


class Review
{
protected: 

	string review;
	int grade;

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

	//< : returns true if the left movie review grade is bigger than the right one
	//		and also if they are equal but the left review should lexigraphically 
	//		appear first
	friend bool operator<(const Review& leftReview, const Review& rightReview);

	//always returns false use
	//this is a trick to add similar reviews in SortedList
	//Don't use this to compare reviews
	friend bool operator==(const Review& leftReview, const Review& rightReview);

	//Returns false if both reviews got same review and grade true otherwise
	friend bool operator!=(const Review& leftReview, const Review& rightReview);

	//calls print depending on what kind of review
	friend ostream& operator<<(ostream& out, const Review* review);

	//added to support const prints
	virtual void print() const = 0;
};



class criticReview: public Review
{
public:
	criticReview(const string &rev, const int &gra): Review(rev, gra) {}
	void print() const;
	void print();
	int getGrade(int *weight);
};



class userReview: public Review
{
public:
	userReview(const string &rev, const int &gra): Review(rev, gra) {}
	void print() const;
	void print();
	int getGrade(int *weight);
};

#endif


