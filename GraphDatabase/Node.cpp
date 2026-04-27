#include <string>
#include <initializer_list>
#include <stdexcept>
#include "Pair.h"
#include "Node.h"
#include "NodeType.h"


Node::Node(NodeType* nodetype, long int id, std::string label, std::vector<std::pair<std::string, std::string>> raw_req, std::vector<std::pair<std::string, std::string>> raw_nreq) : nodetype(nodetype), id(id), label(label)
{
    for (const auto& schemaProp : nodetype->req)
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
        for (const auto& schemaProp : nodetype->nreq)
        {
            if (input.first == schemaProp.name)
            {
                nreq.push_back(PairBase::CreatePair(schemaProp, input.second));
                break;
            }
        }
    }

    nodetype->AddNode(this);
}

Node::~Node()
{
	for (auto p : req) delete p;
	for (auto p : nreq) delete p;
}

std::string Node::ToString()
{
	std::string text = "--NODE--\n";
	text += std::to_string(id) + " " + label + "\n";
	for (PairBase* p : req) text += p->ToString() + "\n";
	for (PairBase* p : nreq) text += p->ToString() + "\n";
	return text;
}

const std::string& Node::GetLabel()
{
	return label;
}