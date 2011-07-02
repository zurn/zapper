
#ifndef __WARREN_H__
#define __WARREN_H__

#include "enemy.h"
#include "bar.h"
#include "level.h"
#include "particleMan.h"
#include "fireworks.h"
#include "counter.h"
#include "tip_jar.h"


#include <list>


class warren
{
	public:
		warren(level * l, particleMan * p, fireworks * f, tip_jar * t);
		virtual ~warren();
		void clean();

		void update();
		void draw();

		void pause();
		void unpause();

		void start_level();
		void add(bar * b);
		void add_displaced(bar * b, int units);
		void random_distract();
		//puts a random number of enemies into their distracted state.

		level * world;
		particleMan * effects;
		fireworks * spells;
		tip_jar * tips;

		int max_monsters;
		std::list<counter *> spawn_times;
		std::list<enemy *> critters;
		void set_counters();
	private:

};
#endif /* __WARREN_H__ */
