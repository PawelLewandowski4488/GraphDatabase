#include "PropertyType.h"

std::string PropertyType::ToString()
{
    std::string text;

    switch (type) {
    case Type::INT:    text = "INT";    break;
    case Type::FLOAT:  text = "FLOAT";  break;
    case Type::STRING: text = "STRING"; break;
    default:           text = "UNKNOWN"; break;
    }

    return text + ": " + name;
}
