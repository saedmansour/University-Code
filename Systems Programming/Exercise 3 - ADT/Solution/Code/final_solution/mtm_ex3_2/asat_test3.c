#include <stdio.h>
#include "moviedatabase.h"

void printError(int line, MDBResult result) {
	switch (result) {
	case MDB_SUCCESS:
		break;
	case MDB_INVALID_ARGUMENT:
		fprintf(stderr,"%d : Error--: invalid argument\n", line);
		break;
	case MDB_INVALID_YEAR:
		fprintf(stderr,"%d : Error--: invalid year\n", line);
		break;
	case MDB_INVALID_GENRE:
		fprintf(stderr,"%d : Error--: bad genre\n", line);
		break;
	case MDB_INVALID_REVIEWTYPE:
		fprintf(stderr,"%d : Error--: bad review type (not USER or CRITIC)\n", line);
		break;
	case MDB_INVALID_GRADE:
		fprintf(stderr,"%d : Error--: grade not between 1 to 10\n", line);
		break;
	case MDB_INVALID_AMOUNT:
		fprintf(stderr,"%d : Error--: invalid n\n", line);
		break;
	case MDB_MOVIE_DOESNT_EXIST:
		fprintf(stderr,"%d : Error--: movie doesn't exist\n", line);
		break;
	case MDB_MOVIE_ALREADY_EXISTS:
		fprintf(stderr,"%d : Error--: movie already exists\n", line);
		break;
	case MDB_REVIEWER_DOESNT_EXIST:
		fprintf(stderr,"%d : Error--: reviewer doesn't exist\n", line);
		break;
	case MDB_REVIEWER_ALREADY_EXISTS:
		fprintf(stderr,"%d : Error--: reviewer already exists\n", line);
		break;
	case MDB_REVIEW_DOESNT_EXIST:
		fprintf(stderr,"%d : Error--: review doesn't exist\n", line);
		break;
	case MDB_REVIEW_ALREADY_EXISTS:
		fprintf(stderr,"%d : Error--: review already exists\n", line);
		break;
	case MDB_NOTHING_TO_PRINT:
		fprintf(stderr,"%d : Error--: nothing to print\n", line);
		break;
	case MDB_OUT_OF_MEMORY:
		fprintf(stderr,"%d : Error--: out of memory\n", line);
		break;
	}
}


int main(int argc, char *argv[]) {
	MovieDatabase mdb = movieDatabaseCreate();

	// AddMovie - OK
	printError(__LINE__, movieDatabaseAddMovie(mdb, "Hello", 1999, "Thriller"));
	printError(__LINE__, movieDatabaseAddMovie(mdb, "Hello", 2999, "Thriller"));	
	printError(__LINE__, movieDatabaseAddMovie(mdb, "Hello", 199, "Thriller"));
	printError(__LINE__, movieDatabaseAddMovie(mdb, "hello", 1999, "Thriller"));	
	printError(__LINE__, movieDatabaseAddMovie(mdb, "Abc", 1999, "Thriller"));	
	printError(__LINE__, movieDatabaseAddMovie(mdb, "ABc", 1999, "Thriller"));	
	printError(__LINE__, movieDatabaseAddMovie(mdb, "zzzZ", 1999, "Thriller"));	
	printError(__LINE__, movieDatabaseAddMovie(mdb, "1", 1999, "Thriller"));	
	printError(__LINE__, movieDatabaseAddMovie(mdb, "", 1999, "Thriller"));	
	printError(__LINE__, movieDatabaseAddMovie(mdb, "Hello World", 1999, "Thriller")); //line 10

	// Add Reviewers - OK
	printError(__LINE__, movieDatabaseAddReviewer(mdb, CRITIC, "One"));
	printError(__LINE__, movieDatabaseAddReviewer(mdb, CRITIC, "Two"));
	printError(__LINE__, movieDatabaseAddReviewer(mdb, CRITIC, "one"));
	printError(__LINE__, movieDatabaseAddReviewer(mdb, USER, "2"));
	printError(__LINE__, movieDatabaseAddReviewer(mdb, USER, "One"));
	printError(__LINE__, movieDatabaseAddReviewer(mdb, USER, "Two"));
	printError(__LINE__, movieDatabaseAddReviewer(mdb, USER, ""));

	// Add Reviewers - Errors
	printError(__LINE__, movieDatabaseAddReviewer(mdb, CRITIC, "One"));
	printError(__LINE__, movieDatabaseAddReviewer(mdb, CRITIC, "two"));
	printError(__LINE__, movieDatabaseAddReviewer(mdb, 7, NULL)); //line 20
	printError(__LINE__, movieDatabaseAddReviewer(mdb, -1, "2"));
	printError(__LINE__, movieDatabaseAddReviewer(mdb, 16, "One"));
	printError(__LINE__, movieDatabaseAddReviewer(NULL, 22, NULL));
	printError(__LINE__, movieDatabaseAddReviewer(NULL, USER, ""));

	//Report
	printError(__LINE__, movieDatabaseReportMovieList(mdb,stdout));

	fprintf(stderr, " -------------------- 1 --------------------- \n");
	fprintf(stdout, " -------------------- 1 --------------------- \n");	



	// Add reviews
	printError(__LINE__, movieDatabaseAddUserReview(mdb, "Hello", 1999, "One", 9));
	printError(__LINE__, movieDatabaseAddUserReview(mdb, "Hello", 1999, "Two", 3));
	printError(__LINE__, movieDatabaseAddUserReview(mdb, "1", 1999, "", 5));
	printError(__LINE__, movieDatabaseAddCriticReview(mdb, "Hello", 1999, "One", "Baaaaad"));	
	printError(__LINE__, movieDatabaseAddCriticReview(mdb, "", 1999, "two", "Robert downy jr. rules!")); //line 30

	//set main
	printError(__LINE__, movieDatabaseSetMainReview(mdb, USER, "Hello", 1999, "One"));
	printError(__LINE__, movieDatabaseSetMainReview(mdb, CRITIC, "Hello", 1999, "One"));

	//Reports
	printError(__LINE__, movieDatabaseReportMovieList(mdb,stdout));

	printError(__LINE__, movieDatabaseReportRecentUsers(mdb, 7, "Hello", 1999, stdout));


	// Add reviews - Errors
	printError(__LINE__, movieDatabaseAddUserReview(NULL, "Hello", 1999, "One", 9));
	printError(__LINE__, movieDatabaseAddUserReview(mdb, NULL, 1999, "Two", 3));
	printError(__LINE__, movieDatabaseAddUserReview(mdb, "1", -1, "", 5));
	printError(__LINE__, movieDatabaseAddCriticReview(mdb, "Hello", 1999, NULL, "Baaaaad"));	
	printError(__LINE__, movieDatabaseAddCriticReview(mdb, "", 1999, "", NULL));
	printError(__LINE__, movieDatabaseAddUserReview(mdb, NULL, -1, "One", 9)); //line 40
	printError(__LINE__, movieDatabaseAddUserReview(NULL, "Hello", 0, "Two", 3));
	printError(__LINE__, movieDatabaseAddUserReview(mdb, "1", 0, "", 5));
	printError(__LINE__, movieDatabaseAddCriticReview(mdb, "",0, NULL, "Baaaaad"));	
	printError(__LINE__, movieDatabaseAddCriticReview(NULL, NULL, -15, NULL, NULL));
	printError(__LINE__, movieDatabaseAddUserReview(mdb, "Hello", 1999, "One", 9));
	printError(__LINE__, movieDatabaseAddUserReview(mdb, "Hello", 1999, "Two", 3));
	printError(__LINE__, movieDatabaseAddUserReview(mdb, "1", 1999, "", 5));
	printError(__LINE__, movieDatabaseAddCriticReview(mdb, "Hello", 1999, "One", "Baaaaad"));	
	printError(__LINE__, movieDatabaseAddCriticReview(mdb, "", 1999, "", "Robert downy jr. rules!"));
	printError(__LINE__, movieDatabaseAddCriticReview(mdb, "Hello", 1999, "", "Baaaaad"));	 //line 50
	printError(__LINE__, movieDatabaseAddCriticReview(mdb, "", 1999, "", "Robert downy jr. rules!"));

	fprintf(stderr, " -------------------- 2 --------------------- \n");
	fprintf(stdout, " -------------------- 2 --------------------- \n");	

	//Reports
	printError(__LINE__, movieDatabaseReportMovieList(mdb,stdout));
	printError(__LINE__, movieDatabaseReportRecentUsers(mdb, 7, "Hello", 1999, stdout));

	//set main review errors
	printError(__LINE__, movieDatabaseSetMainReview(mdb, USER, "Hello", 1999, "One1"));
	printError(__LINE__, movieDatabaseSetMainReview(mdb, CRITIC, "Hello", 1999, "99"));
	printError(__LINE__, movieDatabaseSetMainReview(mdb, USER, NULL, 1999, "One"));
	printError(__LINE__, movieDatabaseSetMainReview(NULL, 77, NULL, -5, NULL));
	printError(__LINE__, movieDatabaseSetMainReview(mdb, 42, "Hello", 1999, "One"));
	printError(__LINE__, movieDatabaseSetMainReview(mdb, CRITIC, "Hello", -3, "One"));
	printError(__LINE__, movieDatabaseSetMainReview(mdb, CRITIC, "Hello", 1999, "two")); //line 60

	//Reports
	printError(__LINE__, movieDatabaseReportMovieList(mdb,stdout));
	printError(__LINE__, movieDatabaseReportRecentUsers(mdb, 7, "Hello", 1999, stdout));

	//removeReviewers - errors
	printError(__LINE__, movieDatabaseRemoveReviewer(NULL, USER, "Javier"));
	printError(__LINE__, movieDatabaseRemoveReviewer(mdb, 7, "Omer"));
	printError(__LINE__, movieDatabaseRemoveReviewer(mdb, USER, NULL));
	printError(__LINE__, movieDatabaseRemoveReviewer(NULL, 22, NULL));

	//Reports
	printError(__LINE__, movieDatabaseReportMovieList(mdb,stdout));
	printError(__LINE__, movieDatabaseReportRecentUsers(mdb, 7, "Hello", 1999, stdout));

	//removeReviewers - OK
	printError(__LINE__, movieDatabaseRemoveReviewer(mdb, USER, "One"));
	printError(__LINE__, movieDatabaseRemoveReviewer(mdb, CRITIC, "One")); //line 70

	//Reports
	printError(__LINE__, movieDatabaseReportMovieList(mdb,stdout));
	printError(__LINE__, movieDatabaseReportRecentUsers(mdb, 7, "Hello", 1999, stdout));

	fprintf(stderr, " -------------------- 3 --------------------- \n");
	fprintf(stdout, " -------------------- 3 --------------------- \n");	


	//Remove Review - Errors
	printError(__LINE__, movieDatabaseRemoveReview(mdb, USER, "Hello", 1999, "One1"));
	printError(__LINE__, movieDatabaseRemoveReview(mdb, CRITIC, "Hello", 1999, "99"));
	printError(__LINE__, movieDatabaseRemoveReview(mdb, USER, "Hello", 1999, "One"));
	printError(__LINE__, movieDatabaseRemoveReview(mdb, CRITIC, "Hello", 1999, "One"));
	printError(__LINE__, movieDatabaseRemoveReview(NULL, USER, "Hello", 1999, "One"));
	printError(__LINE__, movieDatabaseRemoveReview(mdb, CRITIC, NULL, 1999, "One"));
	printError(__LINE__, movieDatabaseRemoveReview(mdb, USER, "Hello", -1, "One"));
	printError(__LINE__, movieDatabaseRemoveReview(mdb, CRITIC, "Hello", 1999, NULL)); //line 80
	printError(__LINE__, movieDatabaseRemoveReview(mdb, USER, "Hello", -7, NULL));
	printError(__LINE__, movieDatabaseRemoveReview(mdb, -5, "Hello", -7, "One"));

	//Reports
	printError(__LINE__, movieDatabaseReportMovieList(mdb,stdout));
	printError(__LINE__, movieDatabaseReportRecentUsers(mdb, 7, "Hello", 1999, stdout));

	//Remove Review - OK
	printError(__LINE__, movieDatabaseRemoveReview(mdb, USER, "Hello", 1999, "Two"));
	printError(__LINE__, movieDatabaseRemoveReview(mdb, CRITIC, "", 1999, "two"));
	printError(__LINE__, movieDatabaseRemoveReview(mdb, USER, "1", 1999, ""));

	//Reports
	printError(__LINE__, movieDatabaseReportMovieList(mdb,stdout));
	printError(__LINE__, movieDatabaseReportRecentUsers(mdb, 7, "Hello", 1999, stdout));

	movieDatabaseDestroy(mdb);
	return 0;
}


