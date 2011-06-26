#ifndef PARTICLEMAN_H
#define PARTICLEMAN_H

#include "emitter.h"
#include <list>

class emitter;
typedef std::list<emitter *> emitters;

class particleMan
{
	public:
		particleMan();
		~particleMan();

		int init();
		void update();
		void draw();
		void clean();

		emitter * getEmitter();
		void remove(emitter * target);

		emitters current;
	private:
		/* particleMan data */
};

#endif /* PARTICLEMAN_H */

