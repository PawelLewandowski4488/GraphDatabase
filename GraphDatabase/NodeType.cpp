#include "NodeTYPE.h"
#include "Property.h"

void NodeType::AddNode(Node* node)
{
	nodes.push_back(node);
}

std::string NodeType::ToString() const
{
	std::string text = "\n--NODE TYPE--\n";
    text += ObjectType::ToString() + "\n";
	return text;
}

bool NodeType::IsRemovable() const
{
	return (nodes.empty() && edgetypes.empty());
}