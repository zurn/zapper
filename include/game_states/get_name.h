
#ifndef __GET_NAME_H__
#define __GET_NAME_H__

#include "state.h"
#include "game_states.h"
#include "keyboard.h"
#include <string>
#include "game.h"

class game;

#define NAME_LENGTH 10

class get_name: public state
{
	public:
		get_name(game * g);
		virtual ~get_name();

		void enter();
		void exit();
		void update();
		void draw();
		void pause();
		void unpause();

		game * fsm;

	private:
		std::string name;
		font * title;
		image * bg;
		player * rogue;
		keyboard * options;
		sound * select;
		sound * error;

};
#endif /* __GET_NAME_H__ */
