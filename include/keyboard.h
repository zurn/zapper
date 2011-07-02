
#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#include <vector>
#include <stdio.h>
#include "gfx.h"
#include "input.h"
#include "audio.h"

#define KB_W 11
#define KB_H 7
#define KB_BACK '['
#define KB_CANCEL ']'
#define KB_DONE '|'

class keyboard
{
	public:
		keyboard();
		~keyboard();

		void draw();
		void update();

		void setPosition(int x, int y);
		void drawCursor();
		char getCursor();
		char getChar(int x, int y);
	private:
		int x; //used for cursor position, valid in letters
		int y;
		int wpx; //size in pixels
		int hpx;
		int xoffset; //screen offset for whole grid
		int yoffset;
		char letters[KB_W][KB_H];
		font * alpha;
		font * special;

};
#endif /* __KEYBOARD_H__ */
