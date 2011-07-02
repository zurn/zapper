
#ifndef __CUP_H__
#define __CUP_H__

#include "object.h"
#include "gfx.h"
#include "counter.h"

class cup: public object
{
	public:
		cup(int x, int y);
		virtual ~cup();

		void draw();
		void update();

		void reset();
		void adjust_pos();

		void start_swap();

		Vector original_pos;
		Vector vel;
		Vector gravity;
		bool go_right;
		bool prized;
		int index;
		//0 -5 the vector in cup_game

		image * empty;
		image * full;
		image * closed;

		image * pic;

		counter delay;
	private:

};
#endif /* __CUP_H__ */
