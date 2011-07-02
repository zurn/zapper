
#include "get_ready.h"

get_ready::get_ready(game * g)
{
	fsm = g;
	background = gfx::loadImage("./data/gfx/paper.png");
	fade = 1.0;
	big = gfx::loadFont("./data/fonts/bit.ttf", 22);
	small = gfx::loadFont("./data/fonts/bit.ttf", 24);
	delay.set(500);
}

get_ready::~get_ready()
{
}

void get_ready::draw()
{
	gfx::replaceMode();
	background->draw(0,0);


	gfx::blendMode();
	gfx::color(0,0,0);

	const char * title = "Get Ready to";
	int xpos = 320 - (big->width(title)/2);
	big->print(title,xpos-20,125);

	title = "Start Zapping!";
	xpos = 320 - (big->width(title)/2);
	big->print(title,xpos-20,125 + big->height());


//	title = "Start Zapping!";
	title = fsm->world->level_files[fsm->world->level_index].first.c_str();
	xpos = 320 - (big->width(title)/2);
	big->print(title,xpos-20,275 + big->height()* 2);




	char buf[256];
	buf[255] = '\0';
	snprintf(buf, sizeof(buf), "Lives: %i", fsm->dude->lives);
	gfx::loadFont("./data/fonts/mono.ttf", 16)->print(buf, 166, 403);

	snprintf(buf, sizeof(buf), "Score: %i", fsm->dude->score);
	gfx::loadFont("./data/fonts/mono.ttf", 16)->print(buf, 266, 403);

	snprintf(buf, sizeof(buf), "Level: %i", fsm->dude->level_num);
	gfx::loadFont("./data/fonts/mono.ttf", 16)->print(buf, 454, 403);

}

void get_ready::enter()
{
	fsm->load_level();
	audio::stopSfx();
	fade = 0;
	input::clear();
	delay.reset();
}

void get_ready::exit()
{
	fsm->enemies->set_counters();
}

void get_ready::pause()
{
}

void get_ready::unpause()
{
}

void get_ready::update()
{
	fade -= .010;
	if (fade < 0)
		fade = 0;

	if (input::anykey && fade > .000005) {
		fade = 0;
		input::clear();
		delay.reset();
		return;
	}
	if (delay.is_past() && input::anykey && fade < .000005) {
		fsm->change(GS_TAPPER);
		return;
	}
}

