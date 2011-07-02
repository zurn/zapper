
#ifndef _2DGRID
#define _2DGRID 1

#include <vector>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "RNG.h"


typedef std::vector<int> row;

//a dynamic 2d matrix class
class grid
{
	public:
		grid();
		grid(int w, int h);
		grid(int w, int h, int color);
		~grid();

		int& operator() (int x, int y);
		//no error checking. you can seg fault using this

		int bounds(int x, int y);
		//returns 0 if x,y are out of bounds
		//returns 1 if x,y are valid indicies

		void build(int w, int h);
		//create new grid of size w,h using fill value
		//erases old data

		int copy(grid * g, int x, int y);
		//returns 0 on failure
		//returns 1 on success
		// copy g->data at this(x,y)


		void print();
		//print w,h and data to stdout


		void print_ppm(char * filename);
		//prints basic image file to filename
		//see http://netpbm.sourceforge.net/doc/ppm.html

		int plot(int x,int y);
		//puts the fill variable at indicies x,y
		//returns 1 on success
		//returns 0 on failure


		void line(int x1, int y1, int x2, int y2);
		void line(int x1, int y1, int x2, int y2, int quit);
		void circle(int x, int y, int radius);
		void flood(int x, int y, int old, int color);
		//4 way connected flood fill


//	private:
		std::vector<row> data;
		int width, height, area;
		int fill; //used by plot as value to be written
};


#endif

