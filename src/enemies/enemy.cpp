
#include "enemy.h"

enemy::enemy(bar * b, particleMan * p, fireworks * f, image * i, tip_jar * t)
{
//	printf("created enemy\n");
	spells = f;
	place = b;
	effects = p;
	tips = t;

	flip = false;
	pic = i;
	shoot = audio::loadSfx("./data/sfx/shoot.wav");

	pos.x = place->endx - (.5*TILE_SIZE);
	pos.y = place->y;

//	printf("monster %i %i\n", (int)pos.x, (int)pos.y);
	if (place->direction == 1) {
		flip = true;
		vel.x -= .25;
	}
	else {
		vel.x += .25;
		flip = false;
	}


	offset.y = 0;
	offset.x = .5 * TILE_SIZE;

	dimension.x = TILE_SIZE;
	dimension.y = TILE_SIZE;


	create_states();
}

enemy::~enemy()
{
	cleanup();
}

void enemy::cleanup()
{
	for (unsigned int i=0; i<states.size(); i++) {
		if (states[i] != NULL)
			delete states[i];
	}
}

void enemy::create_states()
{
	states.resize(EMY_NUM_STATES, NULL);


	current = 
	states[EMY_IDLE]       = new emy_idle(this);
	states[EMY_CHARGE]     = new emy_charge(this);
	states[EMY_PUSH_BACK]  = new emy_push_back(this);
	states[EMY_DISTRACTED] = new emy_distracted(this);

	current->enter();
}

void enemy::launch()
{
	spells->add_enemy(place, this);
}

void enemy::pause()
{
	current->pause();
}

void enemy::reset()
{
}

void enemy::start_level()
{
}

void enemy::unpause()
{
	current->unpause();
}

bool enemy::past_goal()
{
	if (vel.x > 0) {
		if (pos.x > place->startx) {
			return true;
		}
	}
	else {
		if (pos.x < place->startx) {
			return true;
		}
		
	}
	return false;
}

bool enemy::out_of_bounds()
{
	if (vel.x > 0) {
		if (pos.x < place->endx - .5 * TILE_SIZE) {
			return true;
		}
	}
	else {
		if (pos.x > place->endx - .5 * TILE_SIZE) {
			return true;
		}
		
	}
	return false;
}

