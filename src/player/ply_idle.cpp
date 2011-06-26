
#include "ply_idle.h"

ply_idle::ply_idle(player * p)
{
	fsm = p;
	skip = false;
	delay.set(333);
}

ply_idle::~ply_idle()
{
}

void ply_idle::draw()
{
	gfx::replaceMode();
	fsm->pic->draw(fsm->pos.x - TILE_SIZE*.5, fsm->pos.y, fsm->flip);

}

void ply_idle::enter()
{
	input::clear();
//	input::keys[KEY_ACCEPT]->clear();
//	printf("enter idle state\n");
}

void ply_idle::exit()
{
}

void ply_idle::pause()
{
}

void ply_idle::unpause()
{
}

void ply_idle::update()
{
	if (input::pressed(KEY_ACCEPT)) {
			fsm->bar_hop(fsm->bar_pos);
			fsm->launch();
			fsm->shoot->play(0, 1);
			fsm->change(PLY_CHARGE);
			return;
	}


	if (input::pressed(KEY_UP)) {
		fsm->bar_hop(fsm->bar_pos-1);
		fsm->bamf->play(0, 1);
	}
	if (input::pressed(KEY_DOWN)) {
		fsm->bar_hop(fsm->bar_pos+1);
		fsm->bamf->play(0, 1);
	}
	
	if (input::pressed(KEY_LEFT)) {
		fsm->pos.x -= 2.0; 
		if (fsm->place->direction == 1) {
			if (fsm->pos.x < fsm->place->startx) {
				fsm->pos.x = fsm->place->startx;
			}
		}
		else {
			if (fsm->pos.x < fsm->place->endx) {
				fsm->pos.x = fsm->place->endx;
			}
		}

		fsm->flip = true;
	}
	if (input::pressed(KEY_RIGHT)) {
		fsm->pos.x += 2.0;

		if (fsm->place->direction == 1) {
			if (fsm->pos.x > fsm->place->endx) {
				fsm->pos.x = fsm->place->endx;
			}
		}
		else {
			if (fsm->pos.x > fsm->place->startx) {
				fsm->pos.x = fsm->place->startx;
			}
		}


		fsm->flip = false;
	}

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

