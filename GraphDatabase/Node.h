#pragma once
#include <string>
#include <vector>

class PairBase;;
class PropertyType;
class NodeType;
class Edge;

class Node 
{
	NodeType* nodetype;
	long int id;
	std::string label;
	std::vector<PairBase*> req;
	std::vector<PairBase*> nreq;
	std::vector<Edge*> out_edges;
	std::vector<Edge*> in_edges;
public:
	Node(NodeType* nodetype, long int id, std::string label, std::vector<std::pair<std::string, std::string>> req, std::vector<std::pair<std::string, std::string>> nreq);
	~Node();
	Node(const Node&) = delete;
	Node& operator=(const Node&) = delete;
	std::string ToString();
	const std::string& GetLabel();
};

