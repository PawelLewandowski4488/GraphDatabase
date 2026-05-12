#pragma once

#include "Object.h"

#include <string>
#include <vector>
#include <map>


class PropertyBase;
class PropertyType;
class EdgeType;
class Node;

class Edge : public Object
{
public:
	EdgeType* edgetype;
	Node* from;
	Node* to;
	Edge(long int id, EdgeType* edgetype, Node* from, Node* to, std::vector<PropertyBase*> req, std::vector<PropertyBase*> nreq) : Object(id, std::move(req), std::move(nreq)), edgetype(std::move(edgetype)), from(std::move(from)), to(std::move(to)) {}
	~Edge();
	Edge(const Edge&) = delete;
	Edge& operator=(const Edge&) = delete;
	std::string ToString();
};

