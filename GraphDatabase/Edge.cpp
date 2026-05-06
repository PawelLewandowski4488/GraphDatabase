#include "Edge.h"

#include <stdexcept>

#include "Node.h"
#include "Property.h"
#include "EdgeTYPE.h"
#include "PropertyTYPE.h"
#include "NodeType.h"


Edge::~Edge()
{
	for (auto p : req) delete p;
	for (auto p : nreq) delete p;
}

std::string Edge::ToString()
{
	std::string text = "--EDGE--\n";
	text += Object::ToString();
	text += "from: " + edgetype->from->name + " " + std::to_string(from->id) + "\n";
	text += "to: " + edgetype->to->name + " " + std::to_string(to->id) + "\n";
	return text;
}



