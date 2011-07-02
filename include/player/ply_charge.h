
#ifndef __PLY_CHARGE_H__
#define __PLY_CHARGE_H__

#include "state.h"
#include "player.h"
#include "counter.h"

class player;

class ply_charge: public state
{
	public:
		ply_charge(player * p);
		virtual ~ply_charge();

		void update();
		void draw();

		void pause();
		void unpause();

		void enter();
		void exit();

		player * fsm;

		counter charge_held;
		emitter * build;
		sound * buzz;
	private:

};
#endif /* __PLY_CHARGE_H__ */
