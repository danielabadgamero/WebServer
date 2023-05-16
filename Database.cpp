#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
#include <unordered_map>

#include "Database.h"

std::string Activities::get(std::string src)
{
	std::string result{ "[" };
	int ASCII{};
	int character{};
	std::vector<std::string> args(1);
	for (const char& c : src)
		if (ASCII)
		{
			character += (c - '0') * (int)pow(10, 2 - ASCII);
			ASCII++;
			if (ASCII == 3)
			{
				args.back().append(std::to_string(character));
				character = 0;
				ASCII = 0;
			}
		}
		else if (c == ',') args.push_back("");
		else if (c == '%') ASCII = 1;
		else args.back().push_back(c);
	std::unordered_map<std::string, std::string> elems{};
	for (const std::string& arg : args)
		elems.emplace(arg.substr(0, arg.find('=')), arg.substr(arg.find('=') + 1));

	for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator("./activities/"))
	{
		if (entry.path().filename().string().find(elems["s"]) != std::string::npos)
		{
			std::ifstream actIn{ entry.path().string() };
			std::string content{};
			actIn >> content;
			result.append(content);
			result.push_back(',');
		}
	}
	if (result.back() == ',')
		result.pop_back();
	result.push_back(']');
	return result;
}

std::string Users::get(std::string usr)
{
	std::string result{};
	int ASCII{};
	int character{};
	std::vector<std::string> args(1);
	for (const char& c : usr)
		if (ASCII)
		{
			character += (c - '0') * (int)pow(10, 2 - ASCII);
			ASCII++;
			if (ASCII == 3)
			{
				args.back().append(std::to_string(character));
				character = 0;
				ASCII = 0;
			}
		}
		else if (c == ',') args.push_back("");
		else if (c == '%') ASCII = 1;
		else args.back().push_back(c);
	std::unordered_map<std::string, std::string> elems{};
	for (const std::string& arg : args)
		elems.emplace(arg.substr(0, arg.find('=')), arg.substr(arg.find('=') + 1));

	if (!elems.contains("usr") || !elems.contains("pass"))
		return "";

	std::ifstream userIn{ "./users/" + elems["usr"] + ".txt" };
	userIn >> result;
	if (result.empty()) return "";

	size_t pos{ 9 };
	std::string pass{};
	while (result[pos] != '"')
		pass.push_back(result[pos]), pos++;

	if (pass == elems["pass"])
		return result;
	else
		return "";
}