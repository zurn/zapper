
#ifndef __PLY_CELEBRATE_H__
#define __PLY_CELEBRATE_H__

#include "state.h"
#include "player.h"
#include "counter.h"

class player;

class ply_celebrate: public state
{
	public:
		ply_celebrate(player * p);
		virtual ~ply_celebrate();

		void update();
		void draw();

		void pause();
		void unpause();

		void enter();
		void exit();

		player * fsm;
		float spin;
	private:

};
#endif /* __PLY_CELEBRATE_H__ */
