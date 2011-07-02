
#ifndef __BAR_H__
#define __BAR_H__


#include "constants.h"
#include "RNG.h"
#include "particleMan.h"

#include <vector>

struct bar_info
{
	int x1;
	int x2;
	int y;
};

class bar
{
	public:
		bar();
		~bar();

		void load(int sx, int ex, int y, std::vector<image *> pics);

		void update();
		void draw();

		emitter * begin;
		emitter * end;

		int enemy_count;

		int y;
		int startx;
		int endx;
		int direction;

		std::vector<image *> visible_row;

	private:

};
#endif /* __BAR_H__ */
