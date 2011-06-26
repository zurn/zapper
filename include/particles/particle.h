
#ifndef PARTICLE
#define PARTICLE 1

#include "RNG.h"
#include "matho.h"
#include "emitter.h"
#include "gfx.h"
#include "constants.h"

class emitter;

class particle {

	public:

		particle();
		~particle();

		void init();
		void clear();
		void print();
		void draw();
		void update(int renew);

		scalar r;
		scalar g;
		scalar b;
		scalar a;


		emitter * e;

//		int rh, rl;
//		int gh, gl;
//		int bh, bl;

//		scalar starting_life;
//		int max_range;
//		scalar range_mod;

		scalar life;
		scalar fade;
		Vector pos;
		Vector vel;
		Vector dir;
		int dead;
		image * pic;
};

#endif

