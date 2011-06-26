
#include "emy_charge.h"

emy_charge::emy_charge(enemy * e)
{
	fsm = e;
	buzz = audio::loadSfx("./data/sfx/buzz.wav");
	charge_held.set(250);
	build = fsm->effects->getEmitter();

	build->lifetime = -1;
	build->max_range = 12;
	build->range_mod = .22;

	build->rl = 180;
	build->rh = 255;

	build->gl = 0;
	build->gh = 60;

	build->bl = 0;
	build->bh = 10;

	build->render = 0;
	build->init(100, gfx::loadImage(BIG_PARTICLE));

}

emy_charge::~emy_charge()
{
	fsm->effects->remove(build);
	buzz->stop();
}

void emy_charge::draw()
{
//	gfx::replaceMode();

	int r = ran1_int(180, 256);
	int g = ran1_int(0, 16);
	int b = ran1_int(0, 10);
	gfx::color(r, g, b);

	gfx::blendMode();
	fsm->pic->draw(fsm->pos.x - TILE_SIZE*.5, fsm->pos.y, fsm->flip);
}

void emy_charge::enter()
{
	build->pos = fsm->pos;
	build->pos.y += TILE_SIZE * .25;
	build->pos.x -= TILE_SIZE * .25;
//	build->reset();

	buzz->play(-1,0);
	charge_held.reset();
}

void emy_charge::exit()
{
	build->render = 0;
	buzz->stop();
}

void emy_charge::pause()
{
	charge_held.pause();
}

void emy_charge::unpause()
{
	charge_held.unpause();
}

void emy_charge::update()
{
	if (charge_held.is_past()) {
//			charge_held.print();
		buzz->stop();
		fsm->launch();
		fsm->shoot->play(0, 1);
		fsm->change(EMY_IDLE);
		return;
	}
}

