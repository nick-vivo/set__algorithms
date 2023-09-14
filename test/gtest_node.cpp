#include <node.h>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

TEST(node, all)
{
    mstd::Node<int> a(40);

    ASSERT_EQ(a.value(), 40);
    ASSERT_TRUE(a.isLeaf());

    a.left() = mstd::make_Node(10);

    ASSERT_EQ(a.value(), 40);
    ASSERT_EQ(a.left()->value(), 10);
    ASSERT_FALSE(a.isLeaf());
    ASSERT_TRUE(a.left()->isLeaf());

    a.right() = mstd::make_Node<int>(2, nullptr, nullptr);
    ASSERT_EQ(a.value(), 40);
    ASSERT_EQ(a.left()->value(), 10);
    ASSERT_FALSE(a.isLeaf());
    ASSERT_TRUE(a.left()->isLeaf());

    ASSERT_EQ(a.right()->value(), 2);
    ASSERT_FALSE(a.isLeaf());
    ASSERT_TRUE(a.right()->isLeaf());

}