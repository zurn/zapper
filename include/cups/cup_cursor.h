
#ifndef __CUP_CURSOR_H__
#define __CUP_CURSOR_H__

#include "gfx.h"
#include "emitter.h"
#include "audio.h"
#include "matho.h"

class cup_cursor
{
	public:
		cup_cursor();
		virtual ~cup_cursor();

		void update();
		void draw();
		void reset();


		int hot;
		void set_hot(int n);

		Vector pos;
		image * pic;
		emitter * tele;
		sound * bamf;
		bool flip;

	private:

};
#endif /* __CUP_CURSOR_H__ */
