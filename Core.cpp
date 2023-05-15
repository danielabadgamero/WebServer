#include <fstream>
#include <filesystem>

#include <SDL_net.h>

#include "Core.h"

void Core::init()
{
	SDLNet_Init();

	running = true;
}

void Core::loop()
{
	
}

void Core::quit()
{
	SDLNet_Quit();
}