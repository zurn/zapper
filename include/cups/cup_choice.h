
#ifndef __CUP_CHOICE_H__
#define __CUP_CHOICE_H__

#include "state.h"
#include "cup_game.h"
#include "RNG.h"
#include "counter.h"
#include "input.h"

class cup_game;

class cup_choice: public state
{
	public:
		cup_choice(cup_game * c);
		virtual ~cup_choice();

		void update();
		void draw();

		void pause();
		void unpause();

		void enter();
		void exit();

		cup_game * fsm;



	private:

};
#endif /* __CUP_CHOICE_H__ */
