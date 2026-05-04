#include "EdgeType.h"

#include "PropertyType.h"
#include "NodeType.h"

void EdgeType::AddEdge(Edge* edge)
{
	edges.push_back(edge);
}

std::string EdgeType::ToString()
{
	std::string text = "--EDGE TYPE--\n";
	text += name + "\n";
	text += from->name + "\n";
	text += to->name + "\n";
	for (PropertyType p : req) text += p.ToString() + "\n";
	for (PropertyType p : nreq) text += p.ToString() + "\n";
	return text;
}