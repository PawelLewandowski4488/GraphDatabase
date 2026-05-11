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

    node->SetId(finalId);
    std::cout << node->ToString();
    nodes[nodetype].emplace(finalId, std::move(node));
}

void DataBase::AddEdgeType(std::unique_ptr <EdgeType> edgetype)
{
    std::cout << edgetype->ToString();
	edgetypes.emplace(edgetype->name, std::move(edgetype));
}
void DataBase::AddEdge(std::unique_ptr <Edge> edge, EdgeType* edgetype, long int forcedid)
{
    long int finalId;

    if (forcedid != -1) {
        if (edges[edgetype].count(forcedid) > 0) {
            throw std::runtime_error("ID " + std::to_string(forcedid) + " occupied for this edgetype");
        }
        finalId = forcedid;
        if (finalId > edgetype->LastId) edgetype->LastId = finalId;
    }
    else {
        finalId = ++(edgetype->LastId);
    }

    edge->SetId(finalId);
    std::cout << edge->ToString();
    edges[edgetype].emplace(finalId, std::move(edge));
}

std::string DataBase::GetName()
{
	return this->name;
}