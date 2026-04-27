#include "DataBase.h"

void DataBase::AddNodeType(std::unique_ptr<NodeType> nodetype)
{
	nodetypes.emplace(nodetype->name, std::move(nodetype));
}

void DataBase::AddNode(std::unique_ptr <Node> node)
{
	nodes.emplace(node->GetLabel(), std::move(node));
}

void DataBase::AddEdgeType(std::unique_ptr <EdgeType> edgetype)
{
	edgetypes.emplace(edgetype->name, std::move(edgetype));
}
void DataBase::AddEdge(std::unique_ptr <Edge> edge)
{
	edges.emplace(edge->GetKey(), std::move(edge));
}

std::string DataBase::GetName()
{
	return this->name;
}