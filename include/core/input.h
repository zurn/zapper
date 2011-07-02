#ifndef INPUT_H
#define INPUT_H

#include "SDL.h"
#include <vector>
#include <unistd.h> //for checking if a file exists
#include "tinyxml.h"
#include "keys.h"
#include "button.h"

//#define DEBUG 1
//uncomment if you want to see button info printed to console



#define INPUT_CONFIG "./data/config/controls.xml"

typedef std::vector<button *> buttons;

class input
{
	private:
		input();
		~input();

	public:
		static void defaultKeys();
		static bool init();
		static void cleanup();
		static void update();

		static bool loadKeys();
		static void saveKeys();

		static bool pressed(int keydef);
		//returns whether or not the key passed in is
		//currently being pressed
		//keydef should be from keys.h

		static void print();
		static void clear();
		//sets all values for keys as not pressed

		static buttons keys;

		static const char * keyname(int k);
		//k should be from SDLK_*h

		static const char * name(int keydef);
		//returns printable name for the keydef
		//keydef should be from keys.h

		static void poll();
		//grabs event from user

		static bool anykey;
		//set to true if a button was pressed
		//set to false if no button was pressed

		static SDL_Event event;
		//holds a user event detected from getInput()

		static bool quit;
		//false if no quit signal was recieved
		//true if it was recieved

		static const char * keyTags[];
		//used for in game display
};

#endif /* INPUT_H */

