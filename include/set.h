#ifndef __SET_H__
#define __SET_H__

#include <node.h>

using t_count = int;

template<class T>
class Set
{

    mstd::ptr< Node<T> > head;
    t_count _size;

public:

    Set(): head(nullptr), _size(0) {}

    Set(T value): head(value), _size(1) {}

    Set(const Set<T>& other) = delete;

    void insert(T value)
    {
        try
        {
            ptr< Node<T> > search(_insert(head));
            search = mstd::make_Node(value);
            ++_size;
        }
        catch(...)
        {
        }
    }

private:
    ptr< Node<T> >& _insert(T value, ptr< Node<T> >& node)
    {
        if(! node)
            return node;
        else if(node->value() > value)
        {
            return _insert(value, node->left());
        }
        else if(node->value() < value)
        {
            return _insert(value, node->rights());
        }
        throw "asd";
    }

public:

};

#endif