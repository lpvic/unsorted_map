#include "../include/unsorted_map.hpp"

#include <string>

int main() {
    using  umap = unsorted_map<std::string, size_t>;

    std::cout << "Testing unsorted_map" << std::endl;
    std::cout << "====================" << std::endl;

    std::cout << "* Constructors:" << std::endl;    
    std::cout << "  Default constructor: ";
    umap m;
    std::cout << "Object 'm' created -> size = " << m.size() << ", capacity = " << m.capacity() << std::endl;
    std::cout << "  Constructor from initialization list: ";
    umap n = {{"Uno", 1}, {"Dos", 2}, {"Tres", 3}};
    std::cout << "Object 'n' created -> size = " << n.size() << ", capacity = " << n.capacity() << std::endl;

    std::cout << "* Destructors:" << std::endl;    
    std::cout << "  Default destructor: ";
    m.~unsorted_map();
    std::cout << "Object 'm' destroyed" << std::endl;

    std::cout << "* Inserting elements:" << std::endl;
    std::cout << "  push_back(pair) -> ";
    umap::pointer ptr = n.push_back(std::make_pair<std::string, size_t>("Cuatro", 4));
    std::cout << "Addr: " << ptr << " / (\"" << ptr->first << " , " << ptr->second << "\") ";
    std::cout << "-> size = " << n.size() << ", capacity = " << n.capacity() << std::endl;
    std::cout << "  push_back(string, int) -> ";
    ptr = n.push_back("Cinco", 5);
    std::cout << "Addr: " << ptr << " / (\"" << ptr->first << " , " << ptr->second << "\") ";
    std::cout << "-> size = " << n.size() << ", capacity = " << n.capacity() << std::endl;
    std::cout << "  push_back(unsorted_map) -> ";
    m.reserve(10);
    m.push_back({{"Seis", 6}, {"Siete", 7}});
    ptr = n.push_back(m);
    std::cout << "Addr: " << ptr << " / (\"" << ptr->first << " , " << ptr->second << "\") ";
    std::cout << "-> size = " << n.size() << ", capacity = " << n.capacity() << std::endl;
}