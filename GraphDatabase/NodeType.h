#pragma once
#include <string>
#include <vector>

#include "PropertyTYPE.h"
#include "Property.h"
#include "RawProperty.h"
#include "ObjectType.h"

class Node;

class NodeType : public ObjectType
{
public:
	std::vector<Node*> nodes;

	NodeType(std::string name, std::vector<PropertyType> req, std::vector<PropertyType> nreq) : ObjectType(std::move(name), std::move(req), std::move(nreq)) {}

	void AddNode(Node* node);
	std::string ToString() const override;
};

