
#include "emy_push_back.h"

emy_push_back::emy_push_back(enemy * e)
{
	fsm = e;
	delay.set(1500);
	spin = 0.0;
}

emy_push_back::~emy_push_back()
{
}

void emy_push_back::draw()
{
	gfx::replaceMode();
	fsm->pic->drawRotate(fsm->pos.x - TILE_SIZE*.5, fsm->pos.y, spin*360);
}

void emy_push_back::enter()
{
	audio::loadSfx("./data/sfx/bonus.wav")->play(0,1);
	spin = 0.0;
	delay.reset();
}

void emy_push_back::exit()
{
	fsm->tips->add(fsm->pos);
}

void emy_push_back::pause()
{
	delay.pause();
}

void emy_push_back::unpause()
{
	delay.unpause();
}

void emy_push_back::update()
{
	fsm->pos -= fsm->vel * 4;

	spin += .20;
	if (spin > 1) {
		spin = 0.0;
	}

	if (delay.is_past()) {
		fsm->change(EMY_CHARGE);
		return;
	}
}

