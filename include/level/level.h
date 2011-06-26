
#ifndef __LEVEL_H__
#define __LEVEL_H__


#include "input.h"
#include "bar.h"
#include <vector>
#include <utility> //for std::pair
#include <unistd.h> //for checking if a file exists
#include "tinyxml.h"
#include <string>

const std::string TILES = "tiles";
const std::string BAR = "bar";
const std::string BACKGROUND = "background";
const std::string ENEMIES = "enemies";
const std::string RESPAWN_TIME = "respawn_time";

class level
{
	public:
		level();
		~level();

		bool load(int level_num);
		bool load_files(std::string filename);
		void print();
		void clean();

		bool load_level(std::string filename);
		bool load_tiles(TiXmlNode * n);
		bool load_bar(TiXmlNode * n);
		bool load_enemy_pics(TiXmlNode *n);

		int near_TILE_SIZE(int num);

		void update();
		void draw();

		image * background;
		std::string back_file;
		std::vector<image *> tile_set;
		std::vector<bar *> bars;
		std::vector<std::pair<std::string, std::string> > level_files;
		std::vector<bar_info> bar_data;
		std::vector<image *> enemy_pics;

		int level_index;
		//contains index into level_files

		int spawn_time;
	private:

};
#endif /* __LEVEL_H__ */
