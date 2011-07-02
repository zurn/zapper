
#include "RNG.h"

long idum = -1;
int iy = 0;

//-------------------------------------------------------------------

void sran1(long seed)
{
	if (seed > 0) {
		 idum = -seed;
	} else {
		 idum = seed;
	}
}

//-------------------------------------------------------------------
// minimal random number generator of Park and Miller with Bays-Durham shuffel
// and added safeguards.  Returns uniform number of [0.0 to 1.0).  
// RNMX approximates largest number returned
//
// initialize idum with a negative number
//
// From Numerical Recipies in C

// iv is a table of results
//    NRC states that a return value of < 10^-6 will be followed by a value
//    of less than .0168 otherwise.
float ran1()
{
	int j;
	long k;
	static long iv[NTAB];
	float tmp;

	// fill up the iy table.
	if (idum <= 0 || iy == 0 ) { // initialize.
		if (-idum < 1) {
			idum = 1;
		}
		else {
			idum  = - idum;
		}

		for(j=NTAB+7; j>= 0; j--) {
			k = idum/IQ;
			idum = IA*(idum-k*IQ)-IR*k;
			if (idum < 0) {
				idum += IM;
			}
			if (j < NTAB) {
				iv[j] = idum;
			}
		}
		iy = iv[0];
	}

	// generate a new random number
	k = idum/IQ;
	idum = IA*(idum -k *IQ)-IR*k;
	if (idum < 0) {
		idum += IM;
	}

	// pick a random place in the table to return the number from
	j =int (iy/NDIV);

	// take the old value out of the table
	iy = iv[j];

	// stick the new number into the table
	iv[j] = idum;

	// scale the value to  [0, 1)
	tmp = AM*iy;
	if (tmp > RNMX) {
		tmp = RNMX;
	}

	// and return it.
	return tmp;
}

//-------------------------------------------------------------------

int ran1_int(int low, int high)
{

	if (low == high)
		return low;
	int temp = ran1()*101;
	return low + temp % ((high - low));
}

//-------------------------------------------------------------------

int ran1_dice(int x, int size)
{
	if (x<1 || size<1)
		return 0;

	int sum = 0;
	for (int i=0; i<x; i++)
		sum += ran1_int(1, size + 1);

	return sum;
}

//-------------------------------------------------------------------
float poisson_rand(float mean)
{
	float l,k,p;
	static float u;

	l = exp(-mean);
	k = 0;
	p = 1;

	do {
		k++;
		u = ran1();
		p *= u;
	} while (p >= l);

	return k-1;
}

