#include "unsorted_map.hpp"

#include <string>

using  umap = unsorted_map<std::string, size_t, 3>;

void print(umap& map) {
    umap::size_type i = 0;
    for (umap::iterator it = map.begin(); it != map.end(); it++) {
        std::cout << "    Addr: " << &(*it) << " / " << "pos " << i << ": (\"" << it->first << "\" , " << it->second << ") ";
        std::cout << "-> size = " << map.size() << ", capacity = " << map.capacity() << std::endl;
        i++;
    }
    std::cout << std::endl;
}

int main() {
    std::cout << "Testing unsorted_map" << std::endl;
    std::cout << "====================" << std::endl;

    std::cout << "* Constructors:" << std::endl;    
    std::cout << "  Default constructor: ";
    umap m;
    std::cout << "Object 'm' created -> size = " << m.size() << ", capacity = " << m.capacity() << std::endl;
    std::cout << "  Constructor from initialization list: ";
    umap n = {{"Cero", 0}, {"Uno", 1}, {"Dos", 2}, {"Tres", 3}};
    std::cout << R"(umap n = {{"Cero", 0}, {"Uno", 1}, {"Dos", 2}, {"Tres", 3}};)" << std::endl;
    print(n);

/*    std::cout << "* Destructors:" << std::endl;    
    std::cout << "  Default destructor: ";
    m.clear();
    std::cout << "Object 'm' destroyed" << std::endl;
    std::cout << std::endl;
*/

    std::cout << "* Inserting elements:" << std::endl;
    std::cout << "  push_back(pair) -> ";
    umap::iterator it = n.push_back(std::make_pair<std::string, size_t>("Cuatro", 4));
    std::cout << "n.push_back(std::make_pair<std::string, size_t>(\"Cuatro\", 4));" << std::endl;
    print(n);

    std::cout << "  push_back(string, int) -> ";
    it = n.push_back("Cinco", 5);
    std::cout << "n.push_back(\"Cinco\", 5);" << std::endl;
    print(n);

    std::cout << "  push_back(initialization_list) -> ";
    m.push_back({{"Seis", 6}, {"Siete", 7}});
    std::cout << "m.push_back({{\"Seis\", 6}, {\"Siete\", 7}});" << std::endl;
    print(m);

    std::cout << "  push_back(unsorted_map) -> ";
    it = n.push_back(m);
    std::cout << "n.push_back(m);" << std::endl;
    print(n);

    std::cout << "  insert(pair, pos) -> ";
    it = n.insert(std::make_pair("Ocho", 8), 6);
    std::cout << "n.insert(std::make_pair(\"Ocho\", 8), 6);" << std::endl;
    print(n);

    std::cout << "  insert(string, int, pos) -> ";
    it = n.insert("Nueve", 9, 6);
    std::cout << "n.insert(\"Nueve\", 9, 6);" << std::endl;
    print(n);

    std::cout << "  insert(initialization_list, pos) -> ";
    it = n.insert({{"Diez", 10}, {"Once", 11}, {"Doce", 12}}, 6);
    std::cout << "n.insert({{\"Diez\", 10}, {\"Once\", 11}, {\"Doce\", 12}}, 6);" << std::endl;
    print(n);

    std::cout << "  insert(unsorted_map, pos) -> ";
    it = n.insert(m, 6);
    std::cout << "n.insert(m, 6);" << std::endl;
    print(n);

    std::cout << "  push_front(pair) -> ";
    it = n.push_front("Trece", 13);
    std::cout << "n.push_front(\"Trece\", 13);" << std::endl;
    print(n);

    std::cout << "  push_front(string, int) -> ";
    it = n.push_front("Catorce", 14);
    std::cout << "n.push_front(\"Catorce\", 14);" << std::endl;
    print(n);

    std::cout << "  push_front(initialization_list) -> ";
    n.push_front({{"Quince", 15}, {"Dieciseis", 16}});
    std::cout << "n.push_front({{\"Quince\", 15}, {\"Dieciseis\", 16}});" << std::endl;
    print(n);

    std::cout << "  push_front(unsorted_map) -> ";
    it = n.push_front(m);
    std::cout << "n.push_front(m);" << std::endl;
    print(n);
}