
#include "particleMan.h"

//---------------------------------------------------------------------------

particleMan::particleMan()
{
}

//---------------------------------------------------------------------------

particleMan::~particleMan()
{
	clean();
}

//---------------------------------------------------------------------------

int particleMan::init()
{
	return 0;
}

//---------------------------------------------------------------------------

emitter * particleMan::getEmitter()
{
	emitter * temp = new emitter;
	current.push_back(temp);
	return temp;

}

//---------------------------------------------------------------------------

void particleMan::remove(emitter * e)
{
	for (emitters::iterator it = current.begin();
			it != current.end(); ++it) {

		if ((*it)->me == e->me) {
			delete (*it);
			current.erase(it);
			break;
		}
	}


}

//---------------------------------------------------------------------------

void particleMan::update()
{
	for (emitters::iterator it = current.begin();
			it != current.end(); ++it) {
		(*it)->update();
	}
}

//---------------------------------------------------------------------------

void particleMan::draw()
{
	for (emitters::iterator it = current.begin();
			it != current.end(); ++it) {
		(*it)->draw();
	}
}

//---------------------------------------------------------------------------

void particleMan::clean()
{
	for (emitters::iterator it = current.begin();
			it != current.end(); ++it) {

			delete (*it);
	}
	current.clear();
}

