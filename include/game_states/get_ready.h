
#ifndef __GET_READY_H__
#define __GET_READY_H__


#include "game.h"
#include "state.h"
#include "counter.h"


class game;

class get_ready: public state
{
	public:
		get_ready(game * g);
		virtual ~get_ready();

		void update();
		void draw();
		void enter();
		void exit();
		void pause();
		void unpause();

		game * fsm;

		font * big;
		font * small;
		image * background;
		float fade;
		counter delay;

	private:

};
#endif /* __GET_READY_H__ */
