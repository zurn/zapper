
#include "swap.h"

swap::swap(cup_game * cg)
{
	fsm = cg;

	swap_inner = true;
	swap_delay.set(285);
	show_count = 0;
	closed_count = 0;
}

swap::~swap()
{
}

void swap::draw()
{
	gfx::replaceMode();
	fsm->background->draw(0,0);

	fsm->draw_cups();
	font * text = gfx::loadFont("./data/fonts/bit.ttf", 24);
	const char * msg = "Follow the gold!!";
	text->print(msg, gfx::w/2 - text->width(msg)/2 , 142);
}

void swap::enter()
{
	fsm->close_cups();
	closed_count = 0;
//	swap_inner = false;

	if (ran1_int(0, 2)==0) {
		swap_inner = false;
	}
	else {
		swap_inner = true;
	}

	if (swap_inner) {
		cup * temp;

		fsm->start_swap(fsm->cups[0],fsm->cups[1]);
		temp = fsm->cups[0];
		fsm->cups[0] = fsm->cups[1];
		fsm->cups[1] = temp;

		fsm->cups[0]->index = 0; 
		fsm->cups[1]->index = 1;

		fsm->start_swap(fsm->cups[2],fsm->cups[3]);
		temp = fsm->cups[2];
		fsm->cups[2] = fsm->cups[3];
		fsm->cups[3] = temp;

		fsm->cups[2]->index = 2; 
		fsm->cups[3]->index = 3;

		fsm->start_swap(fsm->cups[4],fsm->cups[5]);
		temp = fsm->cups[4];
		fsm->cups[4] = fsm->cups[5];
		fsm->cups[5] = temp;

		fsm->cups[4]->index = 4;
		fsm->cups[5]->index = 5;


//		swap_inner = false;
	}
	else {
		cup * temp;

		fsm->start_swap(fsm->cups[1],fsm->cups[2]);
		temp = fsm->cups[1];
		fsm->cups[1] = fsm->cups[2];
		fsm->cups[2] = temp;

		fsm->cups[1]->index = 1;
		fsm->cups[2]->index = 2;

		fsm->start_swap(fsm->cups[3],fsm->cups[4]);
		temp = fsm->cups[3];
		fsm->cups[3] = fsm->cups[4];
		fsm->cups[4] = temp;

		fsm->cups[3]->index = 3;
		fsm->cups[4]->index = 4;

//		swap_inner = true;
	}

	swap_delay.reset();
}

void swap::exit()
{
	show_count = 0;
}

void swap::pause()
{
}

void swap::unpause()
{
}

void swap::update()
{
	fsm->update_cups();

	if (swap_delay.is_past()) {
			int max = ran1_int(17, 25);
			if (show_count > max) {
//				fsm->done = true;
				fsm->change(CUPS_CHOICE);
				return;
			}
		enter();
		show_count++;
	}
}

