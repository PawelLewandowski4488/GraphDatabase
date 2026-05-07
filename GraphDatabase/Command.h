#pragma once

#include <string>
#include <vector>

#include "ACTION.h"
#include "ENTITY.h"
#include "PropertyType.h"

struct ParsedCommand
{
	ACTION action;
	ENTITY entity;
	std::string name;

	long int id = -1;

	long int from_id = -1; 
	long int to_id = -1;

	std::string from_name;
	std::string to_name;

	std::vector<PropertyType> pt_req;
	std::vector<PropertyType> pt_nreq;

	std::vector<PropertyType> pt_req_to_remove;
	std::vector<PropertyType> pt_nreq_to_remove;

	std::vector<RawProperty> rp_req;
	std::vector<RawProperty> rp_nreq;
};

class Command
{
public:
	static ParsedCommand Parse(const std::string& input);

	//Convert
	static std::vector<PropertyType> ConvertToPropertyTypes(const std::string& content);
	static std::vector<RawProperty> ConvertToRawProperties(std::string content);
	static std::vector<PropertyType> ConvertToChangedPropertyTypes(const std::string& content, bool to_add);
	static long int ConvertToId(const std::string& content);
	static std::pair<long int, long int> ConvertToIdPair(const std::string& content);
	static std::pair<std::string, std::string> ConvertToNamePair(const std::string& content);

	//Helpers
	static bool IsValidName(const std::string& name);
	static std::string Trim(const std::string& s);
	static std::string ExtractContent(const std::string& source, char open, char close);
	static std::vector<std::string> SplitByComma(const std::string& content);
	static std::vector<std::pair<std::string, std::string>> TokenizeToProperties(const std::string& content, bool validateTypes);
};

