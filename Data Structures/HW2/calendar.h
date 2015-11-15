#ifndef _CALENDAR_
#define _CALENDAR_

//========================================================================================
//	Includes
//========================================================================================

#include "hash.h"
#include "library2.h"


//========================================================================================
//	Calendar Class
//========================================================================================
//	This is the main class. Which implements the interface mentioned in the homework.
//	Documentation is found in library2.h
/// We implemented homework by using a Hash Table, in which every cell contains an AVL tree.


class Calendar
{
public:
	Calendar(): activeDay(NULL){}


	~Calendar(){}


	StatusType OpenDay(Date day)
	{
		if(daysHash.isExist(day)){
			return FAILURE;
		}
		daysHash.add(day);
		return SUCCESS;
	}


	StatusType  CloseDay(Date day)
	{
		if((! daysHash.isExist(day)) || !(daysHash.find(day)->isNoEvents())){
			return FAILURE;
		}
		if(activeDay == daysHash.find(day)){
			activeDay = NULL;
		}
		daysHash.remove(day);
		return SUCCESS;
	}


	StatusType  AddEvent(int eventID, Date day, Time timeStart, Time timeEnd)
	{
		if(!daysHash.isExist(day) || daysHash.find(day)->containsEvent(eventID)){
			return FAILURE;
		}
		daysHash.find(day)->AddEvent(eventID, timeStart, timeEnd);
		return SUCCESS;
	}


	StatusType  RemoveEvent(int eventID, Date day)
	{
		if(!daysHash.isExist(day) || !daysHash.find(day)->containsEvent(eventID)){
			return FAILURE;
		}
		daysHash.find(day)->removeEvent(eventID);
		return SUCCESS;
	}


	StatusType  NumberEvents(Date day, int* num)
	{
		if(!daysHash.isExist(day)){
			return FAILURE;
		}
		*num = daysHash.find(day)->getEventsNum();
		return SUCCESS;
	}


	StatusType  SetActiveDay(Date day)
	{
		if(!daysHash.isExist(day)){
			return FAILURE;
		}
		activeDay = daysHash.find(day);
		return SUCCESS;
	}


	StatusType  CurrDayNumEventsAtTime(Time t, int* num)
	{
		if(activeDay == NULL){
			return FAILURE;
		}
		*num = activeDay->NumEventsAtTime(t);
		return SUCCESS;
	}



private:
	HashTable daysHash;
	Data* activeDay;
};

#endif
