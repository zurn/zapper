
#ifndef MACHINE_H
#define MACHINE_H

#include "state.h"
#include <vector>
#include <list>
#include <stdio.h>

typedef std::vector<state *> stateCollection;
typedef std::list<state *> stateHistory;

class machine
{
	public:
		machine();
		~machine();


		void update();
		void draw();

		void change(int state);
		void revert();

		state * current;
		state * last;
		stateCollection states;
		stateHistory history;

};

#endif /* MACHINE_H */

