#pragma once

#include <string>

enum class ACTION { CREATE, DELETE, CHANGE, USE, PRINT, UNKNOWN };

class ActionMapper
{
public:
	static ACTION StringToAction(const std::string& str);
	static std::string ActionToString(const ACTION& action);
};

