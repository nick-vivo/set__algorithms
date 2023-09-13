#ifndef __NODE_H__
#define __NODE_H__

#include <smart_pointers.h>

namespace mstd
{

template<class T>
using ptr = mstd::shared_ptr<T>;

template<class T>
class Node
{

    T _value;
    ptr< Node<T> > _left;
    ptr< Node<T> > _right;

public:

    Node(T value): _value(value), _left(nullptr), _right(nullptr) {}

    Node(const Node& other) = delete;

    ~Node() = default;

    bool isLeaf()
    {
        return (!_left && !_right);
    }

    T& value()
    {
        return this->_value;
    }

    ptr< Node<T> >& left()
    {
        return this->_left;
    }

    ptr< Node<T> >& right()
    {
        return this->_right;
    }

    Node<T>& operator=(const Node<T>& other) = delete;

};

}
#endif