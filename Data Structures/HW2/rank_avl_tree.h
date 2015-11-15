#ifndef _RANK_AVL_TREE_
#define _RANK_AVL_TREE_

#include <stdlib.h>



//NoData is used to make a node with key only.
typedef int* NoData;
#define NO_DATA NULL



//========================================================================================
//	RankTreeNode Template
//========================================================================================
// This class implements a tree node in a binary tree, i.e. every node has one father
// and two sons maximum.
// R = Key, S = Data
//
template <class S, class R>
class RankTreeNode
{
private:
	RankTreeNode<S, R>* RightSon;
	RankTreeNode<S, R>* LeftSon;
	RankTreeNode<S, R>* Father;

	R Key;
	S Data;
	int Height;
	int LeftSons;
	int RightSons;
	int Updated;


public:
	// TODO: check?
	RankTreeNode(): RightSon(NULL), LeftSon(NULL), Father(NULL)/*, Data(NULL)*/, Height(0),Updated(1),RightSons(0),LeftSons(0){}
	// TODO:
	//	~RankTreeNode(){ delete Data; }


	S GetData() const
	{
		return Data;
	}

	void SetData(S NewData)
	{
		Data = NewData;
	}

	//GetRightSon: returns a pointer to right node's son
	RankTreeNode<S, R>* GetRightSon() const
	{
		return RightSon;
	}

	//SetRightSon: sets the right son to be NewSon
	void SetRightSon(RankTreeNode<S, R>* NewSon)
	{
		RightSon = NewSon;
	}

	//GetLeftSon: returns a pointer to left node's son
	RankTreeNode<S, R>* GetLeftSon() const
	{
		return LeftSon;
	}

	//SetLeftSon: sets the left son to be NewSon
	void SetLeftSon(RankTreeNode<S, R>* NewSon) 
	{
		LeftSon = NewSon;
	}

	//GetFather:returns a node pointer to the father
	RankTreeNode<S, R>* GetFather() const
	{
		return Father;
	}

	//returns a node pointer to the father
	void SetFather(RankTreeNode<S, R>* NewFather) 
	{
		Father = NewFather;
	}

	int GetHeight() const
	{
		return Height;
	}
	void SetHeight(int NewHeight)
	{
		Height = NewHeight;
	}

	R GetKey() const
	{
		return Key;
	}
	void SetKey(R NewKey)
	{
		Key=NewKey;
	}
	
	/*rankH*/
	//GetLeftSons
		int GetLeftSons() const
		{
			return LeftSons;
		}

		//
		//SetLeftSons
		void SetLeftSons(int num) 
		{
			LeftSons=num;
		}


		//
		//GetRightSons
		int GetRightSons() const
		{
			return RightSons;
		}

		//
		//SetRightSons
		void SetRightSons(int num) 
		{
			RightSons=num;
		}

		//
		//GetRightSons
		int GetUpdated() const
		{
			return Updated;
	}

		//
		//SetRightSons
		void IncUpdated() 
		{
			Updated++;
		}

	/**/

	int GetBalanceFactor() const
	{
		int BF=0;
		int LeftHeight=-1;
		int RightHeight=-1;

		if (LeftSon != NULL)
			LeftHeight = LeftSon->GetHeight();

		if (RightSon != NULL)
			RightHeight = RightSon->GetHeight();

		BF= LeftHeight - RightHeight;
		return BF;
	}

	//UpdateHeight: updates the height of a node depending on the two sons' heights
	//Return:
	//				true:	if height doesn't change
	//				false:	if height changes
	bool UpdateHeight()
	{
		int OldHeight = Height;
		int LeftHeight = -1;	//initialize - this is a one node's height
		int RightHeight = -1;

		if (LeftSon != NULL)
		{
			LeftHeight = LeftSon->GetHeight();
		}
		if (RightSon != NULL)
		{
			RightHeight = RightSon->GetHeight();
		}

		if (RightHeight > LeftHeight)
		{
			Height = RightHeight+1;
		}
		else
		{
			Height= LeftHeight +1;
		}

		return (OldHeight == Height);
	}
};



//========================================================================================
//	RankAVLTree Template
//========================================================================================
// A class that implmenets an AVL Tree data structure. 
// R = node's key type
// S = node's data type
//
template <class S, class R>
class RankAVLTree
{
public:
	RankAVLTree(): Root(NULL), MinNode(NULL), MaxNode(NULL){}
	~RankAVLTree();

	
	void getAll(int *size, R** KeyArray, S** DataArray)
	{
		*size = getElementsNum(Root);
		if(*size == 0){
			return;
		}
		*KeyArray  = new R[*size];
		*DataArray = new S[*size];
		int index = 0;
		getAllHelper(KeyArray, DataArray, &index, Root);
	}

	void getAllHelper(R** KeyArray, S** DataArray, int* index, RankTreeNode<S, R>* node)
	{
		if(node == NULL){
			(*index)--;
			return;
		}

		(*KeyArray)[*index]  = node->GetKey();
		(*DataArray)[*index] = node->GetData();

		(*index)++;
		getAllHelper(KeyArray, DataArray, index, node->GetLeftSon());
		(*index)++;
		getAllHelper(KeyArray, DataArray, index, node->GetRightSon());
	}

	int getElementsNum(RankTreeNode<S, R>* node)
	{
		if(node == NULL)
		{
			return 0;
		}
		return 1 + getElementsNum(node->GetLeftSon()) + getElementsNum(node->GetRightSon());
	}

	const	RankTreeNode<S, R>* GetRoot() const; 


	//AddByKey: add a new node to tree with key and data 
	//Return:
	//		true: successfully added
	//		false: failed adding and allocation error(using exception)
	bool AddByKey( R NewKey, S Data);


	//FindByKey: find a node in the tree by its key. Returns node pointer.
	//Return:
	//			NULL - Key is not in tree
	//			pointer to the found node otherwise
	RankTreeNode<S, R>* FindByKey(R Key);

	//RemoveByKey: removes a node from the tree by its key.
	//Return:
	//			true:  removed successfully
	//			false: otherwise
	bool	RemoveByKey(R Key);


	//IsEmpty: checks if the tree is empty
	bool	IsEmpty();


	//MinKeyData: returns the data of minimum key in the tree.
	S		MinKeyData();


	//MaxKeyData: returns the data of maximum key in the tree.
	S		MaxKeyData();


	//MinKey: returns the minimal key
	R		MinKey();


	//ManKey: returns the maximal key
	R		MaxKey();
	
	
	//new fordebug
	int getSize()
	{
		return Help_getSize(Root);
		
	}
	int Help_getSize(RankTreeNode<S,R>* node)
	{
		if(node == NULL)
			return 0;
		return Help_getSize(node->GetLeftSon())+Help_getSize(node->GetRightSon())+1;
	}
		//returns the index of node
	int		ReturnFirstIndex(R Key);

	int		ReturnLastIndex(R Key);

private:	
	RankTreeNode<S, R>* Root;
	RankTreeNode<S, R>* MinNode;
	RankTreeNode<S, R>* MaxNode;

	//Rotation's Functions, Vertex is a vertex with unbalanced factor.
	bool    RotateLL(RankTreeNode<S, R>* & Vertex);
	bool    RotateLR(RankTreeNode<S, R>* & Vertex);
	bool    RotateRL(RankTreeNode<S, R>* & Vertex);
	bool    RotateRR(RankTreeNode<S, R>* & Vertex);


	//Destroy : destroys all the tree and frees the data stored in.
	void	Destroy(RankTreeNode<S, R>* Root);


	//SearchByKey: finds a key (functions the same as FindByKey, but FindByKey just calls this one with root,
	//			   while this function works recursively.  
	//			  Root: the start of the tree or subtree to search from.
	//Return:
	//				NULL - key not found
	//				pointer to tree node otherwise
	RankTreeNode<S, R>*	SearchByKey(R Key, RankTreeNode<S, R>* Root);


	//FindPlaceByKey: the function take a key and tree root, and returns the place where the key shold be
	//				  added. (It returns the father)
	RankTreeNode<S, R>*	FindPlaceByKey(R Key, RankTreeNode<S, R>* Root);


	//UpdateAddByKey: this function is used after adding a node to the tree. It does the needed
	//rotations in order to satisfy the AVL tree property.
	void	UpdateAddByKey(RankTreeNode<S, R>* Node);


	//UpdateRemoveByKey: same as UpdateRemoveByKey but is used when removing.
	void	UpdateRemoveByKey(RankTreeNode<S, R>* Node);


	//IsLeaf: 
	//Return:
	//		true:	if node is a leaf
	//		false:	otherwise 
	bool	IsLeaf(RankTreeNode<S, R>* Node);


	//helper function for RemoveByKey
	bool	NextInOrd(RankTreeNode<S, R>* Node, RankTreeNode<S, R>* & NextNode);


	//ReturnMin: returns a pointer to the minimum node in a subtree starting with node.
	RankTreeNode<S, R>* ReturnMin( RankTreeNode<S, R>* Node);


	//ReturnMax: returns a pointer to the maximum node in a subtree starting with node.
	RankTreeNode<S, R>* ReturnMax( RankTreeNode<S, R>* Node);
//rankh

	//UpdateLeftSons: this function updates the number of the left sons after adding a new node to the tree
	void UpdateSons(RankTreeNode<S, R>* Node);

	//
	//UpdateSonsDelete: this function updates the number of the left sons after deleting a node to the tree
	void UpdateSonsDelete(RankTreeNode<S, R>* Node);
	
	
	//
	void ReturnLastIndex_Aux(int* index, R Key, RankTreeNode<S, R>* Root);

	//
	//
	void ReturnFirstIndex_Aux(int* index, R Key, RankTreeNode<S, R>* Root);
	};

//========================================================================================
//	RankAVLTree Template: Public Functions
//========================================================================================
template <class S, class R>
RankAVLTree<S, R>::~RankAVLTree()
{
	if(Root != NULL)
	{
		Destroy(Root);
	}
	Root = NULL;
}

template <class S, class R>
const RankTreeNode<S, R>* RankAVLTree<S, R>::GetRoot() const 
{
	return Root;
}

//this function is a duplicate of SearchByKey but it starts with root always
template <class S, class R>
RankTreeNode<S,R>* RankAVLTree<S, R>::FindByKey( R Key)
{
	return SearchByKey(Key, Root);
}


template <class S, class R>
bool RankAVLTree<S, R>::AddByKey(R NewKey, S Data)

{
	//TODO: ?
	//try 
	//{ 
		RankTreeNode<S, R>* Father;
		RankTreeNode<S, R>* NewNode = new RankTreeNode<S, R> ;

		//check if exist

		//finding the father of the new node
		Father = FindPlaceByKey(NewKey, Root);
	



		//filling the info in new node.
		NewNode->SetFather(Father);
		NewNode->SetKey(NewKey);
		NewNode->SetData(Data);
		NewNode->SetLeftSon(0);
		NewNode->SetRightSons(0);


		if (Father == NULL)	//empty tree

		{
			Root = NewNode;

			MinNode = NewNode;
			MaxNode = NewNode;
			return true;
		}
		if(Father->GetKey()== NewKey)
		{
			return false;
		}


		if (NewKey < Father->GetKey()) 
		{



			Father->SetLeftSon(NewNode);
		}
		else

		{
			Father->SetRightSon(NewNode);

		}

		//updating the number of left sons in the search path
		UpdateSons(NewNode);







		//updating the tree after adding the new node.
		UpdateAddByKey(NewNode);






		MinNode = ReturnMin(Root);
		MaxNode = ReturnMax(Root);

		return true;
	//}
	//catch(bad_alloc&) { return false; }
}



template <class S, class R>

bool RankAVLTree<S, R>::RemoveByKey( R Key)
{

	//searching for the node in the tree
	RankTreeNode<S, R>* Node = SearchByKey(Key, Root);

	if (Node == NULL)
	{
		return false;
	}

	RankTreeNode<S, R>* Father= Node->GetFather();
	if (IsLeaf(Node))
	{
		if (Father != NULL)
		{    
			if (Father->GetLeftSon() == Node)          

			{
				Father->SetLeftSons(Father->GetLeftSons()-1);
				Father->SetLeftSon(NULL);   
			}
			else          
			{
				Father->SetRightSons(Father->GetRightSons()-1);
				Father->SetRightSon(NULL);	  
			}
			delete Node;
		}      
		else 

		{
			//this is the only node in the tree!
			Root = NULL;
			delete Node;

			MinNode = ReturnMin(Root);
			MaxNode = ReturnMax(Root);
			return true; 
		}    

		UpdateSonsDelete(Father);
		UpdateRemoveByKey(Father);


		MinNode = ReturnMin(Root);
		MaxNode = ReturnMax(Root);
		return true;
	}



	RankTreeNode<S, R>* NextNode=NULL; // next smallest
	if (!NextInOrd(Node,NextNode))
	{
		return false; 
	}
	RankTreeNode<S, R>* FatherN=NextNode->GetFather();


	if (IsLeaf(NextNode))
	{
		if (FatherN->GetLeftSon()==NextNode)

		{
			FatherN->SetLeftSons(FatherN->GetLeftSons()-1);
			FatherN->SetLeftSon(NULL);
		}
		else

		{
			FatherN->SetRightSons(FatherN->GetRightSons()-1);
			FatherN->SetRightSon(NULL);
		}

	}
	else // not leaf
	{ 

		if (FatherN->GetLeftSon()==NextNode)
		{
			if (NextNode->GetLeftSon()!=NULL)  //3

			{
				FatherN->SetLeftSon(NextNode->GetLeftSon());
				FatherN->SetLeftSons(NextNode->GetLeftSons());
				(NextNode->GetLeftSon())->SetFather(FatherN);
				
				FatherN->SetRightSon(NextNode->GetRightSon());
				FatherN->SetRightSons(NextNode->GetRightSons());

				if (NextNode->GetRightSon()!=NULL)
					(NextNode->GetRightSon())->SetFather(FatherN);
			}





			else
			{
				FatherN->SetLeftSon(NextNode->GetRightSon());
				FatherN->SetLeftSons(NextNode->GetRightSons());



				if (NextNode->GetRightSon()!=NULL)
				{
					(NextNode->GetRightSon())->SetFather(FatherN);
				}
			}
		}
		else

		{
			FatherN->SetRightSon(NextNode->GetRightSon());
			FatherN->SetRightSons(NextNode->GetRightSons());
			if (NextNode->GetRightSon()!=NULL)
			{
				(NextNode->GetRightSon())->SetFather(FatherN);
			}
		}
	}






	NextNode->SetFather(Node->GetFather());
	NextNode->SetLeftSon(Node->GetLeftSon());
	NextNode->SetRightSon(Node->GetRightSon());
	NextNode->SetHeight(Node->GetHeight());
	NextNode->SetRightSons(Node->GetRightSons());
	NextNode->SetLeftSons(Node->GetLeftSons());





	if (Node==Root) 
	{


		Root=NextNode;
	}
	else

	{  
		if (Father->GetLeftSon()==Node)
		{

			
			Father->SetLeftSon(NextNode);
		}






		else
		{

			Father->SetRightSon(NextNode);
		}

	}



	if ( Node->GetLeftSon()!=NULL )
	{
		(Node->GetLeftSon())->SetFather(NextNode);
	}



	if (Node->GetRightSon()!=NULL)
	{
		(Node->GetRightSon())->SetFather(NextNode);
	}


	if (FatherN==Node) 
	{
		FatherN=NextNode;
	}
	delete Node;

	UpdateSonsDelete(FatherN);
	UpdateRemoveByKey(FatherN);




	MinNode = ReturnMin(Root);
	MaxNode = ReturnMax(Root);

	return true;
}

template <class S, class R>
bool RankAVLTree<S, R>::IsEmpty()
{
	return (Root == NULL);
}

template <class S, class R>
S RankAVLTree<S, R>::MinKeyData()
{
	return MinNode->GetData();
}

template <class S, class R>
S RankAVLTree<S, R>::MaxKeyData()
{
	return MaxNode->GetData();
}

template <class S, class R>
R RankAVLTree<S, R>::MinKey()
{
	return MinNode->GetKey();
}

template <class S, class R>
R RankAVLTree<S, R>::MaxKey()
{
	return MaxNode->GetKey();
}




template <class S, class R>
int RankAVLTree<S, R>::ReturnFirstIndex(R Key)
{
	int index=0;
	ReturnFirstIndex_Aux(&index, Key, Root);
	return index;
}

template <class S, class R>
int RankAVLTree<S, R>::ReturnLastIndex(R Key)
{
	int index=1;
	if(ReturnFirstIndex(Key)==0)
		return 0;
	ReturnLastIndex_Aux(&index, Key, Root);
	return index;
}

//========================================================================================
//	RankAVLTree Template: Private Functions
//========================================================================================
template <class S, class R>
bool    RankAVLTree<S, R>::RotateLL(RankTreeNode<S, R>* & Vertex)
{
	RankTreeNode<S, R>* VertexA=Vertex->GetLeftSon();


	//A is Vertex


	int ARightSons=Vertex->GetRightSons();

	//B is VertexA
	int BLeftSons=VertexA->GetLeftSons();
	int BRightSons=VertexA->GetRightSons();

	if (Vertex==Root)
	{
		Root=VertexA;  
	}

	Vertex->SetLeftSon(VertexA->GetRightSon());
	if (VertexA->GetRightSon()!=NULL)
	{
		(VertexA->GetRightSon())->SetFather(Vertex);
	}

	VertexA->SetRightSon(Vertex);
	VertexA->SetFather(Vertex->GetFather());

	if (Vertex->GetFather()!=NULL)
	{
		if ((Vertex->GetFather())->GetLeftSon()==Vertex)
		{
			(Vertex->GetFather())->SetLeftSon(VertexA);
		}
		else
		{
			(Vertex->GetFather())->SetRightSon(VertexA);
		}
	}

	Vertex->SetFather(VertexA);

	Vertex->UpdateHeight();
	VertexA->UpdateHeight();

	Vertex->SetLeftSons(BRightSons);
	Vertex->SetRightSons(ARightSons);
	
	VertexA->SetLeftSons(BLeftSons);
	VertexA->SetRightSons(ARightSons + BRightSons + 1);
	
	return true;
}


template <class S, class R>
bool    RankAVLTree<S, R>::RotateLR(RankTreeNode<S, R>* & Vertex)
{
	RankTreeNode<S, R>* VertexA=Vertex->GetLeftSon();
	RankTreeNode<S, R>* VertexC=VertexA->GetRightSon();

	//A is Vertex

	int ARightSons=Vertex->GetRightSons();

	//B is VertexA
	int BLeftSons= VertexA->GetLeftSons();
	

	//C is VertexC
	int CLeftSons=VertexC->GetLeftSons();
	int CRightSons=VertexC->GetRightSons();
	
	if (Vertex==Root)
	{
		Root=VertexC;
	}

	VertexA->SetRightSon(VertexC->GetLeftSon());

	if(VertexC->GetLeftSon()!=NULL)
	{
		(VertexC->GetLeftSon())->SetFather(VertexA);
	}

	VertexC->SetLeftSon(VertexA);
	VertexA->SetFather(VertexC);
	VertexC->SetFather(Vertex->GetFather());

	if (Vertex->GetFather()!=NULL)
	{
		if ((Vertex->GetFather())->GetLeftSon()==Vertex)
		{
			(Vertex->GetFather())->SetLeftSon(VertexC);
		}
		else
		{
			(Vertex->GetFather())->SetRightSon(VertexC);
		}
	}

	Vertex->SetLeftSon(VertexC->GetRightSon());

	if (VertexC->GetRightSon()!=NULL)
	{
		(VertexC->GetRightSon())->SetFather(Vertex);
	}

	VertexC->SetRightSon(Vertex);
	Vertex->SetFather(VertexC);


	Vertex->UpdateHeight();
	VertexA->UpdateHeight();
	VertexC->UpdateHeight();


	Vertex->SetLeftSons(CRightSons);
	VertexA->SetLeftSons(BLeftSons);
	VertexC->SetLeftSons(BLeftSons+CLeftSons+1);

	Vertex->SetRightSons(ARightSons);
	VertexA->SetRightSons(CLeftSons);
	VertexC->SetRightSons(ARightSons + CRightSons +1);

	return true;
}



template <class S, class R>
bool    RankAVLTree<S, R>::RotateRL(RankTreeNode<S, R>* & Vertex)
{
	RankTreeNode<S, R>* VertexA= Vertex->GetRightSon();
	RankTreeNode<S, R>* VertexC= VertexA->GetLeftSon();

	//A is Vertex
	int ALeftSons= Vertex->GetLeftSons();
	

	//B is VertexA
	
	int BRightSons=VertexA->GetRightSons();

	//C is VertexC
	int CLeftSons=VertexC->GetLeftSons();
	int CRightSons=VertexC->GetRightSons();
	

	if (Vertex==Root)
	{
		Root=VertexC;
	}

	VertexA->SetLeftSon(VertexC->GetRightSon());

	if(VertexC->GetRightSon()!=NULL)
	{
		(VertexC->GetRightSon())->SetFather(VertexA);
	}

	VertexC->SetRightSon(VertexA);
	VertexA->SetFather(VertexC);
	VertexC->SetFather(Vertex->GetFather());

	if (Vertex->GetFather()!=NULL)
	{
		if ((Vertex->GetFather())->GetLeftSon()==Vertex)
		{
			(Vertex->GetFather())->SetLeftSon(VertexC);
		}
		else
		{
			(Vertex->GetFather())->SetRightSon(VertexC);
		}
	}
	Vertex->SetFather(VertexC);

	Vertex->SetRightSon(VertexC->GetLeftSon());
	if (VertexC->GetLeftSon()!=NULL)
	{
		(VertexC->GetLeftSon())->SetFather(Vertex);
	}
	VertexC->SetLeftSon(Vertex);
	Vertex->SetFather(VertexC);

	Vertex->UpdateHeight();
	VertexA->UpdateHeight();
	VertexC->UpdateHeight();

	Vertex->SetLeftSons(ALeftSons);
	VertexA->SetLeftSons(CRightSons);
	VertexC->SetLeftSons(ALeftSons+CLeftSons+1);

	Vertex->SetRightSons(CLeftSons);
	VertexA->SetRightSons(BRightSons);
	VertexC->SetRightSons(CRightSons+BRightSons+1);
	

	return true;
}


template <class S, class R>
bool    RankAVLTree<S, R>::RotateRR(RankTreeNode<S, R>* & Vertex)
{
	RankTreeNode<S, R>* VertexA=Vertex->GetRightSon();

	//A is Vertex

	int ALeftSons= Vertex->GetLeftSons();
	

	//B is VertexA
	int BLeftSons=VertexA->GetLeftSons();
	int BRightSons=VertexA->GetRightSons();

	if (Vertex==Root)
	{
		Root=VertexA;
	}

	Vertex->SetRightSon(VertexA->GetLeftSon());

	if (VertexA->GetLeftSon()!=NULL)
	{
		(VertexA->GetLeftSon())->SetFather(Vertex);
	}

	VertexA->SetLeftSon(Vertex);
	VertexA->SetFather(Vertex->GetFather());

	if (Vertex->GetFather()!=NULL)
	{
		if ((Vertex->GetFather())->GetLeftSon()==Vertex)
		{
			(Vertex->GetFather())->SetLeftSon(VertexA);
		}
		else
		{
			(Vertex->GetFather())->SetRightSon(VertexA);
		}
	}

	Vertex->SetFather(VertexA);

	Vertex->UpdateHeight();
	VertexA->UpdateHeight();

	Vertex->SetLeftSons(ALeftSons);
	Vertex->SetRightSons(BLeftSons);
	
	VertexA->SetLeftSons(ALeftSons+BLeftSons+1);
	VertexA->SetRightSons(BRightSons);

	return true;
}

template <class S, class R>
void	RankAVLTree<S, R>::Destroy(RankTreeNode<S, R>* Root)
{
	if (Root==NULL)
	{
		return;
	}

	Destroy(Root->GetLeftSon());
	Destroy(Root->GetRightSon());
	// TODO: ?
	//Root->SetData(NULL);
	delete Root; 
}


template <class S, class R>
RankTreeNode<S, R>* RankAVLTree<S, R>::SearchByKey(R Key, RankTreeNode<S, R>* Root)
{
	//the key of the current node.
	if (Root==NULL)
	{
		return NULL;
	}

	R RootKey = Root->GetKey();	
	//checking if we got a match
	if (RootKey == Key)
	{
		return Root;
	}

	//searching in the left sub tree
	if (Key < RootKey && Root->GetLeftSon()!=NULL)
	{
		return SearchByKey(Key, Root->GetLeftSon());
	}

	//Dead End!! no left sub tree, and the key is smaller than the root key
	if (Key < RootKey && Root->GetLeftSon()==NULL) 
	{
		return NULL;
	}

	//searching in the right sub tree
	if (Key >= RootKey && Root->GetRightSon()!=NULL)
	{
		return SearchByKey(Key, Root->GetRightSon());
	}

	//Dead End!! no right sub tree, and the key is bigger than the root key
	return NULL;
}


template <class S, class R>
RankTreeNode<S, R>*	RankAVLTree<S, R>::FindPlaceByKey(R Key, RankTreeNode<S, R>* Root)
{	
	//the key of the current node.

	if (Root==NULL)
	{
		return NULL;
	}

	R RootKey = Root->GetKey();

	//searching in the left sub tree
	if (Key < RootKey && Root->GetLeftSon()!=NULL)
	{
		return FindPlaceByKey(Key, Root->GetLeftSon());
	}

	//no left sub tree, and the key is smaller than the root key => this is the place
	if (Key < RootKey && Root->GetLeftSon()==NULL) 
	{
		return Root;
	}

	//searching in the right sub tree
	if (Key >= RootKey && Root->GetRightSon()!=NULL) 
	{
		return FindPlaceByKey(Key, Root->GetRightSon());
	}

	//no right sub tree, and the key is bigger than the root key => this is the place
	return Root;
}


template <class S, class R>
void	RankAVLTree<S, R>::UpdateAddByKey(RankTreeNode<S, R>* Node)
{
	//if we are in the root, no changes is needed
	RankTreeNode<S, R>* Father= Node->GetFather();
	if (Father==NULL) 
	{
		return ;
	}

	//going up toward the root, and checking where roatrion is needed.
	while (Father != NULL)
	{
		//***********************************************************************************************************************
		//if the father's Height have not been changed then we are done. no changes is needed.
		if( Father->UpdateHeight())
		{
			return;
		}

		//if we get here, that's mean that the Height have been changed, and a rotation is needed to keep 
		//the tree as valid avl tree.
		//we checks the balnce of the node, to find which rotation is needed.
		int FatherBF = Father->GetBalanceFactor();
		int SonBF = Node->GetBalanceFactor();

		if (FatherBF==2)
		{
			if (SonBF>=0)
			{
				RotateLL(Father);
			}
			else
			{
				RotateLR(Father);
			}
			Father=Father->GetFather();
		}

		else
		{
			if (FatherBF == -2)
			{
				if (SonBF <= 0)
				{
					RotateRR(Father);
				}
				else
				{
					RotateRL(Father);
				}
				Father=Father->GetFather();
			}
		}

		//after preforming the needed rotation in the node, we continue upwards.
		Node=Father;

		//checking if we reached the root.
		if (Node!=NULL)
		{
			Father=Node->GetFather();
		}
	}
}

template <class S, class R>
bool	RankAVLTree<S, R>::IsLeaf(RankTreeNode<S, R>* Node)
{
	//checking if the given node is a leaf.
	if (Node->GetRightSon()== NULL)
	{
		if(Node->GetLeftSon() == NULL)
		{
			return true;
		}
	}
	return false;
}

template <class S, class R>
bool RankAVLTree<S, R>::NextInOrd(RankTreeNode<S, R>* Node,RankTreeNode<S, R>* & NextNode)
{
	if (Node == NULL)
	{
		NextNode = NULL;
		return false;
	}

	RankTreeNode<S, R>* NextNode2 = Node->GetRightSon();

	if (NextNode2 == NULL) 
	{
		NextNode=Node->GetLeftSon();
		return true;
	} 

	while (NextNode2->GetLeftSon()!=NULL)
	{
		NextNode2=NextNode2->GetLeftSon();
	}

	NextNode=NextNode2;
	return true;
}     


template <class S, class R>
void RankAVLTree<S, R>::UpdateRemoveByKey(RankTreeNode<S, R>* Node)
{
	RankTreeNode<S, R>* NodeB=Node;

	while(NodeB!=NULL)
	{
		NodeB->UpdateHeight();
		int NodeBBF=NodeB->GetBalanceFactor();


		if (NodeBBF==2)
		{

			if ((NodeB->GetLeftSon())->GetBalanceFactor()>=0)
			{
				RotateLL(NodeB);
			}
			else
			{
				RotateLR(NodeB);
			}
			NodeB=NodeB->GetFather();  
		}
		else
		{  
			if (NodeBBF==-2)
			{
				if ((NodeB->GetRightSon())->GetBalanceFactor()<=0)
				{
					RotateRR(NodeB);
				}
				else
				{
					RotateRL(NodeB);
				}
				NodeB=NodeB->GetFather();
			}
		}

		NodeB=NodeB->GetFather();
	}
}

template <class S, class R>
RankTreeNode<S, R>* RankAVLTree<S, R>::ReturnMin( RankTreeNode<S, R>* Node)
{
	//TODO: added by saed

	if(Node == NULL) {
		return Root;
	}

	if (Node->GetLeftSon() == NULL)
	{
		return Node;
	}
	else
	{
		return ReturnMin(Node->GetLeftSon());
	}
}

template <class S, class R>
RankTreeNode<S, R>* RankAVLTree<S, R>::ReturnMax( RankTreeNode<S, R>* Node)
{
	//TODO: added by saed

	if(Node == NULL) {
		return Root;
	}

	if (Node->GetRightSon() == NULL)
	{
		return Node;
	}
	else
	{
		return ReturnMax(Node->GetRightSon());
	}
}

template <class S, class R>
void RankAVLTree<S, R>::UpdateSonsDelete(RankTreeNode<S, R>* Node)
{
	RankTreeNode<S, R>* Father= Node->GetFather();
	if (Father==NULL) 
		return ;
	
	if (Node==Father->GetLeftSon())
		Father->SetLeftSons(Father->GetLeftSons()-1);

	if (Node==Father->GetRightSon())
		Father->SetRightSons(Father->GetRightSons()-1);


	UpdateSonsDelete(Father);
		

}


template <class S, class R>
void RankAVLTree<S, R>::UpdateSons(RankTreeNode<S, R>* Node)
{
	RankTreeNode<S, R>* Father= Node->GetFather();
	if (Father==NULL) 
		return ;
	
	if (Node==Father->GetLeftSon())
		Father->SetLeftSons(Father->GetLeftSons()+1);

	if (Node==Father->GetRightSon())
		Father->SetRightSons(Father->GetRightSons()+1);


	UpdateSons(Father);
		

}

//HERE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
template <class S, class R>
void RankAVLTree<S, R>::ReturnFirstIndex_Aux(int* index, R Key, RankTreeNode<S, R>* Root)
{
	//the key of the current node.
		
	if (Root==NULL)
		return ;

	R RootKey = Root->GetKey();	
	//checking if we got a match
	if (RootKey==Key)
	{
		*index = *index + Root->GetLeftSons()+ Root->GetUpdated();
		return;
	}

	//searching in the left sub tree
	if (Key < RootKey && Root->GetLeftSon()!=NULL)
	{
		 ReturnFirstIndex_Aux(index, Key, Root->GetLeftSon());
		 return;
	}

	//Dead End!! no left sub tree, and the key is smaller than the root key
	if (Key < RootKey && Root->GetLeftSon()==NULL) 
	{
		//*index+=1;
		return ;
	}

	//searching in the right sub tree
	if (Key >= RootKey && Root->GetRightSon()!=NULL) 
	{
		*index = *index + Root->GetLeftSons()+Root->GetUpdated();
		 ReturnFirstIndex_Aux(index, Key, Root->GetRightSon());
		 return;
	}
	else
	{
		if(Key >=RootKey)
		{
			*index = *index + Root->GetLeftSons()+Root->GetUpdated();
			return;

		}
	}
	
	//Dead End!! no right sub tree, and the key is bigger than the root key
	//*index=0;
	return ;

}


template <class S, class R>
void RankAVLTree<S, R>::ReturnLastIndex_Aux(int* index, R Key, RankTreeNode<S, R>* Root)
{
	//the key of the current node.
		
	if (Root==NULL)
		return ;

	R RootKey = Root->GetKey();	
	//checking if we got a match
	/*
	if (RootKey==Key)
	{
		*index = *index + Root->GetLeftSons();
		return;
	}
	*/

	//searching in the left sub tree
	if (Key < RootKey && Root->GetLeftSon()!=NULL)
	{
		 ReturnLastIndex_Aux(index, Key, Root->GetLeftSon());
		 return;
	}

	//Dead End!! no left sub tree, and the key is smaller than the root key
	if (Key < RootKey && Root->GetLeftSon()==NULL) 
	{
		return ;
	}

	//searching in the right sub tree
	if (Key >= RootKey && Root->GetRightSon()!=NULL) 
	{
		*index = *index + Root->GetLeftSons()+1;
		 ReturnLastIndex_Aux(index, Key, Root->GetRightSon());
		 return;
	}
	
	return ;

}

#endif	//#ifndef _AVL_TREE_

