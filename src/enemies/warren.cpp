
#include "warren.h"

warren::warren(level * l, particleMan * p, fireworks * f, tip_jar * t)
{
	max_monsters = 3;
	world = l;
	effects = p;
	spells = f;
	tips = t;
}

warren::~warren()
{
	clean();
}

void warren::draw()
{
	std::list<enemy *>::iterator it = critters.begin();
	for( ; it!=critters.end(); ++it ) {
		(*it)->draw();
	}
}

void warren::update()
{
	//update
	std::list<enemy *>::iterator it = critters.begin();
	for( ; it!=critters.end(); ++it ) {
		(*it)->update();
	}

	//possibly spawn a new baddy
	int count = 0;
	std::list<counter*>::iterator c=spawn_times.begin();
	for (; c!=spawn_times.end(); ++c) {
		if ((*c)->is_past()) {
			add(world->bars[count]);
			(*c)->reset();
		}
		++count;
	}

}

void warren::add(bar * b)
{
	if (b->enemy_count > max_monsters) {
		return;
	}
	image * i = world->enemy_pics[ran1_int(0, world->enemy_pics.size())];
	enemy * e = new enemy(b, effects, spells, i, tips);
	critters.push_back(e);
	b->enemy_count++;
}

void warren::clean()
{
	std::list<enemy *>::iterator it = critters.begin();
	for( ; it!=critters.end(); ++it ) {
//		(*it)->place->enemy_count = 0;
		delete (*it);
	}
	critters.clear();

	std::list<counter *>::iterator i = spawn_times.begin();
	for( ; i!=spawn_times.end(); ++i ) {
		delete (*i);
	}
	spawn_times.clear();
	for (unsigned int i=0; i<world->bars.size(); i++) {
		world->bars[i]->enemy_count = 0;
	}
}

void warren::set_counters()
{
	std::list<counter *>::iterator i = spawn_times.begin();
	for( ; i!=spawn_times.end(); ++i ) {
		delete (*i);
	}
	spawn_times.clear();
	for (unsigned int i=0; i<world->bars.size(); i++) {
		counter * temp = new counter;
		temp->set(world->spawn_time);
		int n = int(ran1() * 1000);

		for (int j=0; j<ran1_int(0,10); j++) {
			if (ran1_int(0, 2) == 0) {
				n += 500;
			}
		}

		temp->total += n;
//		printf("after rand add\n");
//		printf("delay %i\n ", temp->total);
//		temp->print();
		spawn_times.push_back(temp);
	}
//	printf("repsawn %i\n", world->spawn_time);
}

void warren::start_level()
{
	clean();
	set_counters();


	for (unsigned int i=0; i<world->bars.size(); i++) {
		int num = 0;
		if (world->level_index < 1) {
			num = ran1_int(0, 3);
		}
		else if (world->level_index < 2) {
			num = ran1_int(0, 4);
		}
		else if (world->level_index < 3) {
			num = ran1_int(1, 5);
		}
		else {
			num = ran1_int(3, 5);
		}
//		printf("creating %i critter\n", num);
		for (int j=0; j<num; j++) {
			add_displaced(world->bars[i], j);
//			critters.back()->pos += j * (critters.back()->vel.unit() * TILE_SIZE);
		}
	}
	if (critters.size() == 0) {
		printf("adding at least 1 critter\n");
		bar * b = world->bars[ran1_int(0, world->bars.size())];
		add_displaced(b, 0);
	}
}

void warren::pause()
{
	std::list<counter *>::iterator i = spawn_times.begin();
	for( ; i!=spawn_times.end(); ++i ) {
		(*i)->pause();
	}

	std::list<enemy *>::iterator ei = critters.begin();
	for(; ei!=critters.end(); ++ei) {
		(*ei)->pause();
	}
}

void warren::unpause()
{
	std::list<counter *>::iterator i = spawn_times.begin();
	for( ; i!=spawn_times.end(); ++i ) {
		(*i)->unpause();
	}
	std::list<enemy *>::iterator ei = critters.begin();
	for(; ei!=critters.end(); ++ei) {
		(*ei)->unpause();
	}
}

void warren::add_displaced(bar * b, int units)
{
	add(b);
	critters.back()->pos += units * (critters.back()->vel.unit() * TILE_SIZE);
}

void warren::random_distract()
{
	std::list<enemy *>::iterator i = critters.begin();
	for(; i!=critters.end(); ++i) {
		if (ran1() > .3) {
			(*i)->change(EMY_DISTRACTED);
		}

	}
}

