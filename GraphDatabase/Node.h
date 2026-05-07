#pragma once

#include "Object.h"

#include <string>
#include <vector>

class PropertyBase;;
class PropertyType;
class NodeType;
class Edge;

class Node : public Object
{
	//NodeType* nodetype; Testing
	std::vector<Edge*> out_edges;
	std::vector<Edge*> in_edges;
public:
	Node(long int id, std::vector<PropertyBase*> req, std::vector<PropertyBase*> nreq) : Object(id, std::move(req), std::move(nreq)) {}
	~Node();
	Node(const Node&) = delete;
	Node& operator=(const Node&) = delete;

	std::string ToString() const override;
};

