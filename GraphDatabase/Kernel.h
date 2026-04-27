#pragma once
#include "header.h"
#include "DataBase.h"

class Kernel
{
public:
	static inline std::map<std::string, DataBase> dbs;
	static inline DataBase* current_db = nullptr;

	static void Exec(std::string input);
	static std::string GetCurrentDB();
};

