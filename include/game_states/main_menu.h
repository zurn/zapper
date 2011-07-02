
#ifndef __MAIN_MENU_H__
#define __MAIN_MENU_H__

#include "state.h"
#include "gfx.h"
#include "game.h"

class game;


#define MM_PLAY 0
#define MM_HIGH 1
#define MM_OPTIONS 2
#define MM_CREDITS 3
#define MM_QUIT 4
#define MM_SPLASH 5


class main_menu: public state
{
	public:
		main_menu(game * g);
		virtual ~main_menu();

		void update();
		void draw();

		void pause();
		void unpause();

		void enter();
		void exit();

		game * fsm;
		void set_hot(int n);
	private:

		font * title;
		font * opt;
		sound * select;
		sound * move;
		image * background;

		std::vector<std::string> options;
		int hot;
};


#endif /* __MAIN_MENU_H__ */
