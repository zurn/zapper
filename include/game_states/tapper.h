
#ifndef __TAPPER_H__
#define __TAPPER_H__

#include "state.h"
#include "gfx.h"
#include "game.h"

class game;

class tapper: public state
{
	public:
		tapper(game * g);
		virtual ~tapper();

		void update();
		void draw();

		void pause();
		void unpause();

		void enter();
		void exit();

		game * fsm;

	private:

};
#endif /* __TAPPER_H__ */
