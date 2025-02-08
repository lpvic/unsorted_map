#include "vectormap.hpp"
#include "gtest/gtest.h"

using  vmap = com::vectormap<std::string, size_t, 3>;

class VectorMapTestInsertion : public ::testing::Test {
    protected:
        vmap n = {{"Cero", 0}, {"Uno", 1}, {"Dos", 2}, {"Tres", 3}, {"Cuatro", 4}, {"Cinco", 5}, {"Seis", 6}, {"Siete", 7}, {"Ocho", 8}};
};

TEST_F(VectorMapTestInsertion, InsertPairPos) {
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

TEST_F(VectorMapTestInsertion, InsertKeyValPos) {
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

TEST_F(VectorMapTestInsertion, InsertInitList) {
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

TEST_F(VectorMapTestInsertion, InsertVectormap) {
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

TEST_F(VectorMapTestInsertion, PushBackPair) {
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

TEST_F(VectorMapTestInsertion, PushBackKeyVal) {
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

TEST_F(VectorMapTestInsertion, PushBackInitList) {
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

TEST_F(VectorMapTestInsertion, PushBackVectormap) {
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

TEST_F(VectorMapTestInsertion, PushFrontPair) {
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

TEST_F(VectorMapTestInsertion, PushFrontKeyVal) {
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

TEST_F(VectorMapTestInsertion, PushFrontInitList) {
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

TEST_F(VectorMapTestInsertion, PushFrontVectormap) {
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
