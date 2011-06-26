
#ifndef __TIP_JAR_H__
#define __TIP_JAR_H__

//This class manages the tips in the game.
//it controls memory
//updates and draws them
//generates them

#include <list>

#include "level.h"
#include "tip.h"

typedef std::list<tip *> tip_list;

class tip_jar
{
	public:
		tip_jar(level * l);
		virtual ~tip_jar();

		void update();
		void draw();

		void add(Vector pos);
		void clean();

		level * world;
		tip_list tips;
	private:

};
#endif /* __TIP_JAR_H__ */
