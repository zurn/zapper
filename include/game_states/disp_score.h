
#ifndef __DISP_SCORE_H__
#define __DISP_SCORE_H__

#include "game.h"
#include "state.h"
#include "entry.h"


class disp_score: public state
{
	public:
		disp_score(game * fsm);
		virtual ~disp_score();

		void update();
		void draw();
		void enter();
		void exit();
		void pause();
		void unpause();

		void draw(std::vector<entry> & entries, int x, int y);
		game * fsm;

		font * opt;
		font * title;
		sound * select;
		sound * move;
		image * background;
	private:

};
#endif /* __DISP_SCORE_H__ */
