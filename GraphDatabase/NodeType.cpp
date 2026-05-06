#include "NodeTYPE.h"
#include "Property.h"

void NodeType::AddNode(Node* node)
{
	nodes.push_back(node);
}

std::string NodeType::ToString() const
{
	std::string text = "--NODE TYPE--\n";
    text += ObjectType::ToString();
	return text;
}