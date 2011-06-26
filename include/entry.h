
#ifndef __ENTRY_H__
#define __ENTRY_H__

#include <string>
#include "tinyxml.h"

class entry
{


	public:
		std::string name;
		int score;

		entry & operator=(const entry &e)
		{
			name = e.name;
			score = e.score;
			return *this;
		}

		int operator==(const entry & e) const
		{
			return name == e.name && score == e.score;
		}
		int operator<(const entry & e) const
		{
			return score > e.score;
		}

		int operator>(const entry & e) const
		{
			return score > e.score;
		}
		void clear()
		{
			name = "";
			score = 0;
		}
		void print()
		{
			printf("%s: %i\n", name.c_str(), score);
		}
};




#endif /* __ENTRY_H__ */
