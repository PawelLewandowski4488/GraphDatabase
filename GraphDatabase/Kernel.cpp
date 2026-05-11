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
				std::cout << "Database created: " << pc.name << "\n";
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
				std::cout << "Using DataBase: " << pc.name << "\n";
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

					current_db->AddEdge(std::move(newEdge), typeIt->second.get());
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
	default: {
		std::cout << "Invalid Command \n";
	}
	}
}







