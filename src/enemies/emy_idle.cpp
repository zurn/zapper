
#include "emy_idle.h"

emy_idle::emy_idle(enemy * e)
{
	fsm = e;
	skip = false;
	delay.set(333);
}

emy_idle::~emy_idle()
{
}

void emy_idle::draw()
{
	gfx::replaceMode();
	fsm->pic->draw(fsm->pos.x - TILE_SIZE*.5, fsm->pos.y, fsm->flip);

	//draw hit box
//	gfx::blendMode();
//	gfx::color(0,1,0,.5);
//	gfx::drawRect(fsm->pos.x - fsm->offset.x, fsm->pos.y - fsm->offset.y,
//			fsm->dimension.x, fsm->dimension.y
//	);
}

void emy_idle::enter()
{
	fsm->collidable = true;
}

void emy_idle::exit()
{
	fsm->collidable = false;
}

void emy_idle::pause()
{
}

void emy_idle::unpause()
{
}

void emy_idle::update()
{

	fsm->pos += fsm->vel;

	if (delay.is_past()) {

		if (skip) {
			fsm->pos.y += 4;
			skip = false;
		}
		else {
			fsm->pos.y -= 4;
			skip = true;
		}
		delay.reset();
	}

}

