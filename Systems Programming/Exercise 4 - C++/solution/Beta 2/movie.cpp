#include "movie.h"


string genreToString(const Genre &genre)
{
	switch(genre) 
	{
		case COMEDY: return "COMEDY";
		case HORROR: return "HORROR";
		case THRILLER: return "THRILLER";
		case CLASIC: return "CLASIC";
		case WESTERN: return "WESTERN";
		case FICTION: return "FICTION";
		case CARTOON: return "CARTOON";
		case DRAMA: return "DRAMA";
		default: return "";
	}
}



string Movie::getName() const
{
	return name;
}



int Movie::getYear() const
{
	return year;
}


bool Movie::addReview(const Reviewer type, const string& description, const int grade)
{
	Review* review;
	
	if(type == CRITIC)
	{
		review = new criticReview(description, grade);
	}
	else
	{
		review = new userReview(description, grade);
	}
	if(review == NULL)
	{
		return false;
	}

	if(reviews.add(review))
	{
		return true;
	}	
	delete review;
	return false;
}



void Movie::printReviews() const
{
	reviews.printAll();
}



double Movie::calculateAverage() const
{
	node<Review*>* currentReview = NULL;
	int weight;
	int currentGrade;
	int sum = 0;
	int numberOfReviews = 0;


	for(currentReview = reviews.first; currentReview != NULL; currentReview = currentReview->next)
	{
		currentGrade = (currentReview->data)->getGrade(&weight);
		sum += currentGrade*(weight);
		numberOfReviews+= weight;
	}


	if(numberOfReviews != 0)
	{
		return (double)sum / numberOfReviews;
	}
	else
	{
		return 0;
	}
}


void Movie::print() const
{
	//print layout(without the double quotes): "Movie: <Movie Name> <Year> <Genre> <Average Grade>"
	cout << "Movie: " << name  << " " << year<< " "  
		 << genreToString(genreType) << " " << calculateAverage();
}


bool operator<(const Movie& leftMovie, const Movie& rightMovie)
{
	if(leftMovie.name < rightMovie.name)
	{
		return true;
	}
	if(leftMovie.name == rightMovie.name)
	{
		if(leftMovie.year > rightMovie.year)
		{
			return true;
		}
	}
	return false;
}


bool operator==(const Movie& leftMovie, const Movie& rightMovie)
{
	if(leftMovie.name == rightMovie.name &&
		leftMovie.year == rightMovie.year)
	{
		return true;
	}
	return false;
}


bool operator!=(const Movie& leftMovie, const Movie& rightMovie)
{
	if(leftMovie.name == rightMovie.name &&
		leftMovie.year == rightMovie.year&&
		leftMovie.reviews == rightMovie.reviews
		)
	{
		return false;
	}
	return true;
}


ostream& operator<<(ostream& out, const Movie* movie)
{
	(*movie).print();
	return out;
}

