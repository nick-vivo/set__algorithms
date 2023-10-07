#include <set.hh>
#include <iostream>

int main()
{
    set<int> se;

    se += 1;

    se += 2;

    set<int> se_2;

    se_2 += 3;

    set<int> s = se + se_2;

    mstd::List<int> ls(s.get_list());

    std::cout << ls[0] << ":" << ls[1]; 

}