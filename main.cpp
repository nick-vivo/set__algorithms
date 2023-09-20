#include <set.h>
#include <iostream>

int main()
{
    int arr_A[] = {1, 2, 3, 4};

    int arr_B[] = {1, 2, 3, 4, 5, 6};

    mstd::Set<int> A(arr_A, 4);
    mstd::Set<int> B(arr_B, 4);

    mstd::Set<int> C = A - B;

    if ( C.is_empty() )
    {
        std::cout << "Все элементы из 1 встречаются во 2";
    }
    else
    {
        std::cout << "Не все элементы из 1 встречаются во 2";
    }

    mstd::Set<int> D(3, 7, 2);

    D.insert(3);
    D.insert(4);
    D.insert(5);
}