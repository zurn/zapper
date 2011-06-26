
#include "tapper.h"

tapper::tapper(game * g)
{
	fsm = g;
}

tapper::~tapper()
{
}

void tapper::draw()
{
	fsm->world->draw();
	fsm->tips->draw();
	fsm->dude->draw();
	fsm->enemies->draw();
	fsm->effects->draw();
	fsm->spells->draw();

	gfx::blendMode();
	gfx::color(1,1,1);


	char buf[256];
	buf[255] = '\0';
	snprintf(buf, sizeof(buf), "Lives: %i", fsm->dude->lives);
	gfx::loadFont("./data/fonts/mono.ttf", 16)->print(buf, 0, 0);

	snprintf(buf, sizeof(buf), "Score: %i", fsm->dude->score);
	gfx::loadFont("./data/fonts/mono.ttf", 16)->print(buf, 100, 0);

	snprintf(buf, sizeof(buf), "Level: %i", fsm->dude->level_num);
	gfx::loadFont("./data/fonts/mono.ttf", 16)->print(buf, 300, 0);

}

void tapper::enter()
{
	input::clear();
}

void tapper::exit()
{
}

void tapper::pause()
{
}

void tapper::unpause()
{
}

void tapper::update()
{
	if (input::pressed(KEY_CANCEL)) {
		fsm->change(GS_PAUSED);
		return;
	}
	if (input::pressed(KEY_DBG_ACCEPT1)) {
		fsm->enemies->add(fsm->dude->place);
	}
	if (input::pressed(KEY_DBG_LEFT)) {
		Vector pos = fsm->dude->pos;
		pos.x -= TILE_SIZE * 2;
		fsm->tips->add(pos);
	}
	if (input::pressed(KEY_DBG_UP)) {
//		fsm->enemies->clean();
		fsm->change(GS_WIN_LEVEL);
//		fsm->dude->has_won = true;
		return;
	}

	if (fsm->dude->dead) {
		fsm->dude->die();
		if (fsm->dude->death_message == DEATH_BY_ENEMY) {
			fsm->change(GS_ENEMY_DEATH);
			return;
		}
		else if (fsm->dude->death_message == DEATH_BY_PROJECTILE) {
			fsm->change(GS_PROJECTILE_DEATH);
			return;
		}
		else {
			fsm->change(GS_GET_READY);
			printf("unknown death\n");
			return;
		}
	}

	if (fsm->enemies->critters.size()==0) {
		fsm->change(GS_WIN_LEVEL);
		return;
	}

	fsm->dude->update();
	fsm->enemies->update();
	fsm->world->update();
	fsm->tips->update();
	fsm->spells->update();
	fsm->effects->update();
	fsm->brains->update();
}

