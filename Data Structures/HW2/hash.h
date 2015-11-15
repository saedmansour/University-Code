#ifndef _HASH_TABLE_
#define _HASH_TABLE_


//========================================================================================
//	Includes
//========================================================================================

#include "data.h"
#include "library2.h"



//========================================================================================
//	HashTable Class
//========================================================================================
// This is a non-generic implementation of a hash table data structure. Where the key is 
// Date and data is Data as specified in this project. The starting size is 2 and the 
// hash table gets rehashed every time it gets oversize. (Here when the number of members
// equals the size of the hash).
//
// To solve members collusion we used an AVL tree which solves the complexity specified
// in the homework's instructions.

#define START_SIZE 2

class HashTable
{
public:

	HashTable(): size(START_SIZE), elementsNum(0)
	{
		DateAVLArray = new AVLTree<Data*, Date>[START_SIZE];
	}

	~HashTable()
	{
		delete[] DateAVLArray;
	}


	int getHashSize()
	{
		return size;
	}

	bool isExist(Date date)
	{ 
		return DateAVLArray[hashFunction(date)].FindByKey(date) != NULL;
	}
	bool isFull()
	{
		return elementsNum >= size;
	}

	bool add(Date date)
	{
		if(isExist(date))
		{
			return false;
		}
		if(isFull())
		{
			rehash();
		}
		DateAVLArray[hashFunction(date)].AddByKey(date, new Data(date));

		elementsNum++;
		return true;
	}

	bool remove(Date date)
	{
		if(!isExist(date))
		{
			return false;
		}
		delete DateAVLArray[hashFunction(date)].FindByKey(date)->GetData();
		DateAVLArray[hashFunction(date)].RemoveByKey(date);
		
		elementsNum--;
		return true;
	}

	Data* find(Date date)
	{
		if(!isExist(date))
		{
			return NULL;
		}
		return DateAVLArray[hashFunction(date)].FindByKey(date)->GetData();
	}

	// hashes the key
	int hashFunction(Date key)
	{
		return GetCodedDate(key) % size;
	}

private:
	//rehashes the table
	void rehash()
	{
		int newSize = size * 2;
		int oldSize = size;
		AVLTree<Data*, Date>* newDateAVLArray = new AVLTree<Data*, Date>[newSize];

		int *arraySize = new int;
		Date* keyArray = NULL;
		Data** dataArray = NULL;


		size = newSize;
		for(int j = 0; j < oldSize; j++)
		{			
			DateAVLArray[j].getAll(arraySize, &keyArray, &dataArray);
			for(int i = 0; i < *arraySize; i++)
			{
				newDateAVLArray[hashFunction(keyArray[i])].AddByKey(keyArray[i], dataArray[i]);
			}
		}

		delete arraySize;
		delete[] DateAVLArray;
		DateAVLArray = newDateAVLArray;

	}


	int elementsNum;
	int size;
	AVLTree<Data*, Date> *DateAVLArray;
};

#endif
