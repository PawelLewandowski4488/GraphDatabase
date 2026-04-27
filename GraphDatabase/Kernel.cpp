#include "Kernel.h"
#include "Command.h"

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

			std::vector<PropertyType> requiredFields;
			for (const auto& pair : pc.weird) {
				requiredFields.emplace_back(TypeMapper::StringToType(pair.first), pair.second);
			}

			std::vector<PropertyType> optionalFields;
			for (const auto& pair : pc.square) {
				optionalFields.emplace_back(TypeMapper::StringToType(pair.first), pair.second);
			}

			auto newNodeType = std::make_unique<NodeType>(pc.name, requiredFields, optionalFields);
			current_db->AddNodeType(std::move(newNodeType));

			std::cout << "Success: NodeType '" << pc.name << "' created.\n\n";
			auto it = current_db->nodetypes.find(pc.name);
			std::cout << it->second->ToString() << "\n";
			break;
		}
		case ENTITY::NODE: {
			if (current_db->nodes.find(pc.name) != current_db->nodes.end()) {
				std::cout << "Error: Node '" << pc.name << "' already exists.\n";
				break;
			}

			auto typeIt = current_db->nodetypes.find(pc.from);
			if (typeIt == current_db->nodetypes.end()) {
				std::cout << "Error: NodeType '" << pc.from << "' not found.\n";
				break;
			}

			try {
				long int nextId = static_cast<long int>(current_db->nodes.size() + 1);

				auto newNode = std::make_unique<Node>(typeIt->second.get(), nextId, pc.name, pc.weird, pc.square);

				current_db->AddNode(std::move(newNode));

				std::cout << "Success: Node '" << pc.name << "' [ID: " << nextId << "] created as type '" << pc.from << "'.\n";
				auto it = current_db->nodes.find(pc.name);
				std::cout << it->second->ToString() << "\n";
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

			auto FromIt = current_db->nodetypes.find(pc.from);
			if (current_db->nodetypes.find(pc.from) == current_db->nodetypes.end()) {
				std::cout << "Error: Source NodeType '" << pc.from << "' not found.\n";
				break;
			}

			auto ToIt = current_db->nodetypes.find(pc.to);
			if (current_db->nodetypes.find(pc.to) == current_db->nodetypes.end()) {
				std::cout << "Error: Target NodeType '" << pc.to << "' not found.\n";
				break;
			}

			std::vector<PropertyType> requiredFields;
			for (const auto& pair : pc.weird) {
				requiredFields.emplace_back(TypeMapper::StringToType(pair.first), pair.second);
			}

			std::vector<PropertyType> optionalFields;
			for (const auto& pair : pc.square) {
				optionalFields.emplace_back(TypeMapper::StringToType(pair.first), pair.second);
			}
			
			auto newEdgeType = std::make_unique<EdgeType>(pc.name, FromIt->second.get(), ToIt->second.get(), requiredFields, optionalFields);

			current_db->AddEdgeType(std::move(newEdgeType));

			std::cout << "Success: EdgeType '" << pc.name << "' created (" << pc.from << " -> " << pc.to << ").\n";
			break;
		}
		case ENTITY::EDGE: {
			auto typeIt = current_db->edgetypes.find(pc.name);
			if (typeIt == current_db->edgetypes.end()) {
				std::cout << "Error: EdgeType '" << pc.name << "' not found.\n";
				break;
			}

			auto FromIt = current_db->nodes.find(pc.from);
			if (FromIt == current_db->nodes.end()) {
				std::cout << "Error: Source ('" << pc.from << "') node not found.\n";
				break;
			}

			auto ToIt = current_db->nodes.find(pc.to);

			if (ToIt == current_db->nodes.end()) {
				std::cout << "Error: Target ('" << pc.to << "') node not found.\n";
				break;
			}

			try {
				long int nextId = static_cast<long int>(current_db->edges.size() + 1);

				auto newEdge = std::make_unique<Edge>(typeIt->second.get(), nextId, FromIt->second.get(), ToIt->second.get(), pc.weird, pc.square);

				current_db->AddEdge(std::move(newEdge));
				std::cout << "Success: Edge of type '" << pc.name << "' created with ID: " << nextId << ".\n";
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







