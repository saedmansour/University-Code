/*

	Notation:
		Commenting style: xml tags
		Identifiers: underscores and lowercase
		Macros: uppercase
	
	Comments:
		XML Tags (common ones):
			Attributes: action, info, note, type
			Tags: linked_list, initialize, memory_allocation, error_check, set_values, fields
	Linked list conclusions:
		-When iterating or checking a linked list, differentiate between three cases:
			first, middle, last node
		-Use dummy node at the start and at the end of the list
		-There isn't always a need for double linked list, use of dummy nodes helps
		-Delete current in lists. it has no use

	-To implement:
		-free things
*/


//**** NOT DONE: FREEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE!


#include <stdlib.h>
#include <stdio.h>
#include "mtm_ex2.h"
#include "movie_handling.h"

int main()
{
	//<test>
	FILE* out = stdout ;
	ptr_movie temp;
	ptr_review temp_review;
	
	ptr_movies_list movies_list;
	movies_list = (ptr_movies_list) malloc(sizeof(struct movies_list));
	movies_list->first = NULL;
	movies_list->last = NULL;
	
	/************************************************************/
	/************************************************************/
	//Test 3
	

	
	add_movie(movies_list,"Vandetta", 1999, "Fiction");
	add_movie(movies_list,"V_for_Vandetta", 2005, "Fiction");
	add_movie(movies_list,"Vandetta", 1976, "Fiction");
	//fail adding a review:
	add_review(movies_list, "Vandetta", 1999,"Major_Tim", "freaky","NotUserNotCritic");
	add_review(movies_list, "Vandetta", 1999,"Major_Tim", "boring","Critic");
	add_review(movies_list, "Vandetta", 1999,"King_of_Spain", "4","User");
	add_review(movies_list, "Vandetta", 1999,"Aing_of_Spain", "4","User");
	add_review(movies_list, "Vandetta", 1999,"Agent_Smith", "1","User");
	add_review(movies_list, "Vandetta", 1999,"Queen_Elizabeth", "9","User");
	add_review(movies_list, "V_for_Vandetta", 2005,"Major_Tim", "7","User");
	add_review(movies_list, "V_for_Vandetta", 2005,"Queen_Elizabeth", "stupid_actors","Critic");
	add_review(movies_list, "V_for_Vandetta", 2005,"Major_Tim", "i_hated_it","Critic");
	add_review(movies_list, "V_for_Vandetta", 2005,"King_of_Spain", "10","User");
	add_review(movies_list, "Vandetta", 1976,"King_of_Spain", "pretty_lame","Critic");
	add_review(movies_list, "Vandetta", 1976,"Queen_Elizabeth", "5","User");
	add_review(movies_list, "Vandetta", 1976,"Cat_in_the_Hat", "9","User");
	add_review(movies_list, "Vandetta", 1976,"Einstein", "2","User");
	
	report_meanUsres(movies_list, 4,"Vandetta",1999 ,out);

	report_movieList(movies_list, out);





	
	
	/*
	// TEST 2
	add_movie(movies_list,"The_Matrix", 1999, "Fiction");
	add_movie(movies_list,"Se7en", 1995, "Drama");
	add_movie(movies_list,"Fight_Club", 1999, "Thriller");
	add_movie(movies_list,"Eternal_Sunshine_of_the_Spotless_Mind", 2004, "Drama");
	//fail adding a movie:
	add_movie(movies_list,"NoGenreMovie", 2008, NULL);

	add_review(movies_list, "The_Matrix", 1999,"Major_Tim", "Great","Critic");
	add_review(movies_list, "The_Matrix", 1999,"King_of_Spain", "cool","Critic");
	add_review(movies_list, "The_Matrix", 1999,"Queen_Elizabeth", "didnt_like_it","Critic");
	add_review(movies_list, "Eternal_Sunshine_of_the_Spotless_Mind", 2004,"Major_Tim", "poor_acting","Critic");
	add_review(movies_list, "Eternal_Sunshine_of_the_Spotless_Mind", 2004,"Queen_Elizabeth", "stupid_story","Critic");
	add_review(movies_list, "Se7en", 1995,"Major_Tim", "i_liked_it","Critic");
	add_review(movies_list, "Se7en", 1995,"King_of_Spain", "not_bad","Critic");
	add_review(movies_list, "Fight_Club", 1999,"King_of_Spain", "pretty_cool","Critic");
	add_review(movies_list, "Fight_Club", 1999,"Queen_Elizabeth", "barely_watchable","Critic");


	report_criticMovies(movies_list, "Major_Tim", out);
	report_criticMovies(movies_list, "King_of_Spain", out);
	report_criticMovies(movies_list, "Queen_Elizabeth", out);
	//fail to report
	report_criticMovies(movies_list, "Queen_Ninet", out);




	//test 1
	add_movie(movies_list,"Fight_Club", 1999, "Fiction");
	add_movie(movies_list,"Eternal_Sunshine_of_the_Spotless_Mind", 2004, "Drama");
	// fail adding a movie:
	add_movie(movies_list,"PreHistoric", -123, "General");
	//add some reviews:
	add_review(movies_list, "Fight_Club", 1999,"Nitza", "2","User");
	add_review(movies_list, "Fight_Club", 1999, "Dina", "3","User");
	add_review(movies_list, "Fight_Club", 1999, "Mira", "1","User");
	add_review(movies_list, "Fight_Club", 1999, "Ofra", "2","User");
	add_review(movies_list, "Fight_Club", 1999, "Ofer", "9","User");
	add_review(movies_list, "Fight_Club", 1999, "Aharon", "10","User");
	add_review(movies_list, "Fight_Club", 1999, "Eyal", "10","User");
	add_review(movies_list, "Eternal_Sunshine_of_the_Spotless_Mind", 2004, "Maya", "7","User");
	add_review(movies_list, "Eternal_Sunshine_of_the_Spotless_Mind", 2004, "Dina", "8","User");
	add_review(movies_list, "Eternal_Sunshine_of_the_Spotless_Mind", 2004, "Ofra", "9","User");
	add_review(movies_list, "Eternal_Sunshine_of_the_Spotless_Mind", 2004, "Kfir", "1","User");
	add_review(movies_list, "Eternal_Sunshine_of_the_Spotless_Mind", 2004, "Nahum", "1","User");

	add_review(movies_list, "Fight_Club", 1999,"Nitza", "Baaad","Critic");
	add_review(movies_list, "Fight_Club", 1999, "Dina", "Baaad","Critic");
	add_review(movies_list, "Fight_Club", 1999, "Mira", "Baaad","Critic");
	add_review(movies_list, "Fight_Club", 1999, "Ofra", "Gooood","Critic");
	add_review(movies_list, "Fight_Club", 1999, "Ofer", "Baaad","Critic");
	add_review(movies_list, "Fight_Club", 1999, "Aharon", "Baaad","Critic");
	add_review(movies_list, "Fight_Club", 1999, "Eyal", "Baaad","User");
	add_review(movies_list, "Eternal_Sunshine_of_the_Spotless_Mind", 2004, "Maya", "Baaad","Critic");
	add_review(movies_list, "Eternal_Sunshine_of_the_Spotless_Mind", 2004, "Dina", "Baaad","Critic");
	add_review(movies_list, "Eternal_Sunshine_of_the_Spotless_Mind", 2004, "Ofra", "Baaad","Critic");
	add_review(movies_list, "Eternal_Sunshine_of_the_Spotless_Mind", 2004, "Kfir", "Baaad","Critic");
	add_review(movies_list, "Eternal_Sunshine_of_the_Spotless_Mind", 2004, "Nahum", "Baaad","Critic");
	
	printf("**********************************************\n");
	printf("Start Testing report_meanUsres for Fight_Club\n");
	printf("**********************************************\n");

	report_meanUsres(movies_list, 3,"Fight_Club",1999 ,out);
	printf("**********************************************\n");
	report_meanUsres(movies_list, 10,"Fight_Club",100 ,out);
	printf("**********************************************\n");
	report_meanUsres(movies_list, 5,"staam",1999 ,out);
	printf("**********************************************\n");
	report_meanUsres(movies_list, 2,"Fight_Club",1999 ,out);
	printf("**********************************************\n");
	report_meanUsres(movies_list, 100,"Fight_Club",1999 ,out);
	printf("**********************************************\n");

	printf("**********************************************\n");
	printf("Start Testing report_meanUsres for eeeeee\n");
	printf("**********************************************\n");

	report_meanUsres(movies_list, 3,"Eternal_Sunsh_of_the_Spotless_Mind",2004 ,out);
	printf("**********************************************\n");
	report_meanUsres(movies_list, 3,"Eternal_Sunshine_of_the_Spotless_Mind",2004 ,out);
	printf("**********************************************\n");
	report_meanUsres(movies_list, 5,"Eternal_Sunshine_of_the_Spotless_Mind",2004 ,out);
	printf("**********************************************\n");
	report_meanUsres(NULL, 27,"Eternal_Sunshine_of_the_Spotless_Mind",2004 ,out);
	printf("**********************************************\n");
	report_meanUsres(movies_list, 100,"Eternal_Sunshine_of_the_Spotless_Mind",2004 ,out);
	printf("**********************************************\n");



	printf("Start Testing report_movieList\n");
	report_movieList(movies_list, out);
	printf("**********************************************\n");
	printf("Start Testing report_meanUsres for Fight_Club\n");
	printf("**********************************************\n");
	report_meanUsres(movies_list, 20,"Fight_Club",1999 ,out);
	printf("******* Test must faild for not founding the movie\n");
	report_meanUsres(movies_list, 2,"Fight_Club",2000 ,out);

	printf("**********************************************\n");
	printf("Start Testing report_criticMovies for \n");
	printf("**********************************************\n");
	report_criticMovies(movies_list, "Ofra", out);
	/************************************************************/
	/************************************************************/
	/*
	add_movie(movies_list, "Xx", 2000, "Drama");
	add_movie(movies_list, "Amelie", 2000, "Drama");
	add_movie(movies_list, "The_Prestige", 2000, "Drama");
	add_movie(movies_list, "XMEN", 2000, "Drama");
	add_movie(movies_list, "Leon", 2000, "Drama");
	add_review(movies_list, "Leon", 2000, "Caed_Mansour", "10", "User");
	add_review(movies_list, "Leon", 2000, "AaeD_Mansour", "10", "User");
	add_review(movies_list, "Leon", 2000, "AaeD_Mansoureee", "10", "User");
	add_review(movies_list, "Leon", 2000, "AaeD_Mansourrrr", "6", "User");
	add_review(movies_list, "Leon", 2000, "AaeD_Mansourttt", "2", "User");
	temp = get_movie(movies_list, "Leon", 2000);
	remove_review(temp->users_list, temp, "Caed_Mansour", "User");
	set_main_review(temp->users_list, temp, "AaeD_Mansour", "User");

	temp = movies_list->first;
	while(temp != NULL)
	{
		printf("%s\n", temp->name);
		temp = temp->next;
	}

	temp = get_movie(movies_list, "Fight_Club", 1999);
	temp_review = temp->users_list->first;
	while(temp_review != NULL)
	{
		printf("%s\n", temp_review->reviewer_name);
		temp_review = temp_review->next;
	}
	
	//</test>
	*/
	free(movies_list);
	return EXIT_SUCCESS;
}



/************************************************************
Bugs :

-check describtion_word in critic review
-check errors order 
-update average grade
-Add/Remove main critic not implemented
-run test 3 with add main critic

***********************************************************/




