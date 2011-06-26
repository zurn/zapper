#ifndef SOUNDFACTORY_H
#define SOUNDFACTORY_H

#include <map>
#include "sound.h"
#include "utilities.h"
#include "unique.h"

/*
This class uses the factory pattern to control the creation of sounds.
Each filename will only ever be created once, as long as it remains loaded.

This class associates a c string with a pointer to an sound class.
*/

//some typedefs to make the code easier to read
typedef std::map<const char *, sound *, ltstr> smap;

class soundFactory
{
	public:
		soundFactory(int num_channels);
		//creates channels variable
		//num_channels will specify the maximum amount of sounds that can
		//be loaded.  The maximum is num_channels - 1

		~soundFactory();
		//deletes all loaded sounds
		//deletes channels variable

		sound * load(const char * filename);
		//assumes filename is a valid c string
		//success: returns pointer to an sound loaded with filename
		//failure: returns NULL. this happens if sound fails to be created
		//or if the maximum number of sounds has been loaded.

		void unload(const char * filename);
		//assumes filename is a valid c string
		//delete dynamic data of a sound with matching filename

	private:
		smap sounds; //actual structure holding sound data
		unique * channels; 
		//used to keep each sound playing on its own channel
};

#endif /* SOUNDFACTORY_H */

