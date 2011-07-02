
#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "level.h"
#include "input.h"
#include "audio.h"
#include "particleMan.h"
#include "player_states.h"
#include "ply_idle.h"
#include "ply_charge.h"
#include "machine.h"
#include "fireworks.h"
#include  "object.h"
#include "ply_celebrate.h"

const std::string DEATH_BY_ENEMY = "You were overrun.";
const std::string DEATH_BY_PROJECTILE = "You need to be more careful.";

class player: public machine, public object
{
	public:
		player(level * l, particleMan * p, fireworks * f);
		virtual ~player();

		void create_states();
		void cleanup();


		void reset();
		void start_level();

		void pause();
		void unpause();

		void bar_hop(int pos);
		//teleports player to adjacent bar.

		void launch();
		//adds projectile to the world.

		void add_points(int num);

		void die();

		std::string death_message;
		std::string name;
		int score;
		int level_num;
		bool has_won;
		bool has_lost;
		int lives;


		bool flip;
		image * pic;
		emitter * tele;
		sound * bamf;
		sound * shoot;


		level * world;
		particleMan * effects;
		bar * place;
		int bar_pos;

		fireworks * spells;

	private:

};
#endif /* __PLAYER_H__ */
