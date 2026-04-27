#include "PropertyType.h"

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
