#ifndef REVIEWS_LIST_H
#define REVIEWS_LIST_H


//--Includes------------------------------------------------------
#include "linked_list.h"
#include "mtm_ex3.h"
#include "moviedatabase.h"
#include "general.h"
//----------------------------------------------------------------





//--Typedefs------------------------------------------------------
typedef void* review_element;
typedef struct review_rec* review_ptr;
//----------------------------------------------------------------





//--Functions-----------------------------------------------------

//<parameters_functions action="get review parameters">
boolean get_is_main_review(review_ptr review);
int get_review_num(review_ptr review);
char* get_reviewer_name_from_review(review_ptr review);
char* get_description (review_ptr review);
ReviewType get_type(review_ptr review);
int get_review_grade(review_ptr review);
//<parameters_functions>


//<functions relation="main review">
void unset_as_main(review_ptr review);
void set_as_main(review_ptr review);
boolean is_main_review(review_ptr review);
//</functions>



/*
 * Name: find_review
 *
 * Description: find review in reviews_list (users/critics list in movie)
 *
 * Arguments:
 * reviews_list - a linked list for reviewers list for a specific movie 
 * name			- reviewer name
 *
 * Return value: the review to be found, if not found returns NULL
 *
 */
review_ptr find_review(LinkedList reviews_list, const char* name);



/*
 * Name: match_by_reviewer_name
 *
 * Arguments:
 * review   	- 
 * key   		-
 *
 * Return value: 1 if review match the key, else 0
 *
 * Description: check if the given review match the given key
 *
 */
int match_by_reviewer_name(review_element* review, review_element* key);



/*
 * Name: user_review_create
 *
 * Arguments:
 * name   	- review name
 * grade 	- user grade 
 *
 * Return value: pointer to review if was successful, else NULL
 *
 * Description: Create new user review .
 *
 */
review_ptr user_review_create(const char* name, int grade);



/*
 * Name: critic_review_create
 *
 * Arguments:
 * name   	- review name
 * description  	- critic description about the movie
 *
 * Return value: pointer to review if was successful, else NULL
 *
 * Description: Create new user review .
 *
 */
review_ptr critic_review_create(const char* name, const char* description );



/*
 * Name: free_review
 *
 * Arguments:
 * review   	- review to free
 * type 	    - review type
 *
 * Return value:
 *
 * Description: free review .
 *
 */
void free_review(review_element review);



/*
 * Name: copy_review
 *
 * Arguments:
 * review   	- review to copy
 *
 * Return value: new review if success, else NULL
 *
 * Description: copy the given review .
 *
 */
review_element copy_review(review_element review);



/*
 * Name: print_critic_review
 *
 * Arguments:
 * outstream   	- 
 * review		-
 *
 * Return value: 
 *
 * Description: print critic review.
 *
 */
void print_critic_review(FILE* outstream,review_element* review);



/*
 * Name: print_user_review
 *
 * Arguments:
 * outstream   	- 
 * review		-
 *
 * Return value: 
 *
 * Description: print user review.
 *
 */
void print_user_review(FILE* outstream,review_element* review);
//----------------------------------------------------------------

#endif //#ifndef REVIEWS_LIST_H
