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

