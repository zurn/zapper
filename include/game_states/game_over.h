
#ifndef __GAME_OVER_H__
#define __GAME_OVER_H__

#include "state.h"
#include "game.h"

class game;

class game_over: public state
{
	public:
		game_over(game * g);
		virtual ~game_over();

		void update();
		void draw();
		void pause();
		void unpause();
		void enter();
		void exit();


		counter delay;
		game * fsm;
		image * background;
		font * big;
	private:

};
#endif /* __GAME_OVER_H__ */
