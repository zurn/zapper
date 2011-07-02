
#ifndef __DEATH_BY_ENEMY_H__
#define __DEATH_BY_ENEMY_H__

#include "state.h"
#include "game.h"
#include "counter.h"

class game;

class death_by_enemy: public state
{
	public:
		death_by_enemy(game * g);
		virtual ~death_by_enemy();

		void update();
		void draw();

		void pause();
		void unpause();

		void enter();
		void exit();

		game * fsm;
		counter spawn;
		counter total;
		int count;

	private:

};
#endif /* __DEATH_BY_ENEMY_H__ */
