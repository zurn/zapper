
#include "win_level.h"

win_level::win_level() { }

win_level::win_level(game * g)
{
	fsm = g;
	wait.set(2250);
}

win_level::~win_level()
{
}

void win_level::draw()
{
	fsm->world->draw();
	fsm->dude->draw();
	fsm->enemies->draw();
	fsm->effects->draw();
	fsm->spells->draw();

	char buf[256];
	buf[255] = '\0';

	gfx::blendMode();
	gfx::color(1, 1, 1);

	snprintf(buf, sizeof(buf), "Lives: %i", fsm->dude->lives);
	gfx::loadFont("./data/fonts/mono.ttf", 16)->print(buf, 0, 0);

	snprintf(buf, sizeof(buf), "Score: %i", fsm->dude->score);
	gfx::loadFont("./data/fonts/mono.ttf", 16)->print(buf, 100, 0);

	snprintf(buf, sizeof(buf), "Level: %i", fsm->dude->level_num);
	gfx::loadFont("./data/fonts/mono.ttf", 16)->print(buf, 300, 0);


	if (fsm->dude->level_num == 13 ) {
		snprintf(buf, sizeof(buf), "10000 Bonus Points!");
	}
	else {
		snprintf(buf, sizeof(buf), "1000 Bonus Points!");
	}
	font * big = gfx::loadFont("./data/fonts/mono.ttf", 36);
	big->print(buf, gfx::w/2 - big->width(buf)/2, gfx::h/2 - big->height()/2 + big->height()/2+ 80);

	if (fsm->dude->level_num == 13 ) {
		snprintf(buf, sizeof(buf), "You Won the Game!");
	}
	else {
		snprintf(buf, sizeof(buf), "Winner!");
	}
	big = gfx::loadFont("./data/fonts/mono.ttf", 36);
	big->print(buf, gfx::w/2 - big->width(buf)/2, gfx::h/2 - big->height()+ 80);

}

void win_level::enter()
{
	audio::stopSfx();
	input::clear();
	if (fsm->dude->level_num == 13 ) {
		fsm->dude->add_points(10000);
		audio::loadSfx("./data/sfx/win_game.wav")->play(4,0);
		wait.set(6000);
	}
	else {
		audio::loadSfx("./data/sfx/win.wav")->play(0,1);
		fsm->dude->add_points(1000);
		wait.set(2250);
	}
	fsm->dude->change(PLY_CELEBRATE);
}

void win_level::exit()
{
	fsm->dude->has_won = true;
}

void win_level::pause()
{
}

void win_level::unpause()
{
}

void win_level::update()
{
	if (wait.is_past() ) {
		fsm->dude->level_num++;

		if (fsm->dude->level_num == 3 ||
			fsm->dude->level_num == 6 ||
			fsm->dude->level_num == 10 ||
			fsm->dude->level_num == 14 ) {
				fsm->world->level_index++;
				fsm->change(GS_CUPS);
				return;
		}


		fsm->change(GS_GET_READY);
		return;
	}
	else {
		fsm->dude->update();
		fsm->world->update();
		fsm->effects->update();
		fsm->spells->update();
	}
}

