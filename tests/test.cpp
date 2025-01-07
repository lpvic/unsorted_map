#include "../include/unsorted_map.hpp"

#include <string>

int main() {
    std::cout << "Testing unsorted_map" << std::endl;
    std::cout << "====================" << std::endl;

    std::cout << "Constructors:" << std::endl;    
    std::cout << "Default constructor: ";
    unsorted_map<std::string, size_t> m;
    std::cout << "Object 'm' created -> size = " << m.size() << ", capacity = " << m.capacity() << std::endl;
    std::cout << "Constructor from initialization list: ";
    unsorted_map<std::string, size_t> n = {{"Uno", 1}, {"Dos", 2}, {"Tres", 3}};
    std::cout << "Object 'n' created -> size = " << n.size() << ", capacity = " << n.capacity() << std::endl;

    std::cout << "Destructors:" << std::endl;    
    std::cout << "Default destructor: ";
    m.~unsorted_map();
    std::cout << "Object 'm' destroyed" << std::endl;

    
}