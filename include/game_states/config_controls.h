
#ifndef __CONFIG_CONTROLS_H__
#define __CONFIG_CONTROLS_H__

#include "state.h"
#include "game.h"

#define CP_CONFIRM 0
#define CP_UP 1
#define CP_DOWN 2
#define CP_LEFT 3
#define CP_RIGHT 4
#define CP_DEFAULT KEY_CONFIG_TOTAL
#define CP_BACK KEY_CONFIG_TOTAL + 1

class game;
class config_controls: public state
{
	public:
		config_controls(game * g);
		virtual ~config_controls();

		void update();
		void draw();
		void enter();
		void exit();
		void set_names();
		void pause();
		void unpause();

		game * fsm;
		void setHot(int n);
		bool checkKey(int keydef);
	private:
		config_controls();
		font * title;
		font * opt;
		sound * select;
		sound * move;
		sound * bad;
		image * background;

		std::vector<std::string> opts;
		std::vector<std::string> names;
		int hot;
		bool capture;

		state * store;

	private:

};

#endif /* __CONFIG_CONTROLS_H__ */
