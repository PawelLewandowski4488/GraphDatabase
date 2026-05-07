#include "DataBase.h"

#include "NodeTYPE.h"
#include "Node.h"
#include "EdgeTYPE.h"
#include "Edge.h"

DataBase::~DataBase() = default;

void DataBase::AddNodeType(std::unique_ptr<NodeType> nodetype, long int forcedid= -1)
{
	nodetypes.emplace(nodetype->name, std::move(nodetype));
}

void DataBase::AddNode(std::unique_ptr <Node> node, NodeType* nodetype, long int forcedid = -1)
{
    long int finalId;

    if (forcedid != -1) {
        if (nodes[nodetype].count(forcedid) > 0) {
            throw std::runtime_error("ID " + std::to_string(forcedid) + " zajête dla tego typu!");
        }
        finalId = forcedid;
        if (finalId > nodetype->LastId) nodetype->LastId = finalId;
    }
    else {
        finalId = ++(nodetype->LastId);
    }

    node->SetId(finalId);
    nodes[nodetype].emplace(finalId, std::move(node));
}

void DataBase::AddEdgeType(std::unique_ptr <EdgeType> edgetype)
{
	edgetypes.emplace(edgetype->name, std::move(edgetype));
}
void DataBase::AddEdge(std::unique_ptr <Edge> edge, EdgeType* edgetype, long int forcedid = -1)
{
	if (forcedid != -1) edge->SetId(forcedid);
	else edge->SetId(static_cast<long int>(nodes.size() + 1));
	edges[edgetype].emplace(edge->GetId(), std::move(edge));
}

std::string DataBase::GetName()
{
	return this->name;
}