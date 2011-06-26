
#ifndef __EMY_DISTRACTED_H__
#define __EMY_DISTRACTED_H__

#include "state.h"
#include "gfx.h"
#include "enemy.h"
#include "counter.h"

class enemy;

class emy_distracted: public state
{
	public:
		emy_distracted(enemy * e);
		virtual ~emy_distracted();

		void update();
		void draw();

		void enter();
		void exit();

		void pause();
		void unpause();

		enemy * fsm;
		counter time_total;
		float spin;

	private:

};
#endif /* __EMY_DISTRACTED_H__ */
