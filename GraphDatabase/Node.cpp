#include <string>
#include <initializer_list>
#include <stdexcept>
#include "Pair.h"
#include "Node.h"
#include "NodeType.h"


Node::Node(NodeType* nodetype, long int id, std::string label, std::map<std::string, std::string>data) : nodetype(nodetype), id(id), label(label)
{
	for (const auto& propertytype : nodetype->req)
	{
		if (data.count(propertytype.name)) req.push_back(CreatePair(propertytype, data.at(propertytype.name)));
		else throw std::runtime_error("Missing required field: " + propertytype.name);
	}
	for (const auto& propertytype : nodetype->nreq)
	{
		if (data.count(propertytype.name)) nreq.push_back(CreatePair(propertytype, data.at(propertytype.name)));
	}
	nodetype->AddNode(this);
}

Node::~Node()
{
	for (auto p : req) delete p;
	for (auto p : nreq) delete p;
}

PairBase* Node::CreatePair(const PropertyType& propertytype, std::string rawvalue)
{
	switch (propertytype.type)
	{
	case Type::INT: return new Pair<int>(propertytype.name, std::stoi(rawvalue));
	case Type::FLOAT: return new Pair<float>(propertytype.name, std::stof(rawvalue));
	case Type::STRING: return new Pair<std::string>(propertytype.name, rawvalue);
	}
	return nullptr;
}

std::string Node::ToString()
{
	std::string text;
	text += std::to_string(id) + " " + label + "\n";
	for (PairBase* p : req) text += p->ToString() + "\n";
	for (PairBase* p : nreq) text += p->ToString() + "\n";
	return text;
}