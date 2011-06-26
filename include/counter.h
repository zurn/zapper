
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
		bool is_past();

		int total;
		int begin;
		int delay;
		bool paused;

	private:

};



#endif /* __COUNTER_H__ */
