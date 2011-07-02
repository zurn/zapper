
#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include "gfx.h"

#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <list>


class console
{
	public:
		console();
		~console();
	
		void addMsg(std::string msg);
		void write(std::string msg);
		void draw();
		void dump();
		void clear();
	private:
		void addline(char * msg);

		std::fstream fout;
		std::list<std::string> lines;

		int textCount;
		std::string textStr;
		font * text;
		int CONSOLE_MAX_ROWS;
		int CHARACTER_MAX;
};
#endif /* __CONSOLE_H__ */
