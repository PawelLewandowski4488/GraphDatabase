#pragma once

#include "PropertyTYPE.h"
#include "Property.h"
#include "RawProperty.h"

#include <string>
#include <vector>

class ObjectType
{
public:
	long int id;
	std::string name;
	std::vector<PropertyType> req;
	std::vector<PropertyType> nreq;

	long int LastId = 0;

	ObjectType(std::string name, std::vector<PropertyType> req, std::vector<PropertyType> nreq) : name(std::move(name)), req(std::move(req)), nreq(std::move(nreq)) {}
	virtual ~ObjectType() = default;

	bool Validate(std::vector<RawProperty> req, std::vector<RawProperty> nreq, std::vector<PropertyBase*>& reqOut, std::vector<PropertyBase*>& nreqOut);
	void SetId(long int id);

	virtual std::string ToString() const;
};

