#include "sound.h"

//-------------------------------------------------------------------

sound::sound()
{
	data = NULL;
}

//-------------------------------------------------------------------

sound::~sound()
{
	if (data != NULL )
		Mix_FreeChunk(data);
}

//-------------------------------------------------------------------

int sound::load(const char * path, int value)
{
	data = Mix_LoadWAV(path);
	if(data == NULL) {
		printf("Unable to load (%s) file: %s\n", path, Mix_GetError());
		channel = -1;
		return 0;
	}
	channel = value;
	return 1;
}

//-------------------------------------------------------------------

int sound::play(int loops,int interupt)
{
	int rv = 0;

	if (interupt)
		if (Mix_Playing(channel))
			Mix_HaltChannel(channel);

	if (!Mix_Playing(channel)) {
		rv = Mix_PlayChannel(channel, data, loops);
		if(rv == -1) {
			printf("Unable to play WAV file: %s\n", Mix_GetError());
			return 0;
		}
	}

	return 1;
}

//-------------------------------------------------------------------

void sound::stop()
{
	Mix_HaltChannel(channel);
}

//-------------------------------------------------------------------

int sound::getChannel()
{
	return channel;
}

//-------------------------------------------------------------------

