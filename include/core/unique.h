#ifndef UNIQUE_H
#define UNIQUE_H

#include <list>
#include <algorithm>

/*
This class manages a list of unique positive integers.
*/

class unique
{
	public:
		unique(int maximum);
		//maximum will specify how many unique integers will be available.
		//1 through maximum -1

		~unique();//empty

		int getID();
		//returns an available integer from the list
		//returns -1 if they have all been used already

		int freeID(int id);
		//Makes the specifed id available again.
		//Only works if id is in range 1 to max-1 and is not already free
		//returns 1 on success
		//returns 0 on failure

	private:
		std::list<int> freeList;
		int max; //total number of integers available
		int count; //keeps track of ids given out
};

#endif /* UNIQUE_H */

