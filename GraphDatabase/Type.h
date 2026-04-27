#pragma once
#include "Header.h";

enum class TYPE { INT, FLOAT, STRING, UNKNOWN };

class TypeMapper {
public:
    static TYPE StringToType(const std::string& str);
    static std::string TypeToString(const TYPE& type);
};


