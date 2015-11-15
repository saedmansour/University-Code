#include <iostream>
using namespace std;


//#include "linked_list.h"
//#include "node.h"
//#include "candidate.h"
//#include "avl_tree.h"
//#include "field.h"
#include "optimal_array.h"

int mainTEST()
{
	// TODO: test destructor (memory leak test)
	
	/*
	 *	General Settings
	 *
	 *
	LinkedList<Candidate>* list=new LinkedList<Candidate>();	
	Candidate c1(1,1,1);
	Candidate c2(2,10,1);
	Candidate c3(3,100,1);
	Candidate c4(4,1000,1);
	Candidate c5(5,10000,1);
	Candidate c6(6,100000,1);
	*/

	
	
	
	/*
	 *	LinkedList Test
	 *
	 * 
	list->addFirst(&c1);
	list->addFirst(&c2);
	list->addFirst(&c3);
	list->addFirst(&c4);
	list->addFirst(&c5);
	Node<Candidate>* lastAddedCandidate = list->addFirst(&c6);
	list->printList();
	list->removeFirst();
	list->removeFirst();
	list->removeFirst();
	//list->removeFirst();
	list->removeFirst();
	list->printList();
	//list->removeFirst();
	list->remove(lastAddedCandidate);
	list->printList();
	list->removeFirst();
	list->printList();
	*/




	/*
	 *	Candidate Test: check the operators needed for the AVL
	 * 
	 *
	AVLTree<NoData, Candidate> tree;
	tree.AddByKey(c1 ,NULL);
	tree.AddByKey(c2 ,NULL);
	tree.AddByKey(c3 ,NULL);
	*/




	/*
	 *	Field Test
	 *
	 *
	Field field = *(new Field());
	field.AddCandidate(c1);
	field.AddCandidate(c2);
	field.AddCandidate(c3);
	field.AddCandidate(c4);
	field.AddCandidate(c5);
	field.AddCandidate(c6);
	*/





	/*
     *	Average Test
	 *
	 *
	cout << field.getFirstCandidate().getId() << endl;
	cout << field.getMinSalary() << endl;
	field.HireFirstCandidate();
	cout << field.getFirstCandidate().getId() << endl; 
	cout << field.getMinSalary() << endl;
	cout << field.getMinSalaryCandidate().getSalary() << endl;

	double average;
	field.getAverageFirstK(4, &average);
	cout << average << endl;
	*/




	/*
	 *	Optimal Array Test
	 *
	 *
	OptimalArray<int>* arr = new OptimalArray<int>(400);

	arr->set(1,5);
	arr->set(2,10);
	arr->set(5,25);

	cout << arr->get(1) << endl;
	cout << arr->get(2) << endl;
	cout << arr->get(3) << endl;
	cout << arr->get(4) << endl;
	cout << arr->get(5) << endl;
	cout << arr->get(6) << endl;
	cout << arr->get(9) << endl;
	*/



	return 0;
}
