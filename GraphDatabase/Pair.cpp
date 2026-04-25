#include "Pair.h"

PairBase* PairBase::CreatePair(const PropertyType& propertytype, const std::string& rawvalue)
{
	switch (propertytype.type)
	{
	case Type::INT: return new Pair<int>(propertytype.name, std::stoi(rawvalue));
	case Type::FLOAT: return new Pair<float>(propertytype.name, std::stof(rawvalue));
	case Type::STRING: return new Pair<std::string>(propertytype.name, rawvalue);
	}
	return nullptr;
}

