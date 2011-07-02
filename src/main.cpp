
#include "zlibengn.h"
#include "audio.h"
#include "gfx.h"
#include "input.h"
#include "settings.h"
#include "timer.h"
#include "sprite.h"
#include "game.h"
#include "thing.cpp"
//main game loop
int main(int argc, char * argv[])
{
	gfx::init();

	sran1(SDL_GetTicks()% (SDL_GetTicks()*256));
	sran1(ran1()*1000);

	input::init();
	audio::init();
//	audio::setMusicVol(0);
//	audio::setSFXvol(0);
	
//	TiXmlDocument doc("./data/levels/test.xml");
//	doc.LoadFile();
	glPixelZoom(2.0, 2.0);

//	dump_to_stdout( doc.FirstChildElement());

//	ZlibEngine z;
//	z.compress( "data/controls.xml","controls.xml.z");
//	z.decompress( "controls.xml.z", "thing.xml");


	timer fps(60);

	settings * local = new settings("./data/config/settings.xml");
	game tapper(local);

	input::keys[KEY_UP]->repeat = 0;
	input::keys[KEY_DOWN]->repeat = 0;
	input::keys[KEY_ACCEPT]->delay = -1;
	input::keys[KEY_ACCEPT]->repeat = 0;
//	input::print();

//	audio::song_done();
	while(!input::quit) {
		
		input::poll();
		input::update();
		tapper.update();


//		if (input::pressed(KEY_QUIT)) {
//			gfx::BMPshot((char *)"shot.bmp"); }
//		if (input::pressed(KEY_DBG_QUIT)) {
//			input::quit = true;
//		}
//		if (input::pressed(KEY_DBG_1)) {
//			audio::song_done();
//		}

		gfx::clear();
		tapper.draw();

		gfx::swap();
		fps.delay();

	}


	local->save("./data/config/settings.xml");
	tapper.cleanup();
	delete local;

	input::cleanup();
	audio::cleanup();
	gfx::cleanup();

	return 0;
}

