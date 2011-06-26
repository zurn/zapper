
#include "machine.h"

machine::machine()
{
//	printf("machine make\n");
	current = NULL;
	last = NULL;
//	states = NULL;
}

machine::~machine()
{
}

void  machine::change(int id)
{
//	printf("machine change: %i\n", id);
//	state * next = getState(id);
	state * next = states[id];

		if (next!=NULL) {
//		printf("machine: changeed\n");
			if (current!=NULL) {
				history.push_back(current);
				current->exit();
			}
			next->enter();
			last = current;
			current = next;
			next = NULL;
		}
//		else
//			printf("machine: no changeed\n");

}

void machine::revert()
{
	last = history.back();
	history.pop_back();
	if (current != NULL && last != NULL) {
		current->exit();
		last->enter();
		state * temp = current;
		current = last;
		last = temp;
	}

}

void machine::update()
{
	if (current != NULL)
		current->update();
}

void machine::draw()
{
	if (current != NULL)
		current->draw();
}

