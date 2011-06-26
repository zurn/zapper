#ifndef COLOR_H
#define COLOR_H

#include <stdio.h>
#include "gfx.h"

//a class to manage colors in the form of 4 floats.
//they are the red green blue and alpha components of a color

class color
{
	public:
		color();
		color(float r, float g, float b, float a = 1.0);
		~color();

		void init();
		void print();
		void set();

		void change(float r, float g, float b, float a = 1.0);
		void r(float r);
		void g(float g);
		void b(float b);
		void a(float a);

	private:
		float * rgba;
};

#endif /* COLOR_H */

