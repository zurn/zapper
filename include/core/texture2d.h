
#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include "SDL.h"
#include "SDL_opengl.h"

/*
Bare bones class to encapsulate the conversion between SDL_Surfaces and 
opengl textures.

Used in conjunction with gfx class.  This class will not draw correctly unless
gfx::enter2DMode() has been called.

This class will make any pixel transparent that is 255, 0, 255 (death pink).
*/

class texture2d
{
	public:
		texture2d(SDL_Surface * data);
		//fills texture with data
		//assumes data is a valid surface. You can seg fault here
		//frees the SDL_Surface data

		~texture2d();
		//deletes texture data

		void init();
		//initializes all local variables to 0

		void draw(int x, int y);
		//draws texture at coordinates x,y
		//assumes you called gfx::enter2DMode(..) first

		void drawClipped(int x, int y, SDL_Rect * src);
		//alters texture coordinates to the dimension of src
		//draws texture at coordinates x,y
		//assumes you called gfx::enter2DMode(..) first
		//asumes src is valid SDL_Rect. You could seg fault here

		int flipx;
		//if flipx!=0 then the image is inverted on the x axis when drawn
		int flipy;
		//if flipy!=0 then the image is inverted on the y axis when drawn

		int w, h;
		//actual texture sizes

	private:
		void flip();
		//uses flipx, and flipy to reverse texture coordinates

		void swap(GLfloat &a, GLfloat &b);
		//swaps contents of a and b

		static GLuint load2DTexture(SDL_Surface *surface, GLfloat *texcoord);
		//converts surface to a gl texture
		//puts 4 GLfLoats into texcoord representing texture coordinates
		//returns texture name

		static int power_of_two(int input);
		//returns nearest power of 2 integer that is >= input

		GLuint texture; //texture name
		GLfloat minX, minY; //vertex coordinates
		GLfloat maxX, maxY;
};

#endif /* TEXTURE2D_H */

