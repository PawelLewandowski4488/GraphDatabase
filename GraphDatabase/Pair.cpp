#include "Pair.h"

#include "PropertyType.h"

PairBase* PairBase::CreatePair(const PropertyType& propertytype, const std::string& rawvalue)
{
	switch (propertytype.type)
	{
	case TYPE::INT: return new Pair<int>(propertytype.name, std::stoi(rawvalue));
	case TYPE::FLOAT: return new Pair<float>(propertytype.name, std::stof(rawvalue));
	case TYPE::STRING: return new Pair<std::string>(propertytype.name, rawvalue);
	}
	return nullptr;
}

