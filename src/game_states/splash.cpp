
#include "splash.h"

splash::splash(machine * m)
{
	bg = gfx::loadImage("./data/gfx/paper.png");
	title = "Zapper";
	me = "By Jacob Sadow-Reinshagen";
	big = gfx::loadFont("./data/fonts/bit.ttf", 44);
	small = gfx::loadFont("./data/fonts/bit.ttf", 24);
	name = gfx::loadFont("./data/fonts/mono.ttf", 20);
	fade = 1.0;

	fsm = m;
}

splash::~splash()
{
}

bool splash::init(machine * m)
{
	fsm = m;
	return true;
}

void splash::draw()
{
	gfx::replaceMode();
	bg->draw(0, 0);

	gfx::blendMode();
	gfx::color(0,0,0);

	int xpos = 320 - (big->width(title)/2);

	big->print(title,xpos-20,125);
	small->print("A Tapper clone", xpos-55, 125 + 80);
//	small->print("adventure.", xpos, 125 + 80 + small->height());
	name->print(me, 320 - name->width(me) / 2, 375 );

	gfx::color(0, 0, 0, fade);
	gfx::drawRect(0, 0, WINDOW_W, WINDOW_H);
}

void splash::enter()
{
	audio::song_done();
	fade = 1;
	input::clear();
}

void splash::exit()
{
}

void splash::update()
{
	fade -= .010;
	if (fade < 0)
		fade = 0;

	if (input::anykey && fade > .000005) {
		fade = 0;
		return;
	}
	if (input::anykey && fade < .000005) {
		fsm->change(GS_MAIN_MENU);
		return;
	}
}

void splash::pause()
{
}

void splash::unpause()
{
}

