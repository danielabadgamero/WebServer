#ifndef THUNDER_CORE
#define THUNDER_CORE

#include <SDL_net.h>

namespace Core
{
	inline IPaddress ip{};
	inline TCPsocket server{};
	inline SDLNet_SocketSet set{};

	inline bool running{};

	void init();
	void loop();
	void quit();
}

#endif