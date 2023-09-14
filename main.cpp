#include <set.h>

#include <iostream>

int main()
{
    Set<int> b(4);

    b.insert(5);

    b.insert(2);

    b.insert(1);

    b.insert(3);

    std::cout << b.head->value() << "\n";
    std::cout << b.head->left()->value() << "\n";
    std::cout << b.head->right()->value() << "\n";
    std::cout << b.head->right()->right()->value() << "\n";
    std::cout << b.head->right()->left()->value() << "\n";
}