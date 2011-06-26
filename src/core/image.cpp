
#include "image.h"

image::image()
{
	data = NULL;
}

image::~image()
{
	if (data != NULL)
		delete data;
}

int image::load(const char * filename)
{
	SDL_Surface * image = IMG_Load(filename);
	if (image == NULL) {
		printf("Error loading image: %s\n", filename);
		return 0;
	}
	data = new texture2d(image);
	return 1;
}

void image::draw(int x, int y, int flipx, int flipy)
{
	if (data == NULL)
		return;

	if (flipx)
		data->flipx = 1;
	if (flipy)
		data->flipy = 1;

	data->draw(x,y);

	if (flipx)
		data->flipx = 0;
	if (flipy)
		data->flipy = 0;
}

void image::drawRotate(int x, int y, float theta, int flipx, int flipy)
{
	if (data == NULL)
		return;

	glMatrixMode(GL_TEXTURE);
	glPushMatrix();
	glLoadIdentity();

	glTranslatef(0.5,0.5,0.0);
	glRotatef(theta, 0.0, 0.0, 1.0);
	glTranslatef(-0.5,-0.5, 0.0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	draw(x,y, flipx, flipy);
	glPopMatrix();
}

void image::drawClipped(int x, int y , SDL_Rect * src, int flipx, int flipy)
{
	if (data == NULL || src == NULL)
		return;

	if (flipx)
		data->flipx = 1;
	if (flipy)
		data->flipy = 1;

	data->drawClipped(x,y,src);

	if (flipx)
		data->flipx = 0;
	if (flipy)
		data->flipy = 0;
}

int image::width()
{
	if (data == NULL)
		return 0;
	return data->w;
}

int image::height()
{
	if (data == NULL)
		return 0;
	return data->h;
}

