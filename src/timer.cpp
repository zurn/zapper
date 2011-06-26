
#include "timer.h"

//---------------------------------------------------------------------------

timer::timer(int rate)
{
//	frame = 0;
//	fps = rate;
//	last = SDL_GetTicks();
//	fps_ticks = 1000.0 / (float)rate;

	setFPS(rate);
}

timer::timer(){}
timer::~timer(){}

//---------------------------------------------------------------------------

void timer::setFPS(int rate)
{
	frame = 0;
	fps = rate;
	last = SDL_GetTicks();
	fps_ticks = 1000.0 / (float)rate;
}

//---------------------------------------------------------------------------

void timer::delay()
{
	frame++;
	int delay;
	int current = SDL_GetTicks();

	int target = last + frame * fps_ticks;
	if (current <= target) {
		delay = target - current;
		SDL_Delay(delay);
	}
	else {
		frame = 0;
		last = current;
	}

}

//---------------------------------------------------------------------------

