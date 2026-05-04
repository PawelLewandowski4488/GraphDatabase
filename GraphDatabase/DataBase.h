#pragma once

#include <string>
#include <map>
#include <memory>

#include "NodeType.h"
#include "Node.h"
#include "EdgeType.h"
#include "Edge.h"

class DataBase
{
public:
	std::string name;
	std::map<std::string, std::unique_ptr<NodeType>> nodetypes;
	std::map<std::string, std::unique_ptr<Node>> nodes;
	std::map<std::string, std::unique_ptr<EdgeType>> edgetypes;
	std::map<std::string, std::unique_ptr<Edge>> edges;

	DataBase(std::string name) : name(name) {}
	~DataBase();

	DataBase(const DataBase&) = delete;
	DataBase& operator=(const DataBase&) = delete;

	DataBase(DataBase&&) noexcept = default;
	DataBase& operator=(DataBase&&) noexcept = default;

	void AddNodeType(std::unique_ptr<NodeType> nodetype);
	void AddNode(std::unique_ptr<Node> node);
	void AddEdgeType(std::unique_ptr<EdgeType> edgetype);
	void AddEdge(std::unique_ptr<Edge> edge);

	void RemoveNodeType(std::string name);
	void RemoveNode(std::string name);
	void RemoveEdgeType(std::string name);
	void RemoveEdge(std::string name);

	std::unique_ptr<NodeType> FindNodeType(std::string label);
	std::unique_ptr<Node> FindNode(std::string label);
	std::unique_ptr<EdgeType> FindEdgeType(std::string label);
	std::unique_ptr<Edge> FindEdge(std::string label); // todo

	void Load(); // to do
	void Save(); // to do
	std::string GetName();
};

