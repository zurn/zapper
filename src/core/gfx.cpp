#include "gfx.h"

int gfx::bpp = 8;
int gfx::sync = 0;
int gfx::accel = 0;
int gfx::gamma = 0;
int gfx::fullscreen = 0;
int gfx::noframe = 0;
int gfx::fsaa = 0;
int gfx::w = 0;
int gfx::h = 0;
SDL_Surface * gfx::screen = NULL;
const char * gfx::title = "Zapper";
const char * gfx::iconName = "Zapper";
const char * gfx::icon = "data/gfx/icon.bmp";
fontFactory gfx::ffact;
imageFactory gfx::ifact;

gfx::gfx()
{

	if (!init()) {
		SDL_Quit();
		_Exit(1);
	}
}

gfx::~gfx()
{
	SDL_Quit();
}

int gfx::init()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("Unable to initialize SDL: %s\n", SDL_GetError());
		return 0;
	}

	if (!setupScreen())
		return 0;

	enter2DMode();

	return 1;
}

void gfx::cleanup()
{
	SDL_Quit();
}

int gfx::setupScreen()
{
	//Set the flags we want to use for setting the video mode
	Uint32 video_flags;
	video_flags = SDL_OPENGL;

	if (fullscreen == 1)
		video_flags |= SDL_FULLSCREEN;

	if (noframe)
		video_flags |= SDL_NOFRAME;

	if (w==0 || h==0) {
		w = WINDOW_W;
		h = WINDOW_H;
	}

	//Initialize the display
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, bpp);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	if (fsaa) {
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, fsaa);
	}

	if (accel)
		SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	if (sync)
		SDL_GL_SetAttribute(SDL_GL_SWAP_CONTROL, 1);
	else
		SDL_GL_SetAttribute(SDL_GL_SWAP_CONTROL, 0);

	//setup window icon
	SDL_Surface * i = SDL_LoadBMP(icon);//must use <= 16bit .bmp

	if (i != NULL) {
		//death pink for transparency color
		SDL_SetColorKey(
							i,
							SDL_SRCCOLORKEY,
							SDL_MapRGB(i->format, 255, 0, 255)
						);
		SDL_WM_SetIcon(i, NULL);
		SDL_FreeSurface(i);
	}

	//Set the window manager title bar
	SDL_WM_SetCaption(title, iconName);

	if ((gfx::screen = SDL_SetVideoMode(WINDOW_W,
			WINDOW_H, bpp, video_flags)) == NULL) {
		printf("Couldn't set GL mode: %s\n", SDL_GetError());
		SDL_Quit();
		return 0;
	}

	SDL_ShowCursor(SDL_DISABLE);

	//Set the gamma for the window 
	if (gamma != 0.0) {
		SDL_SetGamma(gamma, gamma, gamma);
	}

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glShadeModel(GL_SMOOTH);
//	glClearColor(1.50, 0.0, 1.50, 1.0);
	glClearColor(0.0, 0.0, 0.0, 1.0);

	return 1;
}

void gfx::swap()
{
	SDL_GL_SwapBuffers();
}

void gfx::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void gfx::color(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	glColor4f(r, g, b, a);
}

void gfx::enter2DMode()
{

	//Note, there may be other things you need to change,
	//depending on how you have your OpenGL state set up.

	glPushAttrib(GL_ENABLE_BIT);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);

	//This allows alpha blending of 2D textures with the scene
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glViewport(0, 0, screen->w, screen->h);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	glOrtho(0.0, (GLdouble)screen->w,(GLdouble)screen->h, 0.0, 0.0, 1.0);
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	glLoadIdentity();

	replaceMode();
}

void gfx::leave2DMode()
{
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glPopAttrib();
}

void gfx::print()
{
	int value;
	//Display info
	printf("Screen BPP: %d\n", SDL_GetVideoSurface()->format->BitsPerPixel);
	printf("\n");
	printf("Vendor     : %s\n", glGetString(GL_VENDOR));
	printf("Renderer   : %s\n", glGetString(GL_RENDERER));
	printf("Version    : %s\n", glGetString(GL_VERSION));
	printf("Extensions : %s\n", glGetString(GL_EXTENSIONS));
	printf("\n");

	SDL_GL_GetAttribute(SDL_GL_RED_SIZE, &value);
	printf("SDL_GL_RED_SIZE: requested 8, got %d\n", value);
	SDL_GL_GetAttribute(SDL_GL_GREEN_SIZE, &value);
	printf("SDL_GL_GREEN_SIZE: requested 8, got %d\n", value);
	SDL_GL_GetAttribute(SDL_GL_BLUE_SIZE, &value);
	printf("SDL_GL_BLUE_SIZE: requested 8, got %d\n", value);
	SDL_GL_GetAttribute(SDL_GL_DEPTH_SIZE, &value);
	printf("SDL_GL_DEPTH_SIZE: requested %d, got %d\n", bpp, value);
	SDL_GL_GetAttribute(SDL_GL_DOUBLEBUFFER, &value);
	printf("SDL_GL_DOUBLEBUFFER: requested 1, got %d\n", value);
	if (fsaa) {
		SDL_GL_GetAttribute(SDL_GL_MULTISAMPLEBUFFERS, &value);
		printf("SDL_GL_MULTISAMPLEBUFFERS: requested 1, got %d\n", value);
		SDL_GL_GetAttribute(SDL_GL_MULTISAMPLESAMPLES, &value);
		printf("SDL_GL_MULTISAMPLESAMPLES: requested %d, got %d\n", fsaa, value);
	}
	if (accel) {
		SDL_GL_GetAttribute(SDL_GL_ACCELERATED_VISUAL, &value);
		printf("SDL_GL_ACCELERATED_VISUAL: requested %d, got %d\n", accel, value);
	}
	if (sync) {
		SDL_GL_GetAttribute(SDL_GL_SWAP_CONTROL, &value);
		printf("SDL_GL_SWAP_CONTROL: requested %d, got %d\n", sync, value);
	}
}

void gfx::drawFrame(int x, int y, int w, int h, int width)
{
	int X, Y, W, H;

	//top line
	X = x - width;
	Y = y - width;
	W = w - 1 + width;
	H = width;
	drawRect(X, Y, W, H);

	//left line
	X = x - width;
	Y = y - width;
	W = width;
	H = h - 1 + width;
	drawRect(X, Y, W, H);

	//right line
	X = (x + w -1) - width;
	Y = y;
	W = width;
	H = h - 1;
	drawRect(X, Y, W, H);

	//bottom line
	X = x;
	Y = (y + h - 1) - width;
	W = w - 1;
	H = width;
	drawRect(X, Y, W, H);
}

void gfx::drawRect(int x, int y, int w, int h)
{
	int swap = 0;
	if (glIsEnabled(GL_TEXTURE_2D) == GL_TRUE) {
		glDisable(GL_TEXTURE_2D);
		swap = 1;
	}

	glBegin(GL_QUADS);
		glVertex2i(x,y);
		glVertex2i(x + w, y);
		glVertex2i(x + w, y + h);
		glVertex2i(x,y + h);
	glEnd();

	if (swap)
		glEnable(GL_TEXTURE_2D);
}

void gfx::blendMode()
{
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
}

void gfx::replaceMode()
{
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
}

void gfx::modMode()
{
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

font * gfx::loadFont(const char * path, int ptsize)
{
	return ffact.load(path, ptsize);
}

image * gfx::loadImage(const char * path)
{
	return ifact.load(path);
}

void gfx::BMPshot(char * filename)
{
	SDL_Surface *temp = NULL;
	unsigned char *pixels = NULL;

#if SDL_BYTEORDER == SDL_LIL_ENDIAN /* OpenGL RGBA masks */
	temp = SDL_CreateRGBSurface(SDL_SWSURFACE,
				WINDOW_W, WINDOW_H,
				24,
				0x000000FF, 0x0000FF00, 0x00FF0000, 0);
#else
	temp = SDL_CreateRGBSurface(SDL_SWSURFACE,
				WINDOW_W,
				WINDOW_H,
				24,
				0x00FF0000, 0x0000FF00, 0x000000FF, 0);
#endif

	if (temp != NULL) {
		pixels = new unsigned char[3 * WINDOW_W * WINDOW_H];
		if (pixels != NULL) {
			glReadPixels(0, 0, WINDOW_W, WINDOW_H, GL_RGB, GL_UNSIGNED_BYTE, pixels);

			for (int i = 0; i < WINDOW_H; i++)	{
				memcpy(((char *) temp->pixels) + temp->pitch * i, pixels + 3 * WINDOW_W * (WINDOW_H-i-1), WINDOW_W * 3);
			}

			SDL_SaveBMP(temp, filename);
			delete [] pixels;
		}
		SDL_FreeSurface(temp);

	}
	printf("File: %s saved.\n", filename);
}

