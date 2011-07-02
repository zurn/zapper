
#ifndef __SETTINGS_H__
#define __SETTINGS_H__

#include "tinyxml.h"
#include <unistd.h> //for checking if a file exists

class settings
{
	public:
		settings(const char * filename);
		settings();
		~settings();

		bool load(const char * filename);
		bool save(const char * filename);
		void loadDefault();
		void print();

		float sfxVol;
		float musVol;

	private:

};
#endif /* __SETTINGS_H__ */
