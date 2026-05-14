#pragma once

#include <string>
#include <map>
#include <memory>

#include "NodeTYPE.h"
#include "Node.h"
#include "EdgeTYPE.h"
#include "Edge.h"

class DataBase
{
public:
	std::string name;
	std::map<std::string, std::unique_ptr<NodeType>> nodetypes;
	std::map<NodeType*, std::map<long int, std::unique_ptr<Node>>> nodes;
	std::map<std::string, std::unique_ptr<EdgeType>> edgetypes;
	std::map<EdgeType*, std::map<std::pair<long int, long int>, std::unique_ptr<Edge>>> edges;

	DataBase(std::string name) : name(name) {}
	~DataBase();

	DataBase(const DataBase&) = delete;
	DataBase& operator=(const DataBase&) = delete;

	DataBase(DataBase&&) = default;
	DataBase& operator=(DataBase&&) = default;

	void AddNodeType(std::unique_ptr<NodeType> nodetype);
	void AddNode(std::unique_ptr<Node> node, NodeType* nodetype, long int forcedid = -1);
	void AddEdgeType(std::unique_ptr<EdgeType> edgetype);
	void AddEdge(std::unique_ptr<Edge> edge, EdgeType* edgetype, long int fromid, long int toid);

	void RemoveNodeType(std::string name);
	void RemoveNode(NodeType* nodetype, long int id);
	void RemoveEdgeType(std::string name);
	void RemoveEdge(EdgeType* edgetype, long int fromid, long int toid);

	std::unique_ptr<NodeType> FindNodeType(std::string label);
	std::unique_ptr<Node> FindNode(std::string label);
	std::unique_ptr<EdgeType> FindEdgeType(std::string label);
	std::unique_ptr<Edge> FindEdge(std::string label); // todo

	void Load(); // to do
	void Save(); // to do
	std::string GetName();
	static long int Cantor(long int n, long int m);
};

