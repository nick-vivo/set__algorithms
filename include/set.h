#ifndef __SET_H__
#define __SET_H__

#include <node.h>

using t_count = int;

template<class T>
class Set
{

    mstd::shared_ptr< Node<T> > head;
    t_count _size;

public:

    Set(): head(nullptr), _size(0) {}

    Set(T value): head( mstd::make_Node(value) ), _size(1) {}

    Set(const Set<T>& other) = delete;

    

};

#endif