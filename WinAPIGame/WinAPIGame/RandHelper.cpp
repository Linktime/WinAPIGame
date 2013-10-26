#include "GameHead.h"
#ifndef RANDHELPER
#define RANDHELPER
#include <ctime>
#include <cstdlib>
class randhelper {
public :
	int randCreate () {
		//srand(unsigned(time(0)));
		//return 0+(2-0)*rand()/(RAND_MAX + 1.0);
		return rand()%10;
	}

	int randX() {
		//srand(unsigned(time(0)));
		return (WINDOW_WIDTH-0)*rand()/(RAND_MAX + 1.0);
	}
};
#endif