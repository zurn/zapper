
#include "cup_choice.h"

cup_choice::cup_choice(cup_game * c)
{
	fsm = c;
}

cup_choice::~cup_choice()
{
}

void cup_choice::draw()
{
	gfx::replaceMode();
	fsm->background->draw(0,0);

	fsm->draw_cups();
	font * text = gfx::loadFont("./data/fonts/bit.ttf", 24);
	const char * msg = "Where is the Gold?";
	text->print(msg, gfx::w/2 - text->width(msg)/2 , 142);

	fsm->draw_cups();
	fsm->cursor.draw();
}

void cup_choice::enter()
{
	fsm->cursor.reset();
//	fsm->print();
}

void cup_choice::exit()
{
}

void cup_choice::pause()
{
}

void cup_choice::unpause()
{
}

void cup_choice::update()
{
	fsm->cursor.update();
	if (input::pressed(KEY_LEFT)) {
		fsm->cursor.set_hot(fsm->cursor.hot - 1);
		fsm->cursor.bamf->play(0,1);
		fsm->cursor.flip = true;
	}
	if (input::pressed(KEY_RIGHT)) {
		fsm->cursor.set_hot(fsm->cursor.hot + 1);
		fsm->cursor.bamf->play(0,1);
		fsm->cursor.flip = false;
	}
	if (input::pressed(KEY_ACCEPT)) {
		if (fsm->cups[fsm->cursor.hot]->prized) {
			fsm->won = true;
			audio::loadSfx("./data/sfx/bonus.wav")->play(0,1);
		}
		else {
			audio::loadSfx("./data/sfx/bad.wav")->play(0,1);
			fsm->lost = true;
		}
		fsm->open_cups();
		fsm->change(CUPS_RESULT);
	}
	if (input::pressed(KEY_DOWN)) {
		fsm->done = true;
	}
}

