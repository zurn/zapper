#ifndef BUTTON_H
#define BUTTON_H

#include "SDL.h"

class button
{
	public:
		button(int key);
		button(int key, int repeated);


		button();
		~button();

		void update();
		void init();
		void clear();
		void set(int key);

		int last;
		int pressed;
		int binding;
		int delay;
		int repeat;

		int time;


	private:
		/*button data */
};


#endif /* BUTTON_H */

