//--Includes------------------------------------------------------
#include "movie.h"
#include "reviewer.h"
//----------------------------------------------------------------



//--Structures----------------------------------------------------
//<movie>
struct movie_rec
{
	char* name;
	char* genre;
	int year;
	int users_num;
	LinkedList critic_reviews_list; 
	LinkedList user_reviews_list;
	review_ptr main_critic_review;
	review_ptr main_user_review;
};
//</movie>
//----------------------------------------------------------------




//--Functions-----------------------------------------------------

//<parameters_functions action="get movie parameters">
LinkedList get_movie_users_list(movie_ptr movie)
{
	return movie->user_reviews_list;
}

LinkedList get_movie_critics_list(movie_ptr movie)
{
	return movie->critic_reviews_list;
}


char* get_movie_name(movie_ptr movie)
{
	return movie->name;
}
int get_movie_year(movie_ptr movie)
{
	return movie->year;
}
//</parameters_functions>


//calculates the average from the reviews of the users
int calculate_average(movie_ptr movie)
{
	int i, sum = 0, main_user_grade;
	boolean is_main_user = FALSE;
	review_element review_node = NULL;
	review_ptr review;
	LinkedList users_list = movie->user_reviews_list;

	if(movie->users_num == 0)
	{
		return 0;
	}

	linkedListGoToHead(users_list);
	for(i = 0; i < movie->users_num; i++, linkedListGoToNext(users_list))
	{
		linkedListGetCurrent(users_list, &review_node);
		review = (review_ptr) review_node;		
		if(get_is_main_review(review) == TRUE)	//if is main user
		{
			is_main_user = TRUE;
			main_user_grade = get_review_grade(review);
			continue;
		}
		sum += get_review_grade(review);
	}

	if(is_main_user) //if there is a main user
	{
		if(movie->users_num == 1)	//if there is only main user return his grade
		{
			return main_user_grade;
		}
		else
		{
			return (int)((ceil)(0.5 * (double)sum/(movie->users_num - 1) + 0.5 * main_user_grade));
		}
	}
	else
	{
		return (int)((ceil)((double)sum/movie->users_num));
	}
}



movie_ptr create_movie(const char* name, const char* genre, int year)
{	
	ListResult list_result;
	movie_ptr new_movie;

	new_movie = (movie_ptr)malloc(sizeof(struct movie_rec));
	if(new_movie == NULL)
	{
		return NULL;
	}
	if(name == NULL)
	{
		new_movie->name = (char*)malloc(sizeof(char) * 1);
	}
	else
	{
		new_movie->name = (char*)malloc(sizeof(char) * (strlen(name)+1));
	}
	if(new_movie->name == NULL)
	{
		free(new_movie);
		return NULL;
	}
	if(genre == NULL)
	{
		new_movie->genre = (char*)malloc(sizeof(char) * 1);
	}
	else
	{
		new_movie->genre = (char*)malloc(sizeof(char) * (strlen(genre)+1));
	}
	if(new_movie->genre == NULL)
	{
		free(new_movie->name);
		free(new_movie);
		return NULL;
	}
	list_result = linkedListCreate(&(new_movie->critic_reviews_list), copy_review,
							 free_review, (printListElemFunc)print_critic_review);
	if(list_result != LIST_SUCCESS)
	{ 
		free(new_movie->name);
		free(new_movie->genre);
		free(new_movie);
		return NULL;
	}
	list_result = linkedListCreate(&(new_movie->user_reviews_list), copy_review,
							 free_review, (printListElemFunc)print_user_review);
	if(list_result != LIST_SUCCESS)
	{ 
		free(new_movie->name);
		free(new_movie->genre);
		free(new_movie);
		return NULL;
	}
	if(name == NULL)
	{
		new_movie->name = NULL;
	}
	else
	{
		strcpy(new_movie->name, name);
	}
	if(genre == NULL)
	{
		new_movie->genre = NULL;
	}
	else
	{
		strcpy(new_movie->genre, genre);
	}
	new_movie->year = year;	
	new_movie->users_num = 0;
	new_movie->main_critic_review = NULL;
	new_movie->main_user_review = NULL;
	
	return new_movie;	
}



void free_movie(movie_element movie)
{
	movie_ptr tmp_movie = (movie_ptr)movie;
	if(tmp_movie == NULL)
	{
		return;
	}
	free(tmp_movie->name);
	free(tmp_movie->genre);
	/* TODO: ISn't this already freed? if you uncomment it it creats run-time error sometimes
	if(tmp_movie->main_critic_review != NULL)
	{
	free_review(tmp_movie->main_critic_review);
	}
	if(tmp_movie->main_user_review != NULL)
	{
	free_review(tmp_movie->main_user_review);
	}
	*/
	linkedListDestroy(tmp_movie->critic_reviews_list);
	linkedListDestroy(tmp_movie->user_reviews_list);
	free(movie);
	return;
}



movie_element copy_movie(movie_element movie)
{
	movie_ptr tmp_movie = (movie_ptr)movie;
	movie_ptr new_movie;
	review_ptr tmp_review;
	int list_size,i;

	if(movie == NULL)
	{
		return NULL;
	}
	new_movie = create_movie(tmp_movie->name, tmp_movie->genre, tmp_movie->year);
	new_movie->users_num = tmp_movie->users_num;
	new_movie->main_critic_review = copy_review(tmp_movie->main_critic_review);
	new_movie->main_user_review = copy_review(tmp_movie->main_user_review);
	//copying critic review list
	linkedListGoToHead(tmp_movie->critic_reviews_list);
	list_size = linkedListGetNumElements(tmp_movie->critic_reviews_list);
	for(i=0; i<list_size; i++)
	{
		linkedListGetCurrent(tmp_movie->critic_reviews_list, (review_element*)(&tmp_review));
		linkedListInsertLast(new_movie->critic_reviews_list, (review_element)tmp_review);

	}
	//copying user review list
	linkedListGoToHead(tmp_movie->user_reviews_list);
	list_size = linkedListGetNumElements(tmp_movie->user_reviews_list);
	for(i=0; i<list_size; i++)
	{
		linkedListGetCurrent(tmp_movie->user_reviews_list, (review_element*)(&tmp_review));
		linkedListInsertLast(new_movie->user_reviews_list, (review_element)tmp_review);

	}
	return new_movie;
}



void print_movie(FILE* outstream,movie_element movie)
{
	int grade = 0;
	movie_ptr tmp_movie = (movie_ptr)movie;
	if(movie == NULL)
	{
		return;
	}
	grade = calculate_average(tmp_movie);
	if(tmp_movie->main_critic_review == NULL)
	{
		mtm_printMovie(outstream, tmp_movie->name, tmp_movie->year,
			tmp_movie->genre, grade, tmp_movie->users_num,NULL);
		return;
	}
	mtm_printMovie(outstream, tmp_movie->name, tmp_movie->year,
		tmp_movie->genre, grade, tmp_movie->users_num, get_description (tmp_movie->main_critic_review));
	return;
}

void print_movie_and_description(FILE* outstream,movie_element movie, char* description)
{
	int grade = 0;
	movie_ptr tmp_movie = (movie_ptr)movie;
	if(movie == NULL)
	{
		return;
	}
	grade = calculate_average(tmp_movie);
	mtm_printMovie(outstream, tmp_movie->name, tmp_movie->year,
		tmp_movie->genre, grade, tmp_movie->users_num, description);
	return;
}


MovieResult set_main_review(movie_ptr movie, review_ptr review)
{	
	ReviewType review_type;
	
	if(review == NULL || movie == NULL)
	{
		return MOVIE_BAD_ARGUMENTS;
	}
	
	review_type = get_type(review);
	if(review_type == USER)
	{
		movie->main_user_review = review;
	}
	else
	{
		movie->main_critic_review = review;
	}
	set_as_main(review);
	return MOVIE_SUCCESS;
}



MovieResult remove_main_critic(movie_ptr movie, review_ptr review)
{
	ReviewType review_type;
	
	if(review == NULL || movie == NULL)
	{
		return MOVIE_BAD_ARGUMENTS;
	}
	
	review_type = get_type(review);
	if(review_type == USER)
	{
		movie->main_user_review = NULL;
	}
	else
	{
		movie->main_critic_review = NULL;
	}
	unset_as_main(review);
	
	return MOVIE_SUCCESS;

}



MovieResult add_review(movie_ptr movie, review_ptr review)
{
	ListResult result;
	ReviewType review_type;
	
	if(movie == NULL || review == NULL)
	{
		return MOVIE_BAD_ARGUMENTS;
	}
	
	review_type = get_type(review);
	if(review_type == USER)
	{
		if(linkedListGetNumElements(movie->user_reviews_list) != 0)
		{
			linkedListGoToHead(movie->user_reviews_list);
			result = linkedListFind(movie->user_reviews_list, review, (matchListElemFunc)match_by_reviewer_name);
			if(result == LIST_SUCCESS)
			{
				return MOVIE_FAIL;
			}
		}
		linkedListInsertFirst(movie->user_reviews_list, review);
		movie->users_num++;
	}
	else
	{
		if(linkedListGetNumElements(movie->critic_reviews_list) != 0)
		{
			linkedListGoToHead(movie->critic_reviews_list);
			result = linkedListFind(movie->critic_reviews_list, review, (matchListElemFunc)match_by_reviewer_name);
			if(result == LIST_SUCCESS)
			{
				return MOVIE_FAIL;
			}
		}
		linkedListInsertFirst(movie->critic_reviews_list, review);
	}
	
	return MOVIE_SUCCESS;
}



MovieResult remove_review(movie_ptr movie, review_ptr review)
{
	ListResult result;
	ReviewType review_type;
	if(movie == NULL || review == NULL)
	{
		return MOVIE_BAD_ARGUMENTS;
	}
	review_type = get_type(review);
	if(review_type == USER)
	{
		linkedListGoToHead(movie->user_reviews_list);
		result = linkedListFind(movie->user_reviews_list, review,
									(matchListElemFunc)match_by_reviewer_name);
		if(result == LIST_SUCCESS)
		{
			if(is_main_review(review)==TRUE)
			{
				movie->main_user_review = NULL;
			}
			linkedListRemoveCurrent(movie->user_reviews_list);
			movie->users_num--;
			return MOVIE_SUCCESS;
		}
	}
	else
	{
		linkedListGoToHead(movie->critic_reviews_list);
		result = linkedListFind(movie->critic_reviews_list, review,
									(matchListElemFunc)match_by_reviewer_name);
		if(result == LIST_SUCCESS)
		{
			if(is_main_review(review)==TRUE)
			{
				movie->main_critic_review = NULL;
			}
			linkedListRemoveCurrent(movie->critic_reviews_list);
			return MOVIE_SUCCESS;
		}
	}
	return MOVIE_FAIL; // review not found
}



//match function for linkedListFind
//matches if movie name and year are the same
int match_by_movie(movie_element movie_temp, movie_element key_temp)
{
	movie_ptr movie = (movie_ptr) movie_temp;
	movie_ptr key = (movie_ptr) key_temp;
	if(key == NULL || movie == NULL)
	{
		return NO_MATCH;
	}
	if((strcmp(movie->name, key->name) == 0) && (movie->year == key->year))
	{
		return MATCH;
	}
	else
	{
		return NO_MATCH;
	}
}


//match function for linkedListFind
//matches if movies name are the same
int match_by_movie_name(movie_element movie_temp, movie_element key_temp)
{
	movie_ptr movie = (movie_ptr) movie_temp;
	movie_ptr key = (movie_ptr) key_temp;

	if(strcmp(key->name, movie->name) == 0)
	{
		return MATCH;
	}
	else
	{
		return NO_MATCH;
	}
}


//compare function for sorting the list depending on name and year
int compare_movies(movie_element movie1_temp, movie_element movie2_temp)
{
	movie_ptr movie2 = (movie_ptr) movie1_temp;
	movie_ptr movie1  = (movie_ptr)  movie2_temp;

	if(strcmp(movie1->name, movie2->name) > 0)
	{
		return AHEAD;
	}
	else
	{
		if(strcmp(movie1->name, movie2->name) == 0)
		{
			if(movie1->year < movie2->year)
			{
				return AHEAD;
			}
			else
			{
				return BEHIND;
			}
		}
		else
		{
			return BEHIND;
		}
	}
}
