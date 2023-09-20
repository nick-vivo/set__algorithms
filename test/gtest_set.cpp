#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <set.h>

template<class T>
using set = mstd::Set<T>;

TEST(Constructors, What)
{
    set<int> A;
    ASSERT_EQ(A.size(), 0);
    ASSERT_ANY_THROW(A[0]);

    set<int> A_cp(A);
    ASSERT_EQ(A_cp.size(), 0);
    ASSERT_ANY_THROW(A_cp[0]);

    set<int> B(0);
    ASSERT_EQ(B.size(), 1);
    ASSERT_EQ(B.is_value(0), true);
    ASSERT_EQ(B.is_value(1), false);
    ASSERT_EQ(B.is_value(-1), false);
    ASSERT_EQ(B[0], 0);
    ASSERT_ANY_THROW(B[-1]);
    ASSERT_ANY_THROW(B[1]);

    auto B_vector = B.get_vector();
    ASSERT_EQ(B_vector.at(0), 0);
    ASSERT_EQ(B_vector.size(), 1);

    set<int> B_cp(B);
    ASSERT_EQ(B_cp.size(), 1);
    ASSERT_EQ(B_cp.is_value(0), true);
    ASSERT_EQ(B_cp.is_value(1), false);
    ASSERT_EQ(B_cp.is_value(-1), false);
    ASSERT_EQ(B_cp[0], 0);
    ASSERT_ANY_THROW(B_cp[-1]);
    ASSERT_ANY_THROW(B_cp[1]);

    auto B_cp_vector = B_cp.get_vector();
    ASSERT_EQ(B_cp_vector.at(0), 0);
    ASSERT_ANY_THROW(B_cp_vector.at(1));
    ASSERT_ANY_THROW(B_cp_vector.at(-1));
    ASSERT_EQ(B_cp_vector.size(), 1);



    int arr[] = {1, 2 ,3};
    set<int> C(arr, 3);
    ASSERT_EQ(C.size(), 3);
    ASSERT_EQ(C.is_value(1), true);
    ASSERT_EQ(C.is_value(2), true);
    ASSERT_EQ(C.is_value(3), true);

    ASSERT_EQ(C.is_value(-1), false);
    ASSERT_EQ(C.is_value(4), false);
    
    ASSERT_EQ(C[0], 1);
    ASSERT_EQ(C[1], 2);
    ASSERT_EQ(C[2], 3);
    ASSERT_ANY_THROW(C[-1]);
    ASSERT_ANY_THROW(C[3]);

    auto C_vector = C.get_vector();
    ASSERT_EQ(C_vector.at(0), 1);
    ASSERT_EQ(C_vector.at(1), 2);
    ASSERT_EQ(C_vector.at(2), 3);
    ASSERT_EQ(C_vector.size(), 3);

    set<int> C_cp(C);
    ASSERT_EQ(C_cp.size(), 3);
    ASSERT_EQ(C_cp.is_value(1), true);
    ASSERT_EQ(C_cp.is_value(2), true);
    ASSERT_EQ(C_cp.is_value(3), true);

    ASSERT_EQ(C_cp.is_value(-1), false);
    ASSERT_EQ(C_cp.is_value(4), false);
    
    ASSERT_EQ(C_cp[0], 1);
    ASSERT_EQ(C_cp[1], 2);
    ASSERT_EQ(C_cp[2], 3);
    ASSERT_ANY_THROW(C_cp[-1]);
    ASSERT_ANY_THROW(C_cp[3]);

    auto C_cp_vector = C.get_vector();
    ASSERT_EQ(C_cp_vector.at(0), 1);
    ASSERT_EQ(C_cp_vector.at(1), 2);
    ASSERT_EQ(C_cp_vector.at(2), 3);
    ASSERT_EQ(C_cp_vector.size(), 3);
}

TEST(methods, All)
{
    
}