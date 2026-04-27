#pragma once
#include <string>
#include <map>
#include <vector>
#include <initializer_list>
#include <memory>
#include <sstream>
#include <iostream>

enum class ACTION { CREATE, DELETE, CHANGE, USE, UNKNOWN };
enum class ENTITY { DATABASE, NODE, NODETYPE, EDGE, EDGETYPE, UNKNOWN };