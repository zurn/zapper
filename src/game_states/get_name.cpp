
#include "get_name.h"

get_name::get_name(game * g)
{
	fsm = g;
	rogue = g->dude;
	name = "";
	options = new keyboard;	
	bg = gfx::loadImage("./data/gfx/paper.png");
	title = gfx::loadFont("./data/fonts/bit.ttf", 33);
	error = audio::loadSfx("./data/sfx/bad.wav");
	select = audio::loadSfx("./data/sfx/select.wav");
}

get_name::~get_name()
{
	delete options;
}

void get_name::enter()
{
	input::keys[KEY_LEFT]->repeat = 0;
	input::keys[KEY_RIGHT]->repeat = 0;
	input::keys[KEY_ACCEPT]->repeat = 0;

	name = rogue->name;
	name += "_";
	options->setPosition(10, 4);
	input::clear();
}

void get_name::exit()
{
//	printf("name exit: %s\n", rogue->name.c_str());
	input::keys[KEY_LEFT]->repeat = 1;
	input::keys[KEY_RIGHT]->repeat = 1;
	input::keys[KEY_ACCEPT]->repeat = 1;
}

void get_name::update()
{

	if (input::pressed(KEY_ACCEPT)) {
		switch (options->getCursor()) {
			case KB_CANCEL: 
//				printf("keyboard canceled %s\n", rogue->name.c_str());
				name = "_";
				select->play(0,1);
			break;

			case KB_BACK:
				if (name.size() < 2) {
					error->play(0,1);
					return;
				}
				select->play(0,1);
				name.resize(name.size() - 2);
				name += "_";
//				printf("backspace\n");
			break;

			case KB_DONE:
				select->play(0,1);
				if (name.size()==1) {
					name.clear();
				}
				else {
					name.resize(name.size() - 1);
				}
				rogue->name = name;
//				printf("saved name: %s\n", rogue->name.c_str());
				fsm->high_score->add_score(fsm->dude);
				fsm->change(GS_VIEW_SCORES);
			break;

			default: 
//				printf("Pressed: %c\n", options->getCursor());
				if (name.size() > NAME_LENGTH) {
					error->play(0,1);
					return;
				}


				select->play(0,1);
				name[name.size()-1] = options->getCursor();
				name += "_";
			break;
		}
		return;
	}

	options->update();
}

void get_name::draw()
{
	gfx::replaceMode();
	bg->draw(0, 0);

	gfx::blendMode();

	gfx::color(1,0,0);
	gfx::loadFont("./data/fonts/bit.ttf", 10)->print("Please enter your name for the scoreboard.", 95,60);



	gfx::color(0,0,0);

	int xpos = 320 - (title->width(name.c_str())/2);
	title->print(name.c_str(), xpos, 73);

	options->draw();
}

void get_name::pause()
{
}

void get_name::unpause()
{
}

