#pragma once
#include <string>
#include <vector>
#include <initializer_list>
#include <map>
#include "Pair.h"

class PropertyType;

class NodeType;

class Node 
{
	NodeType* nodetype;
	long int id;
	std::string label;
	std::vector<PairBase*> req;
	std::vector<PairBase*> nreq;
public:
	Node(NodeType* nodetype, long int id, std::string label, std::map<std::string, std::string>data);
	~Node();
	PairBase* CreatePair(const PropertyType& propertytype, std::string rawvalue);
	Node(const Node&) = delete;
	Node& operator=(const Node&) = delete;
	std::string ToString();
};

