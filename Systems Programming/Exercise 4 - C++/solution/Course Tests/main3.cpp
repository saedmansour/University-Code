#include <iostream>

#include "moviedatabase.h"

using std::cout;
using std::endl;

int main()
{
	MovieDataBase MDB1;

	MDB1.addMovie("Shrek",2001,CARTOON);
	MDB1.addMovie("Shrek",2001,CARTOON);
	MDB1.addMovie("Harold and koomar 2",2008,COMEDY);
	MDB1.addMovie("Harold and koomar 1",2004,COMEDY);
	MDB1.addMovie("Harold and koomar 3",2010,COMEDY);
	MDB1.addMovie("TITANIC",1999,DRAMA);

	MDB1.removeMovie("Shrek",2001);
	
	MDB1.addReview("Shrek",2001,USER,"Great Movie!", 10);
	MDB1.addReview("Shrek",2001,CRITIC,"Great supporting role by Eddie murphy", 9);
	MDB1.addReview("Shrek",2001,USER,"I've seen better", 6);
	MDB1.addReview("Shrek",2001,CRITIC,"Funny but predictable", 7);
	MDB1.addReview("Harold and koomar 1",2004,USER,"LOOOOOOOOOOOL", 9);
	MDB1.addReview("Harold and koomar 1",2004,CRITIC,"Worth every dollar!", 8);
	MDB1.addReview("Harold and koomar 1",2004,USER,"jus't if you're really bored.", 5);
	MDB1.addReview("Harold and koomar 1",2004,CRITIC,"Fantastic connection between the two leading actors.", 7);
	MDB1.addReview("Harold and koomar 2",2008,USER,"booooooring", 2);
	MDB1.addReview("Harold and koomar 2",2008,CRITIC,"Sweet, funnt, inteligent...", 8);
	MDB1.addReview("Harold and koomar 2",2008,USER,"Don't go there!", 4);
	MDB1.addReview("Harold and koomar 2",2008,CRITIC,"Even Bubba Ho-tep is better", 5);
	MDB1.addReview("TITANIC",1999,USER,"Yey, jack is dead", 1);
	MDB1.addReview("TITANIC",1999,CRITIC,"The romantic movie of the year", 8);
	MDB1.addReview("TITANIC",1999,USER,"Too girly", 6);
	MDB1.addReview("TITANIC",1999,CRITIC,"A best movie nominee for sure", 9);
	MDB1.addReview("Harold and koomar 3",2010,USER,"The best movie ever", 10);
	MDB1.addReview("Harold and koomar 3",2010,CRITIC,"Great performance by Kal Penn", 8);
	MDB1.addReview("Harold and koomar 3",2010,USER,"so lame!", 1);
	MDB1.addReview("Harold and koomar 3",2010,CRITIC,"Stay at home!", 1);

	MDB1.printMovies();
	MDB1.printReviews("Shrek",2001);
	MDB1.printReviews("Harold and koomar 1",2004);
	MDB1.printReviews("Harold and koomar 2",2008);
	MDB1.printReviews("TITANIC",1999);
	MDB1.printReviews("Harold and koomar 3",2010);

	return 0;
}

