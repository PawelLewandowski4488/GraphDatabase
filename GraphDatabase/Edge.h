#pragma once
#include <string>
#include <vector>
#include <initializer_list>
#include <map>
#include "Pair.h"
#include "Node.h"

class PropertyType;

class EdgeType;

class Node;

class Edge
{
	EdgeType* edgetype;
	long int id;
	std::string label;
	Node* from;
	Node* to;
	std::vector<PairBase*> req;
	std::vector<PairBase*> nreq;
public:
	Edge(EdgeType* edgetype, long int id, std::string label, Node* from, Node* to, std::map<std::string, std::string>data);
	~Edge();
	Edge(const Edge&) = delete;
	Edge& operator=(const Edge&) = delete;
	std::string ToString();
	const std::string& GetLabel();
};

