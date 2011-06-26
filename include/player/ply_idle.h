
#ifndef __PLY_IDLE_H__
#define __PLY_IDLE_H__

#include "player.h"
#include "state.h"
#include "counter.h"

class player;

class ply_idle: public state
{
	public:
		ply_idle(player * p);
		virtual ~ply_idle();


		void update();
		void draw();

		void pause();
		void unpause();

		void enter();
		void exit();

		player * fsm;
		bool skip;
		counter delay;
	private:

};
#endif /* __PLY_IDLE_H__ */
