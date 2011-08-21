
#include "death_by_enemy.h"

death_by_enemy::death_by_enemy(game * g)
{
	fsm = g;
	spawn.set(500);
	total.set(1000);
	count = 0;
}

death_by_enemy::~death_by_enemy() { }

void death_by_enemy::pause() { } 

void death_by_enemy::unpause() { }

void death_by_enemy::draw()
{
	fsm->world->draw();
	fsm->dude->draw();
	fsm->enemies->draw();
	fsm->effects->draw();
	fsm->spells->draw();

	gfx::blendMode();
	gfx::color(1,1,1);

	font * big = gfx::loadFont("./data/fonts/bit.ttf", 22);
	const char * text = fsm->dude->death_message.c_str();
	int w = big->width(text);

	big->print(text, gfx::w/2 - w/2, gfx::h/2 - big->height()/2);
}

void death_by_enemy::enter()
{
	input::clear();
	audio::stopSfx();
	audio::loadSfx("./data/sfx/death.wav")->play(0,1);

	fsm->dude->dead = false;
	spawn.reset();
	total.reset();
	count = 0;

	fsm->enemies->max_monsters = 40;
	fsm->enemies->clean();
}

void death_by_enemy::exit()
{
	fsm->enemies->max_monsters = 3;
	fsm->dude->has_lost = true;
}

void death_by_enemy::update()
{
	for (unsigned int i=0; i<fsm->world->bars.size(); i++) {
		fsm->enemies->add_displaced(fsm->world->bars[i], count);
	}
	count++;
	if (total.is_past() && input::anykey) {
		if (fsm->dude->lives < 1) {
			fsm->change(GS_GAME_OVER);
		}
		else {
			fsm->change(GS_GET_READY);
		}
		return;
	}
}

