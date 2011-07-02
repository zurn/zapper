
#include "cup_result.h"

cup_result::cup_result(cup_game * c)
{
	fsm = c;
}

cup_result::~cup_result()
{
}

void cup_result::draw()
{
	gfx::replaceMode();
	fsm->background->draw(0,0);

	fsm->draw_cups();

	font * text = gfx::loadFont("./data/fonts/bit.ttf", 24);

	const char * msg;
	if (fsm->won) {
		msg = "1500 Bonus Points!";
	}
	else if (fsm->lost) {
		msg = "Try Again Next Time.";
	}

	text->print(msg, gfx::w/2 - text->width(msg)/2 , 142);
}

void cup_result::enter()
{
}

void cup_result::exit()
{
}

void cup_result::pause()
{
}

void cup_result::unpause()
{
}

void cup_result::update()
{
	if (input::anykey) {
		fsm->done = true;
	}
}

