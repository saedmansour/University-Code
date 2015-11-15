#ifndef REVIEW
#define REVIEW

#include <string>
#include <iostream>


using std::cout;
using std::endl;
using std::ostream;

using std::string;



int const USER_WEIGHT_GRADE = 3;
int const CRITIC_WEIGHT_GRADE = 5;


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

	// TODO: what's the solution to these two?
	virtual void print() const = 0;
	virtual int getGrade(int *weight) const= 0;
	friend bool operator<(const Review& leftMovie, const Review& rightMovie);
	friend bool operator==(const Review& leftMovie, const Review& rightMovie);
	friend bool operator!=(const Review& leftMovie, const Review& rightMovie);
	friend ostream& operator<<(ostream& out, const Review* review);
};



class criticReview: public Review
{
public:
	criticReview(const string &rev, const int &gra): Review(rev, gra) {}
	
	void print() const
	{
		cout << "Critics: \"" << review << "\" (" << grade << ").";
	}

	void print()
	{
		cout << "Critics: \"" << review << "\" (" << grade << ").";
	}


	int getGrade(int *weight) const
	{
		*weight = CRITIC_WEIGHT_GRADE;
		return grade;		
	}

	int getGrade(int *weight)
	{
		*weight = CRITIC_WEIGHT_GRADE;
		return grade;		
	}
};



class userReview: public Review
{
public:
	userReview(const string &rev, const int &gra): Review(rev, gra) {}

	void print() const
	{
		cout << grade << " - " << review << ".";
	}

	void print()
	{
		cout << grade << " - " << review << ".";
	}

	int getGrade(int *weight) const
	{
		*weight = USER_WEIGHT_GRADE;
		return grade;		
	}

	int getGrade(int *weight)
	{
		*weight = USER_WEIGHT_GRADE;
		return grade;		
	}
};

#endif


