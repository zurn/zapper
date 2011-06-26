
#include "tip_jar.h"

tip_jar::tip_jar(level * l)
{
	world = l;
}

tip_jar::~tip_jar()
{
	clean();
}

void tip_jar::draw()
{
	tip_list::iterator i = tips.begin();
	for(; i != tips.end(); ++i) {
		(*i)->draw();
	}
}

void tip_jar::update()
{
	tip_list::iterator i = tips.begin();
	for(; i != tips.end(); ++i) {
		tip * t = (*i);
		t->update();
		if (t->dead) {
			delete t;
			i = tips.erase(i);
		}
	}
}

void tip_jar::add(Vector pos)
{
	if (ran1() > .8) {
		tips.push_back(new tip(pos));
	}
}

void tip_jar::clean()
{
	tip_list::iterator i = tips.begin();
	for(; i != tips.end(); ++i) {
		delete (*i);
	}
	tips.clear();
}

