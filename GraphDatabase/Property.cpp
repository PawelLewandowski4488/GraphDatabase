#include "Property.h"

#include "PropertyTYPE.h"

PropertyBase* PropertyBase::CreateProperty(const PropertyType& propertytype, const std::string& rawvalue)
{
	switch (propertytype.type)
	{
	case TYPE::INT: return new Property<int>(propertytype.name, std::stoi(rawvalue));
	case TYPE::FLOAT: return new Property<float>(propertytype.name, std::stof(rawvalue));
	case TYPE::STRING: return new Property<std::string>(propertytype.name, rawvalue);
	}
	return nullptr;
}



