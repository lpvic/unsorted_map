#include "vectormap.hpp"
#include "gtest/gtest.h"

#include <iostream>

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

class VectorMapTestConstructors : public ::testing::Test {
    protected:
        vmap m;
        vmap n = {{"Cero", 0}, {"Uno", 1}, {"Dos", 2}, {"Tres", 3}};
        vmap p = vmap(n);
        vmap q = vmap(n);
        vmap r = vmap(std::move(q));
};

class VectorMapTestInsertion : public ::testing::Test {
    protected:
        vmap n = {{"Cero", 0}, {"Uno", 1}, {"Dos", 2}, {"Tres", 3}, {"Cuatro", 4}, {"Cinco", 5}, {"Seis", 6}, {"Siete", 7}, {"Ocho", 8}};
};

TEST_F(VectorMapTestConstructors, DefaultConstructor) {
    EXPECT_EQ(m.size(), 0);
    EXPECT_EQ(m.capacity(), 0);
    EXPECT_EQ(m.data(), nullptr);
}

TEST_F(VectorMapTestConstructors, ConstructorFromInitList) {
    EXPECT_EQ(n.size(), 4);
    EXPECT_EQ(n.capacity(), 6);
    EXPECT_EQ(n.data()[0].first, "Cero");
    EXPECT_EQ(n.data()[1].first, "Uno");
    EXPECT_EQ(n.data()[2].first, "Dos");
    EXPECT_EQ(n.data()[3].first, "Tres");
    EXPECT_EQ(n.data()[0].second, 0);
    EXPECT_EQ(n.data()[1].second, 1);
    EXPECT_EQ(n.data()[2].second, 2);
    EXPECT_EQ(n.data()[3].second, 3);
}

TEST_F(VectorMapTestConstructors, CopyConstructor) {
    EXPECT_EQ(p.size(), 4);
    EXPECT_EQ(p.capacity(), 6);
    EXPECT_EQ(p.data()[0].first, "Cero");
    EXPECT_EQ(p.data()[1].first, "Uno");
    EXPECT_EQ(p.data()[2].first, "Dos");
    EXPECT_EQ(n.data()[3].first, "Tres");
    EXPECT_EQ(p.data()[0].second, 0);
    EXPECT_EQ(p.data()[1].second, 1);
    EXPECT_EQ(p.data()[2].second, 2);
    EXPECT_EQ(n.data()[3].second, 3);
}

TEST_F(VectorMapTestConstructors, MoveConstructor) {
    EXPECT_EQ(r.size(), 4);
    EXPECT_EQ(r.capacity(), 6);
    EXPECT_EQ(r.data()[0].first, "Cero");
    EXPECT_EQ(r.data()[1].first, "Uno");
    EXPECT_EQ(r.data()[2].first, "Dos");
    EXPECT_EQ(r.data()[3].first, "Tres");
    EXPECT_EQ(r.data()[0].second, 0);
    EXPECT_EQ(r.data()[1].second, 1);
    EXPECT_EQ(r.data()[2].second, 2);
    EXPECT_EQ(r.data()[3].second, 3);

    EXPECT_EQ(q.size(), 0);
    EXPECT_EQ(q.capacity(), 0);
    EXPECT_EQ(q.data(), nullptr);
}

TEST_F(VectorMapTestInsertion, Insert_pair_pos) {
    const vmap::key_type k = "Nueve";
    const vmap::size_type v = 9;
    const vmap::size_type pos = 3;
    vmap::iterator it = n.insert(std::make_pair(k, v), pos);

    EXPECT_EQ(n.size(), 10);
    EXPECT_EQ(n.capacity(), 12);
    EXPECT_EQ(n.data()[pos].first, k);
    EXPECT_EQ(n.data()[pos].second, v);

    EXPECT_EQ(it->first, k);
    EXPECT_EQ(it->second, v);
}

TEST_F(VectorMapTestInsertion, Insert_key_val_pos) {
    const vmap::key_type k = "Nueve";
    const vmap::size_type v = 9;
    const vmap::size_type pos = 3;
    vmap::iterator it = n.insert(k, v, pos);

    EXPECT_EQ(n.size(), 10);
    EXPECT_EQ(n.capacity(), 12);
    EXPECT_EQ(n.data()[pos].first, k);
    EXPECT_EQ(n.data()[pos].second, v);

    EXPECT_EQ(it->first, k);
    EXPECT_EQ(it->second, v);
}

TEST_F(VectorMapTestInsertion, Insert_init_list) {
    vmap::iterator it = n.insert({{"Nueve", 9}, {"Diez", 10}}, 3);

    EXPECT_EQ(n.size(), 11);
    EXPECT_EQ(n.capacity(), 12);
    EXPECT_EQ(n.data()[3].first, "Nueve");
    EXPECT_EQ(n.data()[3].second, 9);
    EXPECT_EQ(n.data()[4].first, "Diez");
    EXPECT_EQ(n.data()[4].second, 10);

    EXPECT_EQ(it->first, "Nueve");
    EXPECT_EQ(it->second, 9);
}

TEST_F(VectorMapTestInsertion, Insert_vectormap) {
    vmap p = {{"Nueve", 9}, {"Diez", 10}};
    vmap::iterator it = n.insert(p, 3);

    EXPECT_EQ(n.size(), 11);
    EXPECT_EQ(n.capacity(), 12);
    EXPECT_EQ(n.data()[3].first, "Nueve");
    EXPECT_EQ(n.data()[3].second, 9);
    EXPECT_EQ(n.data()[4].first, "Diez");
    EXPECT_EQ(n.data()[4].second, 10);

    EXPECT_EQ(it->first, "Nueve");
    EXPECT_EQ(it->second, 9);
}

TEST_F(VectorMapTestInsertion, PushBack_pair) {
    const vmap::key_type k = "Nueve";
    const vmap::size_type v = 9;
    vmap::iterator it = n.push_back(std::make_pair(k, v));

    EXPECT_EQ(n.size(), 10);
    EXPECT_EQ(n.capacity(), 12);
    EXPECT_EQ(n.data()[9].first, k);
    EXPECT_EQ(n.data()[9].second, v);

    EXPECT_EQ(it->first, k);
    EXPECT_EQ(it->second, v);
}

TEST_F(VectorMapTestInsertion, PushBack_key_val) {
    const vmap::key_type k = "Nueve";
    const vmap::size_type v = 9;
    vmap::iterator it = n.push_back(k, v);

    EXPECT_EQ(n.size(), 10);
    EXPECT_EQ(n.capacity(), 12);
    EXPECT_EQ(n.data()[9].first, k);
    EXPECT_EQ(n.data()[9].second, v);

    EXPECT_EQ(it->first, k);
    EXPECT_EQ(it->second, v);
}

TEST_F(VectorMapTestInsertion, PushBack_init_list) {
    vmap::iterator it = n.push_back({{"Nueve", 9}, {"Diez", 10}});

    EXPECT_EQ(n.size(), 11);
    EXPECT_EQ(n.capacity(), 12);
    EXPECT_EQ(n.data()[9].first, "Nueve");
    EXPECT_EQ(n.data()[9].second, 9);
    EXPECT_EQ(n.data()[10].first, "Diez");
    EXPECT_EQ(n.data()[10].second, 10);

    EXPECT_EQ(it->first, "Nueve");
    EXPECT_EQ(it->second, 9);
}

TEST_F(VectorMapTestInsertion, PushBack_vectormap) {
    vmap p = {{"Nueve", 9}, {"Diez", 10}};
    vmap::iterator it = n.push_back(p);

    EXPECT_EQ(n.size(), 11);
    EXPECT_EQ(n.capacity(), 12);
    EXPECT_EQ(n.data()[9].first, "Nueve");
    EXPECT_EQ(n.data()[9].second, 9);
    EXPECT_EQ(n.data()[10].first, "Diez");
    EXPECT_EQ(n.data()[10].second, 10);

    EXPECT_EQ(it->first, "Nueve");
    EXPECT_EQ(it->second, 9);
}

TEST_F(VectorMapTestInsertion, PushFront_pair) {
    const vmap::key_type k = "Nueve";
    const vmap::size_type v = 9;
    vmap::iterator it = n.push_front(std::make_pair(k, v));

    EXPECT_EQ(n.size(), 10);
    EXPECT_EQ(n.capacity(), 12);
    EXPECT_EQ(n.data()[0].first, k);
    EXPECT_EQ(n.data()[0].second, v);

    EXPECT_EQ(it->first, k);
    EXPECT_EQ(it->second, v);
}

TEST_F(VectorMapTestInsertion, PushFront_key_val) {
    const vmap::key_type k = "Nueve";
    const vmap::size_type v = 9;
    vmap::iterator it = n.push_front(k, v);

    EXPECT_EQ(n.size(), 10);
    EXPECT_EQ(n.capacity(), 12);
    EXPECT_EQ(n.data()[0].first, k);
    EXPECT_EQ(n.data()[0].second, v);

    EXPECT_EQ(it->first, k);
    EXPECT_EQ(it->second, v);
}

TEST_F(VectorMapTestInsertion, PushFront_init_list) {
    vmap::iterator it = n.push_front({{"Nueve", 9}, {"Diez", 10}});

    EXPECT_EQ(n.size(), 11);
    EXPECT_EQ(n.capacity(), 12);
    EXPECT_EQ(n.data()[0].first, "Nueve");
    EXPECT_EQ(n.data()[0].second, 9);
    EXPECT_EQ(n.data()[1].first, "Diez");
    EXPECT_EQ(n.data()[1].second, 10);

    EXPECT_EQ(it->first, "Nueve");
    EXPECT_EQ(it->second, 9);
}

TEST_F(VectorMapTestInsertion, PushFront_vectormap) {
    vmap p = {{"Nueve", 9}, {"Diez", 10}};
    vmap::iterator it = n.push_front(p);

    EXPECT_EQ(n.size(), 11);
    EXPECT_EQ(n.capacity(), 12);
    EXPECT_EQ(n.data()[0].first, "Nueve");
    EXPECT_EQ(n.data()[0].second, 9);
    EXPECT_EQ(n.data()[1].first, "Diez");
    EXPECT_EQ(n.data()[1].second, 10);

    EXPECT_EQ(it->first, "Nueve");
    EXPECT_EQ(it->second, 9);
}
