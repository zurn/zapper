
#ifndef IMAGE_H
#define IMAGE_H

#include "SDL_image.h"
#include "texture2d.h"

/*
This class utilizes the SDL_image library and the gfx class.
A gfx class must be initialzed without failing before this
class will work right.

You can use this class to draw images to the screen.
gfx::enter2DMode() must be called before using any draw functions

If you call gfx::blendMode() before drawing,the data will be blended
with the last color set by gfx::color(...) when rendered.
If you call gfx::replaceMode() before drawing, the data will be drawn as 
normal.

This class supports transparency and also defaults to set pixels of 255, 0, 255
to be transparent via the texture2d class.
*/

class image
{
	public:
		image();
		//sets data to NULL

		image(const char * filename);
		//calls load with filename
		//width() and height() will return 0 if this fails

		~image();
		//frees data if necessary

		int load(const char * filename);
		//assumes filename is a valid c string
		//sets data to contain picture file at filename
		//returns 0 on failure
		//returns 1 on success

		void draw(int x, int y, int flipx = 0, int flipy = 0);
		//draws data to the screen at location x,y
		//if flipx!=0 then the image is inverted on the x axis when drawn
		//if flipy!=0 then the image is inverted on the y axis when drawn

		void drawClipped(int x, int y , SDL_Rect * src, int flipx=0, int flipy=0);
		//assumes src is a valid SDL_Rect
		//assumes src can be contained within data's width and height
		//draws the portion of data provided by src onto the screen at x,y
		//if flipx!=0 then the image is inverted on the x axis when drawn
		//if flipy!=0 then the image is inverted on the y axis when drawn

		void drawRotate(int x, int y, float a, int flipx=0, int flipy=0);
		//only works for images with h and w as equal powers of 2
		//draws data on the screen at x,y rotated by a

		int width();
		//returns file's width

		int height();
		//returns file's height

	private:
		texture2d * data;
		//image data
		//NULL if not loaded or on error
};

#endif /* IMAGE_H */

