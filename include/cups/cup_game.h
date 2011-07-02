
#ifndef __CUP_GAME_H__
#define __CUP_GAME_H__

#define MAX_CUPS 6

#include <vector>
#include "gfx.h"

#include "cup.h"
#include "cup_result.h"
#include "cup_cursor.h"

#include "cup_game_states.h"
#include "machine.h"

#include "swap.h"
#include "cup_intro.h"
#include "cup_choice.h"

class cup_game: public machine
{
	public:
		cup_game();
		virtual ~cup_game();

		void cleanup();
		void create_states();
		void reset();

		void draw_cups();
		void update_cups();
		void open_cups();
		void close_cups();

		void start_swap(cup * left, cup * right);

		cup_cursor cursor;
		std::vector<cup *> cups;
		image * background;
		bool done;
		bool won;
		bool lost;

		void print();
	private:

};
#endif /* __CUP_GAME_H__ */
