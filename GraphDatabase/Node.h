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
	Node(NodeType* nodetype, long int id, std::string label, std::vector<std::pair<std::string, std::string>> req, std::vector<std::pair<std::string, std::string>> nreq);
	~Node();
	Node(const Node&) = delete;
	Node& operator=(const Node&) = delete;
	std::string ToString();
	const std::string& GetLabel();
};

