#pragma once

#include <string>

class RawProperty
{
public:
	std::string name;
	std::string value;

	RawProperty(std::string name, std::string value) : name(std::move(name)), value(std::move(value)) {}
};

