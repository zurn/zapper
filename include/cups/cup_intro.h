
#ifndef __CUP_INTRO_H__
#define __CUP_INTRO_H__

#include "state.h"
#include "cup_game.h"
#include "RNG.h"
#include "counter.h"
#include "input.h"

class cup_game;

class cup_intro: public state
{
	public:
		cup_intro(cup_game * c);
		virtual ~cup_intro();

		void update();
		void draw();

		void pause();
		void unpause();

		void enter();
		void exit();

		cup_game * fsm;

	private:

};
#endif /* __CUP_INTRO_H__ */
