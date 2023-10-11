#include <set.hh>
#include <iostream>
#include <string>
#include <cmath>

std::ostream& operator<<(std::ostream& stream, std::pair<int, double> pa)
{
    stream << "k:" << pa.first << " v:"<< pa.second; 
    return stream;
}

template<class T>
std::ostream& operator<<(std::ostream& stream, set<T> se)
{
    mstd::List<T> ls = se.get_list();
    
    stream << "\nSet: { |";

    for (mstd::t_size i = 0; i < ls.size(); ++i)
    {
        stream << ls.at(i) << " | ";
    }

    stream << " }\n";

    return stream;
}


int main()
{
    //Массивы я ввёл как inter  

    //Для демонстрации рандомных ключей  
    set< std::pair<int, double> > se(10, std::pair<int, double>(2, 8.6), std::pair<int, double>(20, 9.8) );


    //Для демонстрации рандомных стрингов
    set<std::string> se_2(10, "123", "12345");

    //Для демонстрации рандомных int  и double
    set<int> se_3(10, 0, 10);

    set<double> se_4(10, 6, 30);

    std::cout << se;

    std::cout << se_2;

    std::cout << se_3;
    std::cout << se_4;

    //Для демонстрации оператора равенства с заданным EPS

    std::cout << "\n\n\n";

    set< double > s1 = {1.2346, 1.23};
    set< double > s2 = {1.2346, 1.23};

    std::cout << "Вывод: " << s1.operator==(s2) ;

    set< std::string > str1 = {"str", "abs", "karla"};

    set< std::string > str2 = {"str", "abs", "chopchik"};

    set< std::string > s = str1.intersection(str2);

    if (!s.empty())
    {
        std::cout << "\n" << "Хотя бы раз встречается" << "\n";
    }
    else
    {
        std::cout << "\n" << "Не встречается" << "\n";
    }

    std::cout << s;

    // set< std::string > sum = str1 - str2;

    // std::cout << sum;

    // std::cout << "\n" << sum[0];

}