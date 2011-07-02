
#include "cup_cursor.h"

cup_cursor::cup_cursor()
{

	pic = gfx::loadImage((char*)"./data/gfx/wizard.png");
	bamf = audio::loadSfx((char*)"./data/sfx/tele.wav");

	tele = new emitter;

	tele->pos.x = tele->pos.y = -100;
	tele->lifetime = 200;
	tele->max_range = 8;
	tele->range_mod = .22;

	tele->rl = 70;
	tele->rh = 141;
	tele->gl = 70;
	tele->gh = 141;
	tele->bl = 70;
	tele->bh = 141;

	tele->render = 0;
	tele->init(50, gfx::loadImage(BIG_PARTICLE));

	pos.y = 245;
	hot = 0;
	flip = false;
	set_hot(0);
}

cup_cursor::~cup_cursor()
{
	delete tele;
}

void cup_cursor::draw()
{
	gfx::replaceMode();
	pic->draw(pos.x, pos.y, flip);

	tele->draw();
}

void cup_cursor::reset()
{
	pos.y = 245 + TILE_SIZE;
	set_hot(0);
}

void cup_cursor::set_hot(int n)
{
	if (n < 0) {
		hot = 5;
	}
	else if (n > 5) {
		hot = 0;
	}
	else {
		hot = n;
	}

	pos.x = 150 + hot*60;
	tele->pos = pos;
	tele->pos.y += TILE_SIZE * .25;
	tele->pos.x += TILE_SIZE * .25;
	tele->reset();
}

void cup_cursor::update()
{
	tele->update();
}

