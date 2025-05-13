#include <gtest.h>
#include "avl_tree.h"

TEST(AvlTreeTest, can_create_avl_tree)
{
    ASSERT_NO_THROW(AvlTree<int> M);
}

TEST(AvlTreeTest, can_insert_elem)
{
    AvlTree<int> M;
    EXPECT_TRUE(M.insert(1, 8));
}

TEST(AvlTreeTest, cant_insert_elem_with_non_unique_key)
{
    AvlTree<int> M;
    M.insert(1, 8);
    EXPECT_FALSE(M.insert(1, 16));
}

TEST(AvlTreeTest, can_find_elem) 
{
    AvlTree<int> M;
    M.insert(1, 8);
    EXPECT_FALSE(M.find(1) == nullptr);
    EXPECT_TRUE(M.find(2) == nullptr);
}

TEST(AvlTreeTest, cant_find_non_exist_elem) 
{
    AvlTree<int> M;
    EXPECT_TRUE(M.find(8) == nullptr);
}

TEST(AvlTreeTest, can_erase_elem) 
{
    AvlTree<int> M;
    M.insert(1, 8);
    M.erase(1);
    EXPECT_TRUE(M.find(1) == nullptr);
}

TEST(AvlTreeTest, cant_erase_non_exist_elem)
{
    AvlTree<int> M;
    EXPECT_FALSE(M.erase(8));
}

TEST(AvlTreeTest, balancing_works_correctly) 
{
    AvlTree<int> M;
    for (size_t i = 1; i < 11; ++i) 
    {
        M.insert(i, 8);
    }
    auto root = M.get_root();
    EXPECT_LE(abs(M.get_height(root->get_left()) - M.get_height(root->get_right())), 1);
}

TEST(AvlTreeTest, can_rotate_right) 
{
    AvlTree<int> M;
    M.insert(3, 8);
    M.insert(2, 16);
    M.insert(1, 24);

    auto root = M.get_root();
    EXPECT_EQ(root->get_left()->get_data(), 24);
    EXPECT_EQ(root->get_right()->get_data(), 8);
}

TEST(AvlTreeTest, can_rotate_left)
{
    AvlTree<int> M;
    M.insert(1, 8);
    M.insert(2, 16);
    M.insert(3, 24);

    auto root = M.get_root();
    EXPECT_EQ(root->get_left()->get_data(), 8);
    EXPECT_EQ(root->get_right()->get_data(), 24);
}

TEST(AvlTreeTest, can_rotate_left_right)
{
    AvlTree<int> M;
    M.insert(3, 8);
    M.insert(1, 16);
    M.insert(2, 24);

    auto root = M.get_root();
    EXPECT_EQ(root->get_left()->get_data(), 16);
    EXPECT_EQ(root->get_right()->get_data(), 8);
}

TEST(AvlTreeTest, can_rotate_right_left)
{
    AvlTree<int> M;
    M.insert(1, 8);
    M.insert(3, 16);
    M.insert(2, 24);

    auto root = M.get_root();
    EXPECT_EQ(root->get_left()->get_data(), 8);
    EXPECT_EQ(root->get_right()->get_data(), 16);
}