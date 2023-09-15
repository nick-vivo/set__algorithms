#ifndef __SET_H__
#define __SET_H__

#include <node.h>
#include <vector.h>

using t_count = int;

template<class T>
class Set
{

    mstd::shared_ptr< mstd::Node<T> > head;
    t_count _size;

public:

    Set();

    Set(T value);

    Set(const Set<T>& other);

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

    t_count size();
};


//code

template <class T>
Set<T>::Set() : head(nullptr), _size(0) {}

template <class T>
Set<T>::Set(T value) : head(mstd::make_Node(value)), _size(1) {}

template <class T>
Set<T>::Set(const Set<T> &other) : head(nullptr), _size(0)
{
    mstd::vector<T> vec = get_vector();

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
        if (node->right())
            node = _inspect(value, node->right());
    }
    else if (value > node->value())
    {
        if (node->left())
            node = _inspect(value, node->left());
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
t_count Set<T>::size()
{
    return this->_size;
}

#endif