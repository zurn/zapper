
#include "projectile.h"

projectile::projectile(bar * b)
{
	place = b;
	dead = false;


	sparks = new emitter;

}

projectile::~projectile()
{
	delete sparks;
}

void projectile::draw()
{
	sparks->draw();
}

void projectile::pause()
{
}

void projectile::unpause()
{
}

void projectile::update()
{
	sparks->update();


//	if (sparks->vel.x > 0) {
//		if (sparks->pos.x > place->endx) {
//			dead = true;
//		}
//	}
//	else {
//		if (sparks->pos.x < place->endx) {
//			dead = true;
//		}
//		
//	}
}

