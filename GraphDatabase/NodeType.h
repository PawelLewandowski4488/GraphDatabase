#pragma once
#include <string>
#include <vector>

#include "PropertyType.h"

class Node;

class NodeType
{
public:
	std::string name;
	std::vector<PropertyType> req;
	std::vector<PropertyType> nreq;

	std::vector<Node*> nodes;
	NodeType(std::string name, std::vector<PropertyType> req, std::vector<PropertyType> nreq) : name(name), req(req), nreq(nreq) {}
	void AddNode(Node* node);
	std::string ToString();
};

