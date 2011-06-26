
#include "fontFactory.h"

fontFactory::fontFactory()
{
	if(!TTF_WasInit())
		if (TTF_Init() < 0) {
			printf("Couldn't initialize TTF: %s\n",SDL_GetError());
		}
}

fontFactory::~fontFactory()
{
	for(fmap::iterator itr=fonts.begin(); itr!=fonts.end(); ++itr) {
		sizes * temp = itr->second;
		for (sizes::iterator i=temp->begin(); i!=temp->end(); ++i)
			delete i->second;
		delete itr->second;
	}

	if(TTF_WasInit())
		TTF_Quit();
}

font * fontFactory::load(const char * filename, int size)
{
	fmap::iterator itr = fonts.find(filename);

	if (itr==fonts.end()) //file not found
		return create(filename, size, NULL);
	else{ //file found
		sizes * temp = itr->second;
		sizes::iterator i;
		for (i=temp->begin(); i!=temp->end(); ++i) //look for matching size
			if (size == i->first)
				return i->second;

		return create(filename, size, temp); //no matching size
	}
}

font * fontFactory::create(const char * filename, int size, sizes * temp)
{
		font * data = new font();
		if (!data->load(filename, size)) {
			delete data;
			return NULL;
		}
		if (temp==NULL) {
			temp = new sizes;
		}
		temp->push_back(std::make_pair(size,data));
		fonts[filename] = temp;

		return data;
}

void fontFactory::unload(const char * filename, int size)
{
	fmap::iterator itr = fonts.find(filename);

	if (itr!=fonts.end()) { //found font file
		sizes * temp = itr->second;

		for (sizes::iterator i=temp->begin(); i!=temp->end(); ++i) {
			if (size == i->first) { //found size
				delete i->second;
				sizes::iterator old = i; //save size to delete
				++i; //keep valid pointer to next element
				temp->erase(old);
			}

		}
		if (temp->size() == 0) { //filename has no associated sizes
			delete temp;
			fonts.erase(itr);
		}
	}
}

void fontFactory::print()
{
	for(fmap::iterator itr=fonts.begin(); itr!=fonts.end(); ++itr) {
		printf("name: %s sizes: ", itr->first);
		sizes * temp = itr->second;
		for (sizes::iterator i=temp->begin(); i!=temp->end(); ++i)
			printf("%i ", i->first);
		printf("\n");
	}
}

