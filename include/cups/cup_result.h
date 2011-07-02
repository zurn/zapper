
#ifndef __CUP_RESULT_H__
#define __CUP_RESULT_H__

#include "state.h"
#include "cup_game.h"
#include "RNG.h"
#include "counter.h"
#include "input.h"

class cup_game;

class cup_result: public state
{
	public:
		cup_result(cup_game * c);
		virtual ~cup_result();

		void update();
		void draw();

		void pause();
		void unpause();

		void enter();
		void exit();

		cup_game * fsm;
	private:

};
#endif /* __CUP_RESULT_H__ */
