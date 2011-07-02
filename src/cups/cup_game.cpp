
#include "cup_game.h"

cup_game::cup_game()
{
	background = gfx::loadImage("./data/gfx/paper.png");

	for(int i=0; i<MAX_CUPS; i++) {
		cups.push_back(new cup(150 + i*60, 245));
	}

	done = won = lost = false;

	create_states();
}

cup_game::~cup_game()
{
	cleanup();
}

void cup_game::cleanup()
{
	for (unsigned int i=0; i<cups.size(); i++) {
		
	}
}

void cup_game::create_states()
{
	states.resize(CUPS_NUM_STATES, NULL);

	current = 
	states[CUPS_SWAP]   = new swap(this);
	states[CUPS_WAIT]   = new cup_intro(this);
	states[CUPS_CHOICE] = new cup_choice(this);
	states[CUPS_RESULT] = new cup_result(this);

	current->enter();
}

void cup_game::start_swap(cup * left, cup * right)
{
	left->go_right = true;
	left->start_swap();

	right->go_right = false;
	right->start_swap();


}

void cup_game::draw_cups()
{
	for(int i=0; i<MAX_CUPS; i++) {
		cups[i]->draw();
	}
}

void cup_game::update_cups()
{
	for(int i=0; i<MAX_CUPS; i++) {
		cups[i]->update();
	}
}

void cup_game::reset()
{
	cursor.reset();
	for (int i=0; i<MAX_CUPS; i++) {
		cups[i]->index = i;
		cups[i]->reset();
		
//		printf("pos %f %f\n", cups[i]->pos.x, cups[i]->pos.x);
	}

	int c = ran1_int(0, MAX_CUPS);
	cups[c]->pic = cups[c]->full;
	cups[c]->prized = true;
	done = won = lost = false;
}

void cup_game::close_cups()
{
	for (int i=0; i<MAX_CUPS; i++) {
		cup * c = cups[i];
		c->pic = c->closed;
	}
}

void cup_game::open_cups()
{
	for (int i=0; i<MAX_CUPS; i++) {
		cup * c = cups[i];

		if (c->prized) {
			c->pic = c->full;
		}
		else {
			c->pic = c->empty;
		}
	}
}

void cup_game::print()
{
	for (int i=0; i<6; i++) {
		if (cups[i]->prized) {
			printf("%i prized %i\n", i, cups[i]->index);
		}
		else {
			printf("%i no prized %i\n", i, cups[i]->index);
		}
	}
}

