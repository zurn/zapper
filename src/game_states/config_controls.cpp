
#include "config_controls.h"

config_controls::config_controls() { }

config_controls::config_controls(game * g)
{
	fsm = g;
	capture = false;

	opt = gfx::loadFont("./data/fonts/mono.ttf", 20);
	title = gfx::loadFont("./data/fonts/bit.ttf", 33);
	select = audio::loadSfx("./data/sfx/select.wav");
	move = audio::loadSfx("./data/sfx/move.wav");
	bad = audio::loadSfx("./data/sfx/bad.wav");
	background = gfx::loadImage("./data/gfx/paper.png");

	for (int i=0; i<KEY_CONFIG_TOTAL; i++) {
		opts.push_back(input::keyTags[i]);
	}

	opts.push_back("Restore Default Controls");
	opts.push_back("Back");
	set_names();

	setHot(0);
}

void config_controls::set_names()
{
	names.clear();
	for (int i=0; i<KEY_CONFIG_TOTAL; i++) {
		names.push_back(input::name(i));
	}
}

config_controls::~config_controls()
{
}

void config_controls::draw()
{
	gfx::replaceMode();
	background->draw(0, 0);
	gfx::blendMode();
	gfx::color(0,0,0);
	std::string name("Configure");
	int xpos = 320 - (title->width(name.c_str())/2);
	int ypos = 73;
	title->print(name.c_str(), xpos, ypos);

	name = "Controls";
	xpos = 320 - (title->width(name.c_str())/2);
	ypos = 73 + title->height();
	title->print(name.c_str(), xpos, ypos);


//	opt->print("Player 1", xpos + 10, ypos + title->height());

//	int x = 16*6, y = 16*5;
	int x = 16*9, y = 16*11;
	int x2 = 16 *27;

	opt->print("Action ", x, y-21);
	opt->print("Button", x2, y-21);

	std::string Hot = "(*) ";
	std::string Cold = "( ) ";
	std::string ts;

	for (unsigned int i=0; i<opts.size(); i++) {

		if (hot == int(i)) {
			gfx::color(0,0,0);
			ts = Hot + opts[i];
		}
		else {
			gfx::color(.5, .5, .5);
			ts = Cold + opts[i];
		}
		opt->print(ts.c_str(), x, y + (opt->height() * i));
		if (i < names.size())
			opt->print(names[i].c_str(), x2, y + (opt->height() * i));
	}
}

void config_controls::enter()
{
	input::keys[KEY_LEFT]->repeat = 0;
	input::keys[KEY_RIGHT]->repeat = 0;
	input::keys[KEY_ACCEPT]->repeat = 0;

	input::clear();
	setHot(0);
}

void config_controls::exit()
{
	input::keys[KEY_LEFT]->repeat = 1;
	input::keys[KEY_RIGHT]->repeat = 1;
	input::keys[KEY_ACCEPT]->repeat = 1;
}

void config_controls::setHot(int n)
{
	if (n < 0) {
		hot = CP_BACK;
		return;
	}
	if (n > CP_BACK) {
		hot = 0;
		return;
	}
	hot = n;
}

void config_controls::update()
{
	if (capture && input::anykey) {

		int keydef = input::event.key.keysym.sym;
		if (!checkKey(keydef)) {
			bad->play(0,1);
			return;
		}
		select->play(0,1);
		if (hot < (int) names.size()){
			names[hot] = input::keyname(keydef);
			input::keys[hot]->set(keydef);
		}
		capture = false;
		input::clear();
		return;
	}
	if (input::pressed(KEY_UP)) {
		setHot(hot-1);
		move->play(0,1);
		return;
	}

	if (input::pressed(KEY_DOWN)) {
		setHot(hot+1);
		move->play(0,1);
		return;
	}
	if (input::pressed(KEY_ACCEPT)) {
		if (hot < CP_DEFAULT) {
			capture = true;
			names[hot] = "_";
		}
		else if (hot == CP_DEFAULT) {
			select->play(0,1);
			input::defaultKeys();
			set_names();
		}
		else if (hot == CP_BACK) {
			select->play(0,1);
			fsm->change(GS_OPTIONS);

			fsm->history.pop_back();
		}
		return;
	}
}

bool config_controls::checkKey(int keydef)
{
	for (int i=0; i<KEY_CONFIG_TOTAL; i++) {
		if (keydef == input::keys[i]->binding && hot != i) {
			return false;
		}
	}

	return true;
}

void config_controls::pause()
{
}

void config_controls::unpause()
{
}

