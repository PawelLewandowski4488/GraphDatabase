#include "Header.h"
#include "Node.h"
#include "NodeType.h"
#include "Edge.h"
#include "EdgeType.h"
#include "Pair.h"
#include "PropertyType.h"
#include "DataBase.h"

void exec(std::string input, DataBase* current_db);

int main()
{
    std::vector<std::unique_ptr<DataBase>> db;

    db.push_back(std::make_unique<DataBase>("A"));
    db.push_back(std::make_unique<DataBase>("B"));
    db.push_back(std::make_unique<DataBase>("C"));

    DataBase* current_db = nullptr;

    std::string input{};
    while (input != "exit")
    {
        std::cin >> input;
        exec(input, current_db);
    }

    return 0;
    /*NodeType Person = NodeType("Person", {PropertyType(Type::STRING, "imie"), PropertyType(Type::INT, "wiek")}, {PropertyType(Type::FLOAT, "BMI")});

    std::map<std::string, std::string> data = {
        {"imie", "Jan"},
        {"wiek", "25"},
        {"BMI", "22.5"}
    };

    std::map<std::string, std::string> data2 = {
        {"nazwa", "JP"},
        {"od_lat", "7"},
        {"costam", "3.4"}
    };

    Node* p = new Node(&Person, 0, "Jan", data);

    std::cout << Person.ToString() << std::endl;
    std::cout << p->ToString() << "\n";

    Node* q = new Node(&Person, 0, "Pawel", data);

    EdgeType Friendship = EdgeType("Friendship", &Person, &Person, { PropertyType(Type::STRING, "nazwa"), PropertyType(Type::INT, "od_lat") }, { PropertyType(Type::FLOAT, "costam") });

    std::cout << Friendship.ToString() << "\n";


    Edge* r = new Edge(&Friendship, 0, "JP", p, q, data2);

    std::cout << r->ToString();

    delete r;
    delete p;
    delete q;*/
}

void exec(std::string input, DataBase* current_db)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(input);
    while (tokenStream >> token) {
        tokens.push_back(token);
    }
    for (auto t : tokens)
    {
        std::cout << t << "\n";
    }
}

