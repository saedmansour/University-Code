#ifndef MOVIE_H
#define MOVIE_H



//--Includes------------------------------------------------------
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "linked_list.h"
#include "review.h"
//----------------------------------------------------------------





//--Constants-----------------------------------------------------
//<match_function>
#define MATCH 1
#define NO_MATCH 0
//</match_function>

//<compare_function>
#define AHEAD -1
#define BEHIND 1
#define CANT_DECIDE 0
//</compare_function>
//----------------------------------------------------------------





//--Typedefs------------------------------------------------------
//<enum info="return values of movie functions">
typedef enum 
{
  MOVIE_SUCCESS,
  MOVIE_FAIL,
  MOVIE_BAD_ARGUMENTS,
  MOVIE_OUT_OF_MEMORY
} MovieResult;
//</enum>

typedef struct movie_rec* movie_ptr;
typedef void* movie_element;
//----------------------------------------------------------------





//--Functions-----------------------------------------------------

//<parameters_functions action="get movie parameters">
LinkedList get_movie_critics_list(movie_ptr movie);
LinkedList get_movie_users_list(movie_ptr movie);
char* get_movie_name(movie_ptr movie);
int get_movie_year(movie_ptr movie);
//</parameters_functions>



/*
 * Name: match_by_movie
 *
 * Description: checks if two movies match by name and year 
 *
 * Arguments:
 *	-movie
 *	-key
 *
 * Return value: if match, returns MATCH, else NO_MATCH
 *
 */
int match_by_movie(movie_element movie, movie_element key);



/*
 * Name: compare_movies
 *
 * Description: checks in what order movie1 and movie2 should be arranged
 * Arguments:
 * name   	- movie
 * genre 	- the key movie
 *
 * Return value: if match, returns MATCH, else NO_MATCH
 *
 */
int compare_movies(movie_element movie1, movie_element movie2);


/*
 * Name: print_movie_and_description
 *
 * Description: prints the movie and its description
 * Arguments:
 *	outstream
 *	movie_element
 *	description	- a critic literal review of the movie
 *
 *	Return value: none
 */
void print_movie_and_description(FILE* outstream,movie_element movie, char* description);



/*
 * Name: create_movie
 *
 * Arguments:
 * name   	- movie name
 * genre 	- movie grade 
 * year		- movie year
 *
 * Return value: pointer to movie if was successful, else NULL
 *
 * Description: Create new movie .
 *
 */
movie_ptr create_movie(const char* name, const char* genre, int year);



/*
 * Name: free_movie
 *
 * Arguments:
 * movie   	- pointer to movie 
 *
 * Return value:
 *
 * Description: destroy the movie .
 *
 */
void free_movie(movie_element movie);

/*
 * Name: copy_movie
 *
 * Arguments:
 * movie   	- pointer to movie 
 *
 * Return value: new  pointer to a copy of the movie if success, else NULL
 *
 * Description: copy the given movie .
 *
 */
movie_element copy_movie(movie_element movie);


/*
 * Name: print_movie
 *
 * Arguments:
 * outstream   	- out stream
 * movie		- pointer to movie
 * Return value: 
 *
 * Description: prints the movie  .
 *
 */
void print_movie(FILE* outstream,movie_element movie);


/*
 * Name: set_main_critic
 *
 * Arguments:
 * movie   	- pointer to movie 
 * review   - pointer to review
 * Return value:
 *
 * Description: sets the main review according to it's type.
 *
 */
MovieResult set_main_review(movie_ptr movie, review_ptr review);


/*
 * Name: remove_main_critic
 *
 * Arguments:
 * movie   	- pointer to movie 
 * review   - pointer to review
 * Return value:
 *
 * Description: unsets the main review according to it's type .
 *
 */
MovieResult remove_main_critic(movie_ptr movie, review_ptr review);


/*
 * Name: add_review
 *
 * Arguments:
 * movie   	- pointer to movie 
 * review   - pointer to review
 * Return value:
 *			MOVIE_BAD_ARGUMENTS : in case null pointers sent
 *			MOVIE_FAIL : in case review exist in the list
 *			MOVIE_SUCCESS 
 *
 * Description: 
 *
 */
MovieResult add_review(movie_ptr movie, review_ptr review);


/*
 * Name: remove_review
 *
 * Arguments:
 * movie   	- pointer to movie 
 * review   - pointer to review
 * Return value:
 *			MOVIE_BAD_ARGUMENTS : in case null pointers sent
 *			MOVIE_FAIL : in case review does not exist in the list
 *			MOVIE_SUCCESS 
 *
 * Description:
 *
 */
MovieResult remove_review(movie_ptr movie, review_ptr review);





#endif //#ifndef MOVIE_H
//----------------------------------------------------------------
