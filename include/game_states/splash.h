#ifndef __SPLASH_H__
#define __SPLASH_H__

#include "state.h"
#include "machine.h"
#include "game_states.h"
#include "gfx.h"
#include "input.h"
#include "audio.h"

class splash: public state
{
	public:
		splash(machine * m);
		virtual ~splash();

		bool init(machine * m);
		void enter();
		void exit();
		void update();
		void draw();
		void pause();
		void unpause();

		machine * fsm;
	private:
		image * bg;
		font * big;
		font * small;
		font * name;
		const char * title;
		const char * me;
		float fade;

};
#endif /* __SPLASH_H__ */
