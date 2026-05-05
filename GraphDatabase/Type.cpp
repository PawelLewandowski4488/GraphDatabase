#include "TYPE.h"

TYPE TypeMapper::StringToType(const std::string& str)
{
    if (str == "int")    return TYPE::INT;
    if (str == "float")  return TYPE::FLOAT;
    if (str == "string") return TYPE::STRING;
    else return TYPE::UNKNOWN;
}

std::string TypeMapper::TypeToString(const TYPE& type)
{
    switch (type) 
    {
    case TYPE::INT:    return "int";
    case TYPE::FLOAT:  return "float";
    case TYPE::STRING: return "string";
    default: return "unknown";
    }
}