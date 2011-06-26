
#include "credits.h"

credits::credits(machine * m)
{
	fsm = m;
	background = gfx::loadImage("./data/gfx/paper.png");
	title = gfx::loadFont("./data/fonts/bit.ttf", 33);
	header = gfx::loadFont("./data/fonts/bit.ttf", 16);
	text = gfx::loadFont("./data/fonts/mono.ttf", 14);
}

credits::~credits()
{
}

void credits::draw()
{
	gfx::replaceMode();
	background->draw(0,0);

	gfx::blendMode();
	gfx::color(0, 0, 0);

	title->print("Credits",gfx::w/2 - (title->width("Credits")/2), 83 );

	std::string msg = "Programming";
	header->print(msg.c_str(), gfx::w/2 - header->width(msg.c_str())/2, 130 + 30);

	msg = "Jacob Sadow-Reinshagen";
	text->print(msg.c_str(),  gfx::w/2 - text->width(msg.c_str())/2, 148 + 30);

	msg = "Graphics";
	header->print(msg.c_str(), gfx::w/2 - header->width(msg.c_str())/2, 170 + 30);

	msg = "Oryx";
	text->print(msg.c_str(),  gfx::w/2 - text->width(msg.c_str())/2, 188 + 30);

	msg = "Sound Effects";
	header->print(msg.c_str(), gfx::w/2 - header->width(msg.c_str())/2, 210 + 30);

	msg = "as3sfxr";
	text->print(msg.c_str(),  gfx::w/2 - text->width(msg.c_str())/2, 228 + 30);

	msg = "Music";
	header->print(msg.c_str(), gfx::w/2 - header->width(msg.c_str())/2, 250 + 30);

	msg = "Various: Nine Inch Nails";
	text->print(msg.c_str(),  gfx::w/2 - text->width(msg.c_str())/2, 268 + 30);

	msg = "Arcadia: Kevin MacLeod (incompetech.com)";
	text->print(msg.c_str(),  gfx::w/2 - text->width(msg.c_str())/2, 268 + 18 + 30);
}

void credits::enter()
{
	input::clear();
}

void credits::exit()
{
}

void credits::pause()
{
}

void credits::unpause()
{
}

void credits::update()
{
	if (input::anykey) {
		fsm->change(GS_MAIN_MENU);
	}
}

