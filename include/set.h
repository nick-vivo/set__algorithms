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

    Set(): head(nullptr), _size(0) {}

    Set(T value): head( mstd::make_Node(value) ), _size(1) {}

    Set(const Set<T>& other): head(nullptr), _size(0)
    {
        mstd::vector<T> vec = get_vector();
        
        for (t_count i = 0; i < vec.size(); ++i)
        {
            this->insert( vec.at(i) );
        }
    };

    virtual ~Set() {}

    void insert(T value)
    {
        if ( !head )
        {
            head = mstd::make_Node(value);
            
            return;
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

    mstd::vector<T> get_vector()
    {
        mstd::vector<T> vec;
        _get_set_in_vector(head, vec);
        return vec;
    }

private:

    void _get_set_in_vector(mstd::ptr< mstd::Node<T> > node, mstd::vector<T>& vec)
    {
        if( node )
        {
            _get_set_in_vector(node->right(), vec);
            vec.push_back(node->value());
            _get_set_in_vector(node->left(), vec);
        }
    }

public:

    void rm(t_count index)
    {
        mstd::vector<T> save_content( this->get_vector() );

        this->head = nullptr;

        for(t_count i = 0; i < save_content.size(); ++i)
        {
            if (i != index)
                this->insert(save_content.at(i));
        }
    }

    void rm_value(T value)
    {
        for(t_count i = 0; i < this->_size;)
        {
            if (this->operator[](i) == value)
            {
                this->rm(i);
                continue;
            }
            ++i;
        }
    }

    t_count size()
    {
        return this->_size;

    }

    bool is_value(T value)
    {
        mstd::vector<T> vec = this->get_vector();
        
        for(t_count i = 0; i < vec.size(); ++i)
        {
            if (vec.at(i) == value)
                return true;
        }
        return false;
    }

    Set<T> operator+( Set<T>& other )
    {
        mstd::vector<T> a = this->get_vector();
        mstd::vector<T> b = other.get_vector();

        Set<T> set;

        for (t_count i = 0; i < a.size(); ++i)
        {
            set.insert( a.at(i) );
        }
        for (t_count i = 0; i < b.size(); ++i)
        {
            set.insert( b.at(i) );
        }
        return set;
    }

    Set<T> operator-( const Set<T>& other )
    {
        mstd::vector<T> b = other.get_vector();
        mstd::vector<T> c;

        Set<T> set(*this);

        for (t_count i = 0; i < b.size(); ++i)
        {
            if ( this->is_value(b.at(i)) )
                set.rm_value(b.at(i));
        }

        return set;
    }

    T operator[](t_count index)
    {
        mstd::vector<T> vec = get_vector();

        return vec.at(index);
    }
};

// template<class T>
// class Set_range: public Set<T>
// {

//     mstd::shared_ptr<T> _max_range;
//     mstd::shared_ptr<T> _min_range;
//     mstd::shared_ptr<t_count> _max_size;
//     bool range;

// public:
//     Set_range(): Set<T>(), _max_range(nullptr), _min_range(nullptr), _max_size(nullptr), range(false) {}

//     Set_range(const T* array, t_count size): Set<T>(), _max_range(nullptr), _min_range(nullptr), _max_size(nullptr), range(false)
//     {
//         for(t_count i = 0; i < size; ++i)
//         {
//             this->insert( *(array + i) );
//         }
//     }

//     Set_range(t_count size, T min_range, T max_range): range(true), Set<T>()
//     {
//         if (size < 0)
//         {
//             throw "fail";
//         }
//         if (min_range > max_range)
//         {
//             T cp = min_range;
//             min_range = max_range;
//             max_range = cp;
//         }
//         this->_max_range( new T( max_range ) );
//         this->_min_range( new T(min_range) ); 
//     }

//    Set_range<T> operator+( Set_range<T>& other )
//     {
//         mstd::vector<T> a = this->get_vector();
//         mstd::vector<T> b = other.get_vector();

//         Set_range<T> set;

//         for (t_count i = 0; i < a.size(); ++i)
//         {
//             set.insert( a.at(i) );
//         }
//         for (t_count i = 0; i < b.size(); ++i)
//         {
//             set.insert( b.at(i) );
//         }
//         return set;
//     }

//     Set_range<T> operator-( Set_range<T>& other )
//     {
//         mstd::vector<T> b = other.get_vector();
//         mstd::vector<T> c;

//         Set_range<T> set(*this);

//         for (t_count i = 0; i < b.size(); ++i)
//         {
//             if ( this->is_value(b.at(i)) )
//                 set.rm_value(b.at(i));
//         }

//         return set;
//     }

//     Set_range<T>& operator+=(T value)
//     {
//         if(range && (this->size() + 1 <= this->_max_size))
//         {
//             if (this->_min_range.operator*() <= value && value <= this->_max_range.operator*())
//             {
//                 this->insert(value);    
//             }
//         }
//         else
//         {
//             this->insert(value);
//         }
//         return *this;
//     }

//     Set_range<T> operator-(T value)
//     {
//         Set_range<T> set(*this);

//         set.rm_value(value);

//         return set;
//     }

//     Set_range<T>& operator-=(T value)
//     {
//         this->rm_value(value);
//     }

//     Set_range<T> peresechenue(const Set_range<T>& other)
//     {
//         Set_range<T> set;


//         for (t_count i = 0; i < this->size(); ++i)
//         {
//             if ( this->is_value( other[i] ) )
//                 set.insert(other);
//         }
        
//         return set;
//     }


// };


#endif