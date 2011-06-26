
#include "fireworks.h"

fireworks::fireworks(level *l)
{
	world = l;
}

fireworks::~fireworks()
{
	clean_all();
}

void fireworks::add_enemy(bar * b, object * o)
{
	projectile * p = new projectile(b);

	emitter * sparks = p->sparks;

	sparks->lifetime = -1;
	sparks->max_range = 8;
	sparks->range_mod = .12;

	sparks->rl = 180;
	sparks->rh = 255;

	sparks->gl = 0;
	sparks->gh = 255;

	sparks->bl = 0;
	sparks->bh = 10;


	sparks->render = 0;

	float speed = 2.25;

	if (b->direction ==1) {
		sparks->vel.x = -speed;
	}
	else {
		sparks->vel.x = speed;
	}

	sparks->pos = o->pos;
	sparks->pos.y += .35 * TILE_SIZE;

	sparks->init(50, gfx::loadImage(BIG_PARTICLE));
	sparks->reset();

	from_enemies.push_back(p);
}

void fireworks::add_player(bar * b, object * o)
{
	projectile * p = new projectile(b);

	emitter * sparks = p->sparks;

	sparks->lifetime = -1;
	sparks->max_range = 8;
	sparks->range_mod = .12;

	sparks->rl = 0;
	sparks->rh = 10;


	sparks->gl = 0;
	sparks->gh = 101;


	sparks->bl = 90;
	sparks->bh = 101;

	sparks->render = 0;

	float speed = 4.25;

	if (b->direction ==1) {
		sparks->vel.x = speed;
	}
	else {
		sparks->vel.x = -speed;
	}

	sparks->pos = o->pos;
	sparks->pos.y += .35 * TILE_SIZE;

	sparks->init(50, gfx::loadImage(BIG_PARTICLE));
	sparks->reset();


	from_player.push_back(p);
}

void fireworks::draw()
{
	draw_list(from_player);
	draw_list(from_enemies);
}

void fireworks::pause()
{
}

void fireworks::unpause()
{
}

void fireworks::update()
{
	update_list(from_player);
	update_list(from_enemies);
}

void fireworks::clean(std::list<projectile *> & sparks)
{
	std::list<projectile *>::iterator it = sparks.begin();
	for ( ; it!=sparks.end(); ++it) {
		delete (*it);
	}
	sparks.clear();
}

void fireworks::clean_all()
{
	clean(from_player);
	clean(from_enemies);
}

void fireworks::update_list(std::list<projectile *> & sparks)
{
	std::list<projectile *>::iterator it = sparks.begin();
	for ( ; it!=sparks.end(); ++it) {
		(*it)->update();
		if ((*it)->dead) {
			delete (*it);
			it = sparks.erase(it);
		}
	}
}

void fireworks::draw_list(std::list<projectile *> & sparks)
{
	std::list<projectile *>::iterator it = sparks.begin();
	for ( ; it!=sparks.end(); ++it) {
		(*it)->draw();
	}
}

void fireworks::add_random(int x, int y)
{
	if (world->bars.size() == 0) return;
	projectile * p = new projectile(world->bars[ran1_int(0, world->bars.size())]);

	emitter * sparks = p->sparks;

	sparks->lifetime = -1;
	sparks->max_range = 8;
	sparks->range_mod = .12;

	if (ran1_int(0,2)==0) {
		sparks->rl = 180;
		sparks->rh = 255;

		sparks->gl = 0;
		sparks->gh = 60;

		sparks->bl = 0;
		sparks->bh = 10;
	}
	else {
		sparks->rl = 0;
		sparks->rh = 10;

		sparks->gl = 0;
		sparks->gh = 101;

		sparks->bl = 90;
		sparks->bh = 101;
	}



	sparks->render = 0;

	float speed = 6.25;

	if (ran1_int(0,2)==0) {
		sparks->vel.x = -speed;
	}
	else {
		sparks->vel.x = speed;
	}
	if (ran1_int(0,2)==0) {
		sparks->vel.y = -speed;
	}
	else {
		sparks->vel.y = speed;
	}

	sparks->pos.x = x;
	sparks->pos.y = y;

	sparks->pos.x += ran1_int(-2*TILE_SIZE, 2*TILE_SIZE);
	sparks->pos.y += ran1_int(-2*TILE_SIZE, 2*TILE_SIZE);

//	printf("x %f y %f \n", sparks->pos.x, sparks->pos.y);

	sparks->init(50, gfx::loadImage(BIG_PARTICLE));
	sparks->reset();

	from_enemies.push_back(p);


}

void fireworks::add_vel(int x, int y, Vector vel)
{
	if (world->bars.size() == 0) return;
	projectile * p = new projectile(world->bars[ran1_int(0, world->bars.size())]);

	emitter * sparks = p->sparks;

	sparks->lifetime = -1;
	sparks->max_range = 8;
	sparks->range_mod = .12;

	sparks->rl = 0;
	sparks->rh = 10;

	sparks->gl = 0;
	sparks->gh = 101;

	sparks->bl = 90;
	sparks->bh = 101;



	sparks->render = 0;


	sparks->vel = vel;

	sparks->pos.x = x;
	sparks->pos.y = y;

	sparks->pos.x += ran1_int(-2*TILE_SIZE, 2*TILE_SIZE);
	sparks->pos.y += ran1_int(-2*TILE_SIZE, 2*TILE_SIZE);

//	printf("x %f y %f \n", sparks->pos.x, sparks->pos.y);

	sparks->init(50, gfx::loadImage(BIG_PARTICLE));
	sparks->reset();

	from_enemies.push_back(p);





}

