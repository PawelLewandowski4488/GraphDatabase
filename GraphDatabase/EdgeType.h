#pragma once
#include <string>
#include <vector>


#include "PropertyTYPE.h"
#include "ObjectType.h"

class Edge;
class Node;
class NodeType;

class EdgeType : public ObjectType
{
public:
	NodeType* from;
	NodeType* to;

	std::vector<Edge*> edges;

	EdgeType(long int id, std::string name, NodeType* from, NodeType* to, std::vector<PropertyType> req, std::vector<PropertyType> nreq) : ObjectType(id, std::move(name), std::move(req), std::move(nreq)), from(from), to(to) {}

	void AddEdge(Edge* edge);
	std::string ToString() const override;
};

