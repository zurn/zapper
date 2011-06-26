
#ifndef __CUPS_H__
#define __CUPS_H__

#include "state.h"
#include "gfx.h"
#include "game.h"

class game;

class cups: public state
{
	public:
		cups(game * g);
		virtual ~cups();

		void update();
		void draw();

		void pause();
		void unpause();

		void enter();
		void exit();

		game * fsm;

	private:

};
#endif /* __CUPS_H__ */
