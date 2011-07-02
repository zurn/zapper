#ifndef SOUND_DOT_H
#define SOUND_DOT_H

#include "SDL_mixer.h"

/*
This class utilizes the SDL_mixer library.
SDL should be initialized with the SDL_INIT_AUDIO flag before using this class.
Mix_OpenAudio(...) should be called before using an
instance of this class.

You can use this class to load and play .wav files.
*/

class sound
{
	public:
		sound();
		//sets data to NULL

		~sound();
		//frees data if necessary

		int load(const char * filename, int channel);
		//assumes filename is a valid c string
		//sets data to contain sound file at filename
		//sets data to play on channel passed in
		//returns 0 on failure
		//returns 1 on success

		int play(int loops,int interupt);
		//plays sound data as many times as loops
		//if loops == -1 then repeats sound forever
		//if interupt == 0 then sound will only play if is not already playing
		//if interupt != 0 then if sound is already playing it will be stopped
		//and then played again.
		//returns 0 on failure
		//returns 1 on success

		void stop();
		//Stops playing sound if playing, or does nothing.

		int getChannel();
		//returns value in channel variable

	private:
		Mix_Chunk * data;
		//actual sound data. NULL on load failure
		int channel;
		//The channel the soundiwll play on. -1 on load failure.
};

#endif

