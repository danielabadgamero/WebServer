#ifndef HTTP_H
#define HTTP_H

#include <string>
#include <vector>
#include <unordered_map>

class Message
{
protected:
	std::unordered_map<std::string, std::string> headers{};
public:
	std::string& getHeader(std::string);
};

class Request : public Message
{
private:
	std::string method{};
	std::string file{};
	std::string body{};
public:
	Request(std::vector<char>);
};

class Response : public Message
{
private:
	int status{};
public:
	Response(int, std::string, std::string);
};

#endif