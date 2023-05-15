#include "Core.h"

int main(int, char**)
{
	Core::init();

	while (Core::running)
		Core::loop();

	Core::quit();

	return 0;
}