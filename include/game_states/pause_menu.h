
#ifndef __PAUSE_MENU_H__
#define __PAUSE_MENU_H__

#include "state.h"
#include "game.h"

#define PM_RETURN 0
#define PM_OPTIONS 1
#define PM_QUIT 2

class game;

class pause_menu: public state
{
	public:
		pause_menu(game * g);
		virtual ~pause_menu();

		void update();
		void draw();
		void enter();
		void exit();
		void pause();
		void unpause();

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
#endif /* __PAUSE_MENU_H__ */
