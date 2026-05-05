#pragma once

#include <string>

enum class ENTITY { DATABASE, NODE, NODETYPE, EDGE, EDGETYPE, UNKNOWN };

class EntityMapper
{
public:
	static ENTITY StringToEntity(const std::string& str);
	static std::string EntityToString(const ENTITY& action);
};

