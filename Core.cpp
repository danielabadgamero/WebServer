#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <filesystem>

#include <SDL_net.h>

#include "Core.h"
#include "HTTP.h"

void printMsg(std::vector<char>& msg)
{
	std::cout << '\n';
	for (const char& c : msg) std::cout << c;
	std::cout << '\n';
}

const char printIP(IPaddress ip)
{
	unsigned int addr{ SDL_Swap32(ip.host) };
	printf("%d.%d.%d.%d", (addr >> 24) & 0xff, (addr >> 16) & 0xff, (addr >> 8) & 0xff, addr & 0xff);

	return '\n';
}

void Core::init()
{
	SDLNet_Init();
	set = SDLNet_AllocSocketSet(1);

	std::cout << "Starting server\n";
	SDLNet_ResolveHost(&ip, NULL, 80);
	std::cout << "Host resolved\n";
	server = SDLNet_TCP_Open(&ip);
	std::cout << "Socket opened\n";
	std::cout << SDLNet_GetError();

	running = true;
}

void Core::loop()
{
	TCPsocket client{};
	client = SDLNet_TCP_Accept(server);
	if (client)
	{
		SDLNet_TCP_AddSocket(set, client);
		IPaddress* remoteIP{ SDLNet_TCP_GetPeerAddress(client) };
		std::cout << "Client connected with IP: " << printIP(*remoteIP);

		Request req{ client };
		Response msg{};
		if (req.getMethod() == "GET")
			msg = { req.getHeader("accept"), req.getFile() };
		if (msg.valid)
			msg.send(client);

		SDLNet_TCP_Close(client);
		SDLNet_TCP_DelSocket(set, client);
	}
}

void Core::quit()
{
	SDLNet_FreeSocketSet(set);
	SDLNet_Quit();
}