#ifndef __SET_H__
#define __SET_H__

#include <node.h>
#include <vector.h>
#include <exception.h>

namespace mstd
{

using t_count = int;

template<class T>
using ptr = shared_ptr<T>;

template<class T>
class Set
{

    mstd::shared_ptr< mstd::Node<T> > head;
    t_count _size;

public:

//Конструктор по умолчанию создаёт пустое множество
    Set();

    Set(T value);

//Конструктор с параметрами: массив значений для заполнения
    Set(T* array, t_count size);

    Set(Set<T>& other);

    virtual ~Set() {}

    void insert(T value);

private:
    
    mstd::ptr< mstd::Node<T> > _inspect(T value, mstd::ptr< mstd::Node<T> > node);

public:

    mstd::vector<T> get_vector();

private:

    void _get_set_in_vector(mstd::ptr< mstd::Node<T> > node, mstd::vector<T>& vec);

public:

    void rm(t_count index);

    void rm_value(T value);

    t_count size();

private:

    ptr< Node<T> > _search(T value);

public:

//Функция проверки наличия числа во множестве
    bool is_value(T value);

//Вычисление пересечения двух множеств;
    Set<T> intersection(Set<T>& other);

//operators

//Оператор [] для получения числа по его индексу
    T operator[](t_count index);

//Операторы + (объединения) и - (разности) множеств;
    Set<T> operator+(Set<T>& other);

    Set<T> operator-(Set<T>& other);

//Операторы сложения и вычитания множества с числом;
    
    Set<T>& operator+=(T value);
    
    Set<T>& operator-=(T value);

};

//Дополнительные операторы + и - с числом;
template<class T>
Set<T> operator+(Set<T>& set, T value)
{
    Set<T> copy(set);

    copy.insert(value);

    return copy;
}

template<class T>
Set<T> operator+(T value, Set<T>& set)
{
    Set<T> copy(set);

    copy.insert(value);

    return copy;
}

template<class T>
Set<T> operator-(Set<T>& set, T value)
{
    Set<T> copy(set);

    copy.rm_value(value);

    return copy;
}

template<class T>
Set<T> operator-(T value, Set<T>& set)
{
    Set<T> copy(set);

    copy.rm_value(value);

    return copy;
}


//code

template <class T>
Set<T>::Set() : head(nullptr), _size(0) {}

template <class T>
Set<T>::Set(T value) : head(mstd::make_Node(value)), _size(1) {}

template <class T>
Set<T>::Set(T *array, t_count size) : _size(0)
{
    for (t_count i = 0; i < size; ++i)
    {
        this->insert(array[i]);
    }
}

template <class T>
Set<T>::Set(Set<T> &other): head(nullptr), _size(0)
{
    mstd::vector<T> vec = other.get_vector();

    for (t_count i = 0; i < vec.size(); ++i)
    {
        this->insert(vec.at(i));
    }
}

template <class T>
void Set<T>::insert(T value)
{
    if (!head)
    {
        head = mstd::make_Node(value);
        this->_size = 1;
        return;
    }

    mstd::ptr<mstd::Node<T>> current_node = _inspect(value, head);

    if (value < current_node->value())
    {
        current_node->right() = mstd::make_Node(value);
        ++this->_size;
    }
    else if (value > current_node->value())
    {
        current_node->left() = mstd::make_Node(value);
        ++this->_size;
    }
}

template <class T>
mstd::ptr<mstd::Node<T>> Set<T>::_inspect(T value, mstd::ptr<mstd::Node<T>> node)
{
    if (value < node->value())
    {
        if ( node->right() )
            node = _inspect( value, node->right() );
    }
    else if ( value > node->value() )
    {
        if ( node->left() )
            node = _inspect( value, node->left() );
    }
    
    return node;
}

template <class T>
mstd::vector<T> Set<T>::get_vector()
{
    mstd::vector<T> vec;
    _get_set_in_vector(head, vec);
    return vec;
}

template <class T>
void Set<T>::_get_set_in_vector(mstd::ptr<mstd::Node<T>> node, mstd::vector<T> &vec)
{
    if (node)
    {
        _get_set_in_vector(node->right(), vec);
        vec.push_back(node->value());
        _get_set_in_vector(node->left(), vec);
    }
}

template <class T>
void Set<T>::rm(t_count index)
{
    mstd::vector<T> save_content(this->get_vector());

    this->head = nullptr;

    for (t_count i = 0; i < save_content.size(); ++i)
    {
        if (i != index)
            this->insert(save_content.at(i));
    }
}

template <class T>
void Set<T>::rm_value(T value)
{
    if (this->is_value(value))
    {
        mstd::vector<T> save_content(this->get_vector());

        this->head = nullptr;

        for (t_count i = 0; i < save_content.size(); ++i)
        {
            if (save_content.at(i) != value)
                this->insert(save_content.at(i));
        }
    }
}

template <class T>
t_count Set<T>::size()
{
    return this->_size;
}

template<class T>
ptr< Node<T> > Set<T>::_search(T value)
{
    ptr< Node<T> > node = this->_inspect(value, head);

    if ( value == node->value() )
    {
        return node;
    }
    return nullptr;

}

template<class T>
bool Set<T>::is_value(T value)
{
    if(this->_search(value))
        return true;
    return false;
}

template <class T>
Set<T> Set<T>::intersection(Set<T> &other)
{
    vector<T> vector_other = other.get_vector();

    for (t_count i = 0; i < vector_other.size(); ++i)
    {
        this->rm_value(vector_other.at(i));
    }
}

//operators
template <class T>
T Set<T>::operator[](t_count index)
{
    mstd::vector<T> values = this->get_vector();

    return values.at(index);
}

template<class T>
Set<T> Set<T>::operator+(Set<T> &other)
{
    vector<T> vector_other = other.get_vector();

    for (t_count i = 0; i < vector_other.size(); ++i)
    {
        this->insert(vector_other.at(i));
    }
}

template <class T>
Set<T> Set<T>::operator-(Set<T> &other)
{
    vector<T> vector_other = other.get_vector();

    for (t_count i = 0; i < vector_other.size(); ++i)
    {
        this->rm_value(vector_other.at(i));
    }
}

template <class T>
Set<T> &Set<T>::operator+=(T value)
{
    this->insert(value);

    return *this;
}

template<class T>
Set<T>& Set<T>::operator-=(T value)
{
    this->rm_value(value);

    return *this;
}
}
#endif