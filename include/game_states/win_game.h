
#ifndef __WIN_GAME_H__
#define __WIN_GAME_H__

#include "state.h"
#include "gfx.h"
#include "game.h"

class game;

class win_game: public state
{
	public:
		win_game(game * g);
		virtual ~win_game();

		void update();
		void draw();

		void pause();
		void unpause();

		void enter();
		void exit();

		game * fsm;

	private:

};
#endif /* __WIN_GAME_H__ */
