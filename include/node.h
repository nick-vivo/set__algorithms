#ifndef __NODE_H__
#define __NODE_H__

#include <memory.h>


namespace mstd
{

template<class T>
class Node
{

    mstd::shared_ptr<T> _value;
    mstd::shared_ptr< Node<T> > _left;
    mstd::shared_ptr< Node<T> > _right;

public:

    Node(): _value(nullptr), _left(nullptr), _right(nullptr) {}

    Node(T value): _value(new T(value)), _left(nullptr), _right(nullptr) {}

    Node(T value, mstd::shared_ptr<Node<T>> left, mstd::shared_ptr<Node<T>> right): _value(new T(value)), _left(left), _right(right) {}

    //Передаёт все значения по указателям, если нужна глубокая копия, нужен соотвествующий метод
    Node(const Node& other): _value(other._value), _left(other._left), _right(other._value) {}

    ~Node() = default;

    bool isLeaf() const noexcept
    {
        return (!_left && !_right);
    }

    T& value() noexcept
    {
        return this->_value.operator*();
    }

    mstd::shared_ptr< Node<T> >& left() noexcept
    {
        return this->_left;
    }

    mstd::shared_ptr< Node<T> >& right() noexcept
    {
        return this->_right;
    }

    Node<T>& operator=(const Node<T>& other) = delete;

};

template<class T>
mstd::shared_ptr< Node<T> > make_Node(T value)
{
    return shared_ptr< Node<T> > (new Node<T>(value));
}

template<class T>
mstd::shared_ptr< Node<T> > make_Node(T value, mstd::shared_ptr< Node<T> > left, mstd::shared_ptr< Node<T> > right)
{
    return shared_ptr< Node<T> > (new Node<T>(value, left, right));
}

}
#endif