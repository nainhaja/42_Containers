#pragma once

#include "iterator_traits.hpp"

namespace ft
{
    template <class T>
    class random_access_iterator
    {
        public:
            typedef typename ft::iterator<std::random_access_iterator_tag, T>::difference_type          difference_type;
            typedef typename ft::iterator<std::random_access_iterator_tag, T>::value_type               value_type;
            typedef typename ft::iterator<std::random_access_iterator_tag, T>::iterator_category        iterator_category;
            typedef T*                                                                                  pointer;
            typedef T&                                                                                  reference;

            random_access_iterator() : my_pointer(nullptr){}
            random_access_iterator(pointer ptr) : my_pointer(ptr){}
            random_access_iterator(random_access_iterator const & t) : my_pointer(t.base()){}

            pointer base() const {return this->my_pointer;}

            virtual ~random_access_iterator(){}

            reference operator*() { return *my_pointer;};

            /*--------------------ASSIGNMENT/----------------------*/

            random_access_iterator &operator=(random_access_iterator const & t)
            {
                this->my_pointer = t.base();
                return (*this);
            }
            random_access_iterator &operator+=(difference_type  t)
            {
                this->my_pointer += t;
                return (*this);
            }
            random_access_iterator &operator-=(difference_type  t)
            {
                this->my_pointer -= t;
                return (*this);
            }


            /*--------------------INCREMENTATION/DECREMENTATION----------------------*/
            
            random_access_iterator operator++()
            {
                this->my_pointer++;
                return (*this);
            }
            random_access_iterator operator--()
            {
                this->my_pointer--;
                return (*this);
            }
            random_access_iterator operator++(int) 
            {
                random_access_iterator tmp(*this);
                this->my_pointer++;
                return (tmp);
            }
            random_access_iterator operator--(int)
            {
                random_access_iterator tmp(*this);
                this->my_pointer--;
                return (tmp);
            }
            
            /*--------------------MATH_OPTIONS----------------------*/
            random_access_iterator operator+(difference_type n) const
            {
                random_access_iterator tmp(this->my_pointer + n);
                return (tmp);
            }
            random_access_iterator &operator-(difference_type n) const
            {
                random_access_iterator tmp(this->my_pointer - n);
                return (tmp);
            }
            difference_type operator-(random_access_iterator &rhs) const
            {
                return (this->base() - rhs.base());
            }
           

            

        protected:
			pointer	my_pointer;
    };
    template <class T>
    /*--------------------COMPARAISON----------------------*/
    
    bool operator==(const random_access_iterator<T> & first, const random_access_iterator<T> & second)
    {
        return (first.base() == second.base());
    }

    template <class T>
    bool operator!=(const random_access_iterator<T> & first, const random_access_iterator<T> & second)
    {
        return (first.base() != second.base());
    }
    
    template <class T>
    bool operator>(const random_access_iterator<T> & first, const random_access_iterator<T> & second)
    {
        return (first.base() > second.base());
    }
    
    template <class T>
    bool operator<(const random_access_iterator<T> & first, const random_access_iterator<T> & second)
    {
        return (first.base() < second.base());
    }
    
    template <class T>
    bool operator>=(const random_access_iterator<T> & first, const random_access_iterator<T> & second)
    {
        return (first.base() >= second.base());
    }

    template <class T>
    bool operator<=(const random_access_iterator<T> & first, const random_access_iterator<T> & second)
    {
        return (first.get_pointer() <= second.get_pointer());
    }
}