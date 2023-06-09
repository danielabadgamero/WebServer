#ifndef HTTP_H
#define HTTP_H

#include <map>
#include <string>
#include <vector>
#include <fstream>

#include <SDL_net.h>

class Request
{
private:
	std::vector<char> content{};
	std::map<const std::string, std::string> headers{};
	std::string method{};
	std::string file{};
	std::string body{};
public:
	const std::string& getHeader(std::string) const;
	const std::string& getFile() const;
	const std::string& getMethod() const;
	const std::string& getBody() const;
	void write(std::ofstream&) const;
	Request();
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
	Response(std::string, std::string, bool);
	void send(TCPsocket) const;
};

#endif