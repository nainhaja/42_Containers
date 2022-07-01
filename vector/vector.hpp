#include <iostream>
#include <memory.h>
#include "../iterator/iterator_traits.hpp"
#include "../iterator/random_access_iterator.hpp"
#include "../iterator/reverse_iterator.hpp"


#pragma once

namespace ft
{
    template < class T, class Alloc = std::allocator<T> >
    class vector
    {
        public:
            typedef T                                            value_type;
            typedef Alloc                                        allocator_type;

            typedef ft::random_access_iterator<value_type>       iterator;
            typedef ft::random_access_iterator<const value_type> const_iterator;

            typedef ft::reverse_iterator<iterator>               reverse_iterator;
            typedef ft::reverse_iterator<const_iterator>         const_reverse_iterator;


            typedef typename ft::iterator_traits<iterator>::difference_type difference_type;

            typedef size_t                                       size_type;

            typedef typename allocator_type::pointer             pointer;
            typedef typename allocator_type::const_pointer       const_pointer;
            typedef typename allocator_type::reference           reference;
            typedef typename allocator_type::const_reference     const_reference;

            explicit vector(const allocator_type& alloc = allocator_type()) : _size(0), _capacity(0), _data(nullptr),_alloc(alloc)  {};
            explicit vector(size_type n, const value_type& val = value_type(),
                 const allocator_type& alloc = allocator_type()) : _size(n), _alloc(alloc), _data(val) {};
            vector (const vector& x) : _capacity(x.capacity()), _size(x.size()), _alloc(x._alloc) {};
            

            /*---------------------------ITERATORS-------------------*/
            iterator            begin() {return iterator(_data);}
            const_iterator      begin() const {return const_iterator(_data);}
            reverse_iterator    rbegin() {return reverse_iterator(_data);}
            const_iterator      rbegin() const {return const_reverse_iterator(_data);}

            /*---------------------------ITERATORS-------------------*/
            
            size_type size() {return _size;}
            size_type capacity() {return _capacity;}
            
            void    swap(vector &x)
            {
                size_type tmp = _size;
                _size = x._size;
                x._size = tmp;

                tmp = _capacity;
                _capacity = x._capacity;
                x._capacity = tmp;

                value_type *another_tmp = _data;
                _data = x._data;
                x._data = another_tmp;
            }

            void    clear()
            {
                for(int i=0; i < _size ; i++)
                    _alloc.destroy(_data + i);
                _size = 0;
            }
            
            reference front()
            {
                return _data[0];
            }
        
            const_reference front() const
            {
                return _data[0];
            }

            reference back()
            {
                if (_size != 0)
                    return _data[_size - 1];
                return nullptr;
            }
            const_reference back() const
            {
                if (_size != 0)
                    return _data[_size - 1];
                return nullptr;
            }

            reference at (size_type n)
            {
                if (n > _size)
                    throw std::out_of_range("Out of range");
                return _data[n];
            }
            const_reference at (size_type n) const
            {
                if (n > _size)
                    throw std::out_of_range("Out of range");
                return _data[n];
            }

            reference operator[] (size_type n)
            {
                return _data[n];
            }
            const_reference operator[] (size_type n) const
            {
                return _data[n];
            }

            allocator_type get_allocator() const
            {
                allocator_type my_copy(_alloc);
                return my_copy;
            }

            bool empty() const
            {
                if (_size == 0)
                    return true;
                return false;
            }


            virtual ~vector() {};
        
        private:
            size_type       _capacity;
            size_type       _size;
            allocator_type  _alloc;
            value_type      *_data;
            //vector &operator=(vector const & t)
    };

}