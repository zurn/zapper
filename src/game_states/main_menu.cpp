
#include "main_menu.h"

main_menu::main_menu(game * g)
{
	fsm = g;
	opt = gfx::loadFont("./data/fonts/mono.ttf", 20);
	title = gfx::loadFont("./data/fonts/bit.ttf", 44);
	select = audio::loadSfx("./data/sfx/select.wav");
	move = audio::loadSfx("./data/sfx/move.wav");
	background = gfx::loadImage("./data/gfx/paper.png");


	options.push_back("Start Game");
	options.push_back("High Scores");
	options.push_back("Options");
	options.push_back("Credits");
	options.push_back("Quit");
	set_hot(MM_PLAY);
}

main_menu::~main_menu()
{
}

void main_menu::draw()
{
//	gfx::blendMode();
//	gfx::color(0,1,0);
//	gfx::loadFont("./data/fonts/mono.ttf", 16)->print("main menu",32,32);
//
	gfx::replaceMode();
	background->draw(0, 0);
	gfx::blendMode();
	gfx::color(0,0,0);
	std::string name("Zapper");
	int xpos = gfx::w/2 - (title->width(name.c_str())/2);
	title->print(name.c_str(), xpos, 83);

	int x = 16*14, y = 16*10;
	std::string Hot = "(*) ";
	std::string Cold = "( ) ";
	std::string ts;

	for (unsigned int i=0; i<options.size(); i++) {

		if (hot == int(i)) {
			gfx::color(0,0,0);
			ts = Hot + options[i];
		}
		else {
			gfx::color(.5, .5, .5);
			ts = Cold + options[i];
		}
		opt->print(ts.c_str(), x, y + (opt->height() * i));
	}

}

void main_menu::enter()
{
	set_hot(0);
	input::clear();
	audio::stopSfx();
//	audio::song_done();
//	printf("enter main menu\n");
}

void main_menu::exit()
{
}

void main_menu::pause()
{
}

void main_menu::unpause()
{
}

void main_menu::update()
{
	if (input::pressed(KEY_ACCEPT)) {
		select->play(0,1);
		switch(hot) {
			case MM_PLAY:
				fsm->dude->reset();
				fsm->world->level_index = 0;
				fsm->high_score->last_new = 0;
				fsm->change(GS_GET_READY);
			break;
			case MM_OPTIONS:
				fsm->change(GS_OPTIONS);
			break;

			case MM_HIGH:
				fsm->change(GS_VIEW_SCORES);
			break;

			case MM_CREDITS:
//uncomment to change to winning game;
//				fsm->world->level_index = 3;
//				fsm->dude->level_num = 13;
//				fsm->change(GS_WIN_LEVEL);

//				fsm->change(GS_CUPS);

				fsm->change(GS_CREDITS);
			break;

			case MM_QUIT:
				input::quit = 1;
			break;

			default: break;
		}
		return;
	}

	if (input::pressed(KEY_UP)) {
		set_hot(hot-1);
		move->play(0,1);
		return;
	}

	if (input::pressed(KEY_DOWN)) {
		set_hot(hot+1);
		move->play(0,1);
		return;
	}
}

void main_menu::set_hot(int n)
{
	if (n < 0) {
		hot = options.size()-1;
		return;
	}
	if (n >= (int)options.size()) {
		hot = 0;
		return;
	}
	hot = n;
}
