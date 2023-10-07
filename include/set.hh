#ifndef __SET_HH__
#define __SET_HH__

#include <set.h>
#include <exception.h>

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
        set<T> inter = *this;

        mstd::List<T> ls = other.get_list();

        for (t_size i = 0; i < ls.size(); ++i)
        {
            inter.erase( ls.at(i) );
        }

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



#endif