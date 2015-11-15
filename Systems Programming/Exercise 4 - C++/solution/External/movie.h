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

class Movie
{
private:

	string name;
	int year;
	Genre genre;
	SortedList<Review*> reviews;
	
};

#endif

