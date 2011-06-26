
#ifndef FONT_H
#define FONT_H

#include "SDL_ttf.h"
#include "texture2d.h"
#include <vector>
#include <unistd.h>

/*
This class utilizes the SDL_ttf library and the gfx class.
A gfx class must be initialzed without failing before this
class will work right.

You can use this class to draw text to the screen.
gfx::enter2DMode() must be called before using the print(...) function.
If you call gfx::blendMode() the text will be rendered to the last color set by
gfx::color(...).
*/

class font
{
	public:
		font();
		//calls init

		font(const char * path, int ptsize,
					int renderstyle = TTF_STYLE_NORMAL);
		//load font with parameters.
		//height() will return 0 if this failed.

		~font();
		//frees all memory

		int load(const char * path, int ptsize,
					int renderstyle = TTF_STYLE_NORMAL);
		//sets data to the font at path, in size ptsize, using renderstyle
		//renderstyle can be TTF_STYLE_NORMAL or a bitwise or combination of
		//TTF_STYLE_BOLD, TTF_STYLE_ITALIC, TTF_STYLE_UNDERLINE
		//SDL_TTF documention warns of possible seg faults when combining the 
		//latter three
		//returns 1 on success
		//returns 0 on failure

		int print(const char * msg, int x, int y);
		//assumes msg is a valid c string
		//draws msg at location x,y
		//no word wrap
		//Only the following characters will be drawn to the screen
		// !"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ
		//[\]^_`abcdefghijklmnopqrstuvwxyz{|}~
		//returns the width of the message in pixels

		int width(const char * msg);
		//assumes msg is a valid c string
		//returns the width of the message in pixels

		int height();
		//returns height of font or 0 if not loaded

	private:
		int init();
		//initialize SDL_ttf if needed and set color to white
		//returns 1 on success
		//returns 0 on failure

		int load_alpha();
		//fills alphabet with appropriate textures
		//returns 1 on success
		//returns 0 on failure

		TTF_Font * data;
		//contains font object after load
		//contains NULL before load or on loading error

		SDL_Color * color;
		//default color for the font, always white
		//a call to glColor4f(...); can then be blended to render the font
		//in any color

		std::vector<texture2d *> alphabet;
		//array filled with a texture for each of the following characters
		// !"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ
		//[\]^_`abcdefghijklmnopqrstuvwxyz{|}~
		//filled after successful load call
};

#endif /* FONT_H */

