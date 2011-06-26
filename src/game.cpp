
#include "game.h"

game::game(settings * options)
{
	custom = options;

	high_score = new scores(HIGH_SCORE_FILE);
	high_score->load(HIGH_SCORE_FILE);

	effects = new particleMan;
	world = new level();

	if (world->level_files.size() < 4) {
		//not enough level files provided. killing program
		input::quit = true;
	}

	spells = new fireworks(world);
	tips = new tip_jar(world);
	enemies = new warren(world, effects, spells, tips);
	dude = new player(world, effects, spells);
	brains = new obj_manager(enemies, dude, spells, tips);
	create_states();
}

game::game() { }

game::~game()
{
	high_score->save(HIGH_SCORE_FILE);
	delete high_score;
}

void game::cleanup()
{
	for (unsigned int i=0; i<states.size(); i++) {
		if (states[i] != NULL)
			delete states[i];
	}
	delete brains;
	delete dude;
	delete enemies;
	delete spells;
	delete world;
	delete tips;
	delete effects;
}

void game::create_states()
{
//	printf("create game states\n");
	states.resize(GS_NUM_STATES, NULL);

	current =
	states[GS_SPLASH]           = new splash(this);
	states[GS_MAIN_MENU]        = new main_menu(this);
	states[GS_TAPPER]           = new tapper(this);
	states[GS_OPTIONS]          = new options(this);
	states[GS_CONFIG_CONTROLS]  = new config_controls(this);
	states[GS_VIEW_SCORES]      = new disp_score(this);
	states[GS_GET_READY]        = new get_ready(this);
	states[GS_GAME_OVER]        = new game_over(this);
	states[GS_ENTER_NAME]       = new get_name(this);
	states[GS_PAUSED]           = new pause_menu(this);
	states[GS_ENEMY_DEATH]      = new death_by_enemy(this);
	states[GS_PROJECTILE_DEATH] = new death_by_projectile(this);
	states[GS_WIN_LEVEL]        = new win_level(this);
	states[GS_CUPS]             = new cups(this);
	states[GS_WIN_GAME]         = new win_game(this);
	states[GS_CREDITS]          = new credits(this);

	current->enter();
}

void game::load_level()
{
	printf("creating level: %i\n", dude->level_num);

	audio::stopSfx();
	audio::song_done();
	tips->clean();
	spells->clean_all();
	if (!world->load(dude->level_num)) {
		return;
	}
	enemies->start_level();
	dude->start_level();
}

