
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
	gfx::blendMode();
	gfx::color(0,1,0);
	gfx::drawRect(32,32,64,64);

	gfx::color(1, 1, 1);
	gfx::blendMode();

	char buf[256];
	buf[255] = '\0';
	snprintf(buf, sizeof(buf), "TODO make cups mini game");

	font * big = gfx::loadFont("./data/fonts/mono.ttf", 26);
	big->print(buf, gfx::w/2 - big->width(buf)/2, gfx::h/2 - big->height()/2);
}

void cups::enter()
{
	audio::song_done();
}

void cups::exit()
{
}

void cups::pause()
{
}

void cups::unpause()
{
}

void cups::update()
{
	if (input::anykey) {
		if (fsm->world->level_index > 3) {
			fsm->change(GS_GAME_OVER);
		}
		else {
			fsm->change(GS_GET_READY);
		}
	}
}

