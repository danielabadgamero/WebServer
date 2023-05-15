#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>

#include <SDL_net.h>

#include "Map.h"

void Map::getTile(std::string address)
{
	std::string path{ address.substr(6) };
	if (!std::filesystem::exists(path))
	{
		TCPsocket server{ SDLNet_TCP_Open(&ip) };
	retry:
		std::string req{ "GET " + path + " HTTP/1.0\nHost: tile.openstreetmap.org\nUser-Agent: UnplannedEntertainment\n\n" };
		SDLNet_TCP_Send(server, req.c_str(), static_cast<int>(req.size()));

		std::vector<char> content{};
		do content.push_back(0);
		while (SDLNet_TCP_Recv(server, &content.back(), 1) == 1);

		if (content.empty()) goto retry;
		
		while (true)
			if (content.front() == -119) break;
			else content.erase(content.begin());

		std::string dirs{ address };
		while (true)
			if (dirs.back() == '/') break;
			else dirs.pop_back();

		std::filesystem::create_directories("./src" + dirs);
		std::ofstream imgOut{ "./src" + address, std::ios::binary };
		imgOut.write(content.data(), content.size());
	
		SDLNet_TCP_Close(server);
	}
}

void Map::init()
{
	SDLNet_ResolveHost(&ip, "tile.openstreetmap.org", 80);
}