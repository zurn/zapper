
#ifndef EMITTER_DOT_H
#define EMITTER_DOT_H 1

#include <list>
#include "particle.h"
#include "matho.h"
#include "gfx.h"
#include "tinyxml.h"

class particle;

typedef std::list<particle> particles;

class emitter {

	public:
		emitter();
		~emitter();

		void init(int numParticles, image * img);
		bool load(const char * filename);
		void reset();
		void update();
		void draw();

		int render;
		particles parts;
		int renew;
		Vector pos;
		Vector vel;
		int lifetime;
		int initial_time;


		//particle starting values
		scalar starting_life;
		int max_range;
		scalar range_mod;

		//highest and lowest values for each color component
		int rh, rl;
		int gh, gl;
		int bh, bl;


		static int id;
		int me;

};

#endif /* EMITTER_DOT_H */

