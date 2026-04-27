#include "Edge.h"
#include <initializer_list>
#include <stdexcept>
#include "Pair.h"
#include "EdgeType.h"

Edge::Edge(EdgeType* edgetype, long int id, Node* from, Node* to, std::vector<std::pair<std::string, std::string>> raw_req, std::vector<std::pair<std::string, std::string>> raw_nreq) : edgetype(edgetype), id(id), from(from), to(to)
{
    for (const auto& schemaProp : edgetype->req)
    {
        bool found = false;
        for (const auto& input : raw_req)
        {
            if (input.first == schemaProp.name)
            {
                req.push_back(PairBase::CreatePair(schemaProp, input.second));
                found = true;
                break;
            }
        }

        if (!found) {
            throw std::runtime_error("Error: Required field '" + schemaProp.name + "' not found in {} block.");
        }
    }

    for (const auto& input : raw_nreq)
    {
        for (const auto& schemaProp : edgetype->nreq)
        {
            if (input.first == schemaProp.name)
            {
                nreq.push_back(PairBase::CreatePair(schemaProp, input.second));
                break;
            }
        }
    }

	edgetype->AddEdge(this);
}

Edge::~Edge()
{
	for (auto p : req) delete p;
	for (auto p : nreq) delete p;
}

std::string Edge::ToString()
{
	std::string text = "--EDGE--\n";
	text += std::to_string(id) + "\n";
    text += GetKey() + "\n";
	text += "from: " + from->GetLabel() + "\n";
	text += "to: " + to->GetLabel() + "\n";
	for (PairBase* p : req) text += p->ToString() + "\n";
	for (PairBase* p : nreq) text += p->ToString() + "\n";
	return text;
}

std::string Edge::GetKey()
{
    return edgetype->name + "_" + from->GetLabel() + "_" + to->GetLabel();
}

