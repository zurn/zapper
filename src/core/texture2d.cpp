
#include "texture2d.h"


//-------------------------------------------------------------------

texture2d::~texture2d()
{
	if (texture!=0)
		glDeleteTextures(1, &texture);
}

//-------------------------------------------------------------------

void texture2d::init()
{
	flipx = flipy = 0;
	texture = 0;
	w = h =0;
	minX = minY = 0;
	maxX = maxY = 0;
}

//-------------------------------------------------------------------

texture2d::texture2d(SDL_Surface * data)
{
	init();
	if (data == NULL)
		return;
	GLfloat texcoord[4];
//	GLenum gl_error;

	w = data->w;
	h = data->h;

	//Convert the data into an OpenGL texture
	texture = load2DTexture(data, texcoord);

	//Make texture coordinates easy to understand
	minX = texcoord[0];
	minY = texcoord[1];
	maxX = texcoord[2];
	maxY = texcoord[3];

	//We don't need the original data surface anymore 
	SDL_FreeSurface(data);
}

//-------------------------------------------------------------------

void texture2d::flip()
{
	if (flipx)
		swap(minX, maxX);
	if (flipy)
		swap(minY, maxY);
}

//-------------------------------------------------------------------

void texture2d::swap(GLfloat &a, GLfloat &b)
{
	GLfloat temp;
	temp = a;
	a = b;
	b = temp;
}

//-------------------------------------------------------------------

void texture2d::texture2d::draw(int x, int y)
{
	flip();

	glBindTexture(GL_TEXTURE_2D, texture);

	glBegin(GL_QUADS);
		glTexCoord2f(minX, minY); glVertex2i(x, y);
		glTexCoord2f(maxX, minY); glVertex2i(x+w, y);
		glTexCoord2f(maxX, maxY); glVertex2i(x+w, y+h);
		glTexCoord2f(minX, maxY); glVertex2i(x, y+h);
	glEnd();

	flip();

}

//-------------------------------------------------------------------

void texture2d::drawClipped(int x, int y , SDL_Rect * src)
{
	GLfloat maxx, maxy, minx, miny;//,t;

	//get actual texture size used for graphics
	int W = power_of_two(w);
	int H = power_of_two(h);

	//find new dimensions
	maxx = (src->x + src->w) / (GLfloat)W;
	minx = src->x / (GLfloat)W;

	maxy = (src->y + src->h) / (GLfloat)H;
	miny = src->y / (GLfloat)H;

	//flip the image if appropriate
	if (flipx)
		swap(maxx, minx);
	if (flipy)
		swap(maxy, miny);

	glBindTexture(GL_TEXTURE_2D, texture);

	glBegin(GL_QUADS);
		glTexCoord2f(minx, miny); glVertex2i(x, y);
		glTexCoord2f(maxx, miny); glVertex2i(x+src->w, y);
		glTexCoord2f(maxx, maxy); glVertex2i(x+src->w, y+src->h);
		glTexCoord2f(minx, maxy); glVertex2i(x, y+src->h);
	glEnd();
}

//-------------------------------------------------------------------

GLuint texture2d::load2DTexture(SDL_Surface *surface, GLfloat *texcoord)
{
	if (surface == NULL || texcoord == NULL)
		return 0;

	GLuint texture;
	int w, h;
	SDL_Surface *image;
	SDL_Rect area;

	/* Use the surface width and height expanded to powers of 2 */
	w = power_of_two(surface->w);
	h = power_of_two(surface->h);
	texcoord[0] = 0.0f;			/* Min X */
	texcoord[1] = 0.0f;			/* Min Y */
	texcoord[2] = (GLfloat)surface->w / w;	/* Max X */
	texcoord[3] = (GLfloat)surface->h / h;	/* Max Y */

	image = SDL_CreateRGBSurface(
			SDL_SWSURFACE,
			w, h,
			32,
#if SDL_BYTEORDER == SDL_LIL_ENDIAN /* OpenGL RGBA masks */
			0x000000FF, 
			0x0000FF00, 
			0x00FF0000, 
			0xFF000000
#else
			0xFF000000,
			0x00FF0000, 
			0x0000FF00, 
			0x000000FF
#endif
		);

	if ( image == NULL )
		return 0;

	//magic purple is always transparent
	SDL_SetColorKey(surface,
						SDL_SRCCOLORKEY,
						SDL_MapRGB(surface->format, 255,0,255)
						);

	SDL_SetAlpha(surface, 0, 0);

	/* Copy the surface into the GL texture image */
	area.x = 0;
	area.y = 0;
	area.w = surface->w;
	area.h = surface->h;
	SDL_BlitSurface(surface, &area, image, &area);

	/* Create an OpenGL texture for the image */
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D,
					0,
					GL_RGBA,
					w, h,
					0,
					GL_RGBA,
					GL_UNSIGNED_BYTE,
					image->pixels);
	SDL_FreeSurface(image); /* No longer needed */
	image = NULL;

	return texture;
}

//-------------------------------------------------------------------

int texture2d::power_of_two(int input)
{
	int value = 1;

	while (value < input) {
		value <<= 1;
	}
	return value;
}

//-------------------------------------------------------------------

