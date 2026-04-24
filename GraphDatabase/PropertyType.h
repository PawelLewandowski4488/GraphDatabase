#pragma once
#include <string>
#include "Header.h"

class PropertyType
{
public:
	Type type;
	std::string name;
	PropertyType(Type type, std::string name) : type(type), name(name) {}
	std::string ToString();
};

