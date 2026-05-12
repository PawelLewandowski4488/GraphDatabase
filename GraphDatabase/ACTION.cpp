#include "ACTION.h"

ACTION ActionMapper::StringToAction(const std::string& str)
{
	if (str == "create") return ACTION::CREATE;
	if (str == "delete") return ACTION::DELETE;
	if (str == "change") return ACTION::CHANGE;
	if (str == "use") return ACTION::USE;
	if (str == "print") return ACTION::PRINT;
	else return ACTION::UNKNOWN;
}

std::string ActionMapper::ActionToString(const ACTION& action)
{
	switch (action)
	{
	case ACTION::CREATE: return "create";
	case ACTION::DELETE: return "delete";
	case ACTION::CHANGE: return "change";
	case ACTION::USE: return "use";
	case ACTION::PRINT: return "print";
	default: return "unknown";
	}
}
