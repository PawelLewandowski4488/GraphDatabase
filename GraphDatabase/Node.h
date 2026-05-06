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
	NodeType* nodetype;
	std::vector<Edge*> out_edges;
	std::vector<Edge*> in_edges;
public:
	Node(long int id, NodeType* nodetype, std::vector<PropertyBase*> req, std::vector<PropertyBase*> nreq) : Object(id, std::move(req), std::move(nreq)), nodetype(std::move(nodetype)) {}
	~Node();
	Node(const Node&) = delete;
	Node& operator=(const Node&) = delete;

	std::string ToString() const override;
};

