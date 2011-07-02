
#ifndef __SCORES_H__
#define __SCORES_H__

#define MAX_SCORES 10

#include "tinyxml.h"
#include "player.h"
#include <string>
#include "entry.h"
#include <vector>


class scores
{
	public:
		scores();
		scores(const char * filename);
		~scores();

		void print();
		bool load(const char * filename);
		bool save(const char * filename);
		void add_scores(TiXmlHandle & hRoot);

		int is_new_highscore(player * p);
		int check_score(std::vector<entry> & entries, player *p);

		int add_score(player * p);
		int add_score(std::vector<entry> & entries, player * p);
		//returns 0 for no high score
		//else returns 1 thru MAX_SCORES for which place it took over

		int last_new;
		std::string score_file;
		std::vector<entry> high_scores;

	private:

};
#endif /* __SCORES_H__ */
