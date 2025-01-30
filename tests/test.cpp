#include "vectormap.hpp"

#include <string>

using  vmap = com::vectormap<std::string, size_t, 3>;

void print(std::string name, vmap& map) {
    vmap::size_type i = 0;
    std::cout << "    " << name << ":" << std::endl;
    for (vmap::iterator it = map.begin(); it != map.end(); it++) {
        std::cout << "    " << name << "[" << i << "]: Addr: " << &(*it) << " / (\"" << it->first << "\" , " << it->second << ") ";
        std::cout << "-> size = " << map.size() << ", capacity = " << map.capacity() << std::endl;
        i++;
    }
    if (i == 0) {
        std::cout << "    Empty" << std::endl;
    }

    std::cout << std::endl;
}

int main() {
    std::cout << "Testing unsorted_map" << std::endl;
    std::cout << "====================" << std::endl;

    std::cout << "* Constructors:" << std::endl;    
    std::cout << "  Default constructor: ";
    vmap m;
    std::cout << vmap::allocator_traits::propagate_on_container_copy_assignment::value << "  " << vmap::allocator_traits::propagate_on_container_move_assignment::value << "  " << vmap::allocator_traits::propagate_on_container_swap::value << std::endl;
    std::cout << "    Object 'm' created -> size = " << m.size() << ", capacity = " << m.capacity() << std::endl << std::endl;
    
    std::cout << "  Constructor from initialization list -> ";
    vmap n = {{"Cero", 0}, {"Uno", 1}, {"Dos", 2}, {"Tres", 3}};
    std::cout << R"(umap n = {{"Cero", 0}, {"Uno", 1}, {"Dos", 2}, {"Tres", 3}};)" << std::endl;
    print("n", n);

    std::cout << "  Copy constructor -> ";
    vmap p(n);
    std::cout << "umap p(n);" << std::endl;
    print("p", p);
    print("n", n);

    std::cout << "  Move constructor -> ";
    vmap q(std::move(p));
    std::cout << "umap q(std::move(p));" << std::endl;
    print("p", p);
    print("q", q);

    std::cout << "* Inserting elements:" << std::endl;
    std::cout << "  push_back(pair) -> ";
    vmap::iterator it = n.push_back(std::make_pair<std::string, size_t>("Cuatro", 4));
    std::cout << "n.push_back(std::make_pair<std::string, size_t>(\"Cuatro\", 4));" << std::endl;
    print("n", n);

    std::cout << "  push_back(string, int) -> ";
    it = n.push_back("Cinco", 5);
    std::cout << "n.push_back(\"Cinco\", 5);" << std::endl;
    print("n", n);

    std::cout << "  push_back(initialization_list) -> ";
    m.push_back({{"Seis", 6}, {"Siete", 7}});
    std::cout << "m.push_back({{\"Seis\", 6}, {\"Siete\", 7}});" << std::endl;
    print("m", m);

    std::cout << "  push_back(unsorted_map) -> ";
    it = n.push_back(m);
    std::cout << "n.push_back(m);" << std::endl;
    print("n", n);

    std::cout << "  insert(pair, pos) -> ";
    it = n.insert(std::make_pair("Ocho", 8), 6);
    std::cout << "n.insert(std::make_pair(\"Ocho\", 8), 6);" << std::endl;
    print("n", n);

    std::cout << "  insert(string, int, pos) -> ";
    it = n.insert("Nueve", 9, 6);
    std::cout << "n.insert(\"Nueve\", 9, 6);" << std::endl;
    print("n", n);

    std::cout << "  insert(initialization_list, pos) -> ";
    it = n.insert({{"Diez", 10}, {"Once", 11}, {"Doce", 12}}, 6);
    std::cout << "n.insert({{\"Diez\", 10}, {\"Once\", 11}, {\"Doce\", 12}}, 6);" << std::endl;
    print("n", n);

    std::cout << "  insert(unsorted_map, pos) -> ";
    it = n.insert(m, 6);
    std::cout << "n.insert(m, 6);" << std::endl;
    print("n", n);

    std::cout << "  push_front(pair) -> ";
    it = n.push_front("Trece", 13);
    std::cout << "n.push_front(\"Trece\", 13);" << std::endl;
    print("n", n);

    std::cout << "  push_front(string, int) -> ";
    it = n.push_front("Catorce", 14);
    std::cout << "n.push_front(\"Catorce\", 14);" << std::endl;
    print("n", n);

    std::cout << "  push_front(initialization_list) -> ";
    n.push_front({{"Quince", 15}, {"Dieciseis", 16}});
    std::cout << "n.push_front({{\"Quince\", 15}, {\"Dieciseis\", 16}});" << std::endl;
    print("n", n);

    std::cout << "  push_front(unsorted_map) -> ";
    it = n.push_front(m);
    std::cout << "n.push_front(m);" << std::endl;
    print("n", n);

    std::cout << "* Element access:" << std::endl;
    std::cout << "  get(pos) -> ";
    it = n.get(3);
    std::cout << "n.get(3);" << std::endl;
    std::cout << "    (\"" << it->first << "\" , " << it->second << ")" << std::endl;
    std::cout << std::endl;

    std::cout << "  get(key) -> ";
    auto it_pos = n.get("Cero");
    std::cout << "n.get(\"Cero\");" << std::endl;
    std::cout << "    <<(\"" << it_pos.first->first << "\" , " << it_pos.first->second << ") , " << it_pos.second << ">>" << std::endl;
    std::cout << std::endl;

    std::cout << "  get(key, ordinal) -> ";
    it_pos = n.get("Seis", 2);
    std::cout << "n.get(\"Seis\", 2);" << std::endl;
    std::cout << "    <<(\"" << it_pos.first->first << "\" , " << it_pos.first->second << ") , " << it_pos.second << ">>" << std::endl;
    std::cout << std::endl;

    std::cout << "  get_all(key) -> ";
    auto v = n.get_all("Seis");
    std::cout << "n.get_all(\"Seis\");" << std::endl;
    for (auto e : v) {
        std::cout << "    (\"" << e.first->first << "\" , " << e.first->second << ") " << e.second << std::endl;
    }
    std::cout << std::endl;

    std::cout << "  get_value(pos) -> ";
    int val = n.get_value(16);
    std::cout << "n.get_value(16);" << std::endl;
    std::cout << "    " << val << std::endl;
    std::cout << std::endl;

    std::cout << "  get_value(key) -> ";
    val = n.get_value("Cero");
    std::cout << "n.get_value(\"Cero\");" << std::endl;
    std::cout << "    " << val << std::endl;
    std::cout << std::endl;

    std::cout << "  get_value(key, ordinal) -> ";
    val = n.get_value("Siete", 2);
    std::cout << "n.get_value(\"Siete\", 2);" << std::endl;
    std::cout << "    " << val << std::endl;
    std::cout << std::endl;

    std::cout << "  get_all_values(key) -> ";
    auto vval = n.get_all_values("Siete");
    std::cout << "n.get_all_values(\"Siete\");" << std::endl;
    std::cout << "    ";
    for (auto e : vval) {
        std::cout << e << " ";
    }
    std::cout << std::endl << std::endl;

    std::cout << "  get_key(pos) -> ";
    auto key = n.get_key(10);
    std::cout << "n.get_key(10);" << std::endl;
    std::cout << "    " << key << std::endl;
    std::cout << std::endl;

    std::cout << "  get_pos(key) -> ";
    auto pos = n.get_pos("Doce");
    std::cout << "n.get_pos(\"Doce\");" << std::endl;
    std::cout << "    " << pos << std::endl;
    std::cout << std::endl;

    std::cout << "  get_pos(key, ordinal) -> ";
    pos = n.get_pos("Seis", 2);
    std::cout << "n.get_pos(\"Seis\", 2);" << std::endl;
    std::cout << "    " << pos << std::endl;
    std::cout << std::endl;

    std::cout << "  get_all_pos(key) -> ";
    auto vpos = n.get_all_pos("Siete");
    std::cout << "n.get_all_pos(\"Siete\");" << std::endl;
    std::cout << "    ";
    for (auto e : vpos) {
        std::cout << e << " ";
    }
    std::cout << std::endl << std::endl;

    std::cout << "  data() -> ";
    auto ptr = n.data();
    std::cout << "n.data();" << std::endl;
    std::cout << "    " << ptr << std::endl;
    std::cout << std::endl;

    std::cout << "* Element modification:" << std::endl;

    

    std::cout << "* Element management:" << std::endl;
    std::cout << "  erase(pos) -> ";
    n.erase(7);
    std::cout << "n.erase(7);" << std::endl;
    print("n", n);

    std::cout << "  erase(key) -> ";
    n.erase("Dos");
    std::cout << "n.erase(\"Dos\");" << std::endl;
    print("n", n);

    std::cout << "  erase_all(key) -> ";
    n.erase_all("Seis");
    std::cout << "n.erase_all(\"Seis\");" << std::endl;
    print("n", n);

    std::cout << "  swap(from, to) -> ";
    n.swap(8, 10);
    std::cout << "n.swap(8, 10);" << std::endl;
    print("n", n);

    std::cout << "    Copy assignment -> ";
    p = n;
    std::cout << "p = n" << std::endl;
    print("p", p);
    print("n", n);

    std::cout << "    Move assignment -> ";
    q = std::move(n);
    std::cout << "p = std::move(n);" << std::endl;
    print("q", q);
    print("n", n);

    std::cout << "    Move element -> ";
    q.move(10, 2);
    std::cout << "q.move(4, 2);" << std::endl;
    print("q", q);

    std::cout << "Exit with no errors" << std::endl;
}