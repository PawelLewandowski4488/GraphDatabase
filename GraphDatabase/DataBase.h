#pragma once
#include "header.h"
#include "NodeType.h"
#include "Node.h"
#include "EdgeType.h"
#include "Edge.h"


class DataBase
{
	std::string label;
	std::map<int, std::unique_ptr<NodeType>> nodetypes;
	std::map<int, std::unique_ptr<Node>> nodes;
	std::map<int, std::unique_ptr<EdgeType>> edgetypes;
	std::map<int, std::unique_ptr<Edge>> edges;

public:
	DataBase(std::string label) : label(label) {}
	void Load(); // to do
	void Save(); // to do
};

