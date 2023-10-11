#ifndef __SET_HH__
#define __SET_HH__

#include <set.h>
#include <exception.h>
#include <initializer_list>
#include <random>
#include <string>
#include <utility>

template<class T>
class set: public mstd::Set<T>
{
    using t_size = int;
public:
    set(): mstd::Set<T>() {}

    set(T* arr,  t_size size): mstd::Set<T>()
    {
        if ( !arr || size < 0 )
        {
            throw mstd::exception("Bad index");
        }

        for (t_size i = 0; i < size; ++i)
        {
            this->insert( arr[i] );
        }
    }

    set(std::initializer_list<T> b): mstd::Set<T>(b)
    {
    }

    set(t_size size, T min, T max): mstd::Set<T>() 
    {}

    T operator[](t_size i)
    {
        mstd::List<T> ls = this->get_list();

        return ls.at(i);
    }

    set<T> operator+( set<T>& other )
    {
        set<T> sum( *this );
        
        mstd::List<T> ot = other.get_list();

        for (t_size i = 0; i < ot.size(); ++i)
        {
            sum.insert( ot.at(i) );
        }

        return sum;
    }

    set<T> operator-( set<T>& other )
    {
        set<T> sum( *this );
        
        mstd::List<T> ot = other.get_list();

        for (t_size i = 0; i < ot.size(); ++i)
        {
            sum.erase( ot.at(i) );
        }

        return sum;
    }

    set<T>& operator+=( T value )
    {
        this->insert(value);
        return *this;
    }

    set<T>& operator-=(T value)
    {
        this->erase(value);
        return *this;
    }

    set<T> intersection( set<T>& other )
    {
        set<T> tmp = *this - other;

        set<T> inter = *this - tmp;

        return inter;
    }

    bool is(T value)
    {
        mstd::List<T> ls = this->get_list();

        for (t_size i = 0; i < ls.size(); ++i)
        {
            if( ls.at(i) == value )
                return true;
        }

        return false;
    }
};

template<class T>
set<T> operator+(const set<T> set_for, T value)
{
    set<T> sum = set_for;

    sum.insert(value);

    return sum;
}

template<class T>
set<T> operator+(T value, const set<T> set_for)
{
    set<T> sum = set_for;

    sum.insert(value);

    return sum;
}

template<class T>
set<T> operator-(const set<T> set_for, T value)
{
    set<T> sum = set_for;

    sum.erase(value);

    return sum;
}


// мини мусор, который следовало бы поместить в set.cc

template<>
set<double>::set(t_size size, double min, double max): mstd::Set<double>() 
{
    if (size < 0 || min >= max)
    {
        throw mstd::exception("Bad size");
    }

    std::random_device rd;

    std::mt19937 gen( rd() );

    std::uniform_real_distribution<double> dist(min, max);

    for (t_size i = 0; i < size; ++i)
    {
        double randomV = dist(gen);
        this->insert(randomV);
    }
}

template<>
set<int>::set(t_size size, int min, int max): mstd::Set<int>() 
{
    if (size < 0 || min >= max)
    {
        throw mstd::exception("Bad size");
    }

    std::random_device rd;

    std::mt19937 gen( rd() );

    std::uniform_int_distribution<int> dist(min, max);

    for (t_size i = 0; i < size; ++i)
    {
        int randomV = dist(gen);
        this->insert(randomV);
    }
}

#define EPS 0.01
template<>
bool mstd::Set<double>::operator==(const mstd::Set<double> other)
{
    if (this->size() != other.size())
    {
        return false;
    }

    mstd::List<double> ls1 = this->get_list();
    mstd::List<double> ls2 = other.get_list();

    for (t_size i = 0; i < ls1.size(); ++i)
    {
        if ( fabs(ls1[i] - ls2[i]) > EPS)
        {
            return false;
        }
    }
    return true;
}

template<>
set<std::string>::set(t_size size, std::string min, std::string max): mstd::Set<std::string>() 
{

    if (size < 0 || min.size() >= max.size() )
    {
        throw mstd::exception("Bad size");
    }

    static const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<int> dist(0, sizeof(charset) - 2);
    static std::uniform_int_distribution<int> dist_2(min.size() , max.size() );
    

    std::string randomString;
    randomString.reserve( max.size() );

    for(t_size i = 0; i < size; ++i)
    {

    for (int i = 0; i < dist_2(gen); ++i) {
        randomString += charset[dist(gen)];
    }
    this->insert(randomString);
    randomString = "";
    }
}

template<>
set< std::pair<int, double> >::set(t_size size, std::pair<int, double> min, std::pair<int, double> max): mstd::Set<std::pair<int, double>>()
{
    if (size < 0 || min.first >= max.first || min.second >= max.second)
    {
        throw mstd::exception("Bad size");
    }

    std::random_device rd;

    std::mt19937 gen( rd() );

    std::uniform_int_distribution<int> dist(min.first, max.first);

    std::uniform_real_distribution<double> dist_2(min.second, max.second);

    for(t_size i = 0; i < size; ++i)
    {
        std::pair pa(dist(gen), dist_2(gen));
        this->insert( pa );
    }
}

#endif