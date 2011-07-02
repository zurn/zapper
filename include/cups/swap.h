
#ifndef __SWAP_H__
#define __SWAP_H__

#include "state.h"
#include "cup_game.h"
#include "RNG.h"
#include "counter.h"

class cup_game;

class swap: public state
{
	public:
		swap(cup_game * cg);
		virtual ~swap();

		void update();
		void draw();

		void pause();
		void unpause();

		void enter();
		void exit();

		cup_game * fsm;

		counter swap_delay;
		bool swap_inner;
		int show_count;
		int closed_count;
	private:

};
#endif /* __SWAP_H__ */
