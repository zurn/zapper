
#include "tip.h"

tip::tip(Vector pos)
{
	pic = gfx::loadImage("./data/gfx/spell_book.png");
	tip::pos = pos;
	skip = false;
	delay.set(140);

	poof = new emitter;



	poof->pos = pos;
	poof->pos.y += TILE_SIZE * .5;
	poof->pos.x += TILE_SIZE * .5;
	poof->lifetime = 200;
	poof->max_range = 12;
	poof->range_mod = .22;


	poof->rl = 90;
	poof->rh = 101;
	poof->gl = 90;
	poof->gh = 101;
	poof->bl = 90;
	poof->bh = 101;

	poof->render = 0;
	poof->init(100, gfx::loadImage(LITTLE_PARTICLE));

}

tip::~tip()
{
	delete poof;
}

void tip::draw()
{
	if (pic == NULL) return;

	poof->reset();
	poof->draw();
	gfx::replaceMode();
	pic->draw(pos.x, pos.y);
}

void tip::update()
{
	poof->update();
	if (delay.is_past()) {

		if (skip) {
			pos.y += 4;
			skip = false;
		}
		else {
			pos.y -= 4;
			skip = true;
		}
		delay.reset();
	}
}

