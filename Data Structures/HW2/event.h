#ifndef _EVENT_
#define _EVENT_


//========================================================================================
//	Includes
//========================================================================================

#include "library2.h"



//========================================================================================
//	Event Class
//========================================================================================
// Event Class is used in the calendar to add events to days.

class Event
{
public:
	Event( int idEvent,Time startTime ,Time endTime):startTime(startTime),endTime(endTime),
			idEvent(idEvent){}
	Event( ){}
	
	Time getStartTime()
	{
		return startTime;
	}
	Time getEndTime()
	{
		return endTime;
	}
	int getId()
	{
		return idEvent;
	}
private:
	Time startTime;
	Time endTime;
	int idEvent;

};

#endif
