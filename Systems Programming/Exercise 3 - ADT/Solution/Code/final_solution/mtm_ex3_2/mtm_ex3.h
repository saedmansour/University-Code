#ifndef _MTM_EX3_H /* So that we won't include twice... */
#define _MTM_EX3_H

#include <stdio.h>

/*
 * File name: mtm_ex3.h
 *
 * Description:
 * This files contains the supplementary functions to be used in ex3.
 *
 * Functions list:
 * mtm_printMovie		- prints a movie details to an output stream.
 * mtm_printUserGrade	- prints a grade a user gave to an output stream.
 * mtm_printCriticReview - prints a review a critic gave to an output stream.
 */


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
int mtm_printMovie(FILE* fd, const char* movieName, int year,
		const char* genre, int grade, int numOfUsers, const char * review);


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
int mtm_printUserGrade(FILE* fd, const char* name, int grade);

/*
 * Name: mtm_printCriticReview
 *
 * Arguments:
 * Outstream   	- a pointer to the output stream
 * Name			- name of the critic
 * Grade		- review given by the critic

 * Return value: 1 if printing was successful, else 0
 *
 * Description: Prints acritic's review according to the given input.
 *
 */
int mtm_printCriticReview(FILE* fd, const char* name, const char* review);

#endif /* #ifndef _MTM_EX2_H */



