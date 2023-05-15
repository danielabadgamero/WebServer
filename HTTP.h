#ifndef HTTP_H
#define HTTP_H

#include <string>
#include <vector>
#include <map>

#include <SDL_net.h>

class Request
{
private:
	std::map<const std::string, std::string> headers{};
	std::string method{};
	std::string file{};
	std::string body{};
public:
	const std::string& getHeader(std::string) const;
	const std::string& getFile() const;
	const std::string& getMethod() const;
	const std::string& getBody() const;
	Request(TCPsocket);
};

class Response
{
private:
	int status{};
	std::vector<char> content{};
public:
	bool valid{};
	Response();
	Response(std::string, std::string);
	void send(TCPsocket) const;
};

#endif