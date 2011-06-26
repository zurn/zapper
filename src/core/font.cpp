
#include "font.h"

//-------------------------------------------------------------------

font::font()
{
	init();
}

//-------------------------------------------------------------------

font::font(const char * path, int ptsize, int renderstyle)
{
	if (!init())
		return;

	load(path, ptsize, renderstyle);
}

//-------------------------------------------------------------------

font::~font()
{
	for (unsigned int i=0; i<alphabet.size(); i++)
		delete alphabet[i];

	alphabet.clear();

	delete color;
	if (data != NULL)
		TTF_CloseFont(data);
}

//-------------------------------------------------------------------

int font::init()
{
	color = new SDL_Color;
	color->r = 0;
	color->g = 0;
	color->b = 0;
	data = NULL;

	if(!TTF_WasInit())
		if (TTF_Init() < 0) {
			printf("Couldn't initialize TTF: %s\n",SDL_GetError());
			return 0;
		}

	return 1;
}

//-------------------------------------------------------------------

int font::load(const char * path, int ptsize, int renderstyle)
{
	if (data != NULL)
		return 0;

	//quick and dirty hack
	//this if prevents sending a non existant path to TTF_OpenFont(...)
	//TTF_OpenFont(...) works fine in linux but seg faults when I cross
	//compile with i386-mingw32-g++
	if (access(path,F_OK)==-1) {
		printf("Couldn't load %d pt Font from %s: File does not exist.\n",
					ptsize, path);
		return 0;
	}

	data = TTF_OpenFont(path, ptsize);
	if (data == NULL) {
		printf("Couldn't load %d pt Font from %s: %s\n",
					ptsize, path, SDL_GetError());
		return 0;
	}
	TTF_SetFontStyle(data, renderstyle);

	if (!load_alpha())
		return 0;

	return 1;
}

//-------------------------------------------------------------------

int font::height()
{
	if (data == NULL)
		return 0;

	return TTF_FontHeight(data);
}

//-------------------------------------------------------------------

int font::load_alpha()
{
	char message[95];
	int c=0;

	for (int i=32; i<127; i++, c++)
		message[c]= char(i);
	//message should look like this
	// !"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ
	//[\]^_`abcdefghijklmnopqrstuvwxyz{|}~

	SDL_Surface * text;
	char temp[2];
	temp[1]='\0';

	//loop through message and create individual textures
	for (int i=0;i<95;i++) {
		temp[0]= message[i];
		text = TTF_RenderText_Solid(data, temp, *color);

		if (text == NULL) {
			printf("Couldn't create text: %s\n", SDL_GetError());
			return 0;
		}

		alphabet.push_back(new texture2d(text));
	}
	return 1;
}

//-------------------------------------------------------------------

int font::print(const char * msg, int x, int y)
{
	int width = 0;
	int size = strlen(msg);
	int xpos = x;
	unsigned int num;
	for (int i=0;i<size;i++) {
		num = int(msg[i]);	//get ascii value
		num -= 32;				//convert to alphabet index

		if (num < 0 || num > alphabet.size()-1)
			continue;

//		if (num) {//skip space character
		if (1) {//skip space character
			alphabet[num]->draw(xpos,y);
			xpos += (alphabet[num]->w);
			width += (alphabet[num]->w);
		}
//		else {
//			xpos += (alphabet[num]->w >> 1);//cut space width in half
//			width += (alphabet[num]->w >> 1);
//		}
	}
	return width;
}

//-------------------------------------------------------------------

int font::width(const char * msg)
{
	int w = 0;
	int size = strlen(msg);
	unsigned int num;
	for (int i=0;i<size;i++) {
		num = int(msg[i]);	//get ascii value
		num -= 32;				//convert to alphabet index

		if (num < 0 || num > alphabet.size()-1)
			continue;

//		if (num) {//skip space character
		if (1) {//skip space character
			w += (alphabet[num]->w);
		}
//		else {
//			w += (alphabet[num]->w >> 1);//cut space width in half
//		}
	}
	return w;
}

//-------------------------------------------------------------------

