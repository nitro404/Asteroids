#include "Asteroids.h"

#if _DEBUG
#include <vld.h>
#endif

int main(int argc, char * argv[]) {
	Asteroids asteroids;

	if(!asteroids.init()) { return 1; }

	asteroids.start();

	return 0;
}
