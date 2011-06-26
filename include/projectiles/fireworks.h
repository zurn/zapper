
#ifndef __FIREWORKS_H__
#define __FIREWORKS_H__

#include "projectile.h"
#include "level.h"
#include "object.h"

#include <list>

class fireworks
{
	public:
		fireworks(level * l);
		~fireworks();

		void update();
		void draw();

		void pause();
		void unpause();


		void update_list(std::list<projectile *> & sparks);
		void draw_list(std::list<projectile *> & sparks);

		void add_random(int x, int y);
		//used for death sequence of the player

		void add_vel(int x, int y, Vector vel);
		//adds a projectile at location x,y with a starting velocity of vel
		//used for a player win sequence.

		void add_enemy(bar * b, object * o);
		//adds a projectile to the game, shot from an enemy

		void add_player(bar * b, object * o);
		//adds a projectile to the game, shot from the player


		void clean(std::list<projectile *> & sparks);
		//deletes all projectiles in list sparks

		void clean_all();
		//frees all projectiles.  used for restarting a level

		std::list<projectile *> from_player;
		std::list<projectile *> from_enemies;


		level * world;

	private:

};
#endif /* __FIREWORKS_H__ */
