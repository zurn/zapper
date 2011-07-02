
#include "bar.h"

bar::bar()
{
		enemy_count = 0;
		begin = new emitter;
		begin->max_range = 8;
		begin->range_mod = .28;

		begin->rl = 180;
		begin->rh = 255;


		begin->gl = 0;
		begin->gh = 60;


		begin->bl = 0;
		begin->bh = 10;

//		begin->pos = start;
		begin->pos.x = -320;
		begin->pos.y = -220;
		begin->init(120, gfx::loadImage(LITTLE_PARTICLE));
		begin->lifetime = -1;
//		begin->vel.x = 2.25;
//		begin->vel.y = 2.25;
		begin->reset();



		end = new emitter;
		end->max_range = 8;
		end->range_mod = .28;

		end->rl = 0;
		end->rh = 10;


		end->gl = 0;
		end->gh = 101;


		end->bl = 90;
		end->bh = 101;


//		end->pos = start;
		end->pos.x = -320;
		end->pos.y = -220;
		end->init(120, gfx::loadImage(LITTLE_PARTICLE));
		end->lifetime = -1;
//		end->vel.x = 2.25;
//		end->vel.y = 2.25;
		end->reset();
}

bar::~bar()
{
	delete begin;
	delete end;
}

void bar::draw()
{
	gfx::replaceMode();
//	for (unsigned int i=0; i<visible_row.size(); i+=direction) {
//		visible_row[i]->draw(startx + (direction*(i * TILE_SIZE)), y);
//	}
	int start = 0;
	int mod = 0;
	int total = visible_row.size();

		start = startx;
	if (direction == 1) {
		mod = 1;
//	start -= ((.35 * mod) * TILE_SIZE);
	}
	else  {
//		start = endx;
		mod = -1;
//	start += ((.5 * mod) * TILE_SIZE);
	} 





	for (int i=0; i < total; i++){
		if (visible_row[i] != NULL) {
			visible_row[i]->draw(start +(mod * i)*TILE_SIZE , y);
		}
		else {
			gfx::blendMode();
			gfx::color(.78, .47, .45);
			gfx::drawRect(start +(mod * i)*TILE_SIZE , y, TILE_SIZE, TILE_SIZE);
			gfx::color(0, 0, 0);
			gfx::drawFrame(start +(mod * i)*TILE_SIZE +3, y+3, TILE_SIZE, TILE_SIZE, 3);
		}
	}
	begin->draw();
	end->draw();
}

void bar::load(int sx, int ex, int y, std::vector<image *> pics)
{
		bar::y = y;
		startx = sx;
		endx = ex;
		enemy_count=0;


		//figure out which way where going
		direction = endx - startx;
		if (direction > 0) {
			direction = 1;

//			endx += .25 * TILE_SIZE;
		}
		else {
			direction = -1;
//			endx += .25 * TILE_SIZE;
		}

//		startx += (.5 * TILE_SIZE);


		if(startx < TILE_SIZE) {
			startx = TILE_SIZE * .5;
		}
		if(endx < TILE_SIZE) {
			endx = TILE_SIZE * .5;
		}

		if (startx >= gfx::w-1) {
			startx = gfx::w - TILE_SIZE;
		}
		if (endx >= gfx::w-1) {
			endx = gfx::w -  TILE_SIZE;
		}

//		startx += (TILE_SIZE * .5);

		end->pos.x = startx + (.25 * TILE_SIZE);
		end->pos.y = y;

		begin->pos.x = endx;
		begin->pos.y = y;


		//determine how many tiles will be in this bar
		int w = abs(ex - sx + 1)/TILE_SIZE + 1;
		if (direction ==-1)
			w++;
		else
			w--;

		//load tiles
		for (int i=0; i < w; i++) {
			visible_row.push_back(pics[ran1_int(0, pics.size())]);
		}
}

void bar::update()
{
	begin->update();
	end->update();
}

