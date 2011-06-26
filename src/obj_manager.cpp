
#include "obj_manager.h"

obj_manager::obj_manager(warren * w, player * p, fireworks * f, tip_jar * t)
{
	enemies = w;
	dude = p;
	spells = f;
	tips = t;
}

obj_manager::~obj_manager()
{
}

void obj_manager::draw()
{
}

void obj_manager::pause()
{
}

void obj_manager::unpause()
{
}

void obj_manager::update()
{
	//loop through all enemies 
	std::list<enemy *>::iterator it = enemies->critters.begin();
	for(; it!=enemies->critters.end(); ++it) {
		enemy * e = (*it);

		//check to see if the enemy has wandered into victory
		if (e->past_goal()) {
			dude->dead = true;
			dude->death_message = DEATH_BY_ENEMY;
			e->place->enemy_count--;
			delete e;
			it = enemies->critters.erase(it);
//			enemies->go_crazy();
			break;
		}

		//check to see if the enemy was thrown out of the field of play
		if (e->out_of_bounds()) {
			audio::loadSfx("./data/sfx/mug.wav")->play(0,1);
			dude->add_points(50);
			e->place->enemy_count--;
			delete e;
			it = enemies->critters.erase(it);
			continue;
		}

		//check to see if they have been hit with any player projectiles
		std::list<projectile *>::iterator pit = spells->from_player.begin();
		for(; pit!=spells->from_player.end(); ++pit) {
			projectile * p = (*pit);

			if (collide(e, p)) {
				e->change(EMY_PUSH_BACK);

				delete p;
				pit = spells->from_player.erase(pit);

			}
		}
	}

	//loop through all enemy projectiles
	std::list<projectile *>::iterator pit = spells->from_enemies.begin();
	for(; pit!=spells->from_enemies.end(); ++pit) {
		projectile * p = (*pit);
		if (collide(dude, p)) {
			dude->add_points(100);
			pit = spells->from_enemies.erase(pit);
			audio::loadSfx("./data/sfx/catch.wav")->play(0,1);
			delete p;
			continue;
		}

		if (enemy_out_of_bounds(p)) {
			printf("enemy p out of bounds\n");
			pit = spells->from_enemies.erase(pit);
			delete p;
			dude->dead = true;
			dude->death_message = DEATH_BY_PROJECTILE;
			continue;
		}
	}

	//loop through all player projectiles
	std::list<projectile *>::iterator pp = spells->from_player.begin();
	for(; pp!=spells->from_player.end(); ++pp) {
		projectile * p = (*pp);
		if (player_out_of_bounds(p)) {
			printf("player p out of bounds\n");
			delete p;
			pp = spells->from_player.erase(pp);
			dude->dead = true;
			dude->death_message = DEATH_BY_PROJECTILE;
			continue;
			
		}
	}

	//if the player touches a tip change
	//enemies to emy_distracted state.
	{
		tip_list::iterator i = tips->tips.begin();
		for (; i != tips->tips.end(); ++i) {
			if (collide(dude, (*i))) {
				enemies->random_distract();
				dude->add_points(1500);
				audio::loadSfx("./data/sfx/tip.wav")->play(0,1);
				delete (*i);
				i = tips->tips.erase(i);
			}
		}
	}
}

bool obj_manager::collide(object * o, projectile * p)
{
	if (!o->collidable) {
		return false;
	}
	Vector offset;
	Vector dimension;

	offset.y = 0;
	offset.x = .5 * TILE_SIZE;

	dimension.x = TILE_SIZE;
	dimension.y = TILE_SIZE;


	int x1 = o->pos.x - offset.x;
	int y1 = o->pos.y - offset.y;
	int x2 = x1 + dimension.x;
	int y2 = y1 + dimension.y;


	if (p->sparks->pos.x < x1 || p->sparks->pos.x > x2 ||
		p->sparks->pos.y < y1 || p->sparks->pos.y > y2) {
		return false;
	}

	return true;
}

bool obj_manager::enemy_out_of_bounds(projectile * p)
{
	bar * place = p->place;
	Vector vel = p->sparks->vel;
	Vector pos = p->sparks->pos;

	if (vel.x > 0) {
		if (pos.x > place->startx ) {
//			printf("pos %f %f\nsx ex %i %i\n", pos.x, pos.y, place->startx, place->endx);
			return true;
		}
	}
	else {
		if (pos.x < place->startx - .5 * TILE_SIZE) {
			return true;
		}
		
	}
	return false;
}

bool obj_manager::player_out_of_bounds(projectile * p)
{
	bar * place = p->place;
	Vector vel = p->sparks->vel;
	Vector pos = p->sparks->pos;

	if (vel.x > 0) {
		if (pos.x > place->endx ) {
//			printf("pos %f %f\nsx ex %i %i\n", pos.x, pos.y, place->startx, place->endx);
			return true;
		}
	}
	else {
		if (pos.x < place->endx - .5 * TILE_SIZE) {
			return true;
		}
		
	}
	return false;
}

bool obj_manager::collide(object * o, object * t)
{
	int x1 = o->pos.x;
	int y1 = o->pos.y;
	int x2 = x1 + TILE_SIZE;
	int y2 = y1 + TILE_SIZE;

	if (t->pos.x + TILE_SIZE < x1 || t->pos.x > x2 ||
		t->pos.y + TILE_SIZE < y1 || t->pos.y > y2) {
		return false;
	}
	return true;
}

