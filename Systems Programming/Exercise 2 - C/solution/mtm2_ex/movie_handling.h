#ifndef _MOVIE_HANDLING_H
#define _MOVIE_HANDLING_H

#include "mtm_ex2.h"


/*-Constants------------------------------------------------------*/
#define LEGAL_GENRES_NUMBER 7
#define STRINGS_EQUAL 0
#define EXIT_SUCCESS 0
/*----------------------------------------------------------------*/



/*-Typedefs (general)--------------------------------------------*/
typedef enum boolean  
{
	FALSE,
	TRUE
} boolean;

typedef char* string_t;	//"string_t" not "string" to avoid errors
						//Dont use two on same line, for example:
						//string_t st1, st2 (st2 isn't char*)
/*----------------------------------------------------------------*/



/*-Reviews Linked List--------------------------------------------*/
//<review_nodes>
struct review
{
	//<fields type="review properties">
	string_t movie_name;
	string_t reviewer_name;
	string_t describing_word;	//used only with critic
	int movie_year;
	int grade;	//a number between 1-10, used only with user
	boolean is_main_review;	//initialized to false
	//</fields>

	//<fields type="linked list">
	struct review* next;
	struct review* previous;
	//</fields>
};
/*different typedef for review to allow a creation of a different struct 
if implementation is changed afterwards. And to allow differentiation.*/
typedef struct review* ptr_review;	
typedef struct review* ptr_critic_review;
typedef struct review* ptr_user_review;
//</review_nodes>

struct reviews_list_struct
{
	ptr_review first;
	ptr_review current;
	ptr_review last;
};
typedef struct reviews_list_struct* ptr_users_list;
typedef struct reviews_list_struct* ptr_critics_list;
typedef struct reviews_list_struct* ptr_reviews_list;
/*----------------------------------------------------------------*/



/*-Movies Linked List---------------------------------------------*/
struct movie
{
	//<fields type="movie properties">
	//<field name="users_list">
	ptr_users_list users_list;
	int users_num;
	double average_grade;
	ptr_user_review main_user_review;
	//</field>
	//<field name="critics_list">
	ptr_critics_list critics_list;
	ptr_critic_review main_ciritic_review;
	//</field>
	string_t name;
	string_t genre;
	int year;
	//</fields>
	
	//<fields type="linked list">
	struct movie* next;
	struct movie* previous;
	//</fields>
};



typedef struct movie* ptr_movie;

struct movies_list
{
	ptr_movie first;
	ptr_movie current;
	ptr_movie last;
};
typedef struct movies_list* ptr_movies_list;
/*----------------------------------------------------------------*/




/*-Functions------------------------------------------------------*/
boolean is_legal_genre(string_t genre);
ptr_movie allocate_movie(string_t movie_name, int year, string_t genre);
boolean is_movie_in(ptr_movies_list movies_list, string_t movie_name, int year);
mtmErrors add_movie(ptr_movies_list movies_list, string_t movie_name, int year, string_t genre);
ptr_movie get_movie(ptr_movies_list movies_list, string_t movie_name, int year);
mtmErrors add_review(ptr_movies_list movies_list,string_t movie_name, int year,
					 string_t name, string_t paramter, string_t type);
/*----------------------------------------------------------------*/




#endif	//</_MOVIE_HANDLING_H>
