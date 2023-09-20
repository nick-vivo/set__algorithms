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
    set<int> A;

    A.insert(0);
    A.insert(12);
    A.insert(30);
    
    A.insert(0);
    A.insert(12);
    A.insert(30);
    
    ASSERT_EQ(A[0], 0);
    ASSERT_EQ(A[1], 12);
    ASSERT_EQ(A[2], 30);

    ASSERT_EQ(A.is_value(0), true);
    ASSERT_EQ(A.is_value(12), true);
    ASSERT_EQ(A.is_value(30), true);
    ASSERT_EQ(A.is_value(31), false);

    ASSERT_EQ(A.size(), 3);
    ASSERT_ANY_THROW(A[3]);

    A.rm(2);
    ASSERT_EQ(A.is_value(0), true);
    ASSERT_EQ(A.is_value(12), true);
    ASSERT_EQ(A.is_value(30), false);
    ASSERT_EQ(A.size(), 2);

    ASSERT_EQ(A[0], 0);
    ASSERT_EQ(A[1], 12);
    ASSERT_ANY_THROW(A[2]);

    A.insert(-3);
    ASSERT_EQ(A.is_value(0), true);
    ASSERT_EQ(A.is_value(12), true);
    ASSERT_EQ(A.is_value(-3), true);
    ASSERT_EQ(A.size(), 3);

    ASSERT_EQ(A[0], -3);
    ASSERT_EQ(A[1], 0);
    ASSERT_EQ(A[2], 12);
    ASSERT_ANY_THROW(A[3]);

    A.rm_value(-3);
    ASSERT_EQ(A.is_value(0), true);
    ASSERT_EQ(A.is_value(12), true);
    ASSERT_EQ(A.is_value(-3), false);
    ASSERT_EQ(A.size(), 2);

    ASSERT_EQ(A[0], 0);
    ASSERT_EQ(A[1], 12);
    ASSERT_ANY_THROW(A[2]);


    A.insert(1);
    A.insert(3);

    ASSERT_EQ(A[0], 0);
    ASSERT_EQ(A[1], 1);
    ASSERT_EQ(A[2], 3);
    ASSERT_EQ(A[3], 12);

    set<int> B;

    B.insert(2);
    B.insert(3);
    B.insert(4);
    B.insert(5);
    B.insert(12);

    set<int> C = A.intersection(B);
    ASSERT_EQ(C[0], 3);
    ASSERT_EQ(C[1], 12);
    ASSERT_ANY_THROW(C[2]);
    ASSERT_EQ(C.size(), 2);

    A.swap(B);
    
    ASSERT_EQ(B[0], 0);
    ASSERT_EQ(B[1], 1);
    ASSERT_EQ(B[2], 3);
    ASSERT_EQ(B[3], 12);

    ASSERT_EQ(A[0], 2);
    ASSERT_EQ(A[1], 3);
    ASSERT_EQ(A[2], 4);
    ASSERT_EQ(A[3], 5);
    ASSERT_EQ(A[4], 12);
}

TEST(operators, All)
{
    set<int> A;

    A.insert(0);
    A.insert(12);
    A.insert(30);

    set<int> B;

    B.insert(2);
    B.insert(3);
    B.insert(4);
    B.insert(5);
    B.insert(12);

    set<int> C = A + B;

    ASSERT_EQ(C[0], 0);
    ASSERT_EQ(C[1], 2);
    ASSERT_EQ(C[2], 3);
    ASSERT_EQ(C[3], 4);
    ASSERT_EQ(C[4], 5);
    ASSERT_EQ(C[5], 12); 
    ASSERT_EQ(C[6], 30);

    ASSERT_EQ(C.size(), 7);

    set<int> M = A - B;
    ASSERT_EQ(M[0], 0);
    ASSERT_EQ(M[1], 30);

    C -= 0;
    ASSERT_EQ(C[0], 2);
    ASSERT_EQ(C[1], 3);
    ASSERT_EQ(C[2], 4);
    ASSERT_EQ(C[3], 5);
    ASSERT_EQ(C[4], 12); 
    ASSERT_EQ(C[5], 30);

    C += 0;
    ASSERT_EQ(C[0], 0);
    ASSERT_EQ(C[1], 2);
    ASSERT_EQ(C[2], 3);
    ASSERT_EQ(C[3], 4);
    ASSERT_EQ(C[4], 5);
    ASSERT_EQ(C[5], 12); 
    ASSERT_EQ(C[6], 30);

    set<int> T = 4 + A;
    ASSERT_EQ(T[0], 0);
    ASSERT_EQ(T[1], 4);
    ASSERT_EQ(T[2], 12);
    ASSERT_EQ(T[3], 30);

    set<int> T_2 = A - 12;
    ASSERT_EQ(T_2[0], 0);
    ASSERT_EQ(T_2[1], 30);
}