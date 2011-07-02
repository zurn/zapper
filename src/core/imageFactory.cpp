
#include "imageFactory.h"

//-------------------------------------------------------------------

imageFactory::imageFactory() {}

//-------------------------------------------------------------------

imageFactory::~imageFactory()
{
	clean();
}

//-------------------------------------------------------------------

image * imageFactory::load(const char * filename)
{
	image * tmp;
	imap::iterator val = surfaces.find(filename);

	if (val == surfaces.end()) { //didn't find matching image
		tmp = new image;
		if (tmp->load(filename)) {
			char * temp = new char[strlen(filename)+1];
			strcpy(temp, filename);
			surfaces[temp] = tmp;
		}
		else {
			delete tmp;
			tmp = NULL;
		}
	}
	else{ //found a matching image
		tmp = val->second;
	}
	return tmp;
}

//-------------------------------------------------------------------

void imageFactory::unload(const char * filename)
{
	imap::iterator i = surfaces.find(filename);

	if (i!=surfaces.end()) {
		delete [] i->first;
		delete i->second;
		surfaces.erase(i);
	}
}

//-------------------------------------------------------------------
void imageFactory::clean()
{
	imap::iterator i;

	for(i= surfaces.begin(); i!= surfaces.end(); ++i){
		delete [] i->first;
		delete i->second;
	}

	surfaces.clear();
}

