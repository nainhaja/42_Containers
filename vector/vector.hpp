#include <iostream>
#include <memory.h>
#include "../iterator/iterator_traits.hpp"
#include "../iterator/random_access_iterator.hpp"
#include "../iterator/reverse_iterator.hpp"

#include <iostream>     // std::cout
#include "../enable_if.hpp"
#include "../is_integral.hpp"
#include "../equal.hpp"

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

            explicit vector(const allocator_type& alloc = allocator_type()) :  _capacity(0),_size(0),_alloc(alloc), _data(nullptr)  {}; // vec();
            explicit vector(size_type n, const value_type& val = value_type(),
                 const allocator_type& alloc = allocator_type()) :  _capacity(n), _size(n), _alloc(alloc) // vec(size, value)
            {
                _data = _alloc.allocate(n);
                for(size_t i = 0; i < _size ; i++)
                    _alloc.construct(&_data[i], val);
            }
            template <class InputIterator>
            vector (InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = InputIterator() , const allocator_type& alloc = allocator_type()):_alloc(alloc) // vec(begin, end)
            {
                size_t my_distance = std::distance(first, last);
                
                _data = _alloc.allocate(my_distance);
                for(size_t i = 0; i < my_distance ; i++)
                {
                    _alloc.construct(&_data[i], *first);
                    first++;
                }
                _capacity = my_distance;
                _size = my_distance;
                   
            }
            vector (const vector& x) : _capacity(x.capacity()), _size(x.size()), _alloc(x._alloc)
            {
                _data = _alloc.allocate(_capacity);
                for(size_type i = 0;i < _size;i++)
                    _alloc.construct(&_data[i], x._data[i]);
            }
            
            vector& operator= (const vector& x)
            {
                
                _alloc = x.get_allocator();
                if (!_data)
                {
                    _data = _alloc.allocate(x._capacity);
                    for(size_t i=0;i< x._size;i++)
                    {
                        _alloc.construct(&_data[i], x._data[i]);
                    }
                    _capacity = x._capacity;
                    _size = x._size;
                    return *this;
                }
                if (_capacity == x._capacity)
                {
                    for(size_t i = 0; i < _size; i++)
                        _alloc.destroy(&_data[i]);
                    for(size_t i = 0; i < x._size; i++)
                        _alloc.construct(&_data[i], x._data[i]);
                }
                else
                {
                    for(size_t i = 0; i < _size; i++)
                    {
                        _alloc.destroy(&_data[i]);
                    }
                    _alloc.deallocate(_data, _capacity);
                    _data = _alloc.allocate(x._capacity);
                    for(size_t i = 0; i < x._size; i++)
                    {
                        _alloc.construct(&_data[i], x._data[i]);
                    }

                }
                _capacity = x._capacity;
                _size = x._size;
                return *this;
            }
            /*---------------------------ITERATORS-------------------*/
            iterator            begin() {return iterator(_data);}
            const_iterator      begin() const {return const_iterator(_data);}
            iterator            end() {return iterator(_data + _size);}
            const_iterator      end() const {return const_iterator(_data + _size);}
            reverse_iterator    rbegin() {return reverse_iterator(this->end());}
            const_reverse_iterator  rbegin() const {return const_reverse_iterator(this->end());}
            reverse_iterator    rend() {return reverse_iterator(this->begin());}
            const_reverse_iterator     rend() const {return const_reverse_iterator(this->begin());}

            /*---------------------------ITERATORS-------------------*/
            
            size_type size() const {return _size;}
            size_type capacity() const {return _capacity;}
            
            size_type max_size() const
            {
                return _alloc.max_size();
            }
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
                difference_type my_position = std::distance(begin(), position);
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
                if (_size != 0)
                {
                    for(difference_type i = _size - 1; i >= my_position; i--)
                        _alloc.construct(&_data[n + i], _data[i]);
                    
                }
                for(size_type i=0; i < n;i++)
                    _alloc.construct(&_data[my_position + i], val);  
                 _size += n;
            }

            //template<class T> struct enable_if<true, T>; T in this case is InputIterator 
            template <class InputIterator>
            void insert (iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = InputIterator())
            {
                difference_type my_position = std::distance(begin(), position);
                size_type n = std::distance(first, last);
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
                for(size_type i=0; i < n;i++)
                {
                    _alloc.construct(&_data[my_position + i], *first);
                    first++;
                }
                _size += n;
            }
            iterator erase (iterator position)
            {
                difference_type my_position = std::distance(begin(), position);
                for(size_type i = my_position; i < _size - 1; i++)
                    _data[i] = _data[i+1];
                _size--;
                return (iterator(_data + my_position));
            }

            iterator erase (iterator first, iterator last)
            {
                size_type my_position = std::distance(begin(), first);
                size_type pos = std::distance(first, last);
                for(size_type i = my_position; i < _size - pos; i++)
                    _data[i] = _data[i+pos];
                _size -= pos;
                return (iterator(_data + my_position));
            }

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
                    for(size_type i =0; i < _size ; i++)
                        _alloc.construct(tmp+i, _data[i]);
                    for(size_type i =0;i < _size; i++)
                        _alloc.destroy(_data + i);
                    _alloc.deallocate(_data, _capacity);
                    _data = tmp;
                    _capacity = n;
                }
            }
            void    swap(vector &x)
            {
                
                // vector tmp(x);

                // x.operator=(*this);
                // this->operator=(tmp);

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
                for(size_type i=0; i < _size ; i++)
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
                return _data[_size - 1];
            }
            const_reference back() const
            {
                return _data[_size - 1];
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
            void assign (size_type n, const value_type& val)
            {
                if (n > _capacity)
                {
                    reserve(n);
                }
                for(size_t i = 0; i < n; i++)
                    _alloc.construct(&_data[i], val);
                _size = n;
            }
            template <class InputIterator>
            void assign (InputIterator first, InputIterator last,  typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = InputIterator())
            {
                size_type n = std::distance(first, last);
                if (!_data)
                {
                    if (n > _capacity)
                        _data = _alloc.allocate(n);
                    for(size_t i = 0; i < n ; i++)
                    {
                        _alloc.construct(&_data[i], *first);
                        first++;
                    }
                }
                else
                {
                    for(size_t i = 0; i < _size; i++)
                        _alloc.destroy(&_data[i]);
                    if (n > _capacity)
                    {
                        _alloc.deallocate(_data, _capacity);
                        _data = _alloc.allocate(n);                        
                    }
                    for(size_t i = 0; i < n; i++)
                    {
                        _alloc.construct(&_data[i], *first);
                        first++;
                    }
                        
                }
                _size = n;
                _capacity = n; 
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


            virtual ~vector() {
                for(size_type i=0;i< _size;i++)
                {
                    _alloc.destroy(&_data[i]);
                }
                _alloc.deallocate(_data, _size);
            };
        
        private:
            size_type       _capacity;
            size_type       _size;
            allocator_type  _alloc;
            value_type      *_data;
            //vector &operator=(vector const & t)
    };
    template <class T, class Alloc>
    bool operator== (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
    {
        if (lhs.size() == rhs.size())
        {
            return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
        }
        return false;
    }

    template <class T, class Alloc>
    bool operator!= (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
    {
        return !ft::operator==(rhs,lhs);
    }

    template <class T, class Alloc>
    bool operator<  (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
    {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(),rhs.begin(), rhs.end());
    }

    template <class T, class Alloc>
    bool operator<= (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
    {
        if (ft::operator<(lhs,rhs) || ft::operator==(rhs,lhs))
            return true;
        return false;
    }

    template <class T, class Alloc>
    bool operator>  (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
    {
        return !(ft::operator<=(lhs,rhs));
    }

    template <class T, class Alloc>
    bool operator>= (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
    {
        return !(ft::operator<(lhs,rhs));
    }
    template <class T, class Alloc>
    void swap (ft::vector<T,Alloc>& x, ft::vector<T,Alloc>& y)
    {
        x.swap(y);
    }
}