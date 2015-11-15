//========================================================================================
//	Includes
//========================================================================================
#include "library2.h"
#include "calendar.h"
#include <stdlib.h>	



//========================================================================================
//	Comparison Operators
//========================================================================================


//-----------------------------------------------------
//	Time Comparison Operators
//-----------------------------------------------------

bool operator<(const Time& leftTime, const Time& rightTime)
{
	if(leftTime.hour == rightTime.hour)
	{
		return leftTime.minutes < rightTime.minutes;
	}
	return leftTime.hour < rightTime.hour;
}
bool operator>=(const Time& leftTime, const Time& rightTime)
{
	return !(leftTime < rightTime);
}
bool operator==(const Time& leftTime, const Time& rightTime)
{
	if(leftTime.minutes == rightTime.minutes && 
		leftTime.hour == rightTime.hour) {
			return true;
	}
	return false;
}
bool operator>(const Time& leftTime, const Time& rightTime)
{
	return rightTime < leftTime;
}
bool operator<=(const Time& leftTime, const Time& rightTime)
{
	return !(leftTime > rightTime);
}


//-----------------------------------------------------
//	Date Comparison Operators
//-----------------------------------------------------

bool operator<(const Date& leftDate, const Date& rightDate)
{
	if(leftDate.year == rightDate.year){
		if(leftDate.month == rightDate.month){
			return leftDate.day < rightDate.day;
		}
		return leftDate.month < rightDate.month;
	}
	return leftDate.year < rightDate.year;
}
bool operator>=(const Date& leftDate, const Date& rightDate)
{
	return !(leftDate < rightDate);
}
bool operator==(const Date& leftDate,	const Date& rightDate)
{
	if(leftDate.day == rightDate.day && 
		leftDate.month == rightDate.month &&
		leftDate.year == rightDate.year) {
			return true;
	}
	return false;
}
bool operator>(const Date& leftDate, const Date& rightDate)
{
	return rightDate < leftDate;
}
bool operator<=(const Date& leftDate, const Date& rightDate)
{
	return !(leftDate > rightDate);
}

//-----------------------------------------------------
//	startId Comparison Operators
//-----------------------------------------------------

bool operator>(const startId& par1, const startId& par2 )
{
	if(par1.start == par2.start)
	{
		return (par1.id > par2.id);
	}
	return (par1.start > par2.start);

}

bool operator==(const startId &par1, const startId& par2 )
{
	return (par1.id == par2.id  && par1.start == par2.start);
}

bool operator<(const startId& par1, const startId& par2 )
{
	if(par1.start == par2.start)
	{
		return (par1.id < par2.id);
	}
	return (par1.start < par2.start);
}
bool operator>=(const startId& par1, const startId& par2 )
{
	return !(par1< par2);
}
bool operator<=(const startId& par1, const startId& par2 )
{
	return !(par1 > par2);
}



//-----------------------------------------------------
//	endId Comparison Operators
//-----------------------------------------------------
bool operator>(const endId& par1,const endId& par2 )
{
	if(par1.end == par2.end)
	{
		return (par1.id > par2.id);
	}
	return (par1.end > par2.end);

}
bool operator<(const endId& par1, const endId& par2 )
{
	if(par1.end==par2.end)
	{
		return (par1.id<par2.id);
	}
	return (par1.end <par2.end);

}

bool operator>=(const endId& par1, const endId& par2 )
{
	return !(par1<par2);
}
bool operator<=(const endId& par1, const endId& par2 )
{
	return !(par1>par2);
}
bool operator==(const endId &par1, const endId& par2 )
{

	return (par1.id==par2.id  && par1.end==par2.end);

}




//========================================================================================
//	Helping Functions - Error Testing
//========================================================================================
bool isIllegalDate(Date date) 
{
	if(date.day >= 1 && date.day <= 31 &&
		date.month >= 1 && date.month <= 12 &&
		date.year >=0 ) {
			return false;
	}
	return true;
}
	
bool isIllegalTime(Time time)
{
	if(time.hour >= 0 && time.hour <= 23 &&
		time.minutes >= 0 && time.minutes <= 59) {
		return false;
	}
	return true;
}

bool isIllegalEventId(int id)
{
	return id < 0;
}

bool isStartTimeGreater(Time startTime, Time endTime)
{
	if(startTime.hour == endTime.hour)
	{
		return startTime.minutes > endTime.minutes;
	}
	return startTime.hour > endTime.hour;
}




//========================================================================================
//	Library1.h Interface Implementation
//========================================================================================

void* Init()
{
	return (void*) (new Calendar());
}


StatusType  OpenDay(void* DS, Date day)
{
	if(DS == NULL || isIllegalDate(day)){
		return INVALID_INPUT;
	}
	return ((Calendar*)DS)->OpenDay(day);
}


StatusType  CloseDay(void* DS, Date day)
{
	if(DS == NULL || isIllegalDate(day)){
		return INVALID_INPUT;
	}
	return ((Calendar*)DS)->CloseDay(day);
}


StatusType  AddEvent(void* DS, int eventID, Date day, Time timeStart, Time timeEnd)
{
	if(DS == NULL || isIllegalEventId(eventID) || isIllegalDate(day) || isIllegalTime(timeStart) || isIllegalTime(timeEnd)
		|| isStartTimeGreater(timeStart, timeEnd)){
		return INVALID_INPUT;
	}
	return ((Calendar*)DS)->AddEvent(eventID, day, timeStart, timeEnd);
}


StatusType  RemoveEvent(void* DS, int eventID, Date day)
{
	if(DS == NULL || isIllegalEventId(eventID) || isIllegalDate(day)){
		return INVALID_INPUT;
	}
	return ((Calendar*)DS)->RemoveEvent(eventID, day);
}


StatusType  NumberEvents(void* DS, Date day, int* num)
{
	if(DS == NULL || num == NULL || isIllegalDate(day)){
		return INVALID_INPUT;
	}
	return ((Calendar*)DS)->NumberEvents(day, num);
}


StatusType  SetActiveDay(void* DS, Date day)
{
	if(DS == NULL || isIllegalDate(day)){
		return INVALID_INPUT;
	}
	return ((Calendar*)DS)->SetActiveDay(day);
}


StatusType  CurrDayNumEventsAtTime(void* DS, Time t, int* num)
{
	if(DS == NULL || num == NULL || isIllegalTime(t)){
		return INVALID_INPUT;
	}
	return ((Calendar*)DS)->CurrDayNumEventsAtTime(t, num);
}


void Quit(void** DS)
{
	if(DS == NULL){
		return;
	}
	delete *((Calendar**)DS);
	*DS = NULL;
}
