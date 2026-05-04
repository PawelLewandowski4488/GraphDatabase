#include "DataBase.h"
#include "Kernel.h"

#include <iostream>


int main()
{
    Kernel::dbs.emplace("A", DataBase("A"));
    Kernel::dbs.emplace("B", DataBase("B"));
    Kernel::dbs.emplace("C", DataBase("C"));


    std::string input;
    std::cout << Kernel::GetCurrentDB() << "> ";

    while (std::getline(std::cin, input) && input != "exit")
    {
        if (!input.empty()) {
            Kernel::Exec(input);
        }

        std::cout << Kernel::GetCurrentDB() << "> ";
    }

    return 0;
}




