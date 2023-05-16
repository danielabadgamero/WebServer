#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <filesystem>

#include <SDL_net.h>

#include "Core.h"
#include "Map.h"
#include "HTTP.h"
#include "Database.h"

void printMsg(std::vector<char>& msg)
{
	std::cout << '\n';
	for (const char& c : msg) std::cout << c;
	std::cout << '\n';
}

std::string getIPStr(IPaddress ip)
{
	unsigned int addr{ SDL_Swap32(ip.host) };
	std::string ipStr{ std::format("{}.{}.{}.{}", (addr >> 24) & 0xff, (addr >> 16) & 0xff, (addr >> 8) & 0xff, addr & 0xff) };

	return ipStr;
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

	Map::init();

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
		std::cout << "Client connected with IP: " << getIPStr(*remoteIP) << '\n';

		Request req{};
		
		req = { client };
		Response msg{};
		if (req.getMethod() == "GET")
			msg = { req.getHeader("accept"), req.getFile(), true };
		else if (req.getMethod() == "POST")
			if (req.getFile() == "/search.html")
				msg = { req.getHeader("accept"), Activities::get(req.getBody()), false };
			else if (req.getFile() == "/users")
				msg = { req.getHeader("accept"), Users::get(req.getBody()), false };
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