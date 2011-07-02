
#ifndef __EMY_IDLE_H__
#define __EMY_IDLE_H__

#include "state.h"
#include "enemy.h"
#include "counter.h"

class enemy;

class emy_idle: public state
{
	public:
		emy_idle(enemy * e);
		virtual ~emy_idle();

		void update();
		void draw();

		void enter();
		void exit();

		void pause();
		void unpause();

		enemy * fsm;

		bool skip;
		counter delay;
	private:

};
#endif /* __EMY_IDLE_H__ */
