#include "Edge.h"
#include <initializer_list>
#include <stdexcept>
#include "Pair.h"
#include "EdgeType.h"

Edge::Edge(EdgeType* edgetype, long int id, std::string label, Node* from, Node* to, std::map<std::string, std::string>data) : edgetype(edgetype), id(id), label(label), from(from), to(to)
{
	for (const auto& propertytype : edgetype->req)
	{
		if (data.count(propertytype.name)) req.push_back(PairBase::CreatePair(propertytype, data.at(propertytype.name)));
		else throw std::runtime_error("Missing required field: " + propertytype.name);
	}
	for (const auto& propertytype : edgetype->nreq)
	{
		if (data.count(propertytype.name)) nreq.push_back(PairBase::CreatePair(propertytype, data.at(propertytype.name)));
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
	text += std::to_string(id) + " " + label + "\n";
	text += "from: " + from->GetLabel() + "\n";
	text += "to: " + to->GetLabel() + "\n";
	for (PairBase* p : req) text += p->ToString() + "\n";
	for (PairBase* p : nreq) text += p->ToString() + "\n";
	return text;
}

const std::string& Edge::GetLabel()
{
	return label;
}
