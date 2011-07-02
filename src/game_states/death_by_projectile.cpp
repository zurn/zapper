
#include "death_by_projectile.h"

death_by_projectile::death_by_projectile(game * g)
{
	fsm = g;
	total.set(2000);
}

death_by_projectile::~death_by_projectile()
{
}

void death_by_projectile::draw()
{
	fsm->world->draw();
	fsm->dude->draw();
	fsm->enemies->draw();
	fsm->effects->draw();
	fsm->spells->draw();

	gfx::blendMode();
	gfx::color(1,1,1);


	char buf[256];
	buf[255] = '\0';
//	snprintf(buf, sizeof(buf), "Lives: %i", fsm->dude->lives);
//	gfx::loadFont("./data/fonts/mono.ttf", 16)->print(buf, 0, 0);
//
//	snprintf(buf, sizeof(buf), "Score: %i", fsm->dude->score);
//	gfx::loadFont("./data/fonts/mono.ttf", 16)->print(buf, 100, 0);

	font * big = gfx::loadFont("./data/fonts/bit.ttf", 22);
	const char * text = fsm->dude->death_message.c_str();
	int w = big->width(text);

	big->print(text, gfx::w/2 - w/2, gfx::h/2 - big->height()/2);
}

void death_by_projectile::enter()
{
	input::clear();
	audio::stopSfx();
	audio::loadSfx("./data/sfx/death.wav")->play(0,1);

	fsm->dude->dead = false;
	total.reset();



	for (int i=0; i<200; i++) {
		fsm->spells->add_random(fsm->dude->pos.x, fsm->dude->pos.y);
	}
	

}

void death_by_projectile::exit()
{
	fsm->dude->has_lost = true;
}

void death_by_projectile::pause()
{
}

void death_by_projectile::unpause()
{
}

void death_by_projectile::update()
{
	if (total.is_past()) {
		if (fsm->dude->lives < 1) {
			fsm->change(GS_GAME_OVER);
		}
		else {
			fsm->change(GS_GET_READY);
		}
		return;
	}



//	fsm->dude->update();
//	fsm->enemies->update();
	fsm->world->update();
	fsm->spells->update();
	fsm->effects->update();
//	fsm->brains->update();
}

