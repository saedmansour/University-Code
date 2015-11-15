#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "mtm_ex2.h"
#include "movie_handling.h"


/*-- 

	***WARNING ATOL USED INSTEAD OF STRTOL

not implemeneted: 
	free_review

	handling pointers to reviews in movie_handling and initializing values to NULL when 
	adding a movie
	ptr to movie initialize it by finding where the movie is in the movies list

----*/

mtmErrors set_main_review(ptr_reviews_list reviews_list, ptr_movie movie, 
						string_t reviewer_name, string_t type)
{
	ptr_review review = reviews_list->first;; 
	
	while(review != NULL)
	{
		if(strcmp(review->reviewer_name, reviewer_name) == STRINGS_EQUAL)
		{
			review->is_main_review = TRUE;
			if(strcmp(type, "User") == STRINGS_EQUAL)
			{
				if(movie->main_user_review != NULL)
				{
					movie->main_user_review->is_main_review = FALSE;	//set old main review to false
				}
				movie->main_user_review = review;
			}
			else
			{
				if(movie->main_ciritic_review != NULL)
				{
					movie->main_ciritic_review->is_main_review = FALSE;	//set old main review to false
				}
				movie->main_ciritic_review = review;
			}
			movie->main_user_review = review;
			mtm_error(no_err);
			return no_err;
		}
		review = review->next;
	}
	mtm_error(err_ReviewNotExists);
	return err_ReviewNotExists;
}

void free_review(ptr_review review)
{
	if(review == NULL)
	{
		return;
	}
	if(review->movie_name != NULL)
	{
		free(review->movie_name);
	}
	if(review->reviewer_name != NULL)
	{
		free(review->reviewer_name);
	}
	if(review->describing_word != NULL)
	{
		free(review->describing_word);
	}
	free(review);
	return;
}

//removes both user and critic
mtmErrors remove_review(ptr_reviews_list reviews_list, string_t reviewer_name,
													string_t type)
{
	ptr_review review;
	
	review = reviews_list->first;
	while(review != NULL)
	{
		if(strcmp(review->reviewer_name, reviewer_name) == STRINGS_EQUAL)
		{		
			//<linked_list action="rearrange pointers in list so review will be deleted">
			if(review->previous == NULL)	//first node
			{
				if(review->next != NULL)
				{
					review->next->previous = NULL;
					reviews_list->first = review->next;			
				}
				else	//only one node in list
				{
					reviews_list->first = NULL;
					reviews_list->last = NULL;
				}
			}
			else if(review->next == NULL) //last node
			{
				if(review->previous != NULL)
				{
					review->previous->next = NULL;
					reviews_list->last = review->previous;			
				}
				else	//only one node in list
				{
					reviews_list->first = NULL;
					reviews_list->last = NULL;
				}
			}
			else	//middle node
			{
				review->next->previous = review->previous;
				review->previous->next = review->next;
			}
			//</linked_list>
			
			free_review(review, type);
			mtm_error(no_err);
			return no_err;
		}
		review = review->next;
	}
	mtm_error(err_ReviewNotExists);
	return err_ReviewNotExists;
}

ptr_movie get_movie(ptr_movies_list movies_list, string_t movie_name, int year)
{
	ptr_movie current_movie = movies_list->first;
	while(current_movie != NULL)
	{
		if(strcmp(current_movie->name,movie_name) == STRINGS_EQUAL &&
			current_movie->year == year)
		{
			return current_movie;
		}
		current_movie = current_movie->next;
	}
	return NULL;
}

boolean is_already_reviewed(ptr_movie movie, string_t name, string_t type)
{
	boolean is_user_list = FALSE;
	ptr_review current_review;
	if(movie == NULL)
	{
		return FALSE;
	}
	if(strcmp(type, "User") == STRINGS_EQUAL)
	{
		is_user_list = TRUE;
	}
	if(is_user_list)
	{
		current_review = movie->users_list->first;
	}
	else
	{
		current_review = movie->critics_list->first;
	}

	while(current_review != NULL)
	{
		if(strcmp(current_review->reviewer_name, name) == STRINGS_EQUAL)
		{
			return TRUE;
		}
		current_review = current_review->next;
	}
	return FALSE;
}

void add_review_at_start(ptr_reviews_list reviews_list, ptr_review review)
{
	review->next = reviews_list->first;
	review->previous = NULL;
	reviews_list->first->previous = review;
	reviews_list->first = review;
}

void add_review_at_middle(ptr_reviews_list reviews_list,ptr_review review, ptr_review review_place)
{
	review->next = review_place->next;	//this is the convention: review_place is the previous
	review->previous = review_place;
	review_place->next = review;
	review->next->previous = review;	
}

void add_review_at_end(ptr_reviews_list reviews_list,ptr_review review)
{
	review->next = NULL;
	review->previous = reviews_list->last;
	reviews_list->last->next = review;
	reviews_list->last = review;
}

//used for users list
ptr_review find_review_previous_node(ptr_reviews_list reviews_list,
							  string_t reviewer_name, int grade)
{
	ptr_review current_review = reviews_list->first;	//list iterator

	//<check info="if movie must be placed at the list's start">
	if(grade < current_review->grade)
	{
		return NULL;
	}
	if(grade == current_review->grade && 
		strcmp(reviewer_name, current_review->reviewer_name) < 0)
	{
		return NULL;
	}
	//</check>

	while(current_review->next != NULL)
	{
		if(grade > current_review->grade &&
			grade < current_review->next->grade)
		{
			return current_review;
		}
		else if(grade == current_review->grade)
		{
			if(strcmp(reviewer_name, current_review->reviewer_name) > 0 &&
				strcmp(reviewer_name, current_review->next->reviewer_name) < 0 )
			{
						return current_review;
			}
		}
		current_review = current_review->next;	
	}
	return reviews_list->last;	//if it doesn't find a sutiable place
}


ptr_review allocate_review(string_t movie_name, int year, string_t reviewer_name, 
						  string_t parameter, string_t type)
{
	ptr_review review = NULL;
	boolean is_users_list = FALSE;
	if(strcmp(type, "User") == STRINGS_EQUAL)
	{
		is_users_list = TRUE;
	}

	//<memory_allocation>
	review = (ptr_review)malloc(sizeof(struct review));
	if(review == NULL)
	{
		return NULL;
	}
	review->reviewer_name = (string_t)malloc(sizeof(char) * (strlen(reviewer_name) + 1));
	if(review->reviewer_name == NULL)
	{
		free(review);
		return NULL;
	}
	review->movie_name = (string_t)malloc(sizeof(char) * (strlen(movie_name) + 1));
	if(review->movie_name == NULL)
	{
		free(review->reviewer_name);	//must be before free(movie)
		free(review);
		return NULL;
	}
	if(!is_users_list)
	{
		review->describing_word = (string_t)malloc(sizeof(char) * (strlen(parameter) + 1));
		if(review->describing_word == NULL)
		{
			free(review->movie_name);
			free(review->reviewer_name);	//must be before free(movie)
			free(review);
			return NULL;
		}
	}
	//</memory_allocation>
	
	//<set_values type="movie">
	if(!is_users_list)
	{
		strcpy(review->describing_word, parameter);
	}
	else
	{
		review->grade = atol(parameter);
	}
	strcpy(review->movie_name, movie_name);
	strcpy(review->reviewer_name, reviewer_name);
	review->movie_year = year;
	review->is_main_review = FALSE;
	review->next = NULL;
	review->previous = NULL;
	//<set_values>
	
	return review;
}


//review is the general review. critics and users are special reviewers
//paramter: grade or describing word

mtmErrors add_review(ptr_movies_list movies_list,string_t movie_name, int year,
					 string_t name, string_t paramter, string_t type)
{
	//<initialize>
	ptr_review review = NULL;
	ptr_review review_place = NULL;
	ptr_reviews_list reviews_list = NULL;
	ptr_movie movie = NULL;
	boolean is_users_list = FALSE;
	boolean list_is_empty;
	int grade;
	/***********************/
	if((strcmp(type, "User") != STRINGS_EQUAL) && (strcmp(type, "Critic") != STRINGS_EQUAL))
	{
			mtm_error(err_BadTypeParam);
			return err_BadTypeParam;
	}
	/***********************/
	movie = get_movie(movies_list, movie_name, year);
	if(strcmp(type, "User") == STRINGS_EQUAL)
	{
		is_users_list = TRUE;
	}
	if(is_users_list)	//initialize grade for users only
	{
		grade = atol(paramter);
	}
	//</initialize>
	//<error_check> 
	//***********************************************/
	//Why if and else ? both is same
	if(is_users_list)
	{
		if(is_already_reviewed(movie, name, type))
		{
			mtm_error(err_ReviewAlreadyExists);
			return err_ReviewAlreadyExists;
		}
	}
	else
	{
		if(is_already_reviewed(movie , name, type))
		{
			mtm_error(err_ReviewAlreadyExists);
			return err_ReviewAlreadyExists;
		}
	}
	if(is_users_list)
	{
		if(!(grade >=1 && grade <=10))
		{
			mtm_error(err_BadGradeParam);
			return err_BadGradeParam;
		}
	}
	if(!is_movie_in(movies_list, movie_name, year))
	{
		mtm_error(err_MovieNotExists);
		return err_MovieNotExists;
	}
	//</error_check>
	//<initialize variable="reviews_list">
	if(is_users_list)
	{
		reviews_list = movie->users_list;
	}
	else
	{
		reviews_list = movie->critics_list;
	}
	//</initialize>


	//<memory_allocation>
	review = allocate_review(movie_name, year, name, paramter, type);
	if(review == NULL)
	{
		mtm_error(err_OutOfMemory);
		return err_OutOfMemory;
	}
	//</memory_allocation>

 
	//<linked_list action="add node at suitable place">
	//</initilalize variable="list_is_empty">
	if(reviews_list->first == NULL)
	{
		list_is_empty = TRUE;
	}
	else
	{
		list_is_empty = FALSE;
	}
	//</initilalize>

	if(!list_is_empty)
	{
		if(is_users_list)
		{
			review_place = find_review_previous_node(reviews_list, name, grade);
		}
		else
		{	
			review_place = reviews_list->first;
		}
		//</linked_list>
		if(review_place == NULL)
		{
			add_review_at_start(reviews_list, review);
		}
		else if(review_place == reviews_list->last)
		{
			add_review_at_end(reviews_list, review);
		}
		else
		{
			add_review_at_middle(reviews_list, review, review_place);
		}
	}
	else	//list is empty
	{
		reviews_list->first = review;
		reviews_list->last = review;
		review->next = NULL;
		review->previous = NULL;
	}
	//</linked_list>
	if(is_users_list)
	{
		movie->users_num++;
	}
	mtm_error(no_err);
	return no_err;
}
