
#ifndef __PLAYLIST_H__
#define __PLAYLIST_H__

#include "tinyxml.h"
#include <utility> //for std::pair
#include <unistd.h> //for checking if a file exists
#include <string>
#include <vector>

class playlist
{
	public:
		playlist();
		~playlist();

		void load(std::string filename);
		void print();

		std::vector<std::pair<std::string, std::string> > music;
};


#endif /* __PLAYLIST_H__ */
