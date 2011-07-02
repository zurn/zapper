
#ifndef __COUNTER_H__
#define __COUNTER_H__

#include "SDL.h"

class counter
{
	public:
		counter();
		~counter();
		void print();

		void pause();
		void unpause();

		void set(int delay);
		//delay in milliseconds
		void reset();
		//call set() again with original value of delay
		//uses set(0); if set was never called before this

		bool is_past();
		//returns true is delay milliseconds have passed
		//returns false otherwise

		int is_left();
		//returns milliseconds till counter reaches zero

		int total;
		int begin;
		int delay;
		bool paused;

	private:

};



#endif /* __COUNTER_H__ */
