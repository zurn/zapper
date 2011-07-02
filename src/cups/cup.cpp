
#include "cup.h"

cup::cup(int x, int y)
{
	go_right = false;
	prized = false;
	index = 0;

	empty = gfx::loadImage("./data/gfx/cups/chest_empty.png");
	full = gfx::loadImage("./data/gfx/cups/chest_full.png");
	closed = gfx::loadImage("./data/gfx/cups/chest_closed.png");
	pic = empty;

	pos.x = x;
	pos.y = y;
	original_pos = pos;

	reset();
}

cup::~cup()
{
}

void cup::draw()
{
	gfx::replaceMode();
	pic->draw(pos.x, pos.y);
}

void cup::update()
{
	if (delay.is_left() < .5* delay.delay) {
		gravity.y = -gravity.y;
		pos += vel + gravity;
		gravity.y = -gravity.y;
	}
	else {
		pos += vel + gravity;
	}

	if (pos.x > gfx::w) {
		vel.x = -vel.x;
	}
	if (pos.y > gfx::h) {
		vel.y = -vel.y;
	}
	if (pos.x < 0) {
		vel.x = -vel.x;
	}
	if (pos.y < 0) {
		vel.y = -vel.y;
	}

	if (delay.is_past()) {
//		gravity.y = -gravity.y;
		vel = gravity = ZERO;
		adjust_pos();
	}

}

void cup::start_swap()
{
	float speed = 3.27;


	if (go_right) {
		gravity.y = speed;
		gravity.x = 0;

		vel.x = speed;
		vel.y = 0;
	}
	else {
		gravity.y = -speed;
		gravity.x = 0;

		vel.x = -speed;
		vel.y = 0;
	}

	delay.reset();
}
void cup::reset()
{
	adjust_pos();
	pic = empty;
	delay.set(250);
	prized = false;
	vel = gravity = ZERO;
}

void cup::adjust_pos()
{
	pos.y = 245;
	pos.x = 150 + index*60;
}

