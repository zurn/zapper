
#ifndef __WIN_LEVEL_H__
#define __WIN_LEVEL_H__

#include "state.h"
#include "gfx.h"
#include "game.h"
#include "counter.h"

class game;

class win_level: public state
{
	public:
		win_level(game * g);
		virtual ~win_level();

		void update();
		void draw();

		void pause();
		void unpause();

		void enter();
		void exit();

		game * fsm;
		counter wait;

	private:
		win_level();

};
#endif /* __WIN_LEVEL_H__ */
