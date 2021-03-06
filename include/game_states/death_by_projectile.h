
#ifndef __DEATH_BY_PROJECTILE_H__
#define __DEATH_BY_PROJECTILE_H__

#include "state.h"
#include "game.h"
#include "counter.h"

class game;

class death_by_projectile: public state
{
	public:
		death_by_projectile(game * g);
		virtual ~death_by_projectile();

		void update();
		void draw();

		void pause();
		void unpause();

		void enter();
		void exit();

		game * fsm;
		counter spawn;
		counter total;
	private:

};
#endif /* __DEATH_BY_PROJECTILE_H__ */
