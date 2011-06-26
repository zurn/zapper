
#include "emitter.h"

int emitter::id = 0;

emitter::emitter()
{
	me = id;
	id++;
}

emitter::~emitter(){}

void emitter::init(int n, image * img)
{
	parts.clear();

	renew = 1;
	render = 0;
	starting_life = 1;
	particle p;

	for (int i=0;i<n;i++) {

		if (img != NULL) {
			p.pic = img;
		}
		p.e = this;
		p.init();

		parts.push_back(p);
	}
	initial_time = SDL_GetTicks();
}

void emitter::update()
{
	pos += vel;

	if (pos.x > gfx::w) {
		vel.x = -vel.x;
	}
	if (pos.y > gfx::h) {
		vel.y = -vel.y;
	}
	if (pos.x < 0) {
		vel.x = -vel.x;
	}
	if (pos.y < 0) {
		vel.y = -vel.y;
	}
	if (lifetime > -1)
	if ((int)SDL_GetTicks() > initial_time + lifetime) {
		renew = 0;
	}

	for(particles::iterator it=parts.begin();it!=parts.end();it++) {
		it->update(renew);
	}
}

void emitter::draw()
{
	if (!render) return;
	gfx::modMode();
		for(particles::iterator it=parts.begin();it!=parts.end();it++) {
			it->draw();
		}
}

void emitter::reset()
{
	initial_time = SDL_GetTicks();
	renew = 1;
	render = 1;
}

bool emitter::load(const char * filename)
{
	return true;
}

