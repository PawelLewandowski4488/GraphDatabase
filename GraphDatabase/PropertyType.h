#pragma once
#include <string>
#include "TYPE.h"
#include "RawProperty.h"


class PropertyType
{
public:
	TYPE type;
	std::string name;

	PropertyType(TYPE type, std::string name) : type(type), name(name) {}

	bool Validate(const RawProperty& rawproperty) const;

	std::string ToString();
};

