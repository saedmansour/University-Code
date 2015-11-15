#ifndef MOVIES_MDB_H
#define MOVIES_MDB_H


//--Includes------------------------------------------------------
#include "general.h"
#include "set.h"
#include "movie.h"
#include "reviewer.h"
//----------------------------------------------------------------



//--Functions-----------------------------------------------------

//<parameters_functions action="get movie database parameters">
Set get_movie_database_reviewers_set(MovieDatabase mdb);
LinkedList get_movie_database_movies_list(MovieDatabase mdb);
//</parameters_functions>


/*
 * Name: is_valid_genre
 *
 * Description: checks if genre is one of the valid genres
 *
 * Arguments:
 * genre		- the genre name
 *
 * Return value: returns TRUE if genre is valid else FALSE
 *
 */
boolean is_valid_genre(const char* genre);



/*
 * Name: find_movie
 *
 * Description: finds if movie is in the movies list in the movie database
 *
 * Arguments:
 * mdb			- a movie database
 * name			- movie name
 * year			- movie year
 * 
 *	Return value: the found movie
 *
 */
movie_ptr find_movie(MovieDatabase mdb, const char* name, int year);
//----------------------------------------------------------------

#endif //#ifndef MOVIES_MDB_H
