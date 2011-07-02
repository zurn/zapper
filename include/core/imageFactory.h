#ifndef IMAGE_FACTORY
#define IMAGE_FACTORY

#include <map>
#include "image.h"
#include "utilities.h"

/*
This class uses the factory pattern to control the creation of images.
Each filename will only ever be created once, as long as it remains loaded.

This class associates a c string with a pointer to an image class.
*/

//typedef to make the code easier to read
typedef std::map<const char *, image *, ltstr> imap ;

class imageFactory
{
	public:
		imageFactory();
		//empty

		~imageFactory();
		//deletes all dynamic data

		void clean();
		//releases all images


		image * load(const char * filename);
		//assumes filename is a valid c string
		//success: returns pointer to an image loaded with filename
		//failure: returns NULL. this happens if image fails to be created

		void unload(const char * filename);
		//assumes filename is a valid c string
		//delete dynamic data of an image with matching filename

	private:
		imap surfaces; //actual structure holding image data
};

#endif

