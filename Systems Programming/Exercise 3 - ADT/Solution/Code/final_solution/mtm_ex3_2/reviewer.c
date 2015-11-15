//--Includes------------------------------------------------------
#include "reviewer.h"
//----------------------------------------------------------------




//--Constants-----------------------------------------------------
#define GREATER 1
#define LESSER -1
//----------------------------------------------------------------





//--Structures----------------------------------------------------
struct reviewer_rec
{
	char* name;
	ReviewType type;
};
//----------------------------------------------------------------





//--Functions-----------------------------------------------------
char* get_reviewer_name(reviewer_ptr reviewer)
{
	return reviewer->name;
}


int match_reviewer(reviewer_elem reviewer, reviewer_elem reviewer_to_find)
{
	reviewer_ptr tmp_reviewer_to_find = (reviewer_ptr)reviewer_to_find;
	reviewer_ptr tmp_reviewer = (reviewer_ptr)reviewer;
	/*
	if(reviewer == NULL || reviewer_to_find == NULL)
	{
		return 0;
	}
	*/
	if(strcmp(tmp_reviewer->name ,tmp_reviewer_to_find->name ) == 0)
	{
		if(tmp_reviewer->type == tmp_reviewer_to_find->type)
		{
			return 1;
		}
	}
	return 0;
}


reviewer_ptr create_reviewer(const char* name, ReviewType type)
{
	reviewer_ptr reviewer;

	reviewer = (reviewer_ptr)malloc(sizeof(struct reviewer_rec));
	if(reviewer == NULL)
	{
		return NULL;
	}
	if(name == NULL)
	{
		reviewer->name = (char*)malloc(sizeof(char) * 1);
	}
	else
	{
		reviewer->name = (char*)malloc(sizeof(char) * (strlen(name)+1));
	}
	
	if(reviewer->name == NULL)
	{
		free(reviewer);
		return NULL;
	}
	reviewer->type = type;
	if(name == NULL)
	{
		reviewer->name = NULL;
	}
	else
	{
		strcpy(reviewer->name, name);
	}
	reviewer->type = type;
	return reviewer;
}



void free_reviewer(reviewer_elem reviewer)
{
	reviewer_ptr tmp_reviewer = (reviewer_ptr)reviewer;
	if(tmp_reviewer == NULL)
	{
		return;
	}
	if(tmp_reviewer->name != NULL)
	{
		free(tmp_reviewer->name);
	}
	free(tmp_reviewer);
	return;
}


reviewer_elem copy_reviewer(reviewer_elem reviewer)
{
	reviewer_ptr new_reviewer;
	reviewer_ptr tmp_reviewer = (reviewer_ptr)reviewer;
	if(tmp_reviewer == NULL)
	{
		return NULL;
	}
	new_reviewer = (reviewer_ptr)malloc(sizeof(struct reviewer_rec));
	if(new_reviewer == NULL)
	{
		return NULL;
	}
	new_reviewer->name = (char*)malloc(strlen(tmp_reviewer->name)+1);
	if(new_reviewer->name == NULL)
	{
		free(new_reviewer);
		return NULL;
	}
	new_reviewer->type = tmp_reviewer->type;
	strcpy(new_reviewer->name, tmp_reviewer->name);
	new_reviewer->type = tmp_reviewer->type;
	return new_reviewer;
}



// used for set create only
void print_reviewer(FILE* outstream, void* reviewer)
{
	return ;
}


//Compare function, returns 0 if reviewers match by name and type
//otherwise return value not 0(doesn't matter)
int compare_reviewer(reviewer_elem reviewer1_temp, reviewer_elem reviewer2_temp)
{
	reviewer_ptr reviewer1 = (reviewer_ptr)reviewer1_temp;
	reviewer_ptr reviewer2 = (reviewer_ptr)reviewer2_temp;
	//we only need the comparison to know if equal or not, there is no meaning for
	//greater or lesser than here		
	return !((strcmp(reviewer1->name, reviewer2->name) == 0) && (reviewer1->type == reviewer2->type));
}
//----------------------------------------------------------------
