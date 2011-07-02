
#include "sprite.h"

sprite::sprite(char * filename, int xstates, int ystates)
{
	src = new SDL_Rect;
	init(filename, xstates, ystates);
}

sprite::sprite()
{ }

sprite::~sprite()
{
	delete src;
}

void sprite::draw(int x, int y)
{
	pic->drawClipped(x, y, src,flipx, flipy);
}

void sprite::drawX(int x, int y, int statex)
{
	stateX = statex;
	draw(x,y);
}

void sprite::drawY(int x, int y, int statey)
{
	int temp = stateY;
	stateY = statey;
	draw(x,y);
	stateY = temp;
}

void sprite::drawXY(int x, int y, int statex,int statey)
{
	src->x = statex * sizeX;
	src->y = statey * sizeY;

	pic->drawClipped(x, y, src, flipx, flipy);
}

void sprite::init(char * filename, int xstates, int ystates)
{
	pic = gfx::loadImage(filename);

	numstatesX = xstates;
	numstatesY = ystates;

	src->w = sizeX = pic->width() / xstates;
	src->h = sizeY = pic->height() / ystates;

	stateY = 0;
//	stateX = rand() % numstatesX;
	stateX = ran1_int(0, numstatesX +1);

	flipx = flipy = 0;

	delayTime = 1000 / (numstatesX * numstatesX * 2);
	timer=SDL_GetTicks();
}

void sprite::update()
{
	if (numstatesX > 1 ) {
		if ((int)SDL_GetTicks() > timer + delayTime) {

			stateX++;
			if (stateX >= numstatesX)
				stateX = 0;

			timer = SDL_GetTicks();
		}
	}

	src->x = stateX * sizeX;
	src->y = stateY * sizeY;

}

