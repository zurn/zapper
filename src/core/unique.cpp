
#include "unique.h"

//-------------------------------------------------------------------

unique::unique(int maximum)
{
	count = 1;
	if (maximum < 1)
		max = 1;
	else
		max = maximum;
}

//-------------------------------------------------------------------

unique::~unique(){}

//-------------------------------------------------------------------

int unique::getID()
{
	int rv;
	if (freeList.size() == 0) {
		if (count == max) {
			rv = -1;
		} else {
		rv = count;
		count++;
		}

	} else {
		rv = freeList.front();
		freeList.erase(freeList.begin());
	}
	return rv;
}

//-------------------------------------------------------------------

int unique::freeID(int id)
{
	if (id > 0 && id < max) {
		if (find(freeList.begin(), freeList.end(), id) == freeList.end()) {
			freeList.push_back(id);
			return 1;
		}
		else
			return 0;
	}
	else
		return 0;
}

//-------------------------------------------------------------------

