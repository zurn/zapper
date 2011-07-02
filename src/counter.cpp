
#include "counter.h"

counter::counter()
{
	total = 0;
	begin = 0;
	delay = 0;
	paused = false;
}

counter::~counter() { }

void counter::print()
{
	printf("time left: %i\n", delay - (SDL_GetTicks()-begin+total));
	printf("del %i began %i total %i\n\n", delay, begin, total);
}

bool counter::is_past()
{
	if (paused) {
		return false;
	}
	if (((int)SDL_GetTicks() - begin) + total >= delay) {
//		printf("total time passed: %i\n",((int)SDL_GetTicks() - begin) + total);
		return true;
	}
	else {
		return false;
	}
}

void counter::set(int delay)
{
	counter::delay = delay;
	total = 0;
	paused = true;
	unpause();
}

void counter::pause()
{
	if (paused) return;
	total += (SDL_GetTicks() - begin);
//	printf("counter paused\n");
	paused = true;
}

void counter::unpause()
{
	if (!paused) return;
//	printf("counter unpaused\n");
	begin = SDL_GetTicks();
	paused = false;
}

void counter::reset()
{
	set(delay);
}

int counter::is_left()
{
	int left = (int)SDL_GetTicks() - begin + total;
	if (left <= 0) {
		return 0;
	}
	else {
		return left;
	}
}

