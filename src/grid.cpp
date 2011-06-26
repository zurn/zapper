
#include "grid.h"

//-------------------------------------------------------------------

grid::grid()
{
	fill = 0;
}

grid::~grid() {}

//-------------------------------------------------------------------

grid::grid(int w, int h)
{
	fill = 0;
	build(w,h);
}

grid::grid(int w, int h, int color)
{
	fill = color;
	build(w,h);
	fill = 0;
}

int& grid::operator() (int x, int y)
{
	return data[y][x];
}

int grid::bounds(int x, int y)
{
	if (x<0 || y<0) return 0;
	if (x>=width || y>=height) return 0;

	return 1;
}

//-------------------------------------------------------------------

int grid::copy(grid * g, int x, int y)
{
	if (g == NULL) return 0;
	if (x < 0 || y < 0) return 0;
	if (x + g->width > width || y + g->height > height) return 0;

	int xx, yy;

	yy = 0;
	for (int j = y; j < y + g->height; j++) {
		xx = 0;
		for (int i = x; i < x + g->width; i++) {
			data[j][i] = (*g)(xx,yy);
			xx++;
		}
		yy++;
	}

	return 1;
}

//-------------------------------------------------------------------
void grid::print()
{
	printf("w: %i h: %i\n", width, height);

	for (int i=0; i<height; i++) {
		for (int j=0; j<width; j++) {
			printf("%i ", data[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

//-------------------------------------------------------------------

void grid::build(int w, int h)
{
	data.clear();
	row temp(w,fill);

	for (int i=0; i<h; i++)
			data.push_back(temp);

	width = w;
	height = h;
	area = h * w;
}

//-------------------------------------------------------------------

void grid::print_ppm(char * filename)
{

	char white[12] = "255 255 255";
	char black[7] = "0 0 0";
	char red[8] = "255 0 0";
	char green[8] = "0 255 0";
	std::ofstream fout;
	fout.open(filename);

	//header
	fout<< "P3" << "\n"
		 << width <<' '
		 << height << '\n'
		 << "255\n";

	//pixels
	for (int i = 0; i < height; i++) {
		for (int j=0; j < width; j++) {

//		if (data[i][j] != 0)
//			fout << black;
//		else
//			fout << white;

		if (data[i][j] == 1)
			fout << black;
		else if (data[i][j] == 3)
			fout << red;
		else if (data[i][j] == 4)
			fout << green;
		else
			fout << white;


		fout << "   ";

		}
		fout << "\n";
	}

	fout.close();
}

//-------------------------------------------------------------------

int grid::plot(int x,int y)
{
	if (x<0 || y<0) return 0;
	if (x>=width || y>=height) return 0;

	data[y][x] = fill;
	return 1;
}

//-------------------------------------------------------------------

void grid::line(int x1, int y1, int x2, int y2, int quit)
{

	int delta_x = abs(x2 - x1) << 1;
	int delta_y = abs(y2 - y1) << 1;

	// if x1 == x2 or y1 == y2, then it does not matter what we set here
	signed char ix = x2 > x1?1:-1;
	signed char iy = y2 > y1?1:-1;

	plot(x1, y1);

	if (delta_x >= delta_y) {
		// error may go below zero
		int error = delta_y - (delta_x >> 1);

		while (x1 != x2) {
			if (error >= 0) {
				if (error || (ix > 0)) {
					y1 += iy;
					error -= delta_x;
				}
				// else do nothing
			}
			// else do nothing

			x1 += ix;
			error += delta_y;

			if (bounds(x1,y1) && data[y1][x1] != quit)
				plot(x1, y1);
			else
				return;
		}
	}
	else {
		// error may go below zero
		int error = delta_x - (delta_y >> 1);

		while (y1 != y2) {
			if (error >= 0) {
				if (error || (iy > 0)) {
					x1 += ix;
					error -= delta_y;
				}
				// else do nothing
			}
			// else do nothing

			y1 += iy;
			error += delta_x;

			if (bounds(x1,y1) && data[y1][x1] != quit)
				plot(x1, y1);
			else
				return;
//			plot(x1, y1);
		}
	}

}

//-------------------------------------------------------------------

void grid::line(int x1, int y1, int x2, int y2) {

	int delta_x = abs(x2 - x1) << 1;
	int delta_y = abs(y2 - y1) << 1;

	// if x1 == x2 or y1 == y2, then it does not matter what we set here
	signed char ix = x2 > x1?1:-1;
	signed char iy = y2 > y1?1:-1;

	plot(x1, y1);

	if (delta_x >= delta_y) {
		// error may go below zero
		int error = delta_y - (delta_x >> 1);

		while (x1 != x2) {
			if (error >= 0) {
				if (error || (ix > 0)) {
					y1 += iy;
					error -= delta_x;
				}
				// else do nothing
			}
			// else do nothing

			x1 += ix;
			error += delta_y;

			plot(x1, y1);
		}
	}
	else {
		// error may go below zero
		int error = delta_x - (delta_y >> 1);

		while (y1 != y2) {
			if (error >= 0) {
				if (error || (iy > 0)) {
					x1 += ix;
					error -= delta_y;
				}
				// else do nothing
			}
			// else do nothing

			y1 += iy;
			error += delta_x;

			plot(x1, y1);
		}
	}
}

//-------------------------------------------------------------------

void grid::circle(int x0, int y0, int radius) {

	int f = 1 - radius;
	int ddF_x = 1;
	int ddF_y = -2 * radius;
	int x = 0;
	int y = radius;

	plot(x0, y0 + radius);
	plot(x0, y0 - radius);
	plot(x0 + radius, y0);
	plot(x0 - radius, y0);

	while(x < y) {
		// ddF_x == 2 * x + 1;
		// ddF_y == -2 * y;
		// f == x*x + y*y - radius*radius + 2*x - y + 1;
		if(f >= 0) {
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;
		plot(x0 + x, y0 + y);
		plot(x0 - x, y0 + y);
		plot(x0 + x, y0 - y);
		plot(x0 - x, y0 - y);
		plot(x0 + y, y0 + x);
		plot(x0 - y, y0 + x);
		plot(x0 + y, y0 - x);
		plot(x0 - y, y0 - x);
	}
}

//-------------------------------------------------------------------

void grid::flood(int x, int y, int old, int color) {

	if (x < 0 || y < 0) return;
	if (x > width -1 || y > height -1) return;

	if (data[y][x] != old) return;
	if (data[y][x] == color) return;

	data[y][x] = color;

	flood(x, y+1, old, color);
	flood(x, y-1, old, color);
	flood(x+1, y, old, color);
	flood(x-1, y, old, color);
//	flood(x-1, y-1, old, fill);
//	flood(x+1, y+1, old, fill);
//	flood(x-1, y+1, old, fill);
//	flood(x+1, y-1, old, fill);

}

//-------------------------------------------------------------------


//-------------------------------------------------------------------

