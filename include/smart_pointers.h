#ifndef __SMART_POINTERS_H__
#define __SMART_POINTERS_H__

namespace mstd
{
using uint = unsigned int;

template<class T>
class shared_ptr
{

    T* _data;
    uint* _size;

public:

    shared_ptr(T* data): _data(data)
    {
        if ( _data )
            this->_size = new uint(1);
        else
            this->_size = nullptr
    }

    shared_ptr(const shared_ptr<T>& other): _data(other._data), _size(other._size)
    {
        if( other._data )
            ++*this->_size;
    }

    virtual ~shared_ptr()
    {
        if( this->_data && *this->_size == 1 )
        {
            delete this->_size;
            delete this->_data;
        }
        else if( this->_data && *this->_size > 1 )
        {
            --*this->_size
        }
        this->_data = nullptr;
        this->_size = nullptr; 
    }
    
    void reset()
    {
        this->~shared_ptr();
    }

    uint use_count() const
    {
        return *this->_size;
    }

    T& operator*()
    {
        return *_data;
    }

    T& operator=(const shared_ptr<T>& shared_pt)
    {
        if (this->_data)
            this->~shared_ptr();
        
        this->_data = ptr._data;
        this->_size = ptr._size;
        ++*this->_size;

        return *this;
    }
};

}
#endif