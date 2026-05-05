#pragma once

#include <string>
#include <vector>

#include "ACTION.h"
#include "ENTITY.h"

struct ParsedCommand
{
	ACTION action;
	ENTITY entity;
	std::string name;
	std::string from; 
	std::string to;   
	std::vector<std::pair<std::string, std::string>> weird;
	std::vector<std::pair<std::string, std::string>> square;
};

class Command
{
public:
	static ParsedCommand Parse(const std::string& input);

	//Helpers
	static std::string Trim(const std::string& s);
	static std::vector<std::string> SplitByComma(const std::string& content);
	static std::vector<std::pair<std::string, std::string>> TokenizeToPairs(const std::string& content, bool validateTypes);
};

