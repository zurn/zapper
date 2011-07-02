
#include "console.h"

console::console()
{

	text = gfx::loadFont("./data/fonts/mono.ttf", 14);

	int MAXLEN = 80;
	char s[MAXLEN];
	s[MAXLEN-1]= '\0';
	time_t t = time(0);
	strftime(s, MAXLEN, "./logs/%m-%d-%Y-%H_%M_%S.log", localtime(&t));


	fout.open(s, std::ios::out);
//	fout.open(LOG_FILE, std::ios::out);
	if (!fout.is_open()) {
		printf("Error opening file: %s. Game might crash.\n", s);
		return;
	}

	CONSOLE_MAX_ROWS = 5;
	CHARACTER_MAX = 68;

	for (int i=0; i<CONSOLE_MAX_ROWS-1; i++)
		addMsg(" ");

	textCount = 0;
	textStr = "";
}

console::~console()
{
	dump();
	fout.close();
}

void console::clear()
{
	dump();
	for (int i=0; i<CONSOLE_MAX_ROWS-1; i++)
		addMsg(" ");
}

void console::addMsg(std::string msg)
{
	int size = msg.size();
	int c = 0;
	char * temp;

//	printf("size: %i\n", size);
//	printf("index %i\n", c%CHARACTER_MAX);

	do {
		if (c%CHARACTER_MAX == 0) {//create new sub string
			if (c != 0) {//unless first time through add the last line
//				lines.push_back(temp);
				addline(temp);
			}
			temp = new char[CHARACTER_MAX + 1];
			temp[CHARACTER_MAX] = '\0';
		}

		temp[c%CHARACTER_MAX] = msg[c];
		c++;
	} while (c < size);

	if (c%CHARACTER_MAX > 0) {
	//the last substring was shorter than CHARACTER_MAX, so put a null at
	//the end of the characters. wastes a little space here
		temp[c%CHARACTER_MAX]='\0';
	}

//	lines.push_back(temp);
	addline(temp);
}

void console::addline(char * msg)
{
	if ((int)lines.size() == CONSOLE_MAX_ROWS) {
		write(lines.front());
		lines.pop_front();
	}

	lines.push_back(msg);
	delete [] msg;
}

void console::dump()
{
	for (std::list<std::string>::iterator it = lines.begin();
			it != lines.end(); ++it) {
		write((*it));
	}
}

void console::write(std::string msg)
{
	fout << msg << "\n";
}

void console::draw()
{
	int x =  3;
	int y = 400;

	gfx::color(.3,.3,.3);
	gfx::blendMode();

	int count = 0;
	for (std::list<std::string>::iterator it = lines.begin();
			it != lines.end(); ++it) {
		if (count == CONSOLE_MAX_ROWS -1)
			gfx::color(.75,.75,.75);
		text->print((*it).c_str(), x, y);
		y+=text->height();
		count++;
	}
}

