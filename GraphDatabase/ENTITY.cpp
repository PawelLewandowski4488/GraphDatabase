#include "ENTITY.h"

ENTITY EntityMapper::StringToEntity(const std::string& str)
{
	if (str == "database") return ENTITY::DATABASE;
	if (str == "nodetype") return ENTITY::NODETYPE;
	if (str == "node") return ENTITY::NODE;
	if (str == "edgetype") return ENTITY::EDGETYPE;
	if (str == "edge") return ENTITY::EDGE;
	else return ENTITY::UNKNOWN;
}

std::string EntityMapper::EntityToString(const ENTITY& entity)
{
	switch (entity)
	{
	case ENTITY::DATABASE: return "database";
	case ENTITY::NODETYPE: return "nodetype";
	case ENTITY::NODE: return "node";
	case ENTITY::EDGETYPE: return "edgetype";
	case ENTITY::EDGE: return "edge";
	default: return "unknown";
	}
}