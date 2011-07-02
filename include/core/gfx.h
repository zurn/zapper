#ifndef GFX_H
#define GFX_H

#include "SDL.h"
#include "SDL_opengl.h"
#include "fontFactory.h"
#include "imageFactory.h"

/*
This class will setup up a window with SDL and use OpenGL to render on it.
After initialization OpenGL's state is ready for 2D drawing.
The coordinate system mimics SDL's. Upper left corner is (0,0).  The lower
right corner is (screenWidth, screenHeight).
*/

//the default sizes of the window to be created
#define WINDOW_W 640
#define WINDOW_H 480 

class gfx
{
	private:
		gfx();
		//calls init()
		//calls setupScreen()
		//calls enter2DMode()
		//exits PROGRAM on failure

		~gfx();
		//quits SDL

	public:
		static int setupScreen();
		//initializes display
		//returns 1 on success
		//returns 0 on failure

		static int init();
		//intializes SDL and calls setupScreen
		//returns 1 on success
		//returns 0 on failure

		static void cleanup();

		static void clear();
		//clear screen

		static void swap();
		//swap buffers

		static void BMPshot(char * filename);
		//save a bmp of the current screen

		static void print();
		//print screen info

		static void color(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1.0);
		//sets color used to draw primitives or with blending

		static void enter2DMode();
		//setup the opengl state for drawing in 2d with SDL like screen coords
		//saves matrix modes and attributes that will be changed

		static void leave2DMode();
		//undo enter2DMode

		static void drawRect(int x, int y, int w, int h);
		//draws a rectangle with the passed in dimensions at x,y
		//rectangle is filled with current color values

		static void drawFrame(int x, int y, int w, int h, int width);
		//draws a box between two points, with line at width pixels

		static void blendMode();
		//changes textures to blend with current color
		//use before rendering with a font class

		static void replaceMode();
		//changes textures to ignore current color
		//use before rendering with an image class

		static void modMode();
		//changes textures to modulate color
		//GL_MODULATE mode

		/* all the following variables are used by setupScreen() */

		static int bpp, sync, accel, gamma, fullscreen, noframe, fsaa, w, h;
		//set these values and call setupScreen() to update changes

		static const char * title;
		//windows title bar text

		static const char * iconName;
		//window icon name

		static const char * icon;
		//path to icon .bmp file for the window

		static font * loadFont(const char * path, int ptsize);
		//uses the font factory to distribute font data

		static image * loadImage(const char * path);
		//uses the image factory to distrube image data

//	private:
		static SDL_Surface * screen;

		static fontFactory ffact;
		static imageFactory ifact;

};

#endif /* GFX_H */

