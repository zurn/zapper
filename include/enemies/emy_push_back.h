
#ifndef __EMY_PUSH_BACK_H__
#define __EMY_PUSH_BACK_H__

#include "state.h"
#include "enemy.h"
#include "counter.h"

class enemy;

class emy_push_back: public state
{
	public:
		emy_push_back(enemy * e);
		virtual ~emy_push_back();


		void update();
		void draw();

		void enter();
		void exit();

		void pause();
		void unpause();

		enemy * fsm;

		bool skip;
		counter delay;
		float spin;


	private:

};
#endif /* __EMY_PUSH_BACK_H__ */
