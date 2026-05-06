#pragma once

#include "Property.h"

#include<string>
#include<vector>

class Object
{
public:
	long int id;
	std::vector<PropertyBase*> req;
	std::vector<PropertyBase*> nreq;

	Object(long int id, std::vector<PropertyBase*> req, std::vector<PropertyBase*> nreq) : id(id), req(std::move(req)), nreq(std::move(nreq)) {}
	virtual ~Object() = default;

	virtual std::string ToString() const;
};

