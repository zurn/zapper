
#include "pause_menu.h"

pause_menu::pause_menu(game * g)
{
	fsm = g;
	background = gfx::loadImage("./data/gfx/paper.png");
	opt = gfx::loadFont("./data/fonts/mono.ttf", 20);
	title = gfx::loadFont("./data/fonts/bit.ttf", 44);
	select = audio::loadSfx("./data/sfx/select.wav");
	move = audio::loadSfx("./data/sfx/move.wav");


	options.push_back("Return to Game");
	options.push_back("Options");
	options.push_back("Quit to Main Menu");
	set_hot(0);

}

pause_menu::~pause_menu()
{
}

void pause_menu::draw()
{
	gfx::replaceMode();
	background->draw(0, 0);

	gfx::blendMode();
	gfx::color(0,0,0);
	std::string name("Paused");
	int xpos = gfx::w/2 - (title->width(name.c_str())/2);
	title->print(name.c_str(), xpos, 83);

	int x = 16*13, y = 16*10;
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

void pause_menu::enter()
{
	set_hot(0);
	input::clear();
	audio::stopSfx();
	fsm->enemies->pause();
}

void pause_menu::exit()
{
}

void pause_menu::pause()
{
}

void pause_menu::unpause()
{
}

void pause_menu::update()
{
	if (input::pressed(KEY_ACCEPT)) {
		select->play(0,1);
		switch(hot) {
			case PM_RETURN:
				fsm->enemies->unpause();
				fsm->change(GS_TAPPER);
			break;

			case PM_OPTIONS:
				fsm->change(GS_OPTIONS);
			break;

			case PM_QUIT:
				fsm->change(GS_MAIN_MENU);
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

void pause_menu::set_hot(int n)
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

