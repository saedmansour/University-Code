#ifndef REVIEWER_H
#define REVIEWER_H




//--Includes------------------------------------------------------
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "moviedatabase.h"
//----------------------------------------------------------------




//--Typedefs------------------------------------------------------
//<enum info="return values of reviewer functions">
typedef enum 
{
  REVIEWER_SUCCESS,
  REVIEWER_FAIL,
  REVIEWER_BAD_ARGUMENTS,
  REVIEWER_OUT_OF_MEMORY
} reviewer_result;
//<enum>

typedef void* reviewer_elem;
typedef struct reviewer_rec* reviewer_ptr;
//----------------------------------------------------------------





//<parameters_functions action="get reviewer parameters">
ReviewType get_reviewer_type(reviewer_ptr reviewer);
char* get_reviewer_name(reviewer_ptr reviewer);
//<parameters_functions>



/*
 * Name: match_reviewer
 *
 * Description: match function, used with linkedListFind
 *
 * Arguments:
 * reviewer			- a reviewer element (from the reviewers set)
 * reviewer_to_find	- a reviewer (not necessarily in the set) to be matched with
 *
 * Return value: returns MATCH if reviewer matches to reviewer_to_find
 *
 */
int match_reviewer(reviewer_elem reviewer, reviewer_elem reviewer_to_find);



/*
 * Name: create_reviewer
 *
 * Description: 
 *
 * Arguments:
 * name			- the reviewer's name
 * type			- USER/CRITIC
 *
 * Return value: the created reviewer
 *
 */
reviewer_ptr create_reviewer(const char* name, ReviewType type);



/*
* Name: free_reviewer
*
* Description: frees the reviewer from the reviewer's set.
*
* Arguments:
*	
reviewer		
* 
*
* Return value: none
*
*/
void free_reviewer(reviewer_elem reviewer);




/*
 * Name: copy_reviewer
 *
 * Description: copies the reviewer by creating a new one and returning it
 *
 * Arguments:
 *	reviewer		- the reviewer to be copied
 *
 * Return value: a copy of the reviewer
 *
 */
reviewer_elem copy_reviewer(reviewer_elem reviewer);



/*
 * Name: print_reviewer
 *
 * Description: prints data of the reviewer
 *
 * Arguments:
 *	outstream
 *	reviewer
 *
 * Return value: none
 *
 */
void print_reviewer(FILE* outstream, reviewer_elem reviewer);



/*
 * Name: compare_reviewer
 *
 * Description: compares two reviewers, to find their order when sorted
 *				 
 *
 * Arguments:
 *	reviewer1
 *	reviewer2
 *
 * Return value: positive if reviewer1 is greater than reviewer2(lexicographically),
 *				 negative if the opposite. Zero if they share the same name.
 *				 note: it doesn't distinguish between USER/CRITIC. It must be used
 *				 only with a list of the same kind of reviewers.
 *
 */
int compare_reviewer(reviewer_elem reviewer1, reviewer_elem reviewer2);

#endif // #ifndef REVIEWER_H




