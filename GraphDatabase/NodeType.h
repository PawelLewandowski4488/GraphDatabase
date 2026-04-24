#pragma once
#include <string>
#include <vector>
#include <initializer_list>
#include "PropertyType.h"

class Node;

class NodeType
{
public:
	std::string name;
	std::vector<PropertyType> req;
	std::vector<PropertyType> nreq;

	std::vector<Node*> nodes;
	NodeType(std::string name, std::initializer_list<PropertyType> req, std::initializer_list<PropertyType> nreq) : name(name), req(req), nreq(nreq) {}
	void AddNode(Node* node);
	std::string ToString();
};

