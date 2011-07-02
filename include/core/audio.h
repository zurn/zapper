#ifndef AUDIO_DOT_H
#define AUDIO_DOT_H

#include "SDL.h"
#include "soundFactory.h"
#include "playlist.h"
#include "RNG.h"

class audio
{
	private:
		audio();
		~audio();

	public:
		static bool init();
		static void cleanup();
		static int loadMusic(const char * filename);
		static void freeMusic();



		static void song_done();
		static int playMusic(int loops);
		static void toggleMusic();
		static void stopMusic();
		static void stopSfx();
		static void setMusicVol(int vol);
		static void setSFXvol(int vol);
		static void unpauseMusic();

		static sound * loadSfx(const char * filename);

		static int audio_rate;			//Frequency of audio playback
		static Uint16 audio_format;		//Format of the audio we're playing
		static int audio_channels;			//2 channels = stereo
		static int audio_buffers;		//Size of the audio buffers in memory

	private:
		static Mix_Music * music;
		static soundFactory * sfact;
		static playlist songs;
		static int lsong;
};

#endif

