#include <iostream>

#include "moviedatabase.h"

using std::cout;
using std::endl;

bool MovieDataBase::findMovie(const string &name, const int &year) 
{
	if(movies.empty())
	{
		cout << "The movie data-base is empty." << endl;
		return false;
	}

	movies.start();
	
	while(!movies.end()) {
		Movie **current = movies.getCurrent();
		if ((*current)->getName() == name && (*current)->getYear() == year) {
			return true;
		}
		movies.next();
	}
	cout << "The movie " << name << " from " << year 
		 << " is not in the data-base." << endl;
	return false;
}

bool MovieDataBase::addMovie(const string &name, const int &year, 
		const Genre &genre)
{
	Movie *movie = new Movie(name,year,genre);
	if(movie == NULL)
	{
		cout << "The movie " << name << " from " << year 
			 << " wasn't added to the data-base," 
			 << "due to memory problems" << endl;
		return false;
	}
	if(movies.add(movie))
	{
		cout << "The movie " << name << " from " << year 
			 << " was added to the data-base." << endl;
		return true;
	}
	else
	{
		delete movie;
		cout << "The Movie " << name << " from " << year 
			 << " is already in the data-base." << endl; 
		return false;
	}
}

bool MovieDataBase::removeMovie(const string &name, const int &year)
{
	if(this->findMovie(name,year))
	{
		Movie **movie = movies.getCurrent();
		movies.removeCurrent();
		delete *movie;
					
		cout << "The movie " << name << " from " << year 
			 << " was removed from the data-base." << endl;
		return true;
	}
	else
	{
		cout << "The movie " << name << " from " << year 
			 << " is not in the data-base." << endl;
		return false;
	}
}

bool MovieDataBase::addReview(const string &name, const int &year, 
		const Reviewer &reviewer, const string& review,const int &grade) 
{
	if(this->findMovie(name,year))
	{
		Movie **movie = movies.getCurrent();
		if((*movie)->addReview(reviewer,review,grade))
		{
			cout << "The review was added to the movie " << name 
				 << " from " << year << "." << endl;
			return true;
		}
		else
		{
			cout << "This review wasn't added to the movie " << name 
				 << " from " << year << " due to memory problems." << endl;
			return false;
		}
	}
	cout << "This review wasn't added to the movie " << name 
		<< " from " << year << " because the movie " 
		<< "isn't in the data-base." << endl;
	return false;
}

bool MovieDataBase::printReviews(const string &name, const int &year) 
{
	if(this->findMovie(name,year))
	{
		Movie **movie = movies.getCurrent();
		(*movie)->printReviews();
		return true;
	}
	cout << "The movie " << name << " from " << year 
		 << " isn't in the data-base." << endl;
	return false;
}

MovieDataBase::~MovieDataBase()
{
	movies.start();
	while(!movies.empty())
	{
		Movie **movie = movies.getCurrent();
		movies.removeCurrent();
        delete *movie;
	}
}
