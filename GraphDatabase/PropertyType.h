#pragma once
#include <string>
#include "Type.h"


class PropertyType
{
public:
	TYPE type;
	std::string name;
	PropertyType(TYPE type, std::string name) : type(type), name(name) {}
	std::string ToString();
};

