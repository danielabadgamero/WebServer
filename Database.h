#ifndef DATABASE_H
#define DATABASE_H

#include <string>

namespace Activities
{
	std::string get(std::string);
}

namespace Users
{
	std::string get(std::string);
	std::string add(std::string);
}

#endif