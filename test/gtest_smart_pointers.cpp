#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <smart_pointers.h>

TEST(smart_pointers, All)
{

    mstd::shared_ptr<int> a( new int(10) );
    
    ASSERT_EQ(*a, 10);
    ASSERT_EQ(a.use_count(), 1);
    
    *a = 11;
    ASSERT_EQ(*a, 11);
    ASSERT_EQ(a.use_count(), 1);

    mstd::shared_ptr b(a);
    ASSERT_EQ(*b, 11);
    ASSERT_EQ(b.use_count(), 2);


    ASSERT_EQ(*a, 11);
    ASSERT_EQ(a.use_count(), 2);

    b.reset();
    ASSERT_EQ(*a, 11);
    ASSERT_EQ(a.use_count(), 1);

    b = a; 
    ASSERT_EQ(*a, 11);
    ASSERT_EQ(a.use_count(), 2);
    ASSERT_EQ(*b, 11);
    ASSERT_EQ(b.use_count(), 2);

    b.reset(new int(2));
    ASSERT_EQ(*a, 11);
    ASSERT_EQ(a.use_count(), 1);
    ASSERT_EQ(*b, 2);
    ASSERT_EQ(b.use_count(), 1);

    mstd::shared_ptr<int> null;

    null = a;
    ASSERT_EQ(*a, 11);
    ASSERT_EQ(a.use_count(), 2);
    ASSERT_EQ(*null, 11);
    ASSERT_EQ(null.use_count(), 2);

    ASSERT_TRUE(null);
    null = nullptr;
    ASSERT_FALSE(null);

    struct mol
    {
        int a = 3;
        int b = 4;
        int c = 5;
    };

    mstd::shared_ptr<mol> MOOL(new mol);

    MOOL->a = 4;
    ASSERT_EQ(MOOL->a, 4);

    null = a;

    ASSERT_TRUE(null == a);
    ASSERT_FALSE(null == b);

    ASSERT_TRUE(null != b);
    ASSERT_FALSE(null != a);

}
