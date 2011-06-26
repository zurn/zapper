
#ifndef __PROJECTILE_H__
#define __PROJECTILE_H__

#include "emitter.h"
#include "bar.h"
#include "object.h"


class projectile
{
	public:
		projectile(bar * b);
		virtual ~projectile();

		void update();
		void draw();

		void pause();
		void unpause();

		emitter * sparks;
		bar * place;

		bool dead;

	private:

};
#endif /* __PROJECTILE_H__ */
