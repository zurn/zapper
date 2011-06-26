
#include "button.h"

//-------------------------------------------------------------------

button::button()
{
	init();
}

//-------------------------------------------------------------------

button::button(int key)
{
	init();
	binding = key;
}

//-------------------------------------------------------------------

button::button(int key, int repeated)
{
	init();
	binding = key;
	repeat = repeated;

}

//-------------------------------------------------------------------

button::~button(){}

//-------------------------------------------------------------------

void button::init()
{
	last = 0;
	pressed = 0;
	binding = 0;
	delay = 10;
	repeat = 0;
	time = SDL_GetTicks();
}

//-------------------------------------------------------------------

void button::set(int key)
{
//	init();
	clear();
	binding = key;
}

//-------------------------------------------------------------------

void button::update()
{
	Uint8 * keystate = SDL_GetKeyState(NULL);
	int now = SDL_GetTicks();

	if (repeat) {
		if (keystate[binding]) { //user pressed the button
			if (now > delay + time) {
					pressed = 1;
				time = now;
			}
			else {
				pressed = 0;
			}
		}
		else {
			pressed = 0;
		}
	}
	else { //not repeating
		if (!pressed && keystate[binding]) {
			last = 1;
			pressed = 1;
		}
		else {
			pressed = keystate[binding] = 0;
		}
	}
}

//-------------------------------------------------------------------

void button::clear()
{
	Uint8 * keystate = SDL_GetKeyState(NULL);
	pressed = 0;
	time = SDL_GetTicks();
	keystate[binding] = 0;
}

//-------------------------------------------------------------------


