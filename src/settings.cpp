#include "settings.h"

settings::settings(const char * filename)
{
	sfxVol = 0.0;
	musVol = 0.0;

	if (!load(filename)) {
		loadDefault();
		printf("settings file read error\n");
	}
}

settings::settings()
{
}

settings::~settings()
{
}

bool settings::load(const char * filename)
{
	if (access(filename, F_OK)==-1) {
		printf("No settings file found at found at %s.\n \
				Using default settings.\n", filename);
		return false;
	}

	TiXmlDocument doc(filename);
	doc.LoadFile();

	TiXmlHandle hDoc(&doc);
	TiXmlElement* pElem;
	TiXmlHandle hRoot(0);

	pElem = hDoc.FirstChildElement().Element();
	if (!pElem) { //invalid root node
		printf("Error reading1: %s.\n \
				Using default settings.\n", filename);
		return false;
	}
	hRoot = TiXmlHandle(pElem);
	
	//read volume values
	pElem = hRoot.FirstChild( "volume" ).Element();
	if (!pElem) {
		printf("Error reading: %s.\n \
				Using default settings.\n", filename);
		return false;
	}
	pElem->QueryFloatAttribute("sfx", &sfxVol);
	pElem->QueryFloatAttribute("mus", &musVol);

//	print();
	return true;
}

bool settings::save(const char * filename)
{
	TiXmlDocument doc;
	TiXmlElement* msg;
	TiXmlDeclaration * decl = new TiXmlDeclaration("1.0", "", "");
	doc.LinkEndChild(decl);

	TiXmlElement * root = new TiXmlElement("settings");
	doc.LinkEndChild(root );

	TiXmlComment * comment = new TiXmlComment();
	comment->SetValue("Settings configuration");
	root->LinkEndChild(comment);

	msg = new TiXmlElement("volume");
	msg->SetDoubleAttribute("sfx", sfxVol);
	msg->SetDoubleAttribute("mus", musVol);
	root->LinkEndChild(msg);

	doc.SaveFile(filename);
	return true;
}

void settings::loadDefault()
{
	sfxVol = 0.5;
	musVol = 0.5;
}

void settings::print()
{
	printf("sfx %f\n", sfxVol);
	printf("mus %f\n", musVol);

}

