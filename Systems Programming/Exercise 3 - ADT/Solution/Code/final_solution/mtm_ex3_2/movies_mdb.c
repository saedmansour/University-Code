//--Includes------------------------------------------------------
#include "movies_mdb.h"
//----------------------------------------------------------------





//--Constants-----------------------------------------------------
#define VALID_GENRES_NUMBER 7
//----------------------------------------------------------------





//--Structures----------------------------------------------------
struct MovieDatabase_t
{
	LinkedList movies_list;
	Set reviewers;
};
//----------------------------------------------------------------





//--Typedefs (pointers to functions)------------------------------
typedef LinkedList (*ptr_get_reviews_list)(movie_ptr movie);
typedef void (*ptr_print_review)(FILE* outstream, review_element review);
//----------------------------------------------------------------





//--Functions-----------------------------------------------------
//<functions type="read values functions">
LinkedList get_movie_database_movies_list(MovieDatabase mdb)
{
	return mdb->movies_list;
}


Set get_movie_database_reviewers_set(MovieDatabase mdb)
{
	return mdb->reviewers;
}
//</functions>





//<functions type="validation">
boolean is_valid_genre(const char* genre)
{
	int i;
	const char* valid_genres[VALID_GENRES_NUMBER] = 
	{
		"Comedy",
		"Drama",
		"Thriller",
		"Horror",
		"Cartoon",
		"Fiction",
		"General"
	};

	for(i = 0; i < VALID_GENRES_NUMBER; i++)
	{
		if(strcmp(valid_genres[i], genre) == 0)
		{
			return TRUE;
		}
	}
	return FALSE;
}


boolean is_valid_year(int year)
{
	if(!(year > 0))
	{
		return FALSE;
	}
	return TRUE;
}


boolean is_valid_grade(int grade)
{
	if(!(grade >= 1 && grade <= 10))
	{
		return FALSE;
	}
	return TRUE;
}
//</function>





//<functions info="functions passed to linkedListSortElement">
static int compare_grade(review_ptr review1, review_ptr review2)
{
	int grade1 = get_review_grade(review1);
	int grade2 = get_review_grade(review2);
	char* name1 = get_reviewer_name_from_review(review1);
	char* name2 = get_reviewer_name_from_review(review2);

	if(grade1 < grade2)
	{
		return AHEAD;
	}
	else if(grade1 > grade2)
	{
		return BEHIND;
	}
	else
	{
		if(strcmp(name1, name2) < 0)
		{
			return AHEAD;
		}
		else
		{
			return BEHIND;
		}
	}
}


static int dont_sort(review_ptr review1, review_ptr review2)
{
	return AHEAD;
}
//</functions>


static int copy_filter(review_ptr review1, review_ptr review2)
{
	return MATCH;
}


movie_ptr find_movie(MovieDatabase mdb, const char* name, int year)
{
	movie_element movie = NULL;
	movie_ptr key_movie = create_movie(name ,"none", year);
	if(key_movie == NULL)
	{
		return NULL;
	}
	linkedListGoToHead(mdb->movies_list);
	if(linkedListFind(mdb->movies_list, key_movie, match_by_movie) == LIST_SUCCESS)
	{
		free_movie(key_movie);
		linkedListGetCurrent(mdb->movies_list, &movie);
		return (movie_ptr)movie;
	}
	free_movie(key_movie);
	return NULL;
}



MovieDatabase movieDatabaseCreate()
{
	MovieDatabase movie_database;

	//<memory_allocation>
	movie_database = (MovieDatabase) malloc(sizeof(struct MovieDatabase_t));
	if(movie_database == NULL)
	{
		return NULL;
	}
	//initialize struct fields to null so movieDatabaseDestroy won't handle garbage
	movie_database->movies_list = NULL;
	movie_database->reviewers = NULL;

	linkedListCreate(&movie_database->movies_list, copy_movie, free_movie, print_movie);
	if(movie_database->movies_list == NULL)
	{
		movieDatabaseDestroy(movie_database);
		return NULL;
	}
	setCreate(&movie_database->reviewers, compare_reviewer, copy_reviewer, free_reviewer, print_reviewer);
	if(movie_database->reviewers == NULL)
	{
		movieDatabaseDestroy(movie_database);
		return NULL;
	}
	//</memory_allocation>

	return movie_database;
}



void movieDatabaseDestroy(MovieDatabase mdb)
{
	if(mdb->movies_list != NULL)
	{
		linkedListDestroy(mdb->movies_list);
	}
	if(mdb->reviewers != NULL)
	{
		setDestroy(mdb->reviewers);
	}
}



MDBResult movieDatabaseAddMovie(MovieDatabase mdb, const char* name, int year,
								const char* genre)
{
	movie_ptr movie;
	
	movie =  create_movie(name, genre, year);
	if(movie == NULL)
	{
		return MDB_OUT_OF_MEMORY;
	}
	
	//<validate_arguments>
	if(mdb == NULL || name == NULL || genre == NULL)
	{
		free_movie(movie);
		return MDB_INVALID_ARGUMENT;
	}
	if(!is_valid_year(year))
	{
		free_movie(movie);
		return MDB_INVALID_YEAR;
	}
	if(!is_valid_genre(genre))
	{
		free_movie(movie);
		return MDB_INVALID_GENRE;
	}
	if(find_movie(mdb, name, year) != NULL)
	{
		free_movie(movie);
		return MDB_MOVIE_ALREADY_EXISTS;
	}
	//</validate_arguments>


	linkedListInsertFirst(mdb->movies_list, (void*)movie);
	return MDB_SUCCESS;
}



MDBResult movieDatabaseRemoveMovie(MovieDatabase mdb, const char* name,
								   int year)
{
	movie_ptr movie = NULL;
	if(mdb == NULL || name == NULL)
	{
		return MDB_INVALID_ARGUMENT;
	}
	if(!is_valid_year(year))
	{
		return MDB_INVALID_YEAR;
	}
	movie = find_movie(mdb, name, year);
	//we'll look for the movie to make current point to the desired movie
	linkedListGoToHead(mdb->movies_list);
	if(linkedListFind(mdb->movies_list, movie, match_by_movie) == LIST_FAIL)
	{
		return MDB_MOVIE_DOESNT_EXIST;
	}
	linkedListRemoveCurrent(mdb->movies_list);
	return MDB_SUCCESS;
}



MDBResult movieDatabaseAddReviewer(MovieDatabase mdb, ReviewType type, const char* name)
{
	reviewer_ptr new_reviewer ;
	new_reviewer = create_reviewer(name, type);
	if(new_reviewer == NULL)
	{
		return MDB_OUT_OF_MEMORY;
	}
	if(mdb == NULL || name == NULL)
	{
		free_reviewer(new_reviewer);
		return MDB_INVALID_ARGUMENT;
	}
	if(type != USER && type != CRITIC)
	{
		free_reviewer(new_reviewer);
		return MDB_INVALID_REVIEWTYPE;
	}
	if(setIsIn(mdb->reviewers, new_reviewer) == SET_ELEMENT_EXISTS)
	{
		free_reviewer(new_reviewer);
		return MDB_REVIEWER_ALREADY_EXISTS;
	}
	if(setAdd(mdb->reviewers, new_reviewer) != SET_SUCCESS)
	{
		free_reviewer(new_reviewer);
		return MDB_OUT_OF_MEMORY;
	}
	return MDB_SUCCESS;
}



MDBResult movieDatabaseRemoveReviewer(MovieDatabase mdb, ReviewType type,const char* name)
{
	reviewer_ptr tmp_reviewer;
	movie_ptr movie;
	int i, movies_num;
	
	//<memory_allocation>
	tmp_reviewer = create_reviewer(name, type);
	if(tmp_reviewer == NULL)
	{
		return MDB_OUT_OF_MEMORY;
	}
	//</memory_allocation>

	if(mdb == NULL || name == NULL)
	{
		free_reviewer(tmp_reviewer);
		return MDB_INVALID_ARGUMENT;
	}
	if(type != USER && type != CRITIC)
	{
		free_reviewer(tmp_reviewer);
		return MDB_INVALID_REVIEWTYPE;
	}


	//<free data="reviews from movies list">
	movies_num = linkedListGetNumElements(mdb->movies_list);
	linkedListGoToHead(mdb->movies_list);
	for(i = 0; i < movies_num; i++, linkedListGoToNext(mdb->movies_list))
	{
		linkedListGetCurrent(mdb->movies_list, (movie_element*)(&movie));
		movieDatabaseRemoveReview(mdb, type, get_movie_name(movie), get_movie_year(movie), name);
	}
	//</free>

	if(setRemove(mdb->reviewers, tmp_reviewer) != SET_SUCCESS)
	{
		free_reviewer(tmp_reviewer);
		return MDB_REVIEWER_DOESNT_EXIST;
	}

	
	free_reviewer(tmp_reviewer);
	return MDB_SUCCESS;
}



reviewer_ptr find_reviewer(Set reviewers_set,const char* name, ReviewType type)
{
	SetResult result;
	reviewer_ptr reviewer;
	reviewer_ptr reviewer_to_find = create_reviewer(name, type);
	result =  setFind(reviewers_set, (review_element*)(&reviewer),
                   reviewer_to_find, (matchListElemFunc)match_reviewer);
	free_reviewer(reviewer_to_find);
	if(result != SET_SUCCESS)
	{
		return NULL;
	}
	return reviewer;
}



MDBResult movieDatabaseAddUserReview(MovieDatabase mdb, const char* movieName,
									 int year, const char* name, int grade)
{

	movie_ptr tmp_movie;
	review_ptr new_review;
	new_review = user_review_create(name, grade);
	
	//<memory_allocation>
	if(new_review == NULL)
	{
		return MDB_OUT_OF_MEMORY;
	}
	//</memory_allocation>

	if(mdb == NULL || movieName == NULL || name == NULL)
	{
		free_review(new_review);
		return MDB_INVALID_ARGUMENT;
	}
	if(is_valid_year(year) == FALSE)
	{
		free_review(new_review);
		return 	MDB_INVALID_YEAR;
	}
	if(is_valid_grade(grade) == FALSE)
	{
		free_review(new_review);
		return MDB_INVALID_GRADE;
	}
	tmp_movie = find_movie(mdb, movieName, year);
	if(tmp_movie == NULL)
	{
		free_review(new_review);
		return MDB_MOVIE_DOESNT_EXIST;
	}
	if(find_reviewer(mdb->reviewers, name, USER) == NULL)
	{
		free_review(new_review);
		return MDB_REVIEWER_DOESNT_EXIST;
	}
	
	linkedListGoToHead(mdb->movies_list);
	if(linkedListFind(mdb->movies_list, tmp_movie, (matchListElemFunc)match_by_movie) != LIST_SUCCESS)
	{
		free_review(new_review);
		return MDB_MOVIE_DOESNT_EXIST; //just in case (find_movie checks it too)
	}
	linkedListGetCurrent(mdb->movies_list, (movie_element*)(&tmp_movie));
	if(add_review(tmp_movie,  new_review) != MOVIE_SUCCESS)
	{
		free_review(new_review);
		return MDB_REVIEW_ALREADY_EXISTS;
	}
	return MDB_SUCCESS;
}



MDBResult movieDatabaseAddCriticReview(MovieDatabase mdb,
									   const char* movieName, int year, const char* name, const char* review)
{

	movie_ptr tmp_movie;
	review_ptr new_review;
	

	//<memory_allocation>
	new_review = critic_review_create(name, review);
	if(new_review == NULL)
	{
		return MDB_OUT_OF_MEMORY;
	}
	//</memory_allocation>


	//<error_check "arguments validation before adding review">s
	if(mdb == NULL || movieName == NULL || name == NULL || review == NULL)
	{
		free_review(new_review);
		return MDB_INVALID_ARGUMENT;
	}
	if(!is_valid_year(year))
	{
		free_review(new_review);
		return 	MDB_INVALID_YEAR;
	}
	tmp_movie = find_movie(mdb, movieName, year);
	if(tmp_movie == NULL)
	{
		free_review(new_review);
		return MDB_MOVIE_DOESNT_EXIST;
	}
	if(find_reviewer(mdb->reviewers, name, CRITIC) == NULL)
	{
		free_review(new_review);
		return MDB_REVIEWER_DOESNT_EXIST;
	}
	//</error_check>

	//check if review exists and then remove
	linkedListGetCurrent(mdb->movies_list, (movie_element*)(&tmp_movie));
	if(add_review(tmp_movie,  new_review) != MOVIE_SUCCESS)
	{
		free_review(new_review);
		return MDB_REVIEW_ALREADY_EXISTS;
	}
	
	return MDB_SUCCESS;
}



MDBResult movieDatabaseRemoveReview(MovieDatabase mdb, ReviewType type,
									const char* movieName, int year, const char* name)
{
	review_ptr tmp_review = NULL;
	LinkedList reviewers_list = NULL;
	movie_ptr movie = NULL;

	//<error_check info="check all arguments before removing">
	if(mdb == NULL || movieName == NULL || name == NULL)
	{
		return MDB_INVALID_ARGUMENT;
	}
	if(!is_valid_year(year))
	{
		return 	MDB_INVALID_YEAR;
	}
	if(type != USER && type != CRITIC)
	{
		return MDB_INVALID_REVIEWTYPE;
	}
	movie = find_movie(mdb, movieName, year);
	if(movie == NULL)
	{
		return MDB_MOVIE_DOESNT_EXIST;
	}
	
	if(type == USER)
	{
		reviewers_list = get_movie_users_list(movie);
	}
	else
	{
		reviewers_list = get_movie_critics_list(movie);
	}
	if(find_reviewer(mdb->reviewers, name, type) == NULL)
	{
		return MDB_REVIEWER_DOESNT_EXIST;
	}
	tmp_review = find_review(reviewers_list, name);
	if(tmp_review == NULL)
	{
		return MDB_REVIEW_DOESNT_EXIST;
	}
	//<error_check>

	remove_review(movie, tmp_review);
	return MDB_SUCCESS;
}



MDBResult movieDatabaseSetMainReview(MovieDatabase mdb, ReviewType type,
									 const char* movieName, int year, const char* name)
{
	movie_ptr movie;
	review_ptr tmp_review;
	if(mdb == NULL || movieName == NULL || name == NULL)
	{
		return MDB_INVALID_ARGUMENT;
	}
	if(!is_valid_year(year))
	{
		return 	MDB_INVALID_YEAR;
	}
	if(type != USER && type != CRITIC)
	{
		return MDB_INVALID_REVIEWTYPE;
	}
	if((movie = find_movie(mdb, movieName, year)) == NULL)
	{
		return MDB_MOVIE_DOESNT_EXIST;
	}
	if(find_reviewer(mdb->reviewers, name, type) == NULL)
	{
		return MDB_REVIEWER_DOESNT_EXIST;
	}
	if(type == USER)
	{
		if((tmp_review = find_review(get_movie_users_list(movie), name)) == NULL)
		{
			return MDB_REVIEW_DOESNT_EXIST;
		}
	}
	else
	{
		linkedListGoToHead(get_movie_critics_list(movie));
		if(  ( tmp_review = find_review(get_movie_critics_list(movie), name) )  == NULL)
		{
			return MDB_REVIEW_DOESNT_EXIST;
		}
	}
	set_main_review(movie, tmp_review);
	return MDB_SUCCESS;
}



//<functions type="reports">
MDBResult movieDatabaseReportMovieList(MovieDatabase mdb, FILE* stream)
{
	movie_element movie = NULL;
	int i;
	if(mdb == NULL || stream == NULL)
	{
		return MDB_INVALID_ARGUMENT;
	}
	if(linkedListGetNumElements(mdb->movies_list) == 0)
	{
		return MDB_NOTHING_TO_PRINT;
	}

	//sort movie list by name and year
	linkedListSortElements(mdb->movies_list, compare_movies);
	linkedListGoToHead(mdb->movies_list);
	for(i = 0; i < linkedListGetNumElements(mdb->movies_list); i++)
	{
		linkedListGetCurrent(mdb->movies_list, &movie);
		print_movie(stream, movie);
		linkedListGoToNext(mdb->movies_list);
	}
	return MDB_SUCCESS;
}


static MDBResult report_n_reviewers(MovieDatabase mdb, int n,
									const char* movieName, int year, FILE* stream, 
									ptr_print_review print_review, ptr_get_reviews_list get_reviews_list,
									cmpListElemFunc compare_reviews)
{
	LinkedList movie_reviews_list = NULL;
	movie_ptr movie = NULL;
	review_element review = NULL;
	LinkedList copy_list = NULL;
	review_ptr review2 = NULL;
	int i;

	if(mdb == NULL || movieName == NULL || stream == NULL)
	{
		return MDB_INVALID_ARGUMENT;
	}
	if(!is_valid_year(year))
	{
		return MDB_INVALID_YEAR;
	}
	if(!(n > 0))
	{
		return MDB_INVALID_AMOUNT;
	}
	movie = find_movie(mdb, movieName, year);
	if(movie == NULL)
	{
		return MDB_MOVIE_DOESNT_EXIST;
	}
	movie_reviews_list = get_reviews_list(movie);
	if(linkedListGetNumElements(movie_reviews_list) == 0)
	{
		return MDB_NOTHING_TO_PRINT;
	}

	//<copy_list>
	linkedListFilterElements(movie_reviews_list, &copy_list, (matchListElemFunc)copy_filter, review2);
	//</copy_list>

	//<sort_list>
	linkedListGoToHead(copy_list);
	linkedListSortElements(copy_list, compare_reviews);
	//</sort_list>

	linkedListGoToHead(copy_list);
	for(i = 0; i <  linkedListGetNumElements(copy_list) && i < n; i++)
	{
		linkedListGetCurrent(copy_list, &review);
		print_review(stream, review);
		linkedListGoToNext(copy_list);
	}

	linkedListDestroy(copy_list);	//destroy the copy

	return MDB_SUCCESS;
}



MDBResult movieDatabaseReportRecentUsers(MovieDatabase mdb, int n,
										 const char* movieName, int year, FILE* stream)
{
	return report_n_reviewers(mdb, n, movieName, year, stream, 
		(ptr_print_review)print_user_review, (ptr_get_reviews_list)get_movie_users_list, 
		(cmpListElemFunc)dont_sort);
}



MDBResult movieDatabaseReportRecentCritics(MovieDatabase mdb, int n,
										   const char* movieName, int year, FILE* stream)
{
	return report_n_reviewers(mdb, n,movieName, year, stream, 
		(ptr_print_review)print_critic_review, 
		(ptr_get_reviews_list)get_movie_critics_list, (cmpListElemFunc)dont_sort);
}



MDBResult movieDatabaseReportMeanUsers(MovieDatabase mdb, int n,
									   const char* movieName, int year, FILE* stream)
{
	return report_n_reviewers(mdb, n, movieName, year, stream, 
		(ptr_print_review)print_user_review, (ptr_get_reviews_list)get_movie_users_list, 
		(cmpListElemFunc)compare_grade);
}



MDBResult movieDatabaseReportCriticMovies(MovieDatabase mdb, const char* name,
										  FILE* stream)
{
	boolean nothing_printed = TRUE;	//if something prints it's set to false
	int i, j;
	LinkedList movies_list = NULL;
	LinkedList critics_list = NULL;
	int movies_num, critics_num;
	movie_element movie = NULL;
	review_element critic_review = NULL;

	if(mdb == NULL || name == NULL || stream == NULL)
	{
		return MDB_INVALID_ARGUMENT;
	}
	if(find_reviewer(mdb->reviewers, name, CRITIC) == NULL)	//finds if reviewer is in movie database
	{
		return MDB_REVIEWER_DOESNT_EXIST;
	}

	movies_list = get_movie_database_movies_list(mdb);
	if(movies_list == NULL)
	{
		return MDB_NOTHING_TO_PRINT;
	}

	linkedListGoToHead(movies_list);
	movies_num = linkedListGetNumElements(movies_list);
	for(i = 0; i < movies_num; i++)
	{
		linkedListGetCurrent(movies_list, &movie);
		critics_list = get_movie_critics_list((movie_ptr) movie);
		linkedListGoToHead(critics_list);
		critics_num = linkedListGetNumElements(critics_list);
		for(j = 0; j < critics_num; j++)
		{
			linkedListGetCurrent(critics_list, &critic_review);
			if(strcmp(get_reviewer_name((reviewer_ptr)critic_review), name) == 0)
			{
				print_movie_and_description(stream, movie, get_description (critic_review));
				nothing_printed = FALSE;
			}
			linkedListGoToNext(critics_list);
		}
		linkedListGoToNext(movies_list);
	}


	if(nothing_printed)
	{
		return MDB_NOTHING_TO_PRINT;
	}
	return MDB_SUCCESS;
}
//</functions>
//----------------------------------------------------------------
