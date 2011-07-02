
#include "keyboard.h"

keyboard::keyboard()
{
	wpx = 45;
	hpx = 39;
	x = y = 0;
	xoffset = 56 + 8;
	yoffset = 122 + 4 ;

	xoffset = 56 + 24;
	yoffset = 122 + 4 ;

	special = gfx::loadFont("./data/fonts/mono.ttf", 18);
	alpha = gfx::loadFont("./data/fonts/mono.ttf",30);
//	printf("w: %i h: %i\n", alpha->width(" "), alpha->height());

	//fill in letters with upper and lower case alphabet
	char ctemp = 'A';
	for (int y=0; y<5; y++) {
		for (int x=0; x<11; x++) {
			letters[x][y] = ctemp;
			ctemp++;
			if (int(ctemp) > int('Z') && int(ctemp) < int('a')) {
				ctemp = 'a';
			}
		}
	}

	//fill in a row for the numbers
	ctemp = '0';
	for (int i=0; i<10; i++) {
		letters[i][5] = ctemp;
		ctemp++;
	}

	//fill in a row for punctuation
	ctemp = '!';
	for (int i=0; i<10; i++) {
		letters[i][6] = ctemp;
		ctemp++;
	}

	//clear out some garbage, replace some punctuation
	letters[8][4] = ' ';
	letters[9][4] = ' ';
	letters[1][6] = '@';
	letters[6][6] = '?';

	//add special characters used as return values
	letters[10][5] = KB_BACK;
	letters[10][4] = KB_CANCEL;
	letters[10][6] = KB_DONE;

//	for (int i=0; i<KB_H; i++) {
//		for (int j=0; j<KB_W; j++) {
//			printf("%c ", letters[j][i]);
//		}
//		printf("\n");
//	}


}

keyboard::~keyboard()
{
}

void keyboard::setPosition(int x, int y)
{
	if (x < 0)
		x = KB_W - 1;
	if (x > KB_W -1)
		x = 0;

	if (y < 0)
		y = KB_H -1;
	if (y > KB_H -1)
		y = 0;

	keyboard::x = x;
	keyboard::y = y;
}

void keyboard::drawCursor()
{
	gfx::color(1, 0, 0);
	switch (letters[x][y]) {
		case KB_BACK:
		case KB_CANCEL:
		case KB_DONE:
			gfx::drawFrame(
				x*wpx+ xoffset -8-8,
				y *hpx+ yoffset-4,
				wpx*2,hpx-10, 2
			);
		break;

		default:
			gfx::drawFrame(
				x*wpx+ xoffset -8,
				y *hpx+yoffset-4,
				wpx,hpx, 2
			);
		break;
	};
}

char keyboard::getCursor()
{
	return getChar(x, y);
}

char keyboard::getChar(int x, int y)
{
	if (x < 0 || x > KB_W -1 ||
		y < 0 || y > KB_H -1)
		return ' ';
	else
		return letters[x][y];
}

void keyboard::draw()
{
	gfx::blendMode();
	gfx::color(0,0,0);

	char ctemp[2];
	ctemp[1] = '\0';

	//draw grid of characters and the few special cases
	for (int h=0; h<KB_H; h++) {
		for (int w=0; w<KB_W; w++) {

			if (letters[w][h] == KB_BACK) {
				special->print("Bksp", w*wpx+xoffset-8, h*hpx+yoffset);
				continue;
			}
			if (letters[w][h] == KB_CANCEL) {
				special->print("Clear", w*wpx+xoffset-8, h*hpx+yoffset);
				continue;
			}
			if (letters[w][h] == KB_DONE) {
				special->print("Done", w*wpx+xoffset-8, h*hpx+yoffset);
				continue;
			}

			ctemp[0] = letters[w][h];
			alpha->print(
				ctemp,
				w*wpx+xoffset,
				h*hpx+yoffset
			);
		}
	}

	drawCursor();
}

void keyboard::update()
{
	if (input::pressed(KEY_UP)) {
		setPosition(x, y-1);
		return;
	}

	if (input::pressed(KEY_DOWN)) {
		setPosition(x, y+1);
		return;
	}

	if (input::pressed(KEY_LEFT)) {
		setPosition(x-1, y);
		return;
	}

	if (input::pressed(KEY_RIGHT)) {
		setPosition(x+1, y);
		return;
	}
}

