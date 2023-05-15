#ifndef MAP_H
#define MAP_H

#include <string>

#include <SDL_net.h>

namespace Map
{
	inline IPaddress ip{};

	void getTile(std::string);
	void init();
}

#endif