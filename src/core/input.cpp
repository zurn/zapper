
#include "input.h"

bool input::quit = false;
bool input::anykey = false;
buttons input::keys;
SDL_Event input::event;
const char * input::keyTags[] = 
{
	"Accept / Shoot",
	"Pause Game",
	"Up",
	"Down",
	"Left",
	"Right",
};

bool using_joystick = false;

input::input()
{
}

input::~input()
{
}

bool input::pressed(int keydef)
{
	if (keydef < 0 || keydef >= TOTAL_BUTTONS) {
		return false;
	}


	if (keys[keydef]->pressed) {
		return true;
	}
	else {
		return false;
	}
}

void input::defaultKeys()
{
	//vi keys for me
	keys[KEY_ACCEPT]->set(SDLK_SPACE);
	keys[KEY_CANCEL]->set(SDLK_f);
	keys[KEY_UP]->set(SDLK_k);
	keys[KEY_DOWN]->set(SDLK_j);
	keys[KEY_LEFT]->set(SDLK_h);
	keys[KEY_RIGHT]->set(SDLK_l);
	keys[KEY_DBG_ACCEPT1]->set(SDLK_F4);
	keys[KEY_DBG_ACCEPT2]->set(SDLK_F5);
	keys[KEY_DBG_RIGHT]->set(SDLK_F6);
	keys[KEY_DBG_LEFT]->set(SDLK_F7);
	keys[KEY_DBG_UP]->set(SDLK_F8);
	keys[KEY_DBG_DOWN]->set(SDLK_DOWN);
	keys[KEY_UPLEFT]->set(SDLK_y);
	keys[KEY_UPRIGHT]->set(SDLK_u);
	keys[KEY_DOWNLEFT]->set(SDLK_b);
	keys[KEY_DOWNRIGHT]->set(SDLK_n);
	keys[KEY_ATTACK]->set(SDLK_a);
	keys[KEY_INVENTORY]->set(SDLK_s);
	keys[KEY_INTERACT]->set(SDLK_d);
	keys[KEY_OPTIONS]->set(SDLK_w);
	keys[KEY_QUIT]->set(SDLK_F12);
	keys[KEY_RUN]->set(SDLK_LSHIFT);
	keys[KEY_DBG_QUIT]->set(SDLK_F1);
	keys[KEY_DBG_SHOT]->set(SDLK_F12);
	keys[KEY_DBG_1]->set(SDLK_F2);
	keys[KEY_DBG_2]->set(SDLK_F3);

	//real defaults;
	keys[KEY_ACCEPT]->set(SDLK_SPACE);
	keys[KEY_CANCEL]->set(SDLK_ESCAPE);
	keys[KEY_UP]->set(SDLK_UP);
	keys[KEY_DOWN]->set(SDLK_DOWN);
	keys[KEY_LEFT]->set(SDLK_LEFT);
	keys[KEY_RIGHT]->set(SDLK_RIGHT);
	keys[KEY_DBG_ACCEPT1]->set(SDLK_F4);
	keys[KEY_DBG_ACCEPT2]->set(SDLK_F5);
	keys[KEY_DBG_RIGHT]->set(SDLK_F6);
	keys[KEY_DBG_LEFT]->set(SDLK_LEFT);
	keys[KEY_DBG_UP]->set(SDLK_UP);
	keys[KEY_DBG_DOWN]->set(SDLK_DOWN);
	keys[KEY_UPLEFT]->set(SDLK_HOME);
	keys[KEY_UPRIGHT]->set(SDLK_PAGEUP);
	keys[KEY_DOWNLEFT]->set(SDLK_END);
	keys[KEY_DOWNRIGHT]->set(SDLK_PAGEDOWN);
	keys[KEY_ATTACK]->set(SDLK_a);
	keys[KEY_INVENTORY]->set(SDLK_s);
	keys[KEY_INTERACT]->set(SDLK_d);
	keys[KEY_OPTIONS]->set(SDLK_w);
	keys[KEY_QUIT]->set(SDLK_F12);
	keys[KEY_RUN]->set(SDLK_LSHIFT);
	keys[KEY_DBG_QUIT]->set(SDLK_F1);
	keys[KEY_DBG_SHOT]->set(SDLK_F12);
	keys[KEY_DBG_1]->set(SDLK_F2);
	keys[KEY_DBG_2]->set(SDLK_F3);


}

void input::clear()
{
	for (int i=0; i<TOTAL_BUTTONS; i++) {
		keys[i]->clear();
	}
	anykey = false;
}

bool input::init()
{
	quit = false;
	anykey = false;
	SDL_EnableKeyRepeat(0,0);

//	printf("buttons: %i\n", TOTAL_BUTTONS);
	for (int i=0; i<TOTAL_BUTTONS; i++) {
		keys.push_back(new button);
	}
	//if no config file found then create one
	if (access(INPUT_CONFIG,F_OK)==-1) {
		defaultKeys();
	}
	else {
		if (!loadKeys()) {
			printf("error reading keys. loading defualt\n");
			defaultKeys();
		}
	}

	if (sizeof(keyTags)/sizeof(char *) != KEY_CONFIG_TOTAL) {
		printf("Somebody programmed the input file wrong. Probably crash.\n");
		return false;
	}

	if (SDL_InitSubSystem(SDL_INIT_JOYSTICK) != 0) {
		printf("Unable to initialize input device: %s\n", SDL_GetError());
	}


//	for (int i=0; i<TOTAL_BUTTONS; i++) {
//		keys[i]->repeat = 1;
//	}
	return true;
}


void input::cleanup()
{
	saveKeys();
	for (int i=0; i<TOTAL_BUTTONS; i++)
		delete keys[i];

	SDL_QuitSubSystem(SDL_INIT_JOYSTICK);
}

const char * input::name(int keydef)
{
	if (keydef < 0 || keydef >= TOTAL_BUTTONS)
		return NULL;
	return input::keyname(input::keys[keydef]->binding);
}

const char * input::keyname(int k)
{
	return SDL_GetKeyName((SDLKey) k);
}

bool input::loadKeys()
{
	TiXmlDocument doc(INPUT_CONFIG);
	doc.LoadFile();

	TiXmlHandle hDoc(&doc);
	TiXmlElement* pElem;
	TiXmlHandle hRoot(0);

	pElem=hDoc.FirstChildElement().Element();
	// should always have a valid root but handle gracefully if it does
	if (!pElem) {
		printf("Error opening: %s.  Probably going to crash.\n", INPUT_CONFIG);
		return false;
	}
//	printf("name: %s\n", pElem->Value());
	hRoot=TiXmlHandle(pElem);

	int key;
	pElem=hRoot.FirstChild( "keys" ).FirstChild("accept").Element();
	if (!pElem) return false;
	pElem->QueryIntAttribute("value",&key);
	keys[KEY_ACCEPT]->set(key);

	pElem=hRoot.FirstChild( "keys" ).FirstChild("accept_d1").Element();
	if (!pElem) return false;
	pElem->QueryIntAttribute("value",&key);
	keys[KEY_DBG_ACCEPT1]->set(key);

	pElem=hRoot.FirstChild( "keys" ).FirstChild("accept_d2").Element();
	if (!pElem) return false;
	pElem->QueryIntAttribute("value",&key);
	keys[KEY_DBG_ACCEPT2]->set(key);

	pElem=hRoot.FirstChild( "keys" ).FirstChild("cancel").Element();
	if (!pElem) return false;
	pElem->QueryIntAttribute("value",&key);
	keys[KEY_CANCEL]->set(key);

	pElem=hRoot.FirstChild( "keys" ).FirstChild("up").Element();
	if (!pElem) return false;
	pElem->QueryIntAttribute("value",&key);
	keys[KEY_UP]->set(key);

	pElem=hRoot.FirstChild( "keys" ).FirstChild("up_d").Element();
	if (!pElem) return false;
	pElem->QueryIntAttribute("value",&key);
	keys[KEY_DBG_UP]->set(key);

	pElem=hRoot.FirstChild( "keys" ).FirstChild("down").Element();
	if (!pElem) return false;
	pElem->QueryIntAttribute("value",&key);
	keys[KEY_DOWN]->set(key);

	pElem=hRoot.FirstChild( "keys" ).FirstChild("down_d").Element();
	if (!pElem) return false;
	pElem->QueryIntAttribute("value",&key);
	keys[KEY_DBG_DOWN]->set(key);

	pElem=hRoot.FirstChild( "keys" ).FirstChild("left").Element();
	if (!pElem) return false;
	pElem->QueryIntAttribute("value",&key);
	keys[KEY_LEFT]->set(key);

	pElem=hRoot.FirstChild( "keys" ).FirstChild("left_d").Element();
	if (!pElem) return false;
	pElem->QueryIntAttribute("value",&key);
	keys[KEY_DBG_LEFT]->set(key);

	pElem=hRoot.FirstChild( "keys" ).FirstChild("right").Element();
	if (!pElem) return false;
	pElem->QueryIntAttribute("value",&key);
	keys[KEY_RIGHT]->set(key);

	pElem=hRoot.FirstChild( "keys" ).FirstChild("right_d").Element();
	if (!pElem) return false;
	pElem->QueryIntAttribute("value",&key);
	keys[KEY_DBG_RIGHT]->set(key);

	pElem=hRoot.FirstChild( "keys" ).FirstChild("upleft").Element();
	if (!pElem) return false;
	pElem->QueryIntAttribute("value",&key);
	keys[KEY_UPLEFT]->set(key);

	pElem=hRoot.FirstChild( "keys" ).FirstChild("upright").Element();
	if (!pElem) return false;
	pElem->QueryIntAttribute("value",&key);
	keys[KEY_UPRIGHT]->set(key);

	pElem=hRoot.FirstChild( "keys" ).FirstChild("downright").Element();
	if (!pElem) return false;
	pElem->QueryIntAttribute("value",&key);
	keys[KEY_DOWNRIGHT]->set(key);

	pElem=hRoot.FirstChild( "keys" ).FirstChild("downleft").Element();
	if (!pElem) return false;
	pElem->QueryIntAttribute("value",&key);
	keys[KEY_DOWNLEFT]->set(key);

	pElem=hRoot.FirstChild( "keys" ).FirstChild("attack").Element();
	if (!pElem) return false;
	pElem->QueryIntAttribute("value",&key);
	keys[KEY_ATTACK]->set(key);


	pElem=hRoot.FirstChild( "keys" ).FirstChild("inventory").Element();
	if (!pElem) return false;
	pElem->QueryIntAttribute("value",&key);
	keys[KEY_INVENTORY]->set(key);

	pElem=hRoot.FirstChild( "keys" ).FirstChild("interact").Element();
	if (!pElem) return false;
	pElem->QueryIntAttribute("value",&key);
	keys[KEY_INTERACT]->set(key);


	pElem=hRoot.FirstChild( "keys" ).FirstChild("options").Element();
	if (!pElem) return false;
	pElem->QueryIntAttribute("value",&key);
	keys[KEY_OPTIONS]->set(key);

	pElem=hRoot.FirstChild( "keys" ).FirstChild("quit").Element();
	if (!pElem) return false;
	pElem->QueryIntAttribute("value",&key);
	keys[KEY_QUIT]->set(key);

	pElem=hRoot.FirstChild( "keys" ).FirstChild("run").Element();
	if (!pElem) return false;
	pElem->QueryIntAttribute("value",&key);
	keys[KEY_RUN]->set(key);

	pElem=hRoot.FirstChild( "keys" ).FirstChild("db_quit").Element();
	if (!pElem) return false;
	pElem->QueryIntAttribute("value",&key);
	keys[KEY_DBG_QUIT]->set(key);

	pElem=hRoot.FirstChild( "keys" ).FirstChild("db_shot").Element();
	if (!pElem) return false;
	pElem->QueryIntAttribute("value",&key);
	keys[KEY_DBG_SHOT]->set(key);

	pElem=hRoot.FirstChild( "keys" ).FirstChild("dbg1").Element();
	if (!pElem) return false;
	pElem->QueryIntAttribute("value",&key);
	keys[KEY_DBG_1]->set(key);

	pElem=hRoot.FirstChild( "keys" ).FirstChild("dbg2").Element();
	if (!pElem) return false;
	pElem->QueryIntAttribute("value",&key);
	keys[KEY_DBG_2]->set(key);

	return true;
}

void input::saveKeys()
{
//	printf("saving control file\n");

	TiXmlDocument doc;
	TiXmlElement* msg;
	TiXmlDeclaration * decl = new TiXmlDeclaration("1.0", "", "");
	doc.LinkEndChild(decl );

	TiXmlElement * root = new TiXmlElement("controls");
	doc.LinkEndChild(root );

	TiXmlComment * comment = new TiXmlComment();
	comment->SetValue("Keyboard mappings");
	root->LinkEndChild(comment );

	TiXmlElement * msgs = new TiXmlElement("keys");
	root->LinkEndChild(msgs );

	msg = new TiXmlElement("accept");
	msg->SetAttribute("value", input::keys[KEY_ACCEPT]->binding);
	msgs->LinkEndChild(msg);

	msg = new TiXmlElement("accept_d1");
	msg->SetAttribute("value", input::keys[KEY_DBG_ACCEPT1]->binding);
	msgs->LinkEndChild(msg);

	msg = new TiXmlElement("accept_d2");
	msg->SetAttribute("value", input::keys[KEY_DBG_ACCEPT2]->binding);
	msgs->LinkEndChild(msg);

	msg = new TiXmlElement("cancel");
	msg->SetAttribute("value", input::keys[KEY_CANCEL]->binding);
	msgs->LinkEndChild(msg);

	msg = new TiXmlElement("up");
	msg->SetAttribute("value", input::keys[KEY_UP]->binding);
	msgs->LinkEndChild(msg);

	msg = new TiXmlElement("up_d");
	msg->SetAttribute("value", input::keys[KEY_DBG_UP]->binding);
	msgs->LinkEndChild(msg);

	msg = new TiXmlElement("down");
	msg->SetAttribute("value", input::keys[KEY_DOWN]->binding);
	msgs->LinkEndChild(msg);

	msg = new TiXmlElement("down_d");
	msg->SetAttribute("value", input::keys[KEY_DBG_DOWN]->binding);
	msgs->LinkEndChild(msg);

	msg = new TiXmlElement("left");
	msg->SetAttribute("value", input::keys[KEY_LEFT]->binding);
	msgs->LinkEndChild(msg);

	msg = new TiXmlElement("left_d");
	msg->SetAttribute("value", input::keys[KEY_DBG_LEFT]->binding);
	msgs->LinkEndChild(msg);

	msg = new TiXmlElement("right");
	msg->SetAttribute("value", input::keys[KEY_RIGHT]->binding);
	msgs->LinkEndChild(msg);

	msg = new TiXmlElement("right_d");
	msg->SetAttribute("value", input::keys[KEY_DBG_RIGHT]->binding);
	msgs->LinkEndChild(msg);

	msg = new TiXmlElement("upleft");
	msg->SetAttribute("value", input::keys[KEY_UPLEFT]->binding);
	msgs->LinkEndChild(msg);

	msg = new TiXmlElement("upright");
	msg->SetAttribute("value", input::keys[KEY_UPRIGHT]->binding);
	msgs->LinkEndChild(msg);

	msg = new TiXmlElement("downleft");
	msg->SetAttribute("value", input::keys[KEY_DOWNLEFT]->binding);
	msgs->LinkEndChild(msg);

	msg = new TiXmlElement("downright");
	msg->SetAttribute("value", input::keys[KEY_DOWNRIGHT]->binding);
	msgs->LinkEndChild(msg);

	msg = new TiXmlElement("attack");
	msg->SetAttribute("value", input::keys[KEY_ATTACK]->binding);
	msgs->LinkEndChild(msg);


	msg = new TiXmlElement("inventory");
	msg->SetAttribute("value", input::keys[KEY_INVENTORY]->binding);
	msgs->LinkEndChild(msg);

	msg = new TiXmlElement("interact");
	msg->SetAttribute("value", input::keys[KEY_INTERACT]->binding);
	msgs->LinkEndChild(msg);


	msg = new TiXmlElement("options");
	msg->SetAttribute("value", input::keys[KEY_OPTIONS]->binding);
	msgs->LinkEndChild(msg);

	msg = new TiXmlElement("quit");
	msg->SetAttribute("value", input::keys[KEY_QUIT]->binding);
	msgs->LinkEndChild(msg);

	msg = new TiXmlElement("run");
	msg->SetAttribute("value", input::keys[KEY_RUN]->binding);
	msgs->LinkEndChild(msg);

	msg = new TiXmlElement("db_quit");
	msg->SetAttribute("value", input::keys[KEY_DBG_QUIT]->binding);
	msgs->LinkEndChild(msg);

	msg = new TiXmlElement("db_shot");
	msg->SetAttribute("value", input::keys[KEY_DBG_SHOT]->binding);
	msgs->LinkEndChild(msg);

	msg = new TiXmlElement("dbg1");
	msg->SetAttribute("value", input::keys[KEY_DBG_1]->binding);
	msgs->LinkEndChild(msg);

	msg = new TiXmlElement("dbg2");
	msg->SetAttribute("value", input::keys[KEY_DBG_2]->binding);
	msgs->LinkEndChild(msg);


	doc.SaveFile(INPUT_CONFIG);

}

void input::poll()
{
//	SDLKey k;
	anykey = 0;

	while (SDL_PollEvent(&event)) {

		switch (event.type) {

			case SDL_KEYDOWN:
				anykey = 1;
//				printf("The %s key was pressed!\n",
//				SDL_GetKeyName(event.key.keysym.sym));
			break;

			case SDL_QUIT:
				quit = 1;
			break;
			default:
			break;
		}
	}

}

void input::print()
{

	for (int i=0; i< KEY_CONFIG_TOTAL; i++) {
		printf("%s: %s\n", keyTags[i], keyname(keys[i]->binding));
	}



}

void input::update()
{
	for (int i=0; i<TOTAL_BUTTONS; i++)
		keys[i]->update();
}

