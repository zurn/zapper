#include <map>
#include "soundFactory.h"

//-------------------------------------------------------------------

soundFactory::soundFactory(int num_channels)
{
	channels = new unique(num_channels);
}

//-------------------------------------------------------------------

soundFactory::~soundFactory()
{
	for(smap::iterator i= sounds.begin(); i!= sounds.end(); ++i)
		delete i->second;
	delete channels;
}

//-------------------------------------------------------------------

sound * soundFactory::load(const char * filename)
{
	sound * tmp;
	smap::iterator val = sounds.find(filename);

	if (val == sounds.end()) {//not found
//		printf("sound: %s not found\n", filename);
		int chan = channels->getID();
		if (chan == -1) {
			printf("Too many sounds loaded. %s not loaded.\n", filename);
			return NULL;
		}

		tmp = new sound;
		if (tmp->load(filename, chan))
			sounds[filename] = tmp;
		else {//load error, free channel num
			channels->freeID(chan);
			delete tmp;
			tmp = NULL;
		}

	} else {//found
		tmp = sounds[filename];
	}

	return tmp;
}

//-------------------------------------------------------------------

void soundFactory::unload(const char * filename)
{
	smap::iterator i = sounds.find(filename);
	if (i!=sounds.end()) {
		channels->freeID(i->second->getChannel());
		sounds.erase(i);
		delete i->second;
	}
}

//-------------------------------------------------------------------

