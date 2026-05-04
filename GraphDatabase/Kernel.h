#pragma once

#include <map>
#include <string>

class DataBase;

class Kernel
{
public:
	static inline std::map<std::string, DataBase> dbs;
	static inline DataBase* current_db = nullptr;

	static void Exec(std::string input);
	static std::string GetCurrentDB();
};

