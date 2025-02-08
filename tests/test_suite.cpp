#include "vectormap.hpp"
#include "gtest/gtest.h"

#include <iostream>

using  vmap = com::vectormap<std::string, size_t, 3>;

class VectorMapTest : public testing::Test {
    protected:
        vmap m;
        vmap n = {{"Cero", 0}, {"Uno", 1}, {"Dos", 2}, {"Tres", 3}};
        vmap p = vmap(n);
        vmap q = vmap(n);
        vmap r = vmap(std::move(q));

        VectorMapTest() {};

};

TEST_F(VectorMapTest, IsEmptyInitialized) {
    EXPECT_EQ(m.size(), 0);
    EXPECT_EQ(m.capacity(), 0);
    EXPECT_EQ(m.data(), nullptr);
}

TEST_F(VectorMapTest, ConstructorFromInitList) {
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

TEST_F(VectorMapTest, CopyConstructor) {
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

TEST_F(VectorMapTest, MoveConstructor) {
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

TEST_F(VectorMapTest, PushBack_pair) {
    const vmap::key_type k = "Cuatro";
    const vmap::size_type v = 4;
    vmap::iterator it = n.push_back(std::make_pair(k, v));

    EXPECT_EQ(n.size(), 5);
    EXPECT_EQ(n.capacity(), 6);
    EXPECT_EQ(n.data()[4].first, k);
    EXPECT_EQ(n.data()[4].second, v);

    EXPECT_EQ(it->first, k);
    EXPECT_EQ(it->second, v);
}

TEST_F(VectorMapTest, PushBack_string_int) {
    const vmap::key_type k = "Cinco";
    const vmap::size_type v = 5;
    vmap::iterator it = n.push_back(k, v);

    EXPECT_EQ(n.size(), 6);
    EXPECT_EQ(n.capacity(), 6);
    EXPECT_EQ(n.data()[5].first, k);
    EXPECT_EQ(n.data()[5].second, v);

    EXPECT_EQ(it->first, k);
    EXPECT_EQ(it->second, v);
}
