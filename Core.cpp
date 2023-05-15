#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <filesystem>

#include <SDL_net.h>

#include "Core.h"

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

std::vector<char> recv(TCPsocket client)
{
	std::vector<char> msg{};
	int bytes{};
	do if (SDLNet_CheckSockets(Core::set, 0))
		msg.push_back(0), (bytes = SDLNet_TCP_Recv(client, &msg.back(), 1));
	else bytes = 0;
	while (bytes);
	return msg;
}

std::vector<char> makeResponse(std::string& file)
{
	if (file == "/") file = "index.html";
	std::string status{};
	if (file.find(".html"))
		status = "HTTP/2 200 OK\nContent-Type: text/html\nConnection: close\n\n";
	else if (file.find(".png"))
		status = "HTTP/2 200 OK\nContent-Type: image/png\nConnection: close\n\n";

	return content;
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

		std::string fileName{};
		std::vector<char>::iterator nameBegin{};
		std::vector<char>::iterator nameEnd{};
		std::vector<char> response{};

		std::vector<char> req{ recv(client) };
		if (req.empty()) goto end;

		nameBegin = std::find(req.begin(), req.end(), ' ') + 1;
		nameEnd = std::find(nameBegin, req.end(), ' ');
		for (std::vector<char>::iterator c{ nameBegin }; c != nameEnd; c++) fileName.push_back(*c);

		response = makeResponse(fileName);
		SDLNet_TCP_Send(client, response.data(), static_cast<int>(response.size()));
	end:
		SDLNet_TCP_Close(client);
		SDLNet_TCP_DelSocket(set, client);
	}
}

void Core::quit()
{
	SDLNet_FreeSocketSet(set);
	SDLNet_Quit();
}