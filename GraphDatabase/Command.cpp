#include "Command.h"

#include "TYPE.h"

#include <regex>
#include <iostream>
#include <sstream>

std::string Command::Trim(const std::string& s) {
    size_t first = s.find_first_not_of(" \t\n\r");
    if (first == std::string::npos) return "";
    size_t last = s.find_last_not_of(" \t\n\r");
    return s.substr(first, (last - first + 1));
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

std::string Command::ExtractContent(std::string& source, char open, char close) {
    size_t startPos = source.find(open);
    size_t endPos = source.find(close);

    if (startPos == std::string::npos || endPos == std::string::npos) {
        return "";
    }

    if (endPos < startPos) {
        throw std::runtime_error("Malformed brackets: closing bracket before opening");
    }

    std::string content = source.substr(startPos + 1, endPos - startPos - 1);

    source.erase(0, endPos + 1);

    return Command::Trim(content);
}

std::vector<PropertyType> Command::ConvertToPropertyTypes(const std::string& content) {
    std::vector<PropertyType> result;
    if (Command::Trim(content).empty()) return result;

    std::string cleanContent = content;
    for (char& c : cleanContent) {
        if (c == ',') c = ' ';
    }

    std::stringstream ss(cleanContent);
    std::string typeStr, nameStr;

    while (ss >> typeStr >> nameStr) {
        TYPE t = TypeMapper::StringToType(typeStr);

        if (t == TYPE::UNKNOWN) {
            throw std::runtime_error("Unknown data type: " + typeStr);
        }

        result.push_back(PropertyType(t, nameStr));
    }

    if (ss.eof() == false) {
    }

    return result;
}

bool Command::IsValidName(const std::string& name) {
    if (name.empty()) return false;
    for (char c : name) {
        if (!std::isalnum(static_cast<unsigned char>(c)) && c != '_') {
            return false;
        }
    }
    return true;
}

std::vector<RawProperty> Command::ConvertToRawProperties(std::string content) {
    std::vector<RawProperty> result;
    content = Trim(content);
    if (content.empty()) return result;

    std::stringstream ss(content);
    std::string key;

    while (ss >> key) {
        if (key.back() == ',') key.pop_back();

        ss >> std::ws;

        std::string value;
        if (ss.peek() == '"') {
            ss.get(); 
            std::getline(ss, value, '"'); 
        }
        else {
            std::string temp;
            ss >> temp;
            if (!temp.empty() && temp.back() == ',') temp.pop_back();
            value = temp;
        }

        result.push_back(RawProperty(key, value));

        ss >> std::ws;
        if (ss.peek() == ',') ss.get();
    }

    return result;
}

ParsedCommand Command::Parse(const std::string& input) {
    ParsedCommand pc;
    std::stringstream ss(input);
    std::string actionStr, entityStr, nameStr;

    if (!(ss >> actionStr >> entityStr >> nameStr)) {
        pc.action = ACTION::UNKNOWN;
        return pc;
    }

    pc.action = ActionMapper::StringToAction(actionStr);
    pc.entity = EntityMapper::StringToEntity(entityStr);
    pc.name = nameStr; 

    if (pc.action == ACTION::UNKNOWN || pc.entity == ENTITY::UNKNOWN) {
        return pc;
    }

    if (!IsValidName(nameStr)) {
        throw std::runtime_error("Invalid characters in name: " + nameStr);
        return pc;
    }

    std::string remainder;
    std::getline(ss, remainder);
    remainder = Trim(remainder);

    try {
        switch (pc.action) {
        case ACTION::CREATE:
            switch (pc.entity) {
            case ENTITY::DATABASE: //
                break;
            case ENTITY::NODETYPE: //pt_req, pt_nreq
                pc.pt_req = Command::ConvertToPropertyTypes(Command::ExtractContent(remainder, '{', '}'));
                pc.pt_nreq = Command::ConvertToPropertyTypes(Command::ExtractContent(remainder, '[', ']'));
                break;
            case ENTITY::NODE:  //rp_req, rp_nreq
                pc.rp_req = Command::ConvertToRawProperties(Command::ExtractContent(remainder, '{', '}'));
                pc.rp_nreq = Command::ConvertToRawProperties(Command::ExtractContent(remainder, '[', ']'));
                break;
            case ENTITY::EDGETYPE: //from_name, to_name, pt_req, pt_nreq


                pc.pt_req = Command::ConvertToPropertyTypes(Command::ExtractContent(remainder, '{', '}'));
                pc.pt_nreq = Command::ConvertToPropertyTypes(Command::ExtractContent(remainder, '[', ']'));
                break;
            case ENTITY::EDGE:  //from_id, to_id, rp_req, rp_nreq


                pc.rp_req = Command::ConvertToRawProperties(Command::ExtractContent(remainder, '{', '}'));
                pc.rp_nreq = Command::ConvertToRawProperties(Command::ExtractContent(remainder, '[', ']'));
                break;
            }
            break;
        case ACTION::DELETE:
            switch (pc.entity) {
            case ENTITY::DATABASE: //get name
                break;
            case ENTITY::NODETYPE: //get name
                break;
            case ENTITY::NODE:  //get name, id
                break;
            case ENTITY::EDGETYPE:  //get name
                break;
            case ENTITY::EDGE: //get name, from_id, to_id
                break;
            }
            break;
        case ACTION::CHANGE:
            switch (pc.entity) {
            case ENTITY::DATABASE: //return action unknown
                break;
            case ENTITY::NODETYPE: //get name, ???
                break;
            case ENTITY::NODE: //get name, id, rp_req, rp_nreq
                break;
            case ENTITY::EDGETYPE:  //get name, ???
                break;
            case ENTITY::EDGE: //get name, from_id, to_id, rp_req, rp_nreq
                break;
            }
            break;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Parser error: " << e.what() << std::endl;
        pc.action = ACTION::UNKNOWN;
    }

    return pc;
}
