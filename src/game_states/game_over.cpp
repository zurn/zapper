
#include "game_over.h"

game_over::game_over(game * g)
{
	fsm = g;
	background = gfx::loadImage("./data/gfx/paper.png");
	big = gfx::loadFont("./data/fonts/bit.ttf", 44);

	delay.set(500);
}

game_over::~game_over()
{
}

void game_over::draw()
{
//	gfx::replaceMode();
//	background->draw(0, 0);

	fsm->world->draw();
	fsm->dude->draw();
	fsm->enemies->draw();
	fsm->effects->draw();
	fsm->spells->draw();


	gfx::color(1, 0, 0);
	gfx::blendMode();

	const char * text = "Game Over";
	int w = big->width(text);

	big->print(text, gfx::w/2 - w/2, gfx::h/2 - big->height()/2);
}

void game_over::enter()
{
	input::clear();
	audio::stopSfx();
//	audio::loadSfx("./data/sfx/powerup.wav")->play(0,1);
	delay.reset();
}

void game_over::exit()
{
}

void game_over::pause()
{
}

void game_over::unpause()
{
}

void game_over::update()
{
	if (input::anykey && delay.is_past()) {

		if (fsm->high_score->is_new_highscore(fsm->dude) > 0) {
			fsm->change(GS_ENTER_NAME);
		}
		else {
			fsm->change(GS_MAIN_MENU);
		}

	}
}

