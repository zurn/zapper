
#ifndef FONTFACTORY_H
#define FONTFACTORY_H

#include "font.h"
#include <map>
#include <list>
#include <utility>
#include "utilities.h"

/*
This class uses the factory pattern to control the creation of fonts.
Each file and size combo will only ever be created once, as long as it
remains loaded.

Fonts are stored as follows...
Each file name is associated with a list of sizes.
Each size is associated with a pointer to a font class.

so the declaration looks like this
std::map<const char *, std::list<std::pair<int, font *> >, ltstr>
*/

//some typedefs to make the code easier to read
typedef std::list<std::pair<int, font *> > sizes;
typedef std::map<const char *, sizes *, ltstr> fmap;

class fontFactory
{
	public:
		fontFactory();
		//initializes SDL_ttf library if needed

		~fontFactory();
		//deletes all dynamic data
		//quits SDL_ttf library

		font * load(const char * filename, int size);
		//assumes filename is a valid c string
		//success: returns pointer to a font loaded with filename and size
		//failure: returns NULL. this happens if font fails to be created

		void unload(const char * filename, int size);
		//assumes filename is a valid c string
		//delete dynamic data of a font with matching filename and size

		void print();
		//prints info about all data contained in fonts

	private:
		font * create(const char * filename, int size, sizes * s);
		//used by load to allocate data and load the font

		fmap fonts; //actual structure holding font data
};

#endif /* FONTFACTORY_H */

