#ifndef MOVIE_DATA_BASE
#define MOVIE_DATA_BASE

#include <string>
#include "sortedlist.h"
#include "movie.h"

using std::string;

class MovieDataBase
{
private:
	
	SortedList<Movie*> movies;
	
	
	//////////////
	// parameters:
	// name - the name of the movie
	// year - the year it was released
	//
	// the function will set the current value of the list
	// movies to the wanted movie, or to the end, if the 
	// movie doesn't exists in the data-base.
	//
	// return value:
	// true if the movie was found, false otherwise
	//////////////
	bool findMovie(const string &name, const int &year);

public:
	
	MovieDataBase() {} 
	~MovieDataBase(); 


	//////////////
	// parameters:
	// name - the name of the movie
	// year - the year it was released
	// genre - the genre of the movie
	//
	// the function will add the movie to the data-base.
	//
	// return value:
	// true if the movie was added to the data-base, false if
	// the movie was already there or if there is no memory.
	//////////////
	bool addMovie(const string &name, const int &year, const Genre &genre);


	//////////////
	// parameters:
	// name - the name of the movie
	// year - the year it was released
	//
	// the function will remove the movie from the
	// data-base.
	//
	// return value:
	// true if the movie was removed, false if the movie
	// wasn't in the data-base.
	//////////////
	bool removeMovie(const string &name, const int &year);


	//////////////
	// parameters:
	// name - the name of the movie
	// year - the year it was released
	// reviewer - the type of the review
	// review - the review itself
	// grade - the grade given by the reviewer
	//
	// the function will find the movie in the data-base and 
	// will add the review.
	//
	// return value:
	// true if the movie exists, false otherwise
	//////////////
	bool addReview(const string &name, const int &year, const Reviewer &reviewer, const string& review,const int &grade);


	//////////////
	// parameters:
	// none.
	//
	// the function will print all the movies in
	// the data-base, ordered by name (first) and year (second).
	//
	// return value:
	// none.
	//////////////
	void printMovies() const{movies.printAll();}

	
	//////////////
	// parameters:
	// none.
	//
	// the function will print all the reviews of the 
	// given movie, ordered by grade.
	//
	// return value:
	// true if the movie exists, false otherwise
	//////////////
	bool printReviews(const string &name, const int &year);


	//Returns true if the two databases have the same content exactly
	friend bool operator==(const MovieDataBase& leftMovieDatabase, const MovieDataBase& rightMovieDatabase);
};

#endif


