//--Includes------------------------------------------------------
#include "review.h"
#include "movie.h"
//----------------------------------------------------------------




//--Structures----------------------------------------------------
struct review_rec
{
	char* reviewer_name;
	ReviewType type;
	int grade; //for user reviewers
	char* description ; //for critic reviewers
	boolean is_main_review;
};
//----------------------------------------------------------------




char* get_reviewer_name_from_review(review_ptr review)
{
	if(review == NULL)
	{
		return NULL;
	}
	return review->reviewer_name;
}


char* get_description (review_ptr review)
{
	if(review == NULL)
	{
		return NULL;
	}
	return review->description ;
}




ReviewType get_type(review_ptr review)
{
	return review->type;
}



int get_review_grade(review_ptr review)
{
	return review->grade;
}


boolean get_is_main_review(review_ptr review)
{
	return review->is_main_review;
}


boolean is_main_review(review_ptr review)
{
	if(review == NULL)
	{
		return FALSE;
	}
	return review->is_main_review;
}



review_ptr find_review(LinkedList reviewers_list, const char* name)
{
	int i, reviewers_num;
	review_element current_review = NULL;

	linkedListGoToHead(reviewers_list);
	reviewers_num = linkedListGetNumElements(reviewers_list);
	for(i = 0; i < reviewers_num; i++, linkedListGoToNext(reviewers_list))
	{
		linkedListGetCurrent(reviewers_list, &current_review);
		if(strcmp( ((review_ptr)current_review)->reviewer_name, name) == 0)
		{
			return (review_ptr)current_review;
		}
	}
	return NULL;	//if not found
}


void set_as_main(review_ptr review)
{
	if(review == NULL)
	{
		return;
	}
	review->is_main_review = TRUE;
	return;
}


void unset_as_main(review_ptr review)
{
	if(review == NULL)
	{
		return;
	}
	review->is_main_review = FALSE;
	return;
}



review_ptr user_review_create(const char* name, int grade)
{
	// elemet_number
	static int number_of_reviewers;

	//assume that the given grade is legal
	review_ptr review;
	if(name==NULL)
	{
		return NULL;
	}
	review = (review_ptr)malloc(sizeof(struct review_rec));
	if(review==NULL)
	{
		return NULL;
	}
	review->reviewer_name = (char*)malloc(strlen(name)+1);
	if(review->reviewer_name == NULL)
	{
		free(review);
		return NULL;
	}
	strcpy(review->reviewer_name, name);
	review->grade = grade;
	review->type = USER;
	review->description  = NULL;
	review->is_main_review = FALSE;

	number_of_reviewers++;	//element_number
	return review;
}


review_ptr critic_review_create(const char* name, const char* description )
{
	//assume that the given grade is legal
	review_ptr review;
	/*
	if(name==NULL)
	{
		return NULL;
	}
	*/
	review = (review_ptr)malloc(sizeof(struct review_rec));
	if(review==NULL)
	{
		return NULL;
	}
	if(name == NULL)
	{
		review->reviewer_name = (char*)malloc(sizeof(char) * 1);
	}
	else
	{
		review->reviewer_name = (char*)malloc(sizeof(char) * (strlen(name)+1));
	}
	if(review->reviewer_name == NULL)
	{
		free(review);
		return NULL;
	}
	if(description == NULL)
	{
		review->description  = (char*)malloc(sizeof(char) * 1);
	}
	else
	{
		review->description  = (char*)malloc(sizeof(char) * (strlen(description )+1));
	}
	if(review->description  == NULL)
	{
		free(review->reviewer_name);
		free(review);
		return NULL;
	}
	if(name == NULL)
	{
		review->reviewer_name = NULL;
	}
	else
	{
		strcpy(review->reviewer_name, name);
	}
	if(description == NULL)
	{
		review->description = NULL;
	}
	else
	{
		strcpy(review->description, description );
	}
	review->type = CRITIC;
	review->grade = -1; // Ilegal value of grade
	review->is_main_review = FALSE;

	return review;
}



void free_review(review_element review)
{	
	review_ptr tmp_review = (review_ptr)review;
	if(tmp_review == NULL)
	{
		return;
	}
	if(tmp_review->reviewer_name != NULL)
	{
		free(tmp_review->reviewer_name);
	}
	if(tmp_review->description  != NULL)
	{
		free(tmp_review->description );
	}
	free(tmp_review);
	return;
}



review_element copy_review(review_element review)
{
	review_ptr new_review = NULL;
	review_ptr tmp_review = (review_ptr)review;
	if(tmp_review == NULL)
	{
		return NULL;
	}
	if(tmp_review->type == USER)
	{
		new_review = user_review_create(tmp_review->reviewer_name, tmp_review->grade);
		return new_review;
	}
	new_review = critic_review_create(tmp_review->reviewer_name, tmp_review->description );
	return new_review;
}



void print_critic_review(FILE* outstream,review_element* review)
{
	review_ptr tmp_review = (review_ptr)review;
	if(review == NULL)
	{
		return ;
	}
	mtm_printCriticReview(outstream, tmp_review->reviewer_name, tmp_review->description );
	return;
}



void print_user_review(FILE* outstream,review_element* review)
{
	review_ptr tmp_review = (review_ptr)review;
	if(review == NULL)
	{
		return ;
	}
	mtm_printUserGrade(outstream, tmp_review->reviewer_name, tmp_review->grade);
	return;
}




/*
 * Name: match_by_reviewer_name
 *
 * Arguments:
 * review   	- 
 * key   		-
 *
 * Return value: 1 if review match the key, else 0
 *
 * Description: function that matches the compare
 *
 */
int match_by_reviewer_name(review_element* review, review_element* key)
{
	char* name1;
	char* name2;
	if(review == NULL || key == NULL)
	{
		return 0;
	}
	name1 = get_reviewer_name_from_review((review_ptr)review);
	name2 = get_reviewer_name_from_review((review_ptr)key);
	if(strcmp(name1, name2) == 0)
	{
		return 1;
	}
	return 0;
}
