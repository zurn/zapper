
#ifndef __EMY_CHARGE_H__
#define __EMY_CHARGE_H__

#include "state.h"
#include "counter.h"
#include "enemy.h"

class enemy;

class emy_charge: public state
{
	public:
		emy_charge(enemy * e);
		virtual ~emy_charge();

		void update();
		void draw();

		void enter();
		void exit();

		void pause();
		void unpause();

		enemy * fsm;

		counter charge_held;
		emitter * build;
		sound * buzz;
	private:

};
#endif /* __EMY_CHARGE_H__ */
