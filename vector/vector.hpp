#include <iostream>
#include <memory.h>
#include "../iterator/iterator_traits.hpp"
#include "../iterator/random_access_iterator.hpp"
#include "../iterator/reverse_iterator.hpp"

#include <iostream>     // std::cout



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

            explicit vector(const allocator_type& alloc = allocator_type()) : _size(0), _capacity(0), _data(nullptr),_alloc(alloc)  {}; // vec();
            explicit vector(size_type n, const value_type& val = value_type(),
                 const allocator_type& alloc = allocator_type()) : _size(n), _alloc(alloc), _capacity(n) // vec(size, value)
            {
                _data = _alloc.allocate(n);
                for(size_t i = 0; i < _size ; i++)
                    _alloc.construct(&_data[i], val);

            }
            // template <class InputIterator>
            // vector (InputIterator first, InputIterator last, typename std::enable_if<!std::is_integral<InputIterator>::value, InputIterator>::type = InputIterator() , const allocator_type& alloc = allocator_type()) // vec(begin, end)
            // {
            //     size_t my_distance = std::distance(first, last);
            // }
            vector (const vector& x) : _capacity(x.capacity()), _size(x.size()), _alloc(x._alloc) {};
            

            /*---------------------------ITERATORS-------------------*/
            iterator            begin() {return iterator(_data);}
            const_iterator      begin() const {return const_iterator(_data);}
            iterator            end() {return iterator(_data + _size);}
            const_iterator      end() const {return const_iterator(_data + _size);}
            reverse_iterator    rbegin() {return reverse_iterator(_data);}
            const_iterator      rbegin() const {return const_reverse_iterator(_data);}

            /*---------------------------ITERATORS-------------------*/
            
            size_type size() {return _size;}
            size_type capacity() {return _capacity;}
            
            void resize (size_type n, value_type val = value_type())
            {
                if (n < _size)
                    _size = n;
                if (n > _size)
                {
                    reserve(n);
                    for(size_type i = _size ; i < n; i++)
                        _alloc.construct(&_data[i], val);
                    _size = n;
                }
            }
            iterator insert (iterator position, const value_type& val)
            {
                ptrdiff_t my_position = std::distance(begin(), position);
                if (_size + 1 > _capacity)
                {
                    if (_capacity == 0)
                        reserve(1);
                    else
                        reserve(_capacity * 2);
                }
                for(difference_type i = _size - 1; i >= my_position; i--)
                    _data[i+1] = _data[i];
                _alloc.construct(&_data[my_position], val);
                _size++;
                return (iterator(_data + my_position));
            }

            void insert (iterator position, size_type n, const value_type& val)
            {
                difference_type my_position = std::distance(begin(), position);
                if (_size + n > _capacity)
                {
                    if (n > _size)
                        reserve(_size + n);
                    else if (_capacity == 0)
                        reserve(n);
                    else
                        reserve(_capacity * 2); 
                }
                for(difference_type i = _size - 1; i >= my_position; i--)
                    _alloc.construct(&_data[n + i], _data[i]);
                for(int i=0; i < n;i++)
                    _alloc.construct(&_data[my_position + i], val);
                _size += n;
            }

            // template <class InputIterator>
            // void insert (iterator position, InputIterator first, InputIterator last)
            // {

            // }

            void push_back (const value_type& val)
            {
                if (_size + 1 > _capacity)
                {
                    if (_capacity == 0)
                        reserve(1);
                    else
                        reserve(_capacity * 2);
                }
                _alloc.construct(&_data[_size], val);
                _size++;
            }

            void pop_back()
            {
                if (_size != 0)
                {
                    _alloc.destroy(&_data[_size - 1]);
                    _size--;
                }
            }
            // iterator insert (iterator position, const value_type& val)
            // {

            // }
            void reserve (size_type n)
            {
                if (n > _capacity)
                {
                    value_type *tmp;
                    tmp = _alloc.allocate(n);
                    for(int i =0; i < _size ; i++)
                        _alloc.construct(tmp+i, _data[i]);
                    for(int i =0;i < _size; i++)
                        _alloc.destroy(_data + i);
                    _alloc.deallocate(_data, _capacity);
                    _data = tmp;
                    _capacity = n;
                }
            }
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