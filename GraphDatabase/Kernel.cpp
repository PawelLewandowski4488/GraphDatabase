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

			auto newType = std::make_unique<NodeType>(pc.name, requiredFields, optionalFields);
			current_db->AddNodeType(std::move(newType));

			std::cout << "Success: NodeType '" << pc.name << "' created.\n";
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







