#pragma once

#include "iterator_traits.hpp"

namespace ft
{
    template <class Iterator>
    class reverse_iterator
    {
        public:
            typedef Iterator                                                         iterator_type;
            typedef typename iterator_traits<Iterator>::difference_type          difference_type;
            typedef typename iterator_traits<Iterator>::value_type               value_type;
            typedef typename iterator_traits<Iterator>::iterator_category        iterator_category;
            typedef typename iterator_traits<Iterator>::pointer                                  pointer; 
            typedef typename iterator_traits<Iterator>::reference                                reference;

            reverse_iterator() : my_pointer(nullptr){}
            reverse_iterator(iterator_type ptr) : my_pointer(ptr){}
            reverse_iterator(reverse_iterator const & t) : my_pointer(t.get_pointer()){}


            iterator_type get_pointer() {return this->my_pointer;}

            virtual ~reverse_iterator();


            /*--------------------ASSIGNMENT/----------------------*/

            reverse_iterator &operator=(reverse_iterator const & t)
            {
                this->my_pointer = t.get_pointer();
                return (*this);
            }
            reverse_iterator &operator+=(difference_type  t)
            {
                this->my_pointer += t;
                return (*this);
            }
            reverse_iterator &operator-=(difference_type  t)
            {
                this->my_pointer -= t;
                return (*this);
            }


            /*--------------------INCREMENTATION/DECREMENTATION----------------------*/
            
            reverse_iterator operator++()
            {
                this->my_pointer++;
                return (*this);
            }
            reverse_iterator operator--()
            {
                this->my_pointer--;
                return (*this);
            }
            reverse_iterator &operator++(int) const 
            {
                reverse_iterator tmp(*this);
                this->my_pointer++;
                return (tmp);
            }
            reverse_iterator &operator--(int) const
            {
                reverse_iterator tmp(*this);
                this->my_pointer--;
                return (tmp);
            }
            
            /*--------------------MATH_OPTIONS----------------------*/
            reverse_iterator &operator+(difference_type n) const
            {
                reverse_iterator tmp(this->my_pointer + n);
                return (tmp);
            }
            reverse_iterator &operator-(difference_type n) const
            {
                reverse_iterator tmp(this->my_pointer - n);
                return (tmp);
            }

           

            

        protected:
			iterator_type	my_pointer;
    };
    template <class Iterator>
    /*--------------------COMPARAISON----------------------*/
    
    bool operator==(const reverse_iterator<Iterator> & first, const reverse_iterator<Iterator> & second)
    {
        return (first.get_pointer() == second.get_pointer());
    }

    template <class Iterator>
    bool operator!=(const reverse_iterator<Iterator> & first, const reverse_iterator<Iterator> & second)
    {
        return (first.get_pointer() != second.get_pointer());
    }
    
    template <class Iterator>
    bool operator>(const reverse_iterator<Iterator> & first, const reverse_iterator<Iterator> & second)
    {
        return (first.get_pointer() > second.get_pointer());
    }
    
    template <class Iterator>
    bool operator<(const reverse_iterator<Iterator> & first, const reverse_iterator<Iterator> & second)
    {
        return (first.get_pointer() < second.get_pointer());
    }
    
    template <class Iterator>
    bool operator>=(const reverse_iterator<Iterator> & first, const reverse_iterator<Iterator> & second)
    {
        return (first.get_pointer() >= second.get_pointer());
    }

    template <class Iterator>
    bool operator<=(const reverse_iterator<Iterator> & first, const reverse_iterator<Iterator> & second)
    {
        return (first.get_pointer() <= second.get_pointer());
    }
}