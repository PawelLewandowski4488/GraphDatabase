#include "Node.h"

#include <string>


Node::~Node()
{
	for (auto p : req) delete p;
	for (auto p : nreq) delete p;
}

std::string Node::ToString() const
{
	std::string text = "--NODE--\n";
    text += Object::ToString();
	return text;
}