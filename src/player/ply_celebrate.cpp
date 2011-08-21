
#include "ply_celebrate.h"

ply_celebrate::ply_celebrate(player * p)
{
	fsm = p;
	spin = 0.0;
}

ply_celebrate::~ply_celebrate()
{
}

void ply_celebrate::draw()
{
	gfx::replaceMode();
	fsm->pic->drawRotate(fsm->pos.x - TILE_SIZE*.5, fsm->pos.y, spin*360);
//	gfx::replaceMode();
//	fsm->pic->draw(fsm->pos.x - TILE_SIZE*.5, fsm->pos.y, fsm->flip);

//	gfx::replaceMode();
//	gfx::color(1,1,1);
//
//	font * big = gfx::loadFont("./data/fonts/bit.ttf", 22);
//	const char * text = "You have won!";
//	int w = big->width(text);
//
//	big->print(text, gfx::w/2 - w/2, gfx::h/2 - big->height()/2);
}

void ply_celebrate::enter()
{
	spin = 0.0;
	fsm->bamf->play(0,1);

	fsm->pos.x = gfx::w/2;
	fsm->pos.y = gfx::h/2;

	fsm->tele->pos = fsm->pos;
	fsm->tele->pos.y += TILE_SIZE * .25;
	fsm->tele->pos.x -= TILE_SIZE * .25;
	fsm->tele->reset();

	if (fsm->place->direction != 1)
		fsm->flip = true;
	else
		fsm->flip = false;
}

void ply_celebrate::exit()
{
//	fsm->has_won = true;
}

void ply_celebrate::pause()
{
}

void ply_celebrate::unpause()
{
}

void ply_celebrate::update()
{
	spin += .05;
	if (spin > 1) {
		spin = 0.0;
	}

	Vector vec;
	spin *=360;
	vec.x = -sin(spin*PI_OVER_180)*cos(spin*PI_OVER_180);
	vec.y = sin(spin*PI_OVER_180);
	spin /=360;

	float speed = 6.25;
	Vector vel = vec*speed;
	fsm->spells->add_vel(fsm->pos.x, fsm->pos.y, vel);
	fsm->shoot->play(0, 0);
//	printf("vec %f %f\n", vec.x, vec.y);


}

