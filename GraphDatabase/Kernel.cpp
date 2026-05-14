#include "Kernel.h"

#include "Command.h"
#include "PropertyTYPE.h"
#include "NodeTYPE.h"
#include "Node.h"
#include "EdgeTYPE.h"
#include "Edge.h"
#include "DataBase.h"

#include <iostream>

std::string Kernel::GetCurrentDB()
{
	if (current_db) return current_db->GetName();
	else return "_";
}


void Kernel::Exec(std::string input)
{
	
	ParsedCommand pc = Command::Parse(input);

	if (pc.entity == ENTITY::DATABASE) {
		if (pc.action == ACTION::CREATE) {
			if (dbs.find(pc.name) == dbs.end()) {
				dbs.emplace(pc.name, DataBase(pc.name));
				auto it = dbs.find(pc.name);
				Kernel::current_db = &(it->second);
				return;
			}
			else {
				std::cout << "Database already exists: " << pc.name << "\n";
			}
			return;
		}
		if (pc.action == ACTION::USE) {
			auto it = dbs.find(pc.name);

			if (it != dbs.end()) {
				Kernel::current_db = &(it->second);
				return;
			}
			else {
				std::cout << "Invalid DataBase: " << pc.name << "\n";
			}
		}
	}

	if (current_db == nullptr && pc.action != ACTION::UNKNOWN) {
		std::cout << "Error: No database in use. Use: use database \"name\" () {} []\n";
		return;
	}

	switch (pc.action)
	{
	case ACTION::CREATE: {
		switch (pc.entity)
		{
		case ENTITY::NODETYPE: {
			if (current_db->nodetypes.find(pc.name) != current_db->nodetypes.end()) {
				std::cout << "Error: NodeType '" << pc.name << "' already exists.\n";
				break;
			}

			auto newNodeType = std::make_unique<NodeType>(pc.name, pc.pt_req, pc.pt_nreq);
			current_db->AddNodeType(std::move(newNodeType));
			break;
		}
		case ENTITY::NODE: {
			auto typeIt = current_db->nodetypes.find(pc.name);
			if (typeIt == current_db->nodetypes.end()) {
				std::cout << "Error: NodeType '" << pc.name << "' not found.\n";
				break;
			}

			try {
				long int nextId = static_cast<long int>(current_db->nodes.size() + 1);

				std::vector<PropertyBase*> req;
				std::vector<PropertyBase*> nreq;

				if (typeIt->second.get()->Validate(pc.rp_req, pc.rp_nreq, req, nreq)) {
					auto newNode = std::make_unique<Node>(nextId, req, nreq);

					current_db->AddNode(std::move(newNode), typeIt->second.get());
				}
			}
			catch (const std::exception& e) {
				std::cout << "Node Creation Error: " << e.what() << "\n";
			}
			break;
		}
		case ENTITY::EDGETYPE: {
			if (current_db->edgetypes.find(pc.name) != current_db->edgetypes.end()) {
				std::cout << "Error: EdgeType '" << pc.name << "' already exists.\n";
				break;
			}

			auto FromIt = current_db->nodetypes.find(pc.from_name);
			if (current_db->nodetypes.find(pc.from_name) == current_db->nodetypes.end()) {
				std::cout << "Error: Source NodeType '" << pc.from_name << "' not found.\n";
				break;
			}

			auto ToIt = current_db->nodetypes.find(pc.to_name);
			if (current_db->nodetypes.find(pc.to_name) == current_db->nodetypes.end()) {
				std::cout << "Error: Target NodeType '" << pc.to_name << "' not found.\n";
				break;
			}

			auto newEdgeType = std::make_unique<EdgeType>(pc.name, FromIt->second.get(), ToIt->second.get(), pc.pt_req, pc.pt_nreq);
			current_db->AddEdgeType(std::move(newEdgeType));

			break;
		}
		case ENTITY::EDGE: {
			auto typeIt = current_db->edgetypes.find(pc.name);
			if (typeIt == current_db->edgetypes.end()) {
				std::cout << "Error: EdgeType '" << pc.name << "' not found.\n";
				break;
			}


			NodeType* fromType = typeIt->second->from;
			NodeType* toType = typeIt->second->to;

			auto itOuterFrom = current_db->nodes.find(fromType);
			auto itOuterTo = current_db->nodes.find(toType);

			if (itOuterFrom == current_db->nodes.end() || itOuterTo == current_db->nodes.end()) {
				std::cout << "Error: Node types for this edge do not exist in database.\n";
				break;
			}

			auto fromIt = itOuterFrom->second.find(pc.from_id);
			auto toIt = itOuterTo->second.find(pc.to_id);

			if (fromIt == itOuterFrom->second.end() || toIt == itOuterTo->second.end()) {
				std::cout << "Error: Source (" << pc.from_id << ") or Target (" << pc.to_id << ") node not found.\n";
				break;
			}

			try {
				long int nextId = static_cast<long int>(current_db->edges.size() + 1);
				std::vector<PropertyBase*> req;
				std::vector<PropertyBase*> nreq;

				if (typeIt->second.get()->Validate(pc.rp_req, pc.rp_nreq, req, nreq)) {
					auto newEdge = std::make_unique<Edge>(nextId, typeIt->second.get(), fromIt->second.get(), toIt->second.get(), req, nreq);
					fromIt->second.get()->out_edges.push_back(newEdge.get());
					toIt->second.get()->in_edges.push_back(newEdge.get());
					current_db->AddEdge(std::move(newEdge), typeIt->second.get(), pc.from_id, pc.to_id);
				}
			}
			catch (const std::exception& e) {
				std::cout << "Edge Creation Error: " << e.what() << "\n";
			}
			break;

			break;
		}
		}
		break;
	}
	case ACTION::DELETE: {
		switch (pc.entity)
		{
		case ENTITY::NODETYPE: {
			if (current_db->nodetypes.find(pc.name) == current_db->nodetypes.end()) {
				std::cout << "Error: NodeType '" << pc.name << "' doesnt exist.\n";
				return;
			}

			if (!current_db->nodetypes.at(pc.name)->IsRemovable())
			{
				std::cout << "Error: NodeType '" << pc.name << "' is not removable.\n";
				return;
			}

			current_db->RemoveNodeType(pc.name);
			std::cout << "NodeType '" << pc.name << "' has been deleted.\n";
			break;
		}
		case ENTITY::NODE: {
			auto typeIt = current_db->nodetypes.find(pc.name);
			if (typeIt == current_db->nodetypes.end()) {
				std::cout << "Error: Node '" << pc.name << "' ID: " << std::to_string(pc.id) << " not found.\n";
				return;
			}
			NodeType* nodetype = typeIt->second.get();
			Node* node = current_db->nodes.at(nodetype).at(pc.id).get();
			if (!node->out_edges.empty() || !node->in_edges.empty())
			{
				std::cout << "Error: Node '" << pc.name << "' ID: " << std::to_string(pc.id) << " is not removable.\n";
				return;
			}

			std::erase(nodetype->nodes, node);
			current_db->RemoveNode(nodetype, pc.id);
			std::cout << "Node '" << pc.name << "'ID: "  << std::to_string(pc.id)<< " has been deleted.\n";
			break;
		}
		case ENTITY::EDGETYPE: {
			if (current_db->edgetypes.find(pc.name) == current_db->edgetypes.end()) {
				std::cout << "Error: EdgeType '" << pc.name << "' doesnt exist.\n";
				return;
			}

			if (!current_db->edgetypes.at(pc.name)->edges.empty())
			{
				std::cout << "Error: EdgeType '" << pc.name << "' is not removable.\n";
				return;
			}

			current_db->RemoveEdgeType(pc.name);
			std::cout << "EdgeType '" << pc.name << "' has been deleted.\n";
			break;
			break;
		}
		case ENTITY::EDGE: {
			auto typeIt = current_db->edgetypes.find(pc.name);
			if (typeIt == current_db->edgetypes.end()) {
				std::cout << "Error: EdgeType '" << pc.name << "' not found.\n"; // walidacja
				return;
			}

			EdgeType* edgetype = typeIt->second.get();
			
			auto It = current_db->edges[edgetype].find(std::pair{ pc.from_id, pc.to_id });
			if (It == current_db->edges[edgetype].end()) {
				std::cout << "Error: Edge '" << pc.name << "' (" << pc.from_id << ", " << pc.to_id << ") not found.\n";
				return;
			}
			Edge* edge = current_db->edges.at(edgetype).at(std::pair{ pc.from_id, pc.to_id }).get();
			std::erase(edge->from->out_edges, edge);
			std::erase(edge->to->in_edges, edge);
			current_db->RemoveEdge(edgetype, pc.from_id, pc.to_id);
			std::cout << "Edge '" << pc.name << "' (" << pc.from_id << ", " << pc.to_id << ") has been deleted.\n";
			break;
		}
		}
		break;
	}
	case ACTION::CHANGE: {
		switch (pc.entity)
		{
		case ENTITY::NODETYPE: {
			break;
		}
		case ENTITY::NODE: {
			break;
		}
		case ENTITY::EDGETYPE: {
			break;
		}
		case ENTITY::EDGE: {
			break;
		}
		}
		break;
	}
	case ACTION::PRINT: {
		switch (pc.entity)
		{
		case ENTITY::NODETYPE: {
			if (current_db->nodetypes.find(pc.name) == current_db->nodetypes.end()) {
				std::cout << "Error: NodeType '" << pc.name << "' doesnt exist.\n";
				return;
			}

			std::cout << current_db->nodetypes.at(pc.name)->ToString();
			break;
		}
		case ENTITY::NODE: {
			auto typeIt = current_db->nodetypes.find(pc.name);
			if (typeIt == current_db->nodetypes.end()) {
				std::cout << "Error: NodeType '" << pc.name << "' doesnt exist.\n";
				return;
			}
			NodeType* nodetype = typeIt->second.get();

			auto It = current_db->nodes[nodetype].find(pc.id);
			if (It == current_db->nodes[nodetype].end()) {
				std::cout << "Error: Node '" << pc.name << "' ID: " << std::to_string(pc.id) << " not found.\n";
				return;
			}

			std::cout << current_db->nodes.at(nodetype).at(pc.id)->ToString();
			break;
		}
		case ENTITY::EDGETYPE: {
			if (current_db->edgetypes.find(pc.name) == current_db->edgetypes.end()) {
				std::cout << "Error: EdgeType '" << pc.name << "' doesnt exist.\n";
				return;
			}

			std::cout << current_db->edgetypes.at(pc.name)->ToString();
			break;
		}
		case ENTITY::EDGE: {
			auto typeIt = current_db->edgetypes.find(pc.name);
			if (typeIt == current_db->edgetypes.end()) {
				std::cout << "Error: EdgeType '" << pc.name << "' not found.\n"; 
				return;
			}

			EdgeType* edgetype = typeIt->second.get();

			auto It = current_db->edges[edgetype].find(std::pair{ pc.from_id, pc.to_id });
			if (It == current_db->edges[edgetype].end()) {
				std::cout << "Error: Edge '" << pc.name << "' (" << pc.from_id << ", " << pc.to_id << ") not found.\n";
				return;
			}

			std::cout << current_db->edges.at(edgetype).at(std::pair{ pc.from_id, pc.to_id })->ToString();
			break;
		}
		}
		break;
	}
	default: {
		std::cout << "Invalid Command \n";
	}
	}
}







