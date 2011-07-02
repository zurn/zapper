
#include "win_game.h"

win_game::win_game(game * g)
{
	fsm = g;
}

win_game::~win_game()
{
}

void win_game::draw()
{
	gfx::blendMode();
	gfx::color(0,1,1);
	gfx::drawRect(32,32,64,64);

	gfx::color(1, 1, 1);
	gfx::blendMode();

	char buf[256];
	buf[255] = '\0';
	snprintf(buf, sizeof(buf), "You Won the Game!!!!!!");

	font * big = gfx::loadFont("./data/fonts/mono.ttf", 36);
	big->print(buf, gfx::w/2 - big->width(buf)/2, gfx::h/2 - big->height()/2);
}

void win_game::enter()
{
}

void win_game::exit()
{
}

void win_game::pause()
{
}

void win_game::unpause()
{
}

void win_game::update()
{
	if (input::anykey) {
		fsm->change(GS_GAME_OVER);
	}
}

