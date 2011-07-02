
#include "scores.h"

scores::scores()
{
	last_new = 0;
	score_file = "";
}

scores::scores(const char * filename)
{
	score_file = filename;
}

scores::~scores()
{
}

bool scores::load(const char * filename)
{
	high_scores.clear();

	TiXmlDocument doc(filename);
	doc.LoadFile();

	TiXmlHandle hDoc(&doc);
	TiXmlElement* pElem;
	TiXmlHandle hRoot(0);

	pElem=hDoc.FirstChildElement().Element();
	// should always have a valid root but handle gracefully if it does
	if (!pElem) {
		printf("Error opening: %s.  Probably going to crash.\n", filename);
		return false;
	}

//		const char *pKey=pElem->Value();
//		const char *pText=pElem->GetText();
//		printf("root: %s %s\n", pKey, pText);
	hRoot=TiXmlHandle(pElem);

	add_scores(hRoot);

//	print();
	return true;
}

void scores::add_scores(TiXmlHandle & hRoot)
{
		entry etemp;
		TiXmlElement * set = hRoot.FirstChild().Element();
//		const char *pKey=set->Value();
//		const char *pText=set->GetText();
//		printf("root child: %s %s\n", pKey, pText);

		for (; set ; set = set->NextSiblingElement()) {

			etemp.clear();
//			const char *pKey=set->Value();
//			const char *pText=set->GetText();
//
//				set->QueryIntAttribute("val", &etemp.score);
//
//			printf("inner set: %s %s %i\n", pKey, pText, etemp.score);

			std::string key=set->Value();

				if (set->GetText() != NULL) {
					etemp.name = set->GetText();
				}
				else {
					etemp.name = "";
				}
				set->QueryIntAttribute("val", &etemp.score);
			
				high_scores.push_back(etemp);
		}


	sort(high_scores.begin(), high_scores.end());
	if (high_scores.size() > MAX_SCORES)
		high_scores.resize(MAX_SCORES);
}

bool scores::save(const char * filename)
{
	TiXmlDocument doc;
	TiXmlElement* msg2;
	TiXmlDeclaration * decl = new TiXmlDeclaration("1.0", "", "");
	doc.LinkEndChild(decl);

	TiXmlElement * root = new TiXmlElement("scores");
	doc.LinkEndChild(root );


	for (unsigned int i=0; i<high_scores.size(); i++) {
		msg2 = new TiXmlElement("score");
		msg2->SetAttribute("val", high_scores[i].score);
		TiXmlText * text = new TiXmlText(high_scores[i].name.c_str());
		msg2->LinkEndChild(text);
		root->LinkEndChild(msg2);
	}

	doc.SaveFile(filename);
	return true;
}

int scores::add_score(player * p)
{
	int place = -1;


	place = add_score(high_scores, p);

	if (place != 0) {
		last_new = place;
		printf("last new %i\n", last_new);
	}
//	print();
	return place;
}

int scores::check_score(std::vector<entry> & entries, player *p)
{
	if (entries.size() < MAX_SCORES) {
		return true;
	}
	entry temp;
	temp.score = p->score;

	for (unsigned int i=0; i<entries.size(); i++) {
		if (temp > entries[i])
			return i+1;
	}

	return 0;
}

int scores::is_new_highscore(player * p)
{
	if (p->score == 0) {
		return 0;
	}

	int rv = 0;
	rv = check_score(high_scores, p);
	return rv;
}


int scores::add_score(std::vector<entry> & entries, player * p)
{
	if (p->score == 0) {
		return 0;
	}
	entry temp;
	temp.name = p->name;
	temp.score = p->score;
	entries.push_back(temp);

	sort(entries.begin(), entries.end());
	if (entries.size() > MAX_SCORES)
		entries.resize(MAX_SCORES);

	for (unsigned int i=entries.size()-1; i>=0; i--) {
		if (entries[i] == temp) {
			return i+1;
		}
	}

	return 0;
}

void scores::print()
{
	printf("printing high scores.\n");
	for (unsigned int i=0; i<high_scores.size(); i++) {
		printf("%i. ", i);
		high_scores[i].print();
	}
}

