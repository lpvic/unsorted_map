#include "vectormap.hpp"
#include <string>
#include <iostream>

using vmap = com::vectormap<std::string, size_t, 3>;

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
