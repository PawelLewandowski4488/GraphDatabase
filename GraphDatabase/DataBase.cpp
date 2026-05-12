#include "DataBase.h"

#include "NodeTYPE.h"
#include "Node.h"
#include "EdgeTYPE.h"
#include "Edge.h"

#include <stdexcept>
#include <iostream>

DataBase::~DataBase() = default;

void DataBase::AddNodeType(std::unique_ptr<NodeType> nodetype)
{
    std::cout << nodetype->ToString();
	nodetypes.emplace(nodetype->name, std::move(nodetype));
}

void DataBase::AddNode(std::unique_ptr <Node> node, NodeType* nodetype, long int forcedid)
{
    long int finalId;

    if (forcedid != -1) {
        if (nodes[nodetype].count(forcedid) > 0) {
            throw std::runtime_error("ID " + std::to_string(forcedid) + " occupied for this nodetype");
        }
        finalId = forcedid;
        if (finalId > nodetype->LastId) nodetype->LastId = finalId;
    }
    else {
        finalId = ++(nodetype->LastId);
    }

    nodetype->nodes.push_back(node.get());
    node->SetId(finalId);
    std::cout << node->ToString();
    nodes[nodetype].emplace(finalId, std::move(node));
}

void DataBase::AddEdgeType(std::unique_ptr <EdgeType> edgetype)
{
    std::cout << edgetype->ToString();
	edgetypes.emplace(edgetype->name, std::move(edgetype));
}
void DataBase::AddEdge(std::unique_ptr <Edge> edge, EdgeType* edgetype, long int fromid, long int toid)
{
    edgetype->edges.push_back(edge.get());
    edge->SetId(DataBase::Cantor(fromid, toid));
    std::cout << edge->ToString();
    edges[edgetype].emplace(std::pair{fromid, toid}, std::move(edge));
}

void DataBase::RemoveNodeType(std::string name)
{
    nodetypes.erase(name);
}
void DataBase::RemoveNode(NodeType* nodetype, long int id)
{
    nodes[nodetype].erase(id);
}
void DataBase::RemoveEdgeType(std::string name)
{
    edgetypes.erase(name);
}
void DataBase::RemoveEdge(EdgeType* edgetype, long int fromid, long int toid)
{
    edges[edgetype].erase(std::pair{fromid, toid});
}


std::string DataBase::GetName()
{
	return this->name;
}

long int DataBase::Cantor(long int n, long int m)
{
    return (n + m)* (n + m + 1) / 2 + m;
}