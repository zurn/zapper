
#ifndef __CREDITS_H__
#define __CREDITS_H__

#include "state.h"
#include "gfx.h"
#include "machine.h"
#include "input.h"
#include "game_states.h"

class credits: public state
{
	public:
		credits(machine * m);
		virtual ~credits();

		void update();
		void draw();

		void pause();
		void unpause();

		void enter();
		void exit();

		machine * fsm;
		image * background;
		font * title;
		font * header;
		font * text;

	private:

};
#endif /* __CREDITS_H__ */
