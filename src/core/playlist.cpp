
#include "playlist.h"

playlist::playlist() { }

playlist::~playlist() { }

void playlist::load(std::string filename)
{
	music.clear();

	if (access(filename.c_str(), F_OK)==-1) {
		printf("No playlist found(%s).  No music will played.\n",
			filename.c_str());
		return;
	}

	TiXmlDocument doc(filename.c_str());
	doc.LoadFile();

	TiXmlHandle hDoc(&doc);
	TiXmlElement* pElem;
	TiXmlHandle hRoot(0);

	pElem=hDoc.FirstChildElement().Element();
	// should always have a valid root but handle gracefully if it doesn't
	if (!pElem) {
		printf("Error opening: %s.  No music will played.\n", filename.c_str());
		return;
	}
//	printf("name: %s\n", pElem->Value());
	hRoot=TiXmlHandle(pElem);
	TiXmlElement * songs = hRoot.FirstChild().Element();

	for (; songs!=NULL; songs=songs->NextSiblingElement()) {
		const char *pKey=songs->Value();
		const char *pText=songs->GetText();

		if (!pKey || !pText)
			continue;
//	printf("loop: %s %s\n", pKey, pText);

		std::string file = pText;
		std::string disp;
//	songs->QueryStringAttribute("display", &disp);
		if (songs->QueryStringAttribute("display", &disp)!= TIXML_SUCCESS) {
			
			disp = file;
		}
//	printf("%s: %s\n", disp.c_str(), file.c_str());
		if (access(file.c_str(), F_OK)==-1) {
			//no file found
		}
		else {
			music.push_back(std::make_pair(disp, file));
		}
	}


}

void playlist::print()
{
	for (unsigned int i=0; i<music.size(); i++) {
		printf("%s: %s\n", music[i].first.c_str(), music[i].second.c_str());
	}
}


