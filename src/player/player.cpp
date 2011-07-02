
#include "player.h"

player::player(level * l, particleMan * p, fireworks * f)
{
	collidable = true;
	name = "Zurn";
	world = l;
	effects = p;
	spells = f;
	place = NULL;
	pic = gfx::loadImage((char*)"./data/gfx/wizard.png");
	bamf = audio::loadSfx((char*)"./data/sfx/tele.wav");
	shoot = audio::loadSfx((char*)"./data/sfx/shoot.wav");

	tele = effects->getEmitter();

	tele->lifetime = 200;
	tele->max_range = 8;
	tele->range_mod = .22;

	tele->rl = 90;
	tele->rh = 101;
	tele->gl = 90;
	tele->gh = 101;
	tele->bl = 90;
	tele->bh = 101;

	tele->render = 0;
	tele->init(50, gfx::loadImage(BIG_PARTICLE));


	create_states();
	reset();
}

player::~player()
{
	cleanup();
}

void player::reset()
{
	pic = gfx::loadImage((char*)"./data/gfx/wizard.png");
	lives = 3;
	dead = false;
	flip = true;
	score = 0;
	level_num = 1;
	has_won = has_lost = false;

	bar_pos = 0;
	if (world->bars.size() == 0) {
//		printf("error restarting player. no bars found\n");
		return;
	}
	place = world->bars[0];

	player::pos.x = place->startx + (.5*TILE_SIZE);
	pos.y = place->y;

	if (place->direction == 1) {
		flip = false;
	}
	else {
		flip = true;
	}

//	printf("dude pos %f %f\n", pos.x, pos.y);
}

void player::start_level()
{
	change(PLY_IDLE);
	pic = gfx::loadImage((char*)"./data/gfx/wizard.png");
	if (world->bars.size() == 0) {
		printf("error loading player, null level\n\n");
		place = NULL;
		return;
	}

	has_won = has_lost = false;
	dead = false;
	place = world->bars[0];

	if (place->direction == 1) {
		flip = false;
	}
	else {
		flip = true;
	}

	player::pos.x = place->startx + (.5*TILE_SIZE);
	pos.y = place->y;
	bar_pos = 0;
//	printf("current bar dir: %i\n", place->direction);
}

void player::pause() { }

void player::unpause() { }

void player::bar_hop(int pos)
{
	if (pos < 0) {
		bar_pos = world->bars.size()-1;
	}else
	if (pos >= (int)world->bars.size()) {
		bar_pos = 0;
	}else {
		bar_pos = pos;
	}

	place = world->bars[bar_pos];
	player::pos.x = place->startx + (.5*TILE_SIZE);
	player::pos.y = place->y;

	tele->pos = player::pos;
	tele->pos.y += TILE_SIZE * .25;
	tele->pos.x -= TILE_SIZE * .25;
	tele->reset();

	if (place->direction != 1)
		flip = true;
	else
		flip = false;

	input::keys[KEY_RIGHT]->clear();
	input::keys[KEY_LEFT]->clear();
}

void player::launch()
{
	spells->add_player(place, this);
}

void player::create_states()
{
	states.resize(PLY_NUM_STATES, NULL);

	current = 
	states[PLY_IDLE]      = new ply_idle(this);
	states[PLY_CHARGE]    = new ply_charge(this);
	states[PLY_CELEBRATE] = new ply_celebrate(this);

	current->enter();
}

void player::cleanup()
{
	for (unsigned int i=0; i<states.size(); i++) {
		if (states[i] != NULL)
			delete states[i];
	}
}

void player::die()
{
	lives--;
}

void player::add_points(int num)
{
	for (int i=1; i<=num; i++) {
		score += 1;
		if (score % 6000 == 0) {
			lives++;
			audio::loadSfx("./data/sfx/extra_life.wav")->play(0, 1);
		}
	}
}

