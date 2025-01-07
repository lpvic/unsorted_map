#include <iostream>
#include <string>

#include "include/unsorted_map.hpp"

std::pair<std::string*, int> search(std::string* arr, const std::string srch, const size_t size) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == srch)
            return std::make_pair(&arr[i], i);
    }
    return {NULL, -1};
}

template<class K, class V>
std::string print_pair(const std::pair<K, V> &p) {
    return "Key: " + std::to_string(p.first) + " - Value: " + std::to_string(p.second);
}

template<class K, class V>
std::string print_pair(const std::pair<std::string, V> &p) {
    return "Key: \"" + p.first + "\" - Value: " + std::to_string(p.second);
}

template<class K, class V, size_t D = 100>
std::string print_map(unsorted_map<K, V, D> &m) {
    return "Size: " + std::to_string(m.size()) + " - Capacity: " + std::to_string(m.capacity());
}

int main()
{
    using umap_type = unsorted_map<std::string, int>;    
    
    std::cout << __cplusplus << std::endl;

    std::string str_arr[10] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "0"};
    std::pair<std::string*, int> p = search(str_arr, "a", 10);
    std::cout << p.first << " " << ((p.first != NULL) ? *p.first : "Not found") << " " << p.second << std::endl;

    std::pair<std::string, int>* arr1;
    std::pair<std::string, int>* arr2;
    std::allocator<std::pair<std::string, int>> allocator;

    arr1 = allocator.allocate(10);
    std::allocator_traits<std::allocator<std::pair<std::string, int>>>::construct(allocator, arr1, std::make_pair("Uno", 1));
    std::cout << arr1[0].first << std::endl;


    umap_type m;
    std::cout << sizeof(m) << std::endl;
    m.push_back(std::make_pair("Uno", 1));
    std::cout << print_pair<std::string, int>(*m.last()) << " ; " << print_map<std::string, int>(m) << std::endl;
    std::cout << sizeof(m) << std::endl;
    m.push_back(std::make_pair("Dos", 2));
    std::cout << print_pair<std::string, int>(*m.last()) << " ; " << print_map<std::string, int>(m) << std::endl;
    std::cout << sizeof(m) << std::endl;


    unsorted_map<std::string, int, 3> n = {{"Tres", 3}, {"Cuatro", 4}, {"Cinco", 5}};
    std::cout << n.size() << " " << n.capacity() << std::endl;
    n.push_back(std::make_pair("Seis", 6));
    std::cout << print_pair<std::string, int>(*m.last()) << " " << print_map<std::string, int, 3>(n) << std::endl;

    n.push_back({{"Tres", 7}, {"Cuatro", 8}, {"Cinco", 9}});

    for (size_t i = 0; i < n.size(); i++)
        std::cout << print_pair<std::string, int>(n.at(i)) << std::endl;

    for (auto i : n) 
        std::cout << print_pair<std::string, int>(i) << " ; " << print_map<std::string, int, 3>(n) << std::endl;

    std::cout << n.find_first("Cuatro").first << " " << n.find_first("Cuatro").second << std::endl;
}