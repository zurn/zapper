
#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "level.h"
#include "input.h"
#include "audio.h"
#include "particleMan.h"
#include "machine.h"
#include "tip_jar.h"
#include "fireworks.h"
#include  "object.h"
#include "enemy_states.h"
#include "emy_idle.h"
#include "emy_charge.h"
#include "emy_push_back.h"
#include "emy_distracted.h"

class enemy: public machine, public object
{
	public:
		enemy(bar * b, particleMan * p, fireworks * f, image * i, tip_jar * t);
		virtual ~enemy();

		void create_states();
		void cleanup();


		void reset();
		void start_level();

		void pause();
		void unpause();

		void launch();

		bool past_goal();
		//returns true if the enemy has made it to the far
		//end of the bar its on.

		bool out_of_bounds();
		//returns true if the enemy has been pushed off
		//the level


		Vector vel;

		Vector offset;
		Vector dimension;


		bool flip;
		image * pic;
		sound * shoot;


		bar * place;
		particleMan * effects;
		fireworks * spells;
		tip_jar * tips;

	private:

};
#endif /* __ENEMY_H__ */
