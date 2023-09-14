#ifndef __SET_H__
#define __SET_H__

#include <node.h>
#include <array.h>

using t_count = int;

template<class T>
class Set
{
public:
    mstd::shared_ptr< mstd::Node<T> > head;
    t_count _size;

public:

    Set(): head(nullptr), _size(0) {}

    Set(T value): head( mstd::make_Node(value) ), _size(1) {}

    Set(const Set<T>& other) = delete;

    void insert(T value)
    {
        if (head == nullptr)
        {
            head = mstd::make_Node(value);
        }

        mstd::ptr< mstd::Node<T> > current_node =  _inspect(value, head);
        
        if ( value < current_node->value() )
        {
            current_node->right() = mstd::make_Node(value);
            ++this->_size;
        }
        else if( value > current_node->value() )
        {
            current_node->left() = mstd::make_Node(value);
            ++this->_size;
        }
    }

private:
    
    mstd::ptr< mstd::Node<T> > _inspect(T value, mstd::ptr< mstd::Node<T> > node)
    {
        if(value < node->value())
        {
            if ( node->right() )
                node = _inspect(value, node->right() );
        }
        else if(value > node->value())
        {
            if ( node->left() )
                node = _inspect( value, node->left() );
        }
        return node;
    }

public:

    // Array<T> get_array()
    // {
    //     Array<T> array(this->_size);

    //     mstd::ptr< mstd::Node<T> > tmp = this->head;

    //     for(t_size i = 0; i < this->_size; ++i)
    //     {
            
    //     }

    //     tmp = tmp->right();
    // }

};

#endif