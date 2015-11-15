#ifndef _DATA_
#define _DATA_


//========================================================================================
//	Includes
//========================================================================================

#include "rank_avl_tree.h"
#include "avl_tree.h"
#include "event.h"


//========================================================================================
//	startId class
//========================================================================================
// This class is used to create a rank tree which we store in the IDs and start time
// so that get num of events at curr day can work.

class startId
{
	public:
	startId(int id , Time start):id(id),start(start){}
	startId()
	{
	}
	int getID()
	{
		return id;
	}
	Time getStart()
	{
		return start;
	}

	friend bool operator>(const startId& par1, const startId& par2 );
	friend bool operator<(const startId& par1, const startId& par2 );
	friend bool operator==(const startId& par1, const startId& par2 );
	friend bool operator>=(const startId& par1, const startId& par2 );
	friend bool operator<=(const startId& par1, const startId& par2 );

private:
	Time start;
	int	id;	//id so after sorting by time => sort by id.
};



//========================================================================================
//	endId class
//========================================================================================
// This class is used to create a rank tree which we store in the IDs and start time
// so that "get num of events at curr day" can work.

class endId
{
	public:
	endId(int id , Time end):id(id),end(end){}
	endId(){}
	int getID()
	{
		return id;
	}
	Time getEnd()
	{
		return end;
	}

	friend bool operator>(const endId& par1, const endId& par2 );
	friend bool operator<(const endId& par1, const endId& par2 );
	friend bool operator==(const endId& par1, const endId& par2 );
	friend bool operator>=(const endId& par1, const endId& par2 );
	friend bool operator<=(const endId& par1, const endId& par2 );	
private:
	Time end;
	int	id;
};




//========================================================================================
//	Data Class
//========================================================================================
//	This is the Data in the Hash Table we used. It consists of a data structure for events
//	for adding and removing events (AVLTree). Furthermore, it contains two Rank Trees which
//	are used for the getNumOfEventsAtTimeT. One Rank Tree is sorted by the starting time
//	of the event, the other is sorted by the end time. Subtracting the rank of each node
//	will return the result we need.


class Data
{
public:
	Data(Date date):date(date), eventsNum(0){}
	
	Data( ){}
	
	bool isNoEvents()
	{
		return eventsNum == 0;
	}

	bool AddEvent(int eventID, Time timeStart, Time timeEnd)
	{
		//TODO: implement
		Event event1(eventID,timeStart,timeEnd);
		startId start(eventID,timeStart);
		endId end(eventID,timeEnd);

		TreeNode<Event,int>* node  = eventsAvl.FindByKey(eventID);
		if(node != NULL )
		{
			return false;
		}

		eventsAvl.AddByKey(eventID,event1);
		startTimeAvl.AddByKey(start,event1); 
		endTimeAvl.AddByKey(end,event1);
		eventsNum++;					//check if fail
		return true;
	}

	bool removeEvent(int eventID)
	{
		TreeNode<Event,int>* node = eventsAvl.FindByKey(eventID);
		if(node == NULL )
		{
			return false;
		}
		Event event1=node->GetData();
		startId start(eventID,event1.getStartTime());
		endId end(eventID,event1.getEndTime());
		
		eventsAvl.RemoveByKey(event1.getId());
		startTimeAvl.RemoveByKey(start); 
		endTimeAvl.RemoveByKey(end);
		
		eventsNum--;			//check if fail
		return true;
	}
	
	bool containsEvent(int eventID){
		if(eventsAvl.FindByKey(eventID) != NULL){
			return true;
		}
		return false;
	}

	int getEventsNum(){
		return eventsNum;
	}
	
	//return numbers of events at time T
	int NumEventsAtTime(Time t){
		if(eventsNum==0){
			return 0;
		}
		Event event1= eventsAvl.MaxKeyData();
		Event event2= eventsAvl.MinKeyData();
		startId start(event1.getId()+1,t);
		endId end(event2.getId()-1,t);
		int rankStart = startTimeAvl.ReturnFirstIndex(start);
		int rankEnd = endTimeAvl.ReturnFirstIndex(end);
		
		return (rankStart- rankEnd);
		
	}

private:

	int eventsNum;
	AVLTree<Event,int> eventsAvl;   // ranged by idevent 
	RankAVLTree<Event,startId> startTimeAvl;   // ranged by start time
	RankAVLTree<Event,endId> endTimeAvl;   // ranged by start time 
	Date date;
};

#endif
