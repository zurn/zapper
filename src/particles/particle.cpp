
#include "particle.h"

//-------------------------------------------------------------------

particle::particle()
{

	pic = gfx::loadImage(LITTLE_PARTICLE);
	clear();
}

//-------------------------------------------------------------------
particle::~particle() {}

//-------------------------------------------------------------------

void particle::clear()
{
//std::cout << "called const\n";
	r=g=b=dead=0.0;a=1;
	life = fade = 1;
	pos = vel = dir = ZERO;

}

//-------------------------------------------------------------------

void particle::init()
{
//	std::cout << start;
	pos = e->pos;
//	pos.x = e->pos.x;
//	pos.y = e->pos.y;
	life = .6;
	a=.6;
	a=life=e->starting_life;

	fade = ran1_int(25,100) * .001f;
//	fade *=100;
	fade += .003;

	dir.x = (scalar) scalar(ran1_int(0,e->max_range)-(e->max_range >>1));
	dir.y = (scalar) scalar(ran1_int(0,e->max_range)-(e->max_range >>1));

	dir *= e->range_mod;

	r = ran1_int(e->rl, e->rh) * .01;
	g = ran1_int(e->gl, e->gh) * .01;
	b = ran1_int(e->bl, e->bh) * .01;
}

//-------------------------------------------------------------------

void particle::print()
{
	printf("r: %f g: %f b: %f a: %f\n",r,g,b,a);
	printf("fade: %f life: %f\n",fade,life);
	printf("pos: %f %f\n", pos.x, pos.y);
//	std::cout << "pos: " << pos;
//	std::cout << "dir: " << dir;
}

//-------------------------------------------------------------------

void particle::draw()
{
//	print();

//	GAME->Graphics->blendMode();

	gfx::color(r,g,b,a);
	if (pic != NULL) {
		pic->draw(pos.x - (pic->width()*.05), pos.y - (pic->height() * .05));
	}
}


//-------------------------------------------------------------------

void particle::update(int renew)
{
//	pos += e->vel;
	if (life>0) {
		pos+=dir;
	//	pos+=vel;
		life-=fade;
		a-=fade;
	//	r-=fade;
	}

	if (life<0 && renew) {
		init();
//		std::cout<<"respawn\n";
//		print();
	}
}

//-------------------------------------------------------------------

