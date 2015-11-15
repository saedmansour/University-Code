#include <iostream>

#include "moviedatabase.h"

using std::cout;
using std::endl;

int main()
{
	MovieDataBase MDB1;
	MovieDataBase MDB2;

	MDB1.addMovie("Shrek",2001,CARTOON);
	MDB2.addMovie("Shrek",2001,CARTOON);
	
	MDB1.addMovie("Harold and koomar 2",2008,COMEDY);
	MDB2.addMovie("Harold and koomar 2",2008,COMEDY);

	MDB1.addMovie("Harold and koomar 1",2004,COMEDY);
	MDB2.addMovie("Harold and koomar 1",2004,COMEDY);

	MDB1.printMovies();
	MDB2.printMovies();

	MDB1.addReview("Harold and koomar 2",2008,USER,"Great Movie!", 9);
	MDB2.addReview("Harold and koomar 2",2008,USER,"Great Movie!", 9);

	MDB1.addReview("Harold and koomar 1",2004,CRITIC,"Poor acting!", 3);
	MDB2.addReview("Harold and koomar 1",2004,CRITIC,"Poor acting!", 3);

	MDB1.addReview("Shrek",2001,USER,"lol!", 8);
	MDB2.addReview("Shrek",2001,USER,"lol!", 8);

	MDB1.addReview("Shrek",2001,CRITIC,"Excelent animation.", 9);
	MDB2.addReview("Shrek",2001,CRITIC,"Excelent animation.", 9);

	MDB2.printReviews("Shrek",2001);

	if(MDB1 == MDB2)
		cout << "The data-bases are equal." << endl;
	else
		cout << "The data-bases aren't equal." << endl;

	MDB2.addReview("Shrek",2001,CRITIC,"Excelent sounds.", 10);

	if(MDB1 == MDB2)
		cout << "The data-bases are equal." << endl;
	else
		cout << "The data-bases aren't equal." << endl;

	MDB1.printMovies();
	MDB2.printMovies();

	return 0;
}

