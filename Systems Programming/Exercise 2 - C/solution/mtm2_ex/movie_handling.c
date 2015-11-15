#include <string.h>
#include <stdlib.h>
#include "mtm_ex2.h"
#include "movie_handling.h"
#include <math.h>

void free_reviews_list(ptr_users_list users_list)
{
	ptr_review review;
	if(users_list == NULL)
	{
		return;
	}
	review = users_list->first ;
	while(review != NULL)
	{
		remove_review(users_list,review->reviewer_name);
		review = users_list->first;
	}
	return;
}
/*
void free_critics_list(ptr_critics_list critics_list)
{
	ptr_review review;
	if(critics_list == NULL)
	{
		return;
	}
	review = critics_list->first ;
	while(review != NULL)
	{
		remove_review(critics_list,review->reviewer_name,"Critic");
		review = critics_list->first;
	}
	return;
}
*/
void free_movie(ptr_movie movie)
{
	free(movie->name);
	free(movie->genre);
	free_reviews_list(movie->critics_list);
	free_reviews_list(movie->users_list);
	free(movie);
}

mtmErrors remove_movie(ptr_movies_list movies_list, string_t movie_name, int year)
{
	ptr_movie movie;
	
	movie = movies_list->first;
	while(movie != NULL)
	{
		if(strcmp(movie->name, movie_name) == STRINGS_EQUAL && year == movie->year)
		{		
			//<linked_list action="rearrange pointers in list so movie will be deleted">
			if(movie->previous == NULL)	//first node
			{
				if(movie->next != NULL)
				{
					movie->next->previous = NULL;
					movies_list->first = movie->next;			
				}
				else	//only one node in list
				{
					movies_list->first = NULL;
					movies_list->last = NULL;
				}
			}
			else if(movie->next == NULL) //last node
			{
				if(movie->previous != NULL)
				{
					movie->previous->next = NULL;
					movies_list->last = movie->previous;			
				}
				else	//only one node in list
				{
					movies_list->first = NULL;
					movies_list->last = NULL;
				}
			}
			else	//middle node
			{
				movie->next->previous = movie->previous;
				movie->previous->next = movie->next;
			}
			//</linked_list>
			
			free_movie(movie);
			mtm_error(no_err);
			return no_err;
		}
		movie = movie->next;
	}
	mtm_error(err_MovieNotExists);
	return err_MovieNotExists;
}


ptr_movie allocate_movie(string_t movie_name, int year, string_t genre)
{
	ptr_movie movie = NULL;
	ptr_critics_list critics_list = NULL;
	ptr_users_list users_list = NULL;
	
	//<memory_allocation>
	movie = (ptr_movie)malloc(sizeof(struct movie));
	if(movie == NULL)
	{
		return NULL;
	}
	movie->name = (string_t)malloc(sizeof(char) * (strlen(movie_name) + 1));
	if(movie->name == NULL)
	{
		free(movie);
		return NULL;
	}
	movie->genre = (string_t)malloc(sizeof(char) * (strlen(genre) + 1));
	if(movie->genre == NULL)
	{
		free(movie->name);	
		free(movie);
		return NULL;
	}
	critics_list = (ptr_critics_list) malloc(sizeof(struct reviews_list_struct));
	if(critics_list == NULL)
	{
		free(movie->genre);
		free(movie->name);	
		free(movie);
	}
	users_list = (ptr_users_list) malloc(sizeof(struct reviews_list_struct));
	if(users_list == NULL)
	{
		free_reviews_list(critics_list);
		free(movie->genre);
		free(movie->name);	
		free(movie);
	}
	//</memory_allocation>
	
	//<set_values type="movie">
	strcpy(movie->name, movie_name);
	strcpy(movie->genre, genre);
	movie->year = year ;
	movie->main_ciritic_review = NULL;
	movie->main_user_review = NULL;
	movie->next = NULL;
	movie->previous = NULL;
	movie->critics_list = critics_list;
	movie->critics_list->first = NULL;
	movie->critics_list->last = NULL;
	movie->users_list = users_list;
	movie->users_list->first = NULL;
	movie->users_list->last = NULL;
	movie->users_num = 0;
	//<set_values>
	
	return movie;
}


boolean is_movie_in(ptr_movies_list movies_list, string_t movie_name, int year)
{
	ptr_movie current_movie = NULL;

	if(movies_list == NULL)
	{
		return FALSE;
	}
	if(movie_name == NULL)
	{
		return FALSE;
	}
	if(movies_list->first == NULL || movies_list->last == NULL)
	{
		return FALSE;
	}
	
	current_movie = movies_list->first;
	while(current_movie != NULL)
	{
		if(strcmp(movie_name, current_movie->name) == STRINGS_EQUAL && 
			year == current_movie->year)
		{
			return TRUE;
		}
		current_movie = current_movie->next;
	}
	return FALSE ;
}



boolean is_legal_genre(string_t genre)
{
	int i = 0;
	string_t legal_genres[LEGAL_GENRES_NUMBER] = 
	{
		"Comedy",
		"Drama",
		"Thriller",
		"Horror",
		"Cartoon",
		"Fiction",
		"General"
	};
	
	for(i = 0; i < LEGAL_GENRES_NUMBER; ++i)
	{
		if(strcmp(legal_genres[i], genre) == STRINGS_EQUAL)
		{
			return TRUE;
		}
	}
	return FALSE;
}


//movies_list->first must be unequal to NULL if function is called
ptr_movie find_previous_node(ptr_movies_list movies_list, 
					string_t movie_name, int movie_year, string_t genre)
{
	ptr_movie current_movie = movies_list->first;	//list iterator

	//<check info="if movie must be placed at the list's start">
	if(strcmp(movie_name, current_movie->name) < 0)
	{
		return NULL;
	}
	if(strcmp(movie_name, current_movie->name) == 0 && 
		movie_year > current_movie->year)
	{
		return NULL;
	}
	//</check>

	while(current_movie->next != NULL)
	{
		if(strcmp(movie_name, current_movie->name) > 0 &&
			strcmp(movie_name, current_movie->next->name) < 0
			)
		{
			return current_movie;
		}
		else if(strcmp(current_movie->name, movie_name) == 0)
		{
			if(movie_year < current_movie->year)
			{
						return current_movie;
			}
		}
		current_movie = current_movie->next;	
	}
	return movies_list->last;	//if it doesn't find a sutiable place
}



void add_at_start(ptr_movies_list movies_list, ptr_movie movie)
{
	movie->next = movies_list->first;
	movie->previous = NULL;
	movies_list->first->previous = movie;
	movies_list->first = movie;
}

void add_at_middle(ptr_movies_list movies_list,ptr_movie movie, ptr_movie movie_place)
{
	movie->next = movie_place->next;	//this is the convention: movie_place is the previous
	movie->previous = movie_place;
	movie_place->next = movie;
	movie->next->previous = movie;	
}

void add_at_end(ptr_movies_list movies_list,ptr_movie movie)
{
	movie->next = NULL;
	movie->previous = movies_list->last;
	movies_list->last->next = movie;
	movies_list->last = movie;
}

mtmErrors add_movie(ptr_movies_list movies_list, string_t movie_name, int year, string_t genre)
{
	ptr_movie movie_place = NULL;
	ptr_movie movie = NULL;
	boolean list_is_empty;
	
	//<error_check>  
	if(movies_list == NULL || movie_name == NULL || genre == NULL)
	{
		mtm_error(err_WrongArguments);
		return err_WrongArguments;
	}
	if(is_movie_in(movies_list, movie_name, year))
	{
		mtm_error(err_MovieAlreadyExists);
		return err_MovieAlreadyExists;
	}
	if(year < 0)
	{
		mtm_error(err_BadYearParam);
		return err_BadYearParam;
	}
	if(!is_legal_genre(genre))
	{
		mtm_error(err_BadGenreParam);
		return err_BadGenreParam;
	}
	//</error_check> 

	//<memory_allocation>
	movie = allocate_movie(movie_name, year, genre);
	if(movie == NULL)
	{
		mtm_error(err_OutOfMemory);
		return err_OutOfMemory;
	}
	//</memory_allocation>
	

	//<linked_list action="add node at suitable place, lexographically first then by year">
	//</initilalize variable="list_is_empty">
	if(movies_list->first == NULL)
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
		//<linked_list action="find where to place the movie that is passed to the function">
		movie_place = find_previous_node(movies_list, movie_name, year, genre);
		//</linked_list>
		if(movie_place == NULL)
		{
			add_at_start(movies_list, movie);
		}
		else if(movie_place == movies_list->last)
		{
			add_at_end(movies_list, movie);
		}
		else
		{
			add_at_middle(movies_list, movie, movie_place);
		}
	}
	else	//list is empty
	{
		movies_list->first = movie;
		movies_list->last = movie;
		movie->next = NULL;
		movie->previous = NULL;
	}
	//</linked_list>
	mtm_error(no_err);
	return no_err;
}


/************************************************************/
/************************************************************/
/************************************************************/
//Ameer

mtmErrors report_movieList(ptr_movies_list movies_list, FILE* out)
{
	string_t review = "";
	int grade ;
	if(movies_list == NULL)
	{
		mtm_error(err_WrongArguments);
		return err_WrongArguments;
	}
	if(movies_list->first == NULL)
	{
		mtm_error(err_NothingToPrint);
		return err_NothingToPrint;
	}
	movies_list->current = movies_list->first;
	while(movies_list->current != NULL)
	{
		if(movies_list->current->main_ciritic_review != NULL)
		{
			review = movies_list->current->main_ciritic_review;
		}
		grade = (int)ceil(movies_list->current->average_grade);
		//mtm_printMovie(out,"staaaam",2008, "staaaam",100, 10,"staaaam");

		printf("%s %d %s %d %d %s\n", 
			movies_list->current->name, 
			movies_list->current->year, movies_list->current->genre,
			grade, movies_list->current->users_num, review);



		/*
		mtm_printMovie(out, movies_list->current->name, 
			movies_list->current->year, movies_list->current->genre,
			grade, movies_list->current->users_num, review);
		*/
		movies_list->current = movies_list->current->next ;
	}
	mtm_error(no_err);
	return no_err;
}


//********************************************************
ptr_movie go_to_movie(ptr_movies_list movies_list, string_t movie_name, int year)
{
	movies_list->current = movies_list->first ;
	while(movies_list->current != NULL)
	{
		if(strcmp(movie_name, movies_list->current->name) == STRINGS_EQUAL)
		{
			if(year == movies_list->current->year)
			{
				return movies_list->current ;
			}
		}
		movies_list->current = movies_list->current->next ;
	}
	return NULL;
}
//********************************************************
mtmErrors report_meanUsres(ptr_movies_list movies_list, int n,
						   string_t movie_name, int year, FILE* out)
{
	ptr_movie movie ;
	ptr_users_list users_list;
	if(movies_list == NULL || movie_name == NULL)
	{
		mtm_error(err_WrongArguments);
		return err_WrongArguments;
	}
	//check in case emty list (no_err)
	if(movies_list->first == NULL)
	{
		mtm_error(err_NothingToPrint);
		return err_NothingToPrint;
	}
	if(is_movie_in(movies_list, movie_name, year) == FALSE)
	{
		mtm_error(err_MovieNotExists);
		return err_MovieNotExists;
	}
	movie = go_to_movie(movies_list, movie_name, year);
	//check in case emty list (no_err)
	users_list = movie->users_list;
	if(users_list->first == NULL)
	{
		mtm_error(err_NothingToPrint);
		return err_NothingToPrint;
	}
	users_list->current = users_list->first;
	while((users_list->current != NULL) && n > 0)
	{
		printf("%s %d\n",users_list->current->reviewer_name,
							users_list->current->grade);
		/*
		mtm_printUserGrade(out, users_list->current->reviewer_name,
							users_list->current->grade);
		*/
		users_list->current = users_list->current->next ;
		n-- ;
	}
	mtm_error(no_err);
	return no_err;
}
//********************************************************

boolean print_critics(ptr_movies_list movies_list, string_t critic_name, FILE* out)
{
	ptr_critics_list critics_list ;
	boolean reviews_printed = FALSE;
	if(movies_list == NULL || critic_name == NULL)
	{
		return reviews_printed;
	}
	if(movies_list->first == NULL)
	{
		return reviews_printed;
	}
	movies_list->current = movies_list->first;
	while(movies_list->current != NULL)
	{
		critics_list = movies_list->current->critics_list;
		if(critics_list == NULL)
		{
			movies_list->current = movies_list->current->next;
			continue;
		}
		critics_list->current = critics_list->first;
		while(critics_list->current != NULL)
		{
			if(strcmp(critic_name, critics_list->current->reviewer_name) == STRINGS_EQUAL)
			{
				reviews_printed = TRUE;
				printf("%s %d %s %d %d %s\n",movies_list->current->name, 
					movies_list->current->year, movies_list->current->genre,
					0, movies_list->current->users_num, 
					critics_list->current->describing_word);
				/*
				mtm_printMovie(out, movies_list->current->name, 
					movies_list->current->year, movies_list->current->genre,
					movies_list->current->average_grade, movies_list->current->users_num, 
					critics_list->current->describing_word);
				*/			
			}
			critics_list->current = critics_list->current->next;
		}
		movies_list->current = movies_list->current->next;
	}
	return reviews_printed;
}

//************************************************************



mtmErrors report_criticMovies(ptr_movies_list movies_list, string_t critic_name,
												FILE* out)
{
	if(movies_list == NULL || critic_name == NULL)
	{
		mtm_error(err_WrongArguments);
		return err_WrongArguments;
	}
	if(print_critics(movies_list, critic_name, out) == FALSE)
	{
		mtm_error(err_NothingToPrint);
		return err_NothingToPrint;
	}
	mtm_error(no_err);
	return no_err;
}