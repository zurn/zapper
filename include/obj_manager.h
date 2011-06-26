
#ifndef __OBJ_MANAGER_H__
#define __OBJ_MANAGER_H__

#include "player.h"
#include "fireworks.h"
#include "warren.h"
#include "tip_jar.h"

class obj_manager
{
	public:
		obj_manager(warren * w, player * p, fireworks * f, tip_jar * t);
		virtual ~obj_manager();

		void update();
		void draw();

		void pause();
		void unpause();

		warren * enemies;
		player * dude;
		fireworks * spells;
		tip_jar * tips;



		bool collide(object * o, object * t);
		bool collide(object * o, projectile * p);
		bool enemy_out_of_bounds(projectile * p);
		bool player_out_of_bounds(projectile * p);

	private:

};
#endif /* __OBJ_MANAGER_H__ */
