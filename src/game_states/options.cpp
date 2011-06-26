
#include "options.h"

options::options(game * fsm)
{
	options::fsm = fsm;

	opt = gfx::loadFont("./data/fonts/mono.ttf", 20);
	title = gfx::loadFont("./data/fonts/bit.ttf", 44);
	select = audio::loadSfx("./data/sfx/select.wav");
	move = audio::loadSfx("./data/sfx/move.wav");
	background = gfx::loadImage("./data/gfx/paper.png");

	opts.push_back("Sound Effect Volume");
	opts.push_back("Music Volume");
	opts.push_back("Skip Song");
	opts.push_back("Configure Controls");
	opts.push_back("Restore Default Settings");
	opts.push_back("Back");
	set_hot(0);

	music_vol = fsm->custom->musVol;
	sfx_vol = fsm->custom->sfxVol;

	audio::setMusicVol(MIX_MAX_VOLUME * music_vol);
	audio::setSFXvol(MIX_MAX_VOLUME * sfx_vol);
}

options::~options()
{
}

void options::draw()
{
	gfx::replaceMode();
	background->draw(0, 0);
	gfx::blendMode();
	gfx::color(0,0,0);
	std::string name("Options");
	int xpos = WINDOW_W/2 - (title->width(name.c_str())/2);
	title->print(name.c_str(), xpos, 73);

	int x = 16*10, y = 16*9;
	std::string Hot = "(*) ";
	std::string Cold = "( ) ";
	std::string ts;

	for (unsigned int i=0; i<opts.size(); i++) {

		if (hot == int(i)) {
			gfx::color(0,0,0);
			ts = Hot + opts[i];
		}
		else {
			gfx::color(.5, .5, .5);
			ts = Cold + opts[i];
		}
		opt->print(ts.c_str(), x, y + (opt->height() * i));
		if (i == OM_SFX || i == OM_MUS) {
			y += opt->height();
			int nx = x + 40;
			int ny = y + 2 + (opt->height() * i);
			gfx::drawRect(nx, ny, 300, opt->height() -14);
			if (i == OM_SFX) {
				gfx::drawRect(nx + (300 * sfx_vol), ny - 5, 10, 20);
			}
			else {
				gfx::drawRect(nx + (300 * music_vol), ny - 5, 10, 20);
			}
		}
	}

}

void options::update()
{
	if (input::pressed(KEY_UP)) {
		set_hot(hot-1);
		move->play(0,1);
		return;
	}

	if (input::pressed(KEY_DOWN)) {
		set_hot(hot+1);
		move->play(0,1);
		return;
	}

	if (input::pressed(KEY_LEFT) && hot == OM_SFX) {
		sfx_vol -= .05;
		if (sfx_vol < 0) {
			sfx_vol = 0;
		}
		audio::setSFXvol(MIX_MAX_VOLUME * sfx_vol);
		select->play(0,1);

	fsm->custom->musVol = music_vol;
	fsm->custom->sfxVol = sfx_vol;
	}
	if (input::pressed(KEY_RIGHT) && hot == OM_SFX) {
		sfx_vol += .05;
		if (sfx_vol > 1.0) {
			sfx_vol = 1.0;
		}
		audio::setSFXvol(MIX_MAX_VOLUME * sfx_vol);
		select->play(0,1);

		fsm->custom->musVol = music_vol;
		fsm->custom->sfxVol = sfx_vol;
	}
	if (input::pressed(KEY_LEFT) && hot == OM_MUS) {
		music_vol -= .05;
		if (music_vol < 0) {
			music_vol = 0;
		}
		audio::setMusicVol(MIX_MAX_VOLUME * music_vol);
		select->play(0,1);

		fsm->custom->musVol = music_vol;
		fsm->custom->sfxVol = sfx_vol;
	}
	if (input::pressed(KEY_RIGHT) && hot == OM_MUS) {
		music_vol += .05;
		if (music_vol > 1.0) {
			music_vol = 1.0;
		}
		audio::setMusicVol(MIX_MAX_VOLUME * music_vol);
		select->play(0,1);

		fsm->custom->musVol = music_vol;
		fsm->custom->sfxVol = sfx_vol;
	}

	if (input::pressed(KEY_ACCEPT)) {
		switch(hot) {
			case OM_BACK:
				select->play(0,1);
				fsm->revert();
//				fsm->change(GS_MAIN_MENU);
			break;
			case OM_SKIP:
				select->play(0,1);
				audio::song_done();
			break;
			case OM_DEFAULT:
				select->play(0,1);
				fsm->custom->loadDefault();
				music_vol = fsm->custom->musVol;
				sfx_vol = fsm->custom->sfxVol;

				audio::setMusicVol(MIX_MAX_VOLUME * music_vol);
				audio::setSFXvol(MIX_MAX_VOLUME * sfx_vol);
			break;
			case OM_CONFIG:
				select->play(0,1);
				fsm->change(GS_CONFIG_CONTROLS);
				fsm->history.pop_back();
			break;

			default: break;
		}
		return;
	}

//	if (input::anykey) {
//		fsm->change(GS_MAIN_MENU);
//		
//	}
}

void options::enter()
{
	input::keys[KEY_LEFT]->repeat = 0;
	input::keys[KEY_RIGHT]->repeat = 0;
	input::keys[KEY_ACCEPT]->repeat = 0;

	input::clear();
	set_hot(0);
}

void options::exit()
{
	input::keys[KEY_LEFT]->repeat = 1;
	input::keys[KEY_RIGHT]->repeat = 1;
	input::keys[KEY_ACCEPT]->repeat = 1;
}

void options::set_hot(int n)
{
	if (n < 0) {
		hot = OM_BACK;
		return;
	}
	if ((unsigned int)n >= opts.size()) {
		hot = 0;
		return;
	}
	hot = n;
}

options::options()
{
}

void options::pause()
{
}

void options::unpause()
{
}

