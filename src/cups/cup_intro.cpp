
#include "cup_intro.h"

cup_intro::cup_intro(cup_game * c)
{
	fsm = c;
}

cup_intro::~cup_intro()
{
}

void cup_intro::draw()
{
	gfx::replaceMode();
	fsm->background->draw(0,0);

	fsm->draw_cups();

	font * text = gfx::loadFont("./data/fonts/bit.ttf", 24);
	const char * msg = "Follow the gold!!";
	text->print(msg, gfx::w/2 - text->width(msg)/2 , 142);
}

void cup_intro::enter()
{
//	fsm->reset();
}

void cup_intro::exit()
{
}

void cup_intro::pause()
{
}

void cup_intro::unpause()
{
}

void cup_intro::update()
{
	fsm->update_cups();
	if (input::anykey) {
//		fsm->print();
		fsm->change(CUPS_SWAP);
	}
}

