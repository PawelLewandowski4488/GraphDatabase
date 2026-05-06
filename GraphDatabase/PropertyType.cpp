#include "PropertyTYPE.h"

std::string PropertyType::ToString()
{
    std::string text;

    switch (type) {
    case TYPE::INT:    text = "INT";    break;
    case TYPE::FLOAT:  text = "FLOAT";  break;
    case TYPE::STRING: text = "STRING"; break;
    default:           text = "UNKNOWN"; break;
    }

    return text + ": " + name;
}

bool PropertyType::Validate(const RawProperty& rawproperty) const
{
    if (this->name != rawproperty.name) return false;

    try {
        if (type == TYPE::INT) {
            size_t pos;
            std::stoi(rawproperty.value, &pos);
            return pos == rawproperty.value.length();
        }
        else if (type == TYPE::FLOAT) {
            size_t pos;
            std::stof(rawproperty.value, &pos);
            return pos == rawproperty.value.length();
        }
        else if (type == TYPE::STRING) {
            return true; 
        }
    }
    catch (...) {
        return false; 
    }

    return false;
}
