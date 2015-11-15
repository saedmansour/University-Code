#ifndef MOVIE
#define MOVIE

#include <string>
#include <iostream>
#include "sortedlist.h"
#include "review.h"

using std::string;
using std::cout;
using std::endl;

typedef enum genre {COMEDY, HORROR, THRILLER, CLASIC, WESTERN, FICTION, CARTOON, DRAMA} Genre;
typedef enum reviewer {CRITIC, USER} Reviewer;

//////////////
// parameters:
// genre - genre of a movie
//
// the function will return the genre in a string format.
//
// return value:
// a string that holds the given genre.
//////////////
string genreToString(const Genre &genre);




//////////////
//	Class Movie - brief details:
//		Functions List:
//			getName
//			getYear
//			addReview
//			printReviews
//			print
//			operator<
//////////////



class Movie
{
public:

	// TODO: ha??
	Movie(const string nameParameter, const int yearParameter, const Genre generParameter):
	  name(nameParameter), year(yearParameter), genreType(generParameter){}

	//////////////
	// Function name: getName
	//
	// parameters:
	// void
	//
	// return value:
	// movie's name
	//////////////
	string getName() const;


	//////////////
	// Function name: getYear
	//
	// parameters:
	// void
	//
	// return value:
	// movie's year
	//////////////
	int getYear() const;


	//////////////
	// Function name: addReview
	//
	// parameters:
	// type - CRITIC/USER
	// description - the reviewer review
	// grade - movie rating, 1-10
	//
	// return value:
	// true if review added successfully, false otherwise
	//////////////
	bool addReview(const Reviewer type, const string& description, const int grade);


	//////////////
	// Function name: printReviews
	//
	// Description: print the reviews in a sorted way(the order is defined in review.h)
	//
	// parameters:
	// void
	//
	// return value:
	// void
	//////////////
	void printReviews() const;


	//////////////
	// Function name: print
	//
	// Description: print the movie's details. 
	// Printing layout: "Movie: <Movie Name> <Year> <Genre> <Average Grade>"
	//
	// parameters:
	// void
	//
	// return value:
	// void
	//////////////
	void print() const;


	//////////////
	// Function name: operator<
	// 
	// Description: helps to sort the movies. (note: The "bigger" one must appear first in the list)
	//				Sort ascending by name(dictionary order) and then by year descending.
	//
	// leftMovie < rightMovie	<=> rightMovie's name in the dictionary appears before LeftMovie's name or
	//								if they got the same name, but rightMovie's year is bigger than
	//								leftMovie's year
	//	
	//////////////
	friend bool operator<(const Movie& leftMovie, const Movie& rightMovie);
	
	//calls print();
	friend ostream& operator<<(ostream& out, const Movie* movie);

	//returns true if both movies share the same year and name
	friend bool operator==(const Movie& leftMovie, const Movie& rightMovie);

	//returns false if the two movies are different in any of these:
	//	name, year, reviews list(NOTE! this isn't checked in ==)
	friend bool operator!=(const Movie& leftMovie, const Movie& rightMovie);
		
private:
	string name;
	int year;
	Genre genreType;
	SortedList<Review*> reviews;
	double calculateAverage() const;	//used only in print() that's why it's private
};

#endif
