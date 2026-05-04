#include "Command.h"

#include "Type.h"

#include <regex>
#include <iostream>
#include <sstream>

ACTION Command::StringToACTION(const std::string& str) 
{
	if (str == "create") return ACTION::CREATE;
	if (str == "delete") return ACTION::DELETE;
	if (str == "change") return ACTION::CHANGE;
	if (str == "use")    return ACTION::USE;
	if (str == "unknown") return ACTION::UNKNOWN;
	return ACTION::UNKNOWN;
}

ENTITY Command::StringToENTITY(const std::string& str)
{
	if (str == "database") return ENTITY::DATABASE;
	if (str == "nodetype") return ENTITY::NODETYPE;
	if (str == "node") return ENTITY::NODE;
	if (str == "edgetype") return ENTITY::EDGETYPE;
	if (str == "edge")    return ENTITY::EDGE;
	return ENTITY::UNKNOWN;
}

std::string Command::Trim(const std::string& s) {
    size_t first = s.find_first_not_of(" \t\n\r");
    if (first == std::string::npos) return "";
    size_t last = s.find_last_not_of(" \t\n\r");
    return s.substr(first, (last - first + 1));
}

std::vector<std::pair<std::string, std::string>> Command::TokenizeToPairs(const std::string& content, bool validateTypes) {
    std::vector<std::pair<std::string, std::string>> result;
    if (Command::Trim(content).empty()) return result;

    std::string cleanContent = content;

    for (char& c : cleanContent) {
        if (c == ',') c = ' ';
    }

    std::vector<std::string> tokens;
    std::stringstream ss(cleanContent);
    std::string word;
    while (ss >> word) {
        tokens.push_back(word);
    }
    if (tokens.size() % 2 != 0) {
        throw std::runtime_error("Odd number of elements in brackets");
    }

    for (size_t i = 0; i < tokens.size(); i += 2) {
        std::string key = tokens[i];
        std::string value = tokens[i + 1];

        if (validateTypes) {
            if (TypeMapper::StringToType(key) == TYPE::UNKNOWN) {
                throw std::runtime_error("Invalid data type definition: " + key);
            }
        }
        result.push_back({ key, value });
    }

    return result;
}

std::vector<std::string> Command::SplitByComma(const std::string& content) {
    std::vector<std::string> result;
    std::stringstream ss(content);
    std::string item;

    while (std::getline(ss, item, ',')) {
        std::string trimmed = Command::Trim(item);
        if (!trimmed.empty()) {
            result.push_back(trimmed);
        }
    }
    return result;
}

void PrintParsedCommand(const ParsedCommand& pc) {
    std::cout << "--- Parsed Command Details ---" << std::endl;

    // Nazwa (label)
    std::cout << "Name:   \"" << pc.name << "\"" << std::endl;

    // Relacje/Typy ()
    if (!pc.to.empty()) {
        std::cout << "Round:  (" << pc.from << ", " << pc.to << ")" << std::endl;
    }
    else {
        std::cout << "Round:  (" << pc.from << ")" << std::endl;
    }

    // Dane wymagane {}
    std::cout << "Weird:  { ";
    for (const auto& p : pc.weird) {
        std::cout << p.first << ":" << p.second << " ";
    }
    std::cout << "}" << std::endl;

    // Dane opcjonalne []
    std::cout << "Square: [ ";
    for (const auto& p : pc.square) {
        std::cout << p.first << ":" << p.second << " ";
    }
    std::cout << "]" << std::endl;

    std::cout << "------------------------------" << std::endl;
}


ParsedCommand Command::Parse(const std::string& input) {
    ParsedCommand pc;
    std::regex pattern(R"custom(^\s*([a-zA-Z]+)\s+([a-zA-Z]+)\s*"([^"]*)"\s*\(([^)]*)\)\s*\{([^}]*)\}\s*\[([^\]]*)\]\s*$)custom");
    std::smatch matches;
    try {
        if (!std::regex_match(input, matches, pattern)) {
            throw std::runtime_error("Invalid structure");
        }

        pc.action = StringToACTION(matches[1].str());
        pc.entity = StringToENTITY(matches[2].str());
        pc.name = matches[3].str();

        if (pc.action == ACTION::UNKNOWN || pc.entity == ENTITY::UNKNOWN) {
            throw std::runtime_error("Unknown action or entity");
        }

        std::string rawRound = matches[4].str();
        std::string rawWeird = matches[5].str();
        std::string rawSquare = matches[6].str();


        switch (pc.entity) {
        case ENTITY::DATABASE: {
            break;
        }
        case ENTITY::NODETYPE: {
            if (!Command::Trim(rawRound).empty()) throw std::runtime_error("NodeType must have empty ()");
            pc.weird = TokenizeToPairs(rawWeird, true);  
            pc.square = TokenizeToPairs(rawSquare, true);
            PrintParsedCommand(pc);
            break;
        }
        case ENTITY::NODE: {
            if (Command::Trim(rawRound).empty()) throw std::runtime_error("Node needs type in ()");
            pc.from = Command::Trim(rawRound);
            pc.weird = TokenizeToPairs(rawWeird, false); 
            pc.square = TokenizeToPairs(rawSquare, false);
            PrintParsedCommand(pc);
            break;
        }
        case ENTITY::EDGETYPE: {
            auto rels = SplitByComma(rawRound);
            if (rels.size() != 2) throw std::runtime_error("EdgeType needs (T1, T2)");
            pc.from = rels[0];
            pc.to = rels[1];
            pc.weird = TokenizeToPairs(rawWeird, true);
            pc.square = TokenizeToPairs(rawSquare, true);
            PrintParsedCommand(pc);
            break;
        }
        case ENTITY::EDGE: {
            auto targets = SplitByComma(rawRound);
            if (targets.size() != 2) throw std::runtime_error("Edge needs (N1, N2)");
            pc.from = targets[0];
            pc.to = targets[1];
            pc.weird = TokenizeToPairs(rawWeird, false);
            pc.square = TokenizeToPairs(rawSquare, false);
            PrintParsedCommand(pc);
            break;
        }
        default:
            break;
        }
    }
    catch (...) {
        pc.action = ACTION::UNKNOWN;
    }

    return pc;
}
