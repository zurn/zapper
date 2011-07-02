
#include "ply_charge.h"

ply_charge::ply_charge(player * p)
{
	fsm = p;
	buzz = audio::loadSfx("./data/sfx/buzz.wav");
	charge_held.set(75);
	build = p->effects->getEmitter();

	build->lifetime = -1;
	build->max_range = 12;
	build->range_mod = .22;

	build->rl = 0;
	build->rh = 30;

	build->gl = 0;
	build->gh = 10;

	build->bl = 70;
	build->bh = 101;

	build->render = 0;
	build->init(100, gfx::loadImage(BIG_PARTICLE));
}

ply_charge::~ply_charge()
{
//	buzz->stop();
}

void ply_charge::draw()
{
//	gfx::replaceMode();
	fsm->pic->draw(fsm->pos.x - TILE_SIZE*.5, fsm->pos.y, fsm->flip);
}

void ply_charge::enter()
{
//	printf("charge mdoe\n");

	build->pos = fsm->pos;
	build->pos.y += TILE_SIZE * .25;
	build->pos.x -= TILE_SIZE * .25;
//	build->reset();

	buzz->play(-1,0);
	charge_held.reset();
}

void ply_charge::exit()
{
	build->render = 0;
	buzz->stop();
}

void ply_charge::pause()
{
	charge_held.pause();
}

void ply_charge::unpause()
{
	charge_held.unpause();
}

void ply_charge::update()
{

	if (!input::pressed(KEY_ACCEPT)) {
		fsm->revert();
		return;
	}
	else {
		if (charge_held.is_past()) {
//			charge_held.print();
			buzz->stop();
//			fsm->launch();
//			fsm->shoot->play(0, 1);
			fsm->change(PLY_IDLE);
			return;
		}
	}
}

