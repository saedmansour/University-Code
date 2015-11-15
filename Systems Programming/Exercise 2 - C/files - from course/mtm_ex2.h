#ifndef _MTM_EX2_H /* So that we won't include twice... */
#define _MTM_EX2_H

#include <stdio.h>

/* 
 * File name: mtm_ex2.h 
 * Author: Ariel Dotan (MATAM course staff, Spring 2007-2008)
 * Last update: 28th June 2008
 *
 * Description:
 * This files contains the supplementary functions to be used in ex2.
 *
 * Functions list:
 * mtm_error 			- prints error messages to stderr.
 * mtm_printMovie		- prints a movie details to stdout.
 * mtm_printUserGrade	- prints a grade a user gave to stdout.
 */

/* Maximum characters in an input line */
#define MAX_LEN 120 

/*
 * Enum: mtmErrors
 * Error values to be used with mtm_error
 */

typedef enum mtmErrors_t
{
	err_OutOfMemory,		/* out of memory (after this error, you should abort the program) */
	err_WrongArguments,		/* program (main) called with wrong parameters (after this, you should abort the program) */
	err_OpenFailed,			/* failed to open file (after this, you should abort the program) */
	err_CloseFailed,		/* failed to close file (after this, you should abort the program) */
	err_BadCommandParam,	/* illegal command given */
	err_BadSpecifierParam,	/* command given with an illegal specifier */
	err_BadParamNum,		/* command given with wrong number of parameters */
	err_BadYearParam,		/* command given with an illegal year parameter */
	err_BadNParam,			/* command given with an illegal N parameter */
	err_BadGenreParam,		/* command given with an illegal genre parameter */
	err_BadTypeParam,		/* command given with an illegal type parameter */
	err_BadGradeParam,		/* command given with an illegal grade parameter */
	err_MovieAlreadyExists, /* movie for adding already exists */
	err_MovieNotExists,		/* referenced movie does not exist */
	err_ReviewAlreadyExists,/* review for adding already exists */
	err_ReviewNotExists,	/* referenced review does not exist  */
	err_NothingToPrint,		/* requested report contains no entries to print */
	no_err				    /* in case no error has occured */
} mtmErrors;

/*
 * Name: mtm_error
 *
 * Arguments: 
 * ErrorCode   - error code, of type mtmErrors (see above).
 * 
 * Return value: none
 *
 * Description: Prints error message to stderr
 * if the value passed is "no_err", does nothing
 *
 */
void mtm_error(mtmErrors errorCode);

/*
 * Name: mtm_printMovie
 *
 * Arguments: 
 * Outstream   	- a pointer to the output stream
 * MovieName	- name of the movie
 * Year			- year of the movie
 * Genre		- genre of the movie
 * Grade		- grade of the movie by users
 * NumOfUsers	- number of users that reviewed this movie
 * Review		- review of the movie to print, may be NULL if not required to print.
 * 
 * Return value: 1 if printing was successful, else 0
 *
 * Description: Prints movie's info according to the given input.
 *
 */
int mtm_printMovie(FILE* Outstream, const char* MovieName, 
				   int Year, const char* Genre, int Grade, int NumOfUsers, 
				   const char * Review );


/*
 * Name: mtm_printUserGrade
 *
 * Arguments: 
 * Outstream   	- a pointer to the output stream
 * Name			- name of the user
 * Grade		- grade of the movie given by the user

 * Return value: 1 if printing was successful, else 0
 *
 * Description: Prints user's grade according to the given input.
 *
 */
int mtm_printUserGrade(FILE* Outstream, const char* Name, int Grade);

#endif /* #ifndef _MTM_EX2_H */


