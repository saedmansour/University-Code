#ifndef _NODE_
#define _NODE_



//========================================================================================
//	Node Class
//========================================================================================
//
//	Summary: Node in  a linked list.
//

template <class T>
class Node 
{
public:
	Node(T candidate): candidate(candidate){}
	Node()
	{
		 T *tempCand = (new T());
		 candidate = *tempCand;
	}


	// TODO:
	//~Node(){delete &candidate;}


	void setData(T data)
	{
		candidate = data;
	}

	Node<T>*				next;
	Node<T>*				prev;
	T						candidate;
};

#endif
