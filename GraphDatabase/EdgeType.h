#pragma once
#include <string>
#include <vector>


#include "PropertyType.h"

class Edge;
class Node;
class NodeType;

class EdgeType
{
public:
	std::string name;
	NodeType* from;
	NodeType* to;
	std::vector<PropertyType> req;
	std::vector<PropertyType> nreq;

	std::vector<Edge*> edges;

	EdgeType(std::string name, NodeType* from, NodeType* to, std::vector<PropertyType> req, std::vector<PropertyType> nreq) : name(name), from(from), to(to), req(req), nreq(nreq) {}
	void AddEdge(Edge* edge);
	std::string ToString();
};

