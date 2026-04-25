#pragma once
#include <string>
#include <vector>
#include <initializer_list>
#include "PropertyType.h"
#include "NodeType.h"

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

	EdgeType(std::string name, NodeType* from, NodeType* to, std::initializer_list<PropertyType> req, std::initializer_list<PropertyType> nreq) : name(name), from(from), to(to), req(req), nreq(nreq) {}
	void AddEdge(Edge* edge);
	std::string ToString();
};

