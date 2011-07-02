
#ifndef __GAME_H__
#define __GAME_H__

#define HIGH_SCORE_FILE "./data/score.xml"

#include <stdio.h>
#include "machine.h"
#include "settings.h"
#include "scores.h"
#include "gfx.h"
#include "input.h"
#include "audio.h"

#include "particleMan.h"

#include "game_states.h"
#include "tapper.h"
#include "main_menu.h"
#include "splash.h"
#include "options.h"
#include "config_controls.h"
#include "disp_score.h"
#include "get_ready.h"
#include "game_over.h"
#include "get_name.h"
#include "pause_menu.h"
#include "death_by_enemy.h"
#include "death_by_projectile.h"
#include "win_level.h"
#include "cups.h"
#include "win_game.h"
#include "credits.h"

#include "level.h"
#include "fireworks.h"
#include "player.h"
#include "tip_jar.h"
#include "warren.h"
#include "obj_manager.h"

class game: public machine
{
	public:
		game(settings * options);
		virtual ~game();

		void cleanup();


		void create_states();
		void load_level();


		scores * high_score;
		level * world;
		player * dude;
		settings * custom;
		particleMan * effects;
		fireworks * spells;
		warren * enemies;
		tip_jar * tips;
		obj_manager * brains;
	private:
		game();
};




#endif /* __GAME_H__ */
