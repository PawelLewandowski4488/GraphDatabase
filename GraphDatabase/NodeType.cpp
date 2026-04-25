#include "NodeType.h"

void NodeType::AddNode(Node* node)
{
	nodes.push_back(node);
}

std::string NodeType::ToString()
{
	std::string text = "--NODE TYPE--\n";
	text +=  name + "\n";
	for (PropertyType p : req) text += p.ToString() + "\n";
	for (PropertyType p : nreq) text += p.ToString() + "\n";
	return text;
}