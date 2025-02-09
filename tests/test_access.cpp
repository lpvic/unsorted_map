#include "vectormap.hpp"
#include "gtest/gtest.h"

#include <iostream>

using vmap = com::vectormap<std::string, size_t, 3>;

class VectorMapTestAccess : public ::testing::Test {
    protected:
        vmap n = {{"Cero", 0}, {"Uno", 1}, {"Dos", 2}, {"Tres", 3}, {"Dos", 4}, {"Cinco", 5}, {"Seis", 6}, {"Dos", 7}, {"Ocho", 8}};
};

TEST_F(VectorMapTestAccess, GetByPos) {
    vmap::iterator it = n.get(5);

    EXPECT_EQ(it->first, "Cinco");
    EXPECT_EQ(it->second, 5);
}

TEST_F(VectorMapTestAccess, GetByKey) {
    std::vector<vmap::iterator_pos> v = n.get("Dos");

    ASSERT_EQ(v.size(), 1);
    EXPECT_EQ(v.at(0).first->first, "Dos");
    EXPECT_EQ(v.at(0).first->second, 2);
    EXPECT_EQ(v.at(0).second, 2);
}

TEST_F(VectorMapTestAccess, GetByKeyByOrd) {
    std::vector<vmap::iterator_pos> v = n.get("Dos", 2);

    ASSERT_EQ(v.size(), 1);
    EXPECT_EQ(v.at(0).first->first, "Dos");
    EXPECT_EQ(v.at(0).first->second, 4);
    EXPECT_EQ(v.at(0).second, 4);
}

TEST_F(VectorMapTestAccess, GetByKeyByOrdByNum) {
    std::vector<vmap::iterator_pos> v = n.get("Dos", 2, 2);

    ASSERT_EQ(v.size(), 2);
    EXPECT_EQ(v.at(0).first->first, "Dos");
    EXPECT_EQ(v.at(0).first->second, 4);
    EXPECT_EQ(v.at(0).second, 4);
    EXPECT_EQ(v.at(1).first->first, "Dos");
    EXPECT_EQ(v.at(1).first->second, 7);
    EXPECT_EQ(v.at(1).second, 7);
}

TEST_F(VectorMapTestAccess, GetAll) {
    std::vector<vmap::iterator_pos> v = n.get_all("Dos");

    ASSERT_EQ(v.size(), 3);
    EXPECT_EQ(v.at(0).first->first, "Dos");
    EXPECT_EQ(v.at(0).first->second, 2);
    EXPECT_EQ(v.at(0).second, 2);
    EXPECT_EQ(v.at(1).first->first, "Dos");
    EXPECT_EQ(v.at(1).first->second, 4);
    EXPECT_EQ(v.at(1).second, 4);
    EXPECT_EQ(v.at(2).first->first, "Dos");
    EXPECT_EQ(v.at(2).first->second, 7);
    EXPECT_EQ(v.at(2).second, 7);
}

TEST_F(VectorMapTestAccess, GetValuePos) {
    vmap::mapped_type m = n.get_value(5);

    EXPECT_EQ(m, 5);
}

TEST_F(VectorMapTestAccess, GetValueByKey) {
    std::vector<vmap::mapped_type> v = n.get_value("Dos");

    ASSERT_EQ(v.size(), 1);
    EXPECT_EQ(v.at(0), 2);
}

TEST_F(VectorMapTestAccess, GetValueByKeyByOrd) {
    std::vector<vmap::mapped_type> v = n.get_value("Dos", 2);

    ASSERT_EQ(v.size(), 1);
    EXPECT_EQ(v.at(0), 4);
}

TEST_F(VectorMapTestAccess, GetValueByKeyByOrdByNum) {
    std::vector<vmap::mapped_type> v = n.get_value("Dos", 2, 2);

    ASSERT_EQ(v.size(), 2);
    EXPECT_EQ(v.at(0), 4);
    EXPECT_EQ(v.at(1), 7);
}

TEST_F(VectorMapTestAccess, GetAllValues) {
    std::vector<vmap::mapped_type> v = n.get_all_values("Dos");

    ASSERT_EQ(v.size(), 3);
    EXPECT_EQ(v.at(0), 2);
    EXPECT_EQ(v.at(1), 4);
    EXPECT_EQ(v.at(2), 7);
}

TEST_F(VectorMapTestAccess, GetKeyByPos) {
    EXPECT_EQ(n.get_key(6), "Seis");
}

TEST_F(VectorMapTestAccess, GetPosByKey) {
    std::vector<vmap::size_type> v = n.get_pos("Dos");

    ASSERT_EQ(v.size(), 1);
    EXPECT_EQ(v.at(0), 2);
}

TEST_F(VectorMapTestAccess, GetPosByKeyByOrd) {
    std::vector<vmap::size_type> v = n.get_pos("Dos", 2);

    ASSERT_EQ(v.size(), 1);
    EXPECT_EQ(v.at(0), 4);
}

TEST_F(VectorMapTestAccess, GetPosByKeyByOrdByNum) {
    std::vector<vmap::size_type> v = n.get_pos("Dos", 2, 2);

    ASSERT_EQ(v.size(), 2);
    EXPECT_EQ(v.at(0), 4);
    EXPECT_EQ(v.at(1), 7);

    v.clear();
    v = n.get_pos("Dos", 2, 3);
    ASSERT_EQ(v.size(), 2);
    EXPECT_EQ(v.at(0), 4);
    EXPECT_EQ(v.at(1), 7);


    std::cerr << "\033[0;32m" << "[          ] " << "\033[0;0m" << "Hola" << std::endl;
    v.clear();
    v = n.get_pos("Dos", 4, 3);
    ASSERT_EQ(v.size(), 0);
}

TEST_F(VectorMapTestAccess, GetAllPos) {
    std::vector<vmap::size_type> v = n.get_all_pos("Dos");

    ASSERT_EQ(v.size(), 3);
    EXPECT_EQ(v.at(0), 2);
    EXPECT_EQ(v.at(1), 4);
    EXPECT_EQ(v.at(2), 7);
}
