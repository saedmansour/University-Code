#ifndef _MOVIEDATABASE_H
#define _MOVIEDATABASE_H

#include <stdio.h>

typedef struct MovieDatabase_t *MovieDatabase;

typedef enum ReviewType_t {
	USER, CRITIC
} ReviewType;

typedef enum MDBResult_t {
	MDB_SUCCESS,
	MDB_OUT_OF_MEMORY,
	MDB_INVALID_ARGUMENT,
	MDB_INVALID_YEAR,
	MDB_INVALID_GENRE,
	MDB_INVALID_REVIEWTYPE,
	MDB_INVALID_GRADE,
	MDB_INVALID_AMOUNT,
	MDB_MOVIE_DOESNT_EXIST,
	MDB_MOVIE_ALREADY_EXISTS,
	MDB_REVIEWER_DOESNT_EXIST,
	MDB_REVIEWER_ALREADY_EXISTS,
	MDB_REVIEW_DOESNT_EXIST,
	MDB_REVIEW_ALREADY_EXISTS,
	MDB_NOTHING_TO_PRINT
} MDBResult;

/*
 * MovieDatabaseCreate
 *
 *	Description:
 *		Creates a new empty movie database;
 *	Parameters:
 *		None
 *  Result:
 *		NULL - In case of memory allocation failure.
 *		A new MovieDatabase - In case of success.
 */
MovieDatabase movieDatabaseCreate();

/*
 * MovieDatabaseAddMovie
 *
 *	Description:
 *		Adds a new movie into the given database.
 *	Parameters:
 *		mdb - An existing movie database.
 *		name - The name of the movie to add.
 *		year - The year of making of the movie to add.
 *		genre - The name of the movie's genre.
 * Result:
 *		MDB_INVALID_ARGUMENT - If one of the arguments is NULL.
 *		MDB_INVALID_YEAR - IF the year is not greater than 0.
 *		MDB_INVALID_GENRE - The genre supplied is not valid.
 *		MDB_MOVIE_ALREADY_EXISTS - A movie with this name and year already exists.
 *		MDB_SUCCESS - The movie was added to the database.
 */
MDBResult movieDatabaseAddMovie(MovieDatabase mdb, const char* name, int year,
		const char* genre);
/*
 * movieDatabaseRemoveMovie
 *
 * Description:
 * 		Removes a movie from the given database.
 * Parameters:
 * 		mdb - An existing movie database.
 *		name - The name of the movie to remove.
 *		year - The year of making of the movie to remove.
 * Result:
 *		MDB_INVALID_ARGUMENT - If one of the arguments is NULL.
 *		MDB_INVALID_YEAR - IF the year is not greater than 0.
 * 		MDB_MOVIE_DOESNT_EXIST - The movie isn't in the database.
 * 		MDB_SUCCESS - The movie was removed from the database.
 */
MDBResult movieDatabaseRemoveMovie(MovieDatabase mdb, const char* name,
		int year);
/*
 * movieDatabaseAddReviewer
 *
 * Description:
 * 		Adds a user/critic to the given database.
 * Parameters:
 * 		mdb - An existing movie database.
 *		type - The type of the user to add: USER or CRITIC.
 *		name - The name of the user to add.
 * Result:
 * 		MDB_INVALID_ARGUMENT - One of the arguments is NULL or invalid.
 * 		MDB_INVALID_REVIEWTYPE - The review type is not USER or CRITIC.
 * 		MDB_REVIEWER_ALREADY_EXIST - A reviewer with the same name and type is
 * 									already in the database.
 * 		MDB_SUCCESS - The reviewer was removed from the database.
 */
MDBResult movieDatabaseAddReviewer(MovieDatabase mdb, ReviewType type,
		const char* name);

/*
 * movieDatabaseRemoveReviewer
 *
 * Description:
 * 		Removes a user/critic to the given database along with his reviews.
 * Parameters:
 * 		mdb - An existing movie database.
 *		type - The type of the user to remove: USER or CRITIC.
 *		name - The name of the user to remove.
 * Result:
 * 		MDB_INVALID_ARGUMENT - One of the arguments is NULL or invalid.
 * 		MDB_INVALID_REVIEWTYPE - The review type is not USER or CRITIC.
 * 		MDB_REVIEWER_DOESNT_EXIST - The reviewer isn't in the database.
 * 		MDB_SUCCESS - The reviewer was removed from the database, including all
 * 						of his reviews.
 */
MDBResult movieDatabaseRemoveReviewer(MovieDatabase mdb, ReviewType type,
		const char* name);
/*
 * movieDatabaseAddUserReview
 *
 * Description:
 * 		Adds a user review to the given database.
 * Parameters:
 * 		mdb - An existing movie database.
 *		movieName - The name of the movie.
 *		year - The year of making of the movie.
 *		name - The name of the user.
 *		grade - Grade given by the user to the movie.
 * Result:
 *		MDB_INVALID_ARGUMENT - If one of the arguments is NULL.
 *		MDB_INVALID_YEAR - If the year is not greater than 0.
 *		MDB_INVALID_GRADE - If the grade isn't between 1 to 10.
 * 		MDB_MOVIE_DOESNT_EXIST - The movie isn't in the database.
 * 		MDB_REVIEWER_DOESNT_EXIST - The user isn't registered in the database.
 * 		MDB_REVIEW_ALREADY_EXIST - The user has already reviewed the movie.
 * 		MDB_SUCCESS - The user's review was added to the database.
 */
MDBResult movieDatabaseAddUserReview(MovieDatabase mdb, const char* movieName,
		int year, const char* name, int grade);

/*
 * movieDatabaseAddCriticReview
 *
 * Description:
 * 		Adds a critic's to the given database.
 * Parameters:
 * 		mdb - An existing movie database.
 *		movieName - The name of the movie.
 *		year - The year of making of the movie.
 *		name - The name of the critic.
 *		review - The text of the review.
 * Result:
 *		MDB_INVALID_ARGUMENT - If one of the arguments is NULL.
 *		MDB_INVALID_YEAR - IF the year is not greater than 0.
 * 		MDB_MOVIE_DOESNT_EXIST - The movie isn't in the database.
 * 		MDB_REVIEWER_DOESNT_EXIST - The critic isn't registered in the database.
 * 		MDB_REVIEW_ALREADY_EXIST - The critic has already reviewed the movie.
 * 		MDB_SUCCESS - The critic's review was added to the database.
 */
MDBResult movieDatabaseAddCriticReview(MovieDatabase mdb,
		const char* movieName, int year, const char* name, const char* review);
/*
 * movieDatabaseRemoveReview
 *
 * Description:
 * 		Removes a review from the given database.
 * Parameters:
 * 		mdb - An existing movie database.
 * 		type - The type of the review: USER or CRITIC.
 *		movieName - The name of the movie.
 *		year - The year of making of the movie.
 *		name - The name of the user/critic.
 * Result:
 *		MDB_INVALID_ARGUMENT - If one of the arguments is NULL.
 *		MDB_INVALID_YEAR - IF the year is not greater than 0.
 * 		MDB_INVALID_REVIEWTYPE - The review type is not USER or CRITIC.
 * 		MDB_MOVIE_DOESNT_EXIST - The movie isn't in the database.
 * 		MDB_REVIEWER_DOESNT_EXIST - The user/critic isn't registered in the database.
 * 		MDB_REVIEW_DOESNT_EXIST - The review doesn't exist in the database.
 * 		MDB_SUCCESS - The review was removed from the database.
 */
MDBResult movieDatabaseRemoveReview(MovieDatabase mdb, ReviewType type,
		const char* movieName, int year, const char* name);

/*
 * movieDatabaseSetMainReview
 *
 * Description:
 * 		Set a movie's main review in the given database.
 * Parameters:
 * 		mdb - An existing movie database.
 * 		type - The type of the review: USER or CRITIC.
 *		movieName - The name of the movie.
 *		year - The year of making of the movie.
 *		name - The name of the user/critic.
 * Result:
 *		MDB_INVALID_ARGUMENT - If one of the arguments is NULL.
 *		MDB_INVALID_YEAR - IF the year is not greater than 0.
 * 		MDB_INVALID_REVIEWTYPE - The review type is not USER or CRITIC.
 * 		MDB_MOVIE_DOESNT_EXIST - The movie isn't in the database.
 * 		MDB_REVIEWER_DOESNT_EXIST - The user/critic isn't registered in the database.
 * 		MDB_REVIEW_DOESNT_EXIST - The review doesn't exist in the database.
 * 		MDB_SUCCESS - The review was set as main review.
 */
MDBResult movieDatabaseSetMainReview(MovieDatabase mdb, ReviewType type,
		const char* movieName, int year, const char* name);

/*
 * movieDatabaseReportMovieList
 *
 * Description:
 * 		Prints all the movies in the database to the given channel,
 * 		sorted first lexicographically and by year secondary.
 * Parameters:
 * 		mdb - An existing movie database.
 * 		stream - An output stream to print the data to.
 * Result:
 * 		MDB_INVALID_ARGUMENT - One of the arguments is NULL or invalid.
 * 		MDB_NOTHING_TO_PRINT - If there are no movies in the database.
 * 		MDB_SUCCESS - The movies were printed successfully.
 */
MDBResult movieDatabaseReportMovieList(MovieDatabase mdb, FILE* stream);

/*
 * movieDatabaseReportMeanUsers
 *
 * Description:
 * 		Prints the worst n grades given to target movie,
 * 		sorted by grade and by the user's name.
 * Parameters:
 * 		mdb - An existing movie database.
 * 		n - Number of reviews to print.
 * 		movieName - Name of the movie to print its reviews.
 * 		year - Year of the movie to print its reviews.
 * 		stream - An output stream to print the data to.
 * Result:
 *		MDB_INVALID_ARGUMENT - If one of the arguments is NULL.
 *		MDB_INVALID_YEAR - If the year is not greater than 0.
 *		MDB_INVALID_AMOUNT - If n isn't greater than 0.
 * 		MDB_MOVIE_DOESNT_EXIST - The movie isn't in the database.
 * 		MDB_NOTHING_TO_PRINT - If there are no reviews to print.
 * 		MDB_SUCCESS - The reviews were printed successfully.
 */
MDBResult movieDatabaseReportMeanUsers(MovieDatabase mdb, int n,
		const char* movieName, int year, FILE* stream);

/*
 * movieDatabaseReportCriticMovies
 *
 * Description:
 * 		Prints all movies reviewed by target critic, with his review.
 * Parameters:
 * 		mdb - An existing movie database.
 *		name - The name of the critic to print his reviews.
 * 		stream - An output stream to print the data to.
 * Result:
 * 		MDB_INVALID_ARGUMENT - One of the arguments is NULL or invalid.
 * 		MDB_REVIEWER_DOESNT_EXIST - The movie isn't in the database.
 * 		MDB_NOTHING_TO_PRINT - If there are no reviews to print.
 * 		MDB_SUCCESS - The movies were printed successfully.
 */
MDBResult movieDatabaseReportCriticMovies(MovieDatabase mdb, const char* name,
		FILE* stream);

/*
 * movieDatabaseReportRecentCritics
 *
 * Description:
 * 		Prints the n most recent critic reviews of a movie.
 * 		Format is "critic review".
 * 		Ordered chronologically (newer first).
 * Parameters:
 * 		mdb - An existing movie database.
 * 		movieName - The name of the movie print its reviews.
 * 		year - Year of the movie to print its reviews.
 * 		n - The number of reviews to print.
 * 		stream - An output stream to print the data to.
 * Result:
 *		MDB_INVALID_ARGUMENT - If one of the arguments is NULL.
 *		MDB_INVALID_YEAR - If the year is not greater than 0.
 *		MDB_INVALID_AMOUNT - If n isn't greater than 0.
 * 		MDB_MOVIE_DOESNT_EXIST - The movie isn't in the database.
 * 		MDB_NOTHING_TO_PRINT - If there are no reviews to print.
 * 		MDB_SUCCESS - The movies were printed successfully.
 */
MDBResult movieDatabaseReportRecentCritics(MovieDatabase mdb, int n,
		const char* movieName, int year, FILE* stream);

/*
 * movieDatabaseReportRecentUsers
 *
 * Description:
 * 		Prints the n most recent user reviews of a movie.
 * 		Format is "critic grade".
 * 		Ordered chronologically (newer first).
 * Parameters:
 * 		mdb - An existing movie database.
 * 		movieName - The name of the movie print its reviews.
 * 		year - Year of the movie to print its reviews.
 * 		n - The number of reviews to print.
 * 		stream - An output stream to print the data to.
 * Result:
 *		MDB_INVALID_ARGUMENT - If one of the arguments is NULL.
 *		MDB_INVALID_YEAR - If the year is not greater than 0.
 *		MDB_INVALID_AMOUNT - If n isn't greater than 0.
 * 		MDB_MOVIE_DOESNT_EXIST - The movie isn't in the database.
 * 		MDB_NOTHING_TO_PRINT - If there are no reviews to print.
 * 		MDB_SUCCESS - The movies were printed successfully.
 */
MDBResult movieDatabaseReportRecentUsers(MovieDatabase mdb, int n,
		const char* movieName, int year, FILE* stream);

/*
 * movieDatabaseDestroy
 */
void movieDatabaseDestroy(MovieDatabase mdb);

#endif
