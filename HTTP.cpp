#include <vector>
#include <string>
#include <fstream>
#include <filesystem>
#include <unordered_map>

#include "HTTP.h"

static std::string lowerCase(std::string& str)
{
	std::string lowerCase{ str };
	for (char c : lowerCase)
		if (isalpha(c))
			if (c < 'a')
				c += 0x20;
	return lowerCase;
}

std::string& Message::getHeader(std::string header)
{
	return headers[lowerCase(header)];
}

Request::Request(std::vector<char> msg)
{
	std::vector<std::string> lines(1);
	for (const char& c : msg)
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
				else line.back().push_back(c);

			headers.emplace(lowerCase(line[0]));
			for (int j{ 1 }; j != line.size(); j++)
				headers[lowerCase(line[0])].append(line[j]);
		}

	for (int i{ bodyStart }; i != lines.size(); i++)
		if (!lines[i].empty())
			body.append(lines[i]), body.push_back('\n');
	if (!body.empty())
		body.pop_back();
}

Response::Response(int code, std::string type, std::string file)
{
	std::vector<char> content(1);
	if (!std::filesystem::exists("src/" + file)) status = 404;
	else
	{
		std::ifstream in{ "src/" + file, std::ios::binary };
		while (!in.eof()) in.read(&content.back(), 1), content.push_back(0);
	}
	for (std::string::const_reverse_iterator c{ status.rbegin() }; c != status.rend(); c++)
		content.insert(content.begin(), *c);
}