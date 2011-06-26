#ifndef ANIMATED_IMAGE_DOT_H
#define ANIMATED_IMAGE_DOT_H 1

#include "gfx.h"
#include "RNG.h"

class sprite
{

	public:

		sprite(char * filename, int xstates, int ystates);
		~sprite();

		void init(char * filename, int xstates, int ystates);

		void update();
		//advances timers

		void draw(int x, int y);
		//draws at position x,y

		void drawX(int x, int y, int statex);
		//draws at position x,y
		//draws frame x (0 -> numStatesX-1)
		void drawY(int x, int y, int statey);

		void drawXY(int x, int y, int statex,int statey);
		//draws at position x,y
		//draws frame x (0 -> numStatesX-1)
		//draws frame y (0 -> numStatesY-1)

		image * pic;
		int delayTime;
		int timer;

		int flipx, flipy;

		int sizeX, sizeY;
		SDL_Rect * src;
		int stateX, numstatesX;
		int stateY, numstatesY;
		sprite();

};


#endif



