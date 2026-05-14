#include "EdgeTYPE.h"

#include "PropertyTYPE.h"
#include "NodeTYPE.h"

void EdgeType::AddEdge(Edge* edge)
{
	edges.push_back(edge);
}

std::string EdgeType::ToString() const
{
	std::string text = "\n--EDGE TYPE--\n";
	text += ObjectType::ToString();
	text += from->name + "\n";
	text += to->name + "\n";
	return text;
}

bool EdgeType::IsRemovable() const
{
	return edges.empty();
}