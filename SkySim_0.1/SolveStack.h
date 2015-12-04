#pragma once

#include "FSObject.h"
#include "StackObject.h"
#include <iostream>


//class FSObject;

class SolveStack
{
public:
	SolveStack()
	{
		_top = -1;
	};
	void SetParent(FSObject* theFS)
	{
		_parent = theFS;
	}
	int Count(){ return _count; }
	void Add(StackObject* item)
	{
		//check first if item is already there;
		for (int i = 0; i < _count; i++)
		{
			if (item == _items[i])
			{
				return;
			}
		}
		
		_count++;

		//_items = new FSObject[_count];

		//realloc is similar to redim preserve. members of array are preserved and sent to new array (newchildren)
		//should be possible to reallocate straight to itself ie _children = (FSObject**)realloc(...... but this is safer. can catch errors.
		//is this safe? sizeof items may be different cos some are streams some are unit ops. 

		_items = (StackObject**)realloc(_items, _count* sizeof(*item)); //allocate new array

		if (_items != NULL) //if it's null then realloc tak jadi//means theres only one guy;
		{
			_items[_count - 1] = &(*item);
		}
	}

	
	void Forget()
	{
		bool retval = false;
		double fracknown = 0;
		int i = 0;
		int j = 0 ;


		//see who else depends on me. add to stack; 
		//this will only work when editing a spec. first time you solve all will be dirty and added already
		for (int i = 0; i < _count; i++)
		{
			if (_count == _parent->NStackObjects())
			{
				goto arrange;
			}
			for (int j = 0; j < _parent->NStackObjects(); j++)
			{
				if (_parent->GetStackObject(j)->DependsOn(_items[i]))
				{
					_parent->GetStackObject(j)->IsDirty(true);
					Add(_parent->GetStackObject(j));
				}
			}
		}

		//go through each item
		//arrange by isknown?
	arrange:
	//	double fracknownj, fracknownj_ ;

		cout << "";
		for (int i = 0; i < _count; i++)
		{
			j = i;
			//std::cout << _items[j]->Name().c_str() << _items[j]->FractionKnown() << "\n";

			while (j > 0 && _items[j - 1]->FractionKnown() <_items[j]->FractionKnown())
			{
				_swap(j, j - 1);
				j = j - 1;
			}
		}


		//go through each item
		//see who depends on it
		//put that guy next
		StackObject* tempSO = 0;

		for (int i = 0; i < _count; i++)
		{
			tempSO = _items[i];
			for (int j = i+1; j < _count; j++)
			{
				if (_items[j]->DependsOn(tempSO))
				{
					_swap(j, i + 1);
					//_insert(j, i + 1);
				}
			}
		}
	
		for (int i = 0; i < _count; i++)
		{
			std::cout << _items[i]->StackName().c_str() << " fraction known "<< _items[i]->FractionKnown() << "\n";
		}
	}

	bool Solve()
	{
		bool retval = false;
		int itemssolved=0;
		int i = 0;
		bool thisitemsolved;
		int solvepasses=0;
		int nitems = _count;


		std::cout << "stack is: " << "\n";
		for (int k = 0; k < _count; k++)//if i get to second last then must be the last one that needs to be removed;
		{
			std::cout << "item " << k << " is " << _items[k]->StackName().c_str()<< "\n";
		}
		bool testbool;
		while (_count>0)
		{
			
			testbool = true;
			std::cout << "solving " << _items[i]->StackName().c_str() << "\n";
			thisitemsolved = _items[i]->Solve();
			if (thisitemsolved)
			{
				std::cout << "solved " << _items[i]->StackName().c_str() << "\n";
				_items[i]->IsDirty(false);
				testbool = _items[i]->IsDirty();
				if (testbool == false){ std::cout << _items[i]->StackName().c_str() << ":isdirty = false \n"; }
				_remove(_items[i]);
				i--;
			}
			
			i++;

			if (i == _count)
			{
				solvepasses++;
				i = 0;
			}
			
			if (solvepasses == nitems * 5)// at most for n items you need n passes. add one for luck.
			{
				std::cout << "i've tried so hard but didnt get far \n";
				break;
			}
		}
		if (_count==0)
		{ 
			retval = true; 
			std::cout << "Solved in " << solvepasses<< " passes \n";
		}

		return retval;
	}

	//at some point figure out how to move stuff around the stack. Makes it that much faster.
	~SolveStack(){ delete[] _items; };
private:
	int _top;
	StackObject** _items;
	int _count = 0;
	FSObject* _parent;

	
	void _remove(StackObject* item)
	{
		int offset = 0;
		StackObject** newitems;
		if (_count == 1)
		{
			_count = 0;
			_items = NULL;
			return;
		}
		newitems = (StackObject**)realloc(_items, (_count - 1)* sizeof(*item));
		for (int i = 0; i < _count; i++)//if i get to second last then must be the last one that needs to be removed;
		{
			if (_items[i] != item)
			{
				//std::cout << "adding " << _items[i]->Name().c_str() << "\n";
				newitems[i+offset] = &(*_items[i]);
			}
			else
			{
				offset = -1;
				std::cout << "removed " << _items[i]->StackName().c_str() << "\n";
			}
		}
		_count--;
		_items = NULL;
		_items = (StackObject**)realloc(newitems, _count* sizeof(*item)); //allocate to existing array
		
		std::cout << "new stack is: " << "\n";
		for (int i = 0; i < _count ; i++)//if i get to second last then must be the last one that needs to be removed;
		{
			std::cout << "item " << i << " is " << _items[i]->StackName().c_str() << "\n";
		}
	}

	void _insert(int fromindex, int toindex)
	{
		//anything above to index (i>toindex) will be pushed up

	}
	void _move(StackObject* item, int toindex)
	{

	}
	void _swap(int fromindex, int toindex)
	{
		StackObject* tempSO;
		tempSO = _items[fromindex];
		_items[fromindex] = _items[toindex];
		_items[toindex] = tempSO;
	}
};

