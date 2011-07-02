#ifndef RNG_H
#define RNG_H 
#include <math.h>
	const int IA= 16807;        // this is a
	const int IM = 2147483647;  // this is m
	const double AM = 1.0/IM;
	const int IQ = 127773;
	const int IR = 2836;
	const int NTAB = 32;
	const double NDIV = (1+(IM-1)/NTAB);
	const double EPS = 1.2e-7;
	const double RNMX = (1.0-EPS);


	void sran1(long seed);
//	long lran1();
	float ran1();
	float poisson_rand(float mean);

	int ran1_int(int low, int high);
	//returns random int from low to high -1

	int ran1_dice(int multiple, int size);
	//add multiple rolls of a dice with size max sides

#endif

