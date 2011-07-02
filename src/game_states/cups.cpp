
#include "cups.h"

cups::cups(game * g)
{
	fsm = g;
}

cups::~cups()
{
}

void cups::draw()
{
//	gfx::blendMode();
//	gfx::color(0,1,0);
//	gfx::drawRect(32,32,64,64);
//
//	gfx::color(1, 1, 1);
//	gfx::blendMode();
//
//	char buf[256];
//	buf[255] = '\0';
//	snprintf(buf, sizeof(buf), "TODO make cups mini game");
//
//	font * big = gfx::loadFont("./data/fonts/mono.ttf", 26);
//	big->print(buf, gfx::w/2 - big->width(buf)/2, gfx::h/2 - big->height()/2);
	bonus_round.draw();
}

void cups::enter()
{
	input::keys[KEY_LEFT]->repeat = 0;
	input::keys[KEY_RIGHT]->repeat = 0;
	input::keys[KEY_ACCEPT]->repeat = 0;
	
	audio::song_done();
	bonus_round.reset();
	bonus_round.open_cups();
	bonus_round.change(CUPS_WAIT);
}

void cups::exit()
{
	input::keys[KEY_LEFT]->repeat = 1;
	input::keys[KEY_RIGHT]->repeat = 1;
	input::keys[KEY_ACCEPT]->repeat = 1;

	if (bonus_round.won) {
		fsm->dude->add_points(1500);
	}
}

void cups::pause()
{
}

void cups::unpause()
{
}

void cups::update()
{
	bonus_round.update();
	if (bonus_round.done) {
		if (fsm->world->level_index > 3) {
			fsm->change(GS_GAME_OVER);
		}
		else {
			fsm->change(GS_GET_READY);
		}
	}
}

