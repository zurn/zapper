
#include "disp_score.h"

disp_score::disp_score(game * fsm)
{
	disp_score::fsm = fsm;

	opt = gfx::loadFont("./data/fonts/mono.ttf", 20);
	title = gfx::loadFont("./data/fonts/bit.ttf", 33);
	select = audio::loadSfx("./data/sfx/select.wav");
	move = audio::loadSfx("./data/sfx/move.wav");
	background = gfx::loadImage("./data/gfx/paper.png");
}

disp_score::~disp_score()
{
}

void disp_score::enter()
{
	input::clear();
}

void disp_score::exit()
{
}

void disp_score::draw()
{
	gfx::replaceMode();
	background->draw(0,0);
	gfx::blendMode();
	gfx::color(0,0,0);
	std::string name("High Scores");
	int xpos = WINDOW_W/2 - (title->width(name.c_str())/2);
	int ypos = 80;
	title->print(name.c_str(), xpos, ypos);

	int x = 16*8, y = 16*9;
	int x2 = 16 *22;

	draw(fsm->high_score->high_scores, x, y);
	gfx::color(0,0,0);
	opt->print("Name ", x, y-21);
	opt->print("Score", x2, y-21);
}

void disp_score::draw(std::vector<entry> & entries, int x, int y)
{
	for (unsigned int i=0; i<entries.size(); i++) {

		if ((int)i+1 == fsm->high_score->last_new) {
			gfx::color(1,0,0);
		}
		else {
			gfx::color(0,0,0);
		}

		char buf[256];
		buf[255] = '\0';

		//double digit place gets moved to the side to line up better
		if (i > 8) {
			x -= opt->width(" ");
		}

		snprintf(buf, sizeof(buf), "%i%s%s", i+1, ": ",  entries[i].name.c_str());
//		opt->print(entries[i].name.c_str(), x, y + (opt->height() * i));
		opt->print(buf, x, y + (opt->height() * i));
		snprintf(buf, sizeof(buf), "%i", entries[i].score);
		opt->print(buf, 16 * 22, y + (opt->height() * i));
	}
}

void disp_score::update()
{
	if (input::pressed(KEY_ACCEPT) ) {
		fsm->change(GS_MAIN_MENU);
	}
}

void disp_score::pause()
{
}

void disp_score::unpause()
{
}

