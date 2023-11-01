#include <iostream>
#include "HashTable.h"

int main()
{
    HashTable<std::string, int> table(14);
    table.add("Pomidor", 5);
    table.add("Iamaguti", 15);
    table.add("Privet", 43);
    table.add("1234aguti", 1);
    table.add("kakdela", 65);
    table.print();
    std::cout << std::endl << table.get("Privet");
    std::cout << std::endl;
    table.remove("kakdela");
    table.print();
}