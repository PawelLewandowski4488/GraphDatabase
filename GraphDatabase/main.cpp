#include <iostream>
#include "Header.h"
#include "Node.h"
#include "NodeType.h"
#include "Pair.h"
#include "PropertyType.h"

int main()
{
    NodeType Person = NodeType("Person", {PropertyType(Type::STRING, "imie"), PropertyType(Type::INT, "wiek")}, {PropertyType(Type::FLOAT, "BMI")});

    std::map<std::string, std::string> data = {
        {"imie", "Jan"},
        {"wiek", "25"},
        {"BMI", "22.5"}
    };

    Node* p = new Node(&Person, 0, "Jan", data);

    std::cout << Person.ToString() << std::endl;
    std::cout << p->ToString();

    delete p;
}


