
#include "emy_distracted.h"

emy_distracted::emy_distracted(enemy * e)
{
	fsm = e;
	time_total.set(3000);
	spin = 0.0;
}

emy_distracted::~emy_distracted()
{
}

void emy_distracted::draw()
{
	gfx::blendMode();
	gfx::color(ran1(), ran1(), ran1(), ran1() + .2);
	fsm->pic->drawRotate(fsm->pos.x - TILE_SIZE*.5, fsm->pos.y, spin*360);
}

void emy_distracted::enter()
{
	spin = 0.0;
	time_total.set(ran1_int(2, 4)*1000);
}

void emy_distracted::exit()
{
}

void emy_distracted::pause()
{
	time_total.pause();
}

void emy_distracted::unpause()
{
	time_total.unpause();
}

void emy_distracted::update()
{
	spin += .12;
	if (spin > 1) {
		spin = 0.0;
	}

	if (time_total.is_past()) {
		fsm->change(EMY_IDLE);
	}
}

