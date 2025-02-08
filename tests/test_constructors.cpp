#include "vectormap.hpp"
#include "gtest/gtest.h"

using  vmap = com::vectormap<std::string, size_t, 3>;

class VectorMapTestConstructors : public ::testing::Test {
    protected:
        vmap m;
        vmap n = {{"Cero", 0}, {"Uno", 1}, {"Dos", 2}, {"Tres", 3}};
        vmap p = vmap(n);
        vmap q = vmap(n);
        vmap r = vmap(std::move(q));
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
