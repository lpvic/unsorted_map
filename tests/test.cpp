#include "../include/unsorted_map.hpp"

#include <string>

int main() {
    using  umap = unsorted_map<std::string, size_t, 3>;

    std::cout << "Testing unsorted_map" << std::endl;
    std::cout << "====================" << std::endl;

    std::cout << "* Constructors:" << std::endl;    
    std::cout << "  Default constructor: ";
    umap m;
    std::cout << "Object 'm' created -> size = " << m.size() << ", capacity = " << m.capacity() << std::endl;
    std::cout << "  Constructor from initialization list: ";
    umap n = {{"Uno", 1}, {"Dos", 2}, {"Tres", 3}};
    std::cout << "Object 'n' created -> size = " << n.size() << ", capacity = " << n.capacity() << std::endl;
    std::cout << std::endl;

    std::cout << "* Destructors:" << std::endl;    
    std::cout << "  Default destructor: ";
    m.clear();
    std::cout << "Object 'm' destroyed" << std::endl;
    std::cout << std::endl;

    std::cout << "* Inserting elements:" << std::endl;
    std::cout << "  push_back(pair) -> ";
    umap::iterator it = n.push_back(std::make_pair<std::string, size_t>("Cuatro", 4));
    std::cout << "Addr: " << &(*it) << " / (\"" << it->first << "\" , " << it->second << ") ";
    std::cout << "-> size = " << n.size() << ", capacity = " << n.capacity() << std::endl;

    std::cout << std::endl;
    for (umap::iterator it = n.begin(); it != n.end(); it++) {
        std::cout << "Addr: " << &(*it) << " / (\"" << it->first << "\" , " << it->second << ") ";
        std::cout << "-> size = " << n.size() << ", capacity = " << n.capacity() << std::endl;
    }
    std::cout << std::endl;

    std::cout << "  push_back(string, int) -> ";
    it = n.push_back("Cinco", 5);
    std::cout << "Addr: " << &(*it) << " / (\"" << it->first << "\" , " << it->second << ") ";
    std::cout << "-> size = " << n.size() << ", capacity = " << n.capacity() << std::endl;
    
    std::cout << std::endl;
    for (umap::iterator it = n.begin(); it != n.end(); it++) {
        std::cout << "Addr: " << &(*it) << " / (\"" << it->first << "\" , " << it->second << ") ";
        std::cout << "-> size = " << n.size() << ", capacity = " << n.capacity() << std::endl;
    }
    std::cout << std::endl;

    std::cout << "  push_back(unsorted_map) -> ";
    m.push_back({{"Seis", 6}, {"Siete", 7}});
    it = n.push_back(m);
    std::cout << "Addr: " << &(*it) << " / (\"" << it->first << "\" , " << it->second << ") ";
    std::cout << "-> size = " << n.size() << ", capacity = " << n.capacity() << std::endl;

    std::cout << std::endl;
    for (umap::iterator it = n.begin(); it != n.end(); it++) {
        std::cout << "Addr: " << &(*it) << " / (\"" << it->first << "\" , " << it->second << ") ";
        std::cout << "-> size = " << n.size() << ", capacity = " << n.capacity() << std::endl;
    }
    std::cout << std::endl;

    std::cout << "  insert(pair, pos) -> ";
    it = n.insert(std::make_pair("Ocho", 8), 6);
    std::cout << "Addr: " << &(*it) << " / (\"" << it->first << "\" , " << it->second << ") ";
    std::cout << "-> size = " << n.size() << ", capacity = " << n.capacity() << std::endl;

    std::cout << std::endl;
    for (umap::iterator it = n.begin(); it != n.end(); it++) {
        std::cout << "Addr: " << &(*it) << " / (\"" << it->first << "\" , " << it->second << ") ";
        std::cout << "-> size = " << n.size() << ", capacity = " << n.capacity() << std::endl;
    }
    std::cout << std::endl;

    std::cout << "  insert(string, int, pos) -> ";
    it = n.insert("Nueve", 9, 6);
    std::cout << "Addr: " << &(*it) << " / (\"" << it->first << "\" , " << it->second << ") ";
    std::cout << "-> size = " << n.size() << ", capacity = " << n.capacity() << std::endl;

    std::cout << std::endl;
    for (umap::iterator it = n.begin(); it != n.end(); it++) {
        std::cout << "Addr: " << &(*it) << " / (\"" << it->first << "\" , " << it->second << ") ";
        std::cout << "-> size = " << n.size() << ", capacity = " << n.capacity() << std::endl;
    }
    std::cout << std::endl;

    std::cout << "  insert(initialization_list, pos) -> ";
    it = n.insert({{"Diez", 10}, {"Once", 11}, {"Doce", 12}}, 6);
    std::cout << "Addr: " << &(*it) << " / (\"" << it->first << "\" , " << it->second << ") ";
    std::cout << "-> size = " << n.size() << ", capacity = " << n.capacity() << std::endl;

    std::cout << std::endl;
    for (umap::iterator it = n.begin(); it != n.end(); it++) {
        std::cout << "Addr: " << &(*it) << " / (\"" << it->first << "\" , " << it->second << ") ";
        std::cout << "-> size = " << n.size() << ", capacity = " << n.capacity() << std::endl;
    }
    std::cout << std::endl;

}