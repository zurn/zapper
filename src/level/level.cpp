
#include "level.h"

level::level()
{
	spawn_time = 10000;
	background = NULL;
	back_file = "";
	level_index = 0;
//	load_level(level_files[0].second);
	if (!load_files("./data/levels/levels.xml") || level_files.size() != 4) {
		printf("error loading level files. game will hault\n");
		input::quit = 1;
	}
}

level::~level()
{
	clean();
}

bool level::load(int level_num)
{
	level_num--;
	for (unsigned int i=0; i<bars.size(); i++) {
		bars[i]->enemy_count = 0;
	}

	printf("\n\nloading level: %s\n",level_files[level_index].second.c_str() );
	printf("loading level num %i\n\n", level_index);
	if (!load_level(level_files[level_index].second)) {
		printf("failed loading level: %s. Shutting down game\n", level_files[level_index].second.c_str());
		input::quit = true;
		return false;
	}
	return true;
}

void level::draw()
{
	gfx::replaceMode();
	if (background != NULL)
	for (int x=0; x<gfx::w/TILE_SIZE; x++) {
		for (int h=0;h<gfx::h/TILE_SIZE; h++) {
			if (background != NULL) {
				background->draw(x*TILE_SIZE, h*TILE_SIZE);
			}
		}
	}
	for (unsigned int i=0; i<bars.size(); i++) {
		bars[i]->draw();
	}
}

void level::update()
{
	for (unsigned int i=0; i<bars.size(); i++) {
		bars[i]->update();
	}
}

bool level::load_files(std::string filename)
{

	if (access(filename.c_str(), F_OK)==-1) {
		printf("No level file found(%s).\n",
			filename.c_str());
		return false;
	}

	TiXmlDocument doc(filename.c_str());
	doc.LoadFile();

	TiXmlHandle hDoc(&doc);
	TiXmlElement* pElem;
	TiXmlHandle hRoot(0);

	pElem=hDoc.FirstChildElement().Element();
	// should always have a valid root but handle gracefully if it doesn't
	if (!pElem) {
		printf("Error opening level file: %s.\n", filename.c_str());
		return false;
	}
//	printf("name: %s\n", pElem->Value());
	hRoot=TiXmlHandle(pElem);
	TiXmlElement * files = hRoot.FirstChild().Element();

	for (; files!=NULL; files=files->NextSiblingElement()) {
		const char *pKey=files->Value();
		const char *pText=files->GetText();

		if (!pKey || !pText)
			continue;
//	printf("loop: %s %s\n", pKey, pText);

		std::string file = pText;
		std::string disp;
//	files->QueryStringAttribute("display", &disp);
		if (files->QueryStringAttribute("display", &disp)!= TIXML_SUCCESS) {
			
			disp = file;
		}
//	printf("%s: %s\n", disp.c_str(), file.c_str());
		if (access(file.c_str(), F_OK)==-1) {
			//no file found
			printf("error cant find file: %s\n", file.c_str());
			return false;
		}
		else {
			level_files.push_back(std::make_pair(disp, file));
		}
	}

	return true;
}

void level::print()
{
	for (unsigned int i=0; i<level_files.size(); i++) {
		printf("%s: %s\n", level_files[i].first.c_str(), level_files[i].second.c_str());
	}
}

bool level::load_level(std::string filename)
{
	for(unsigned int i=0; i<bars.size(); i++) {
		delete bars[i];
	}
	bars.clear();
	bar_data.clear();
	background = NULL;
	back_file = "";

	TiXmlDocument doc(filename);
	doc.LoadFile();

	TiXmlNode * e = doc.FirstChildElement();
	e = e->FirstChild();

	while (e != NULL) {

		TiXmlNode * temp = e;
		if (e->Value() == TILES) {
			bool r = load_tiles(temp);
			if (!r) return false;
//			printf("tile size %i\n\n", tile_set.size());
		}
		if (e->Value() == BAR) {
			bool r = load_bar(temp);
		if (!r) return false;
//			printf("bar size %i\n",bars.size());
		}
		if (e->Value() == BACKGROUND) {
			back_file = e->ToElement()->GetText();
			background = gfx::loadImage(back_file.c_str());
			
//			printf("loaded bg: %s\n", e->ToElement()->GetText());
		}
//		printf("%s\n", e->Value());
		if (e->Value() == ENEMIES) {
			bool r = load_enemy_pics(temp);
			if (!r) return false;
		}
		if (e->Value() == RESPAWN_TIME) {
			e->ToElement()->QueryIntAttribute("time", &spawn_time);
		}
		e = e->NextSibling();
	} 

	for (unsigned int i=0; i<bar_data.size(); i++) {

		bar * b = new bar;
		b->load(bar_data[i].x1, bar_data[i].x2, bar_data[i].y, tile_set);
		bars.push_back(b);

	}
	return true;
}

bool level::load_tiles(TiXmlNode * n)
{
	if (n == NULL) return false;
	tile_set.clear();
	TiXmlElement * e = n->FirstChildElement();

	while (e != NULL) {
//		printf("tile name: %s\n", e->GetText());
		tile_set.push_back(gfx::loadImage(e->GetText()));

		e = e->NextSiblingElement();
	} 

//	printf("tiles %i\n", tile_set.size());
	return true;
}

bool level::load_bar(TiXmlNode * n)
{
	if (n == NULL) return false;

	TiXmlElement * e = n->FirstChildElement();

	int x1 = 0;
	int x2 = 0;
	int y = 0;

	if (e->QueryIntAttribute("x", &x1)!= TIXML_SUCCESS) {
		x1 = -1;
	}
	if (e->QueryIntAttribute("y", &y)!= TIXML_SUCCESS) {
		y = -1;
	}

	e = e->NextSiblingElement();

	if (e == NULL) return false;

	if (e->QueryIntAttribute("x", &x2)!= TIXML_SUCCESS) {
		x1 = -1;
	}
	if (e->QueryIntAttribute("y", &y)!= TIXML_SUCCESS) {
		y = -1;
	}

	if (x1==-1 || x2==-1 || y ==-1) return false;

	bar_info b;
	b.x1 = near_TILE_SIZE(x1);
	b.x2 = near_TILE_SIZE(x2);
	b.y = near_TILE_SIZE(y);

//	printf("%i %i %i\n\n", b.x1, b.x2, b.y);
	
	bar_data.push_back(b);

	if (bar_data.size() < 1) {
		return false;
	}
	return true;
}

void level::clean()
{
	background = NULL;
	back_file = "";
	tile_set.clear();
	level_files.clear();
	enemy_pics.clear();
	for(unsigned int i=0; i<bars.size(); i++) {
		delete bars[i];
	}
	bars.clear();
	bar_data.clear();
}

int level::near_TILE_SIZE(int num)
{
	if (num < 0) return -1;
//	printf("called %i\n", num);

	int rem = num % TILE_SIZE;

	//check to see if the number is already divisible by TILE_SIZE
	//adjust and return it
	if (rem == 0) {
		if (num-1 < 0) {
			return 0;
		}
		else {
			return num-1;
		}
	}
	else if (rem==TILE_SIZE-1) {
		return num;
	}

	//if the number is above half of TILE_SIZE,
	//then increment until it is
	if (rem < TILE_SIZE *.5) {

		int result = num;

		do {
			num--;
			result = num % TILE_SIZE;
		} while (result > 0);
		num--;
		if (num < 0) num = 0;
	}
	//the is less than half of TILE_SIZE, 
	//decrement until divisible by TILE_SIZE
	else {

		int result = num;

		do {
			num++;
			result = num % TILE_SIZE;
		} while (result < TILE_SIZE-1);
		num++;
		if (num >= TILE_SIZE) num--;
	}
	return num;
}

bool level::load_enemy_pics(TiXmlNode *n)
{
	if (n == NULL) return false;
	enemy_pics.clear();
	TiXmlElement * e = n->FirstChildElement();

	while (e != NULL) {
//		printf("enemy name: %s\n", e->GetText());
		image * i = NULL;
		i = gfx::loadImage(e->GetText());
		if (i != NULL) {
			enemy_pics.push_back(i);
		}

		e = e->NextSiblingElement();
	} 

	if (enemy_pics.size() == 0) {
		printf("warning no enemy pictures loaded.\n");
		return false;
	}
	return true;
}

