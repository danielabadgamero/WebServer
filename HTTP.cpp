#include <vector>
#include <string>
#include <fstream>
#include <filesystem>
#include <map>

#include <SDL_net.h>

#include "HTTP.h"
#include "Core.h"

static const std::string lowerCase(std::string& str)
{
	std::string lowerCase{ str };
	for (char& c : lowerCase)
		if (isalpha(c))
			if (c < 'a')
				c += 0x20;
	return lowerCase;
}

const std::string& Request::getHeader(std::string header) const
{
	return headers.at(lowerCase(header));
}

const std::string& Request::getFile() const
{
	return file;
}

const std::string& Request::getMethod() const
{
	return method;
}

const std::string& Request::getBody() const
{
	return body;
}

Request::Request(TCPsocket client)
{
	std::vector<char> content{};

	int bytes{};
	do if (SDLNet_CheckSockets(Core::set, 0))
		content.push_back(0), (bytes = SDLNet_TCP_Recv(client, &content.back(), 1));
	else bytes = 0;
	while (bytes);

	std::vector<std::string> lines(1);
	for (const char& c : content)
		if (c == '\n') lines.push_back("");
		else lines.back().push_back(c);

	std::vector<std::string> firstLine(1);
	for (const char& c : lines[0])
		if (c == ' ') firstLine.push_back("");
		else firstLine.back().push_back(c);
	
	method = firstLine[0];
	file = firstLine[1];
	
	int bodyStart{};
	for (int i{ 1 }; i != lines.size(); i++)
		if (lines[i].empty()) { bodyStart = i; break; }
		else
		{
			std::vector<std::string> line(1);
			for (const char& c : lines[i])
				if (c == ' ') line.push_back("");
				else if (c == ',') break;
				else line.back().push_back(c);

			line[0].pop_back();
			headers.emplace(lowerCase(line[0]), "");
			for (int j{ 1 }; j != line.size(); j++)
				headers.at(lowerCase(line[0])).append(line[j]);
		}

	for (int i{ bodyStart }; i != lines.size(); i++)
		if (!lines[i].empty())
			body.append(lines[i]), body.push_back('\n');
	if (!body.empty())
		body.pop_back();
}

Response::Response() {}
Response::Response(std::string type, std::string file)
{
	std::string name{ file };
	if (file == "/") name = "index.html";
	content.resize(1);
	if (!std::filesystem::exists("src/" + name)) status = 404;
	else
	{
		std::ifstream in{ "src/" + name, std::ios::binary };
		while (!in.eof()) in.read(&content.back(), 1), content.push_back(0);
		status = 200;
	}
	std::string firstLine{ "HTTP/2 " + std::to_string(status) + "\nContent-type: " + type + "\nConnection: close\n\n" };

	for (std::string::const_reverse_iterator c{ firstLine.crbegin() }; c != firstLine.crend(); c++)
		content.insert(content.begin(), *c);

	valid = true;
}

void Response::send(TCPsocket client) const
{
	SDLNet_TCP_Send(client, content.data(), static_cast<int>(content.size()));
}