#ifndef UTILITIES_H
#define UTILITIES_H

//#include "math.h"


//a stucture used as the comparison function for two c strings
struct ltstr
{
	bool operator()(const char* s1, const char* s2) const
	{
		return strcmp(s1, s2) < 0;
	}
};

//helpful macros
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(X, Y) ( ((X) < (Y)) ? (X) : (Y) )


//static const char * intToAsci(int value)
//{
//	char str[6];

//	sprintf(str,"%d", value);

//	return str;
//};





#endif /* UTILITIES_H */

