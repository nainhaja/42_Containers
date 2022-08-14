#pragma once

#include "iterator_traits.hpp"

namespace ft
{
    template <class Iterator>
    class reverse_iterator
    {
        public:
            typedef Iterator                                                     iterator_type;
            typedef typename iterator_traits<Iterator>::difference_type          difference_type;
            typedef typename iterator_traits<Iterator>::value_type               value_type;
            typedef typename iterator_traits<Iterator>::iterator_category        iterator_category;
            typedef typename iterator_traits<Iterator>::pointer                  pointer; 
            typedef typename iterator_traits<Iterator>::reference                reference;

            reverse_iterator() : my_pointer(){}
            explicit reverse_iterator (iterator_type it) : my_pointer(--it){}

            //reverse_iterator(const reverse_iterator  & t){this->operator=(t);}
            template <typename Iter>
            reverse_iterator (const reverse_iterator<Iter>& rev_it):my_pointer(--rev_it.base()) {}
            //reverse_iterator(iterator_type ptr) : my_pointer(ptr){}
            


            iterator_type base() const {
                iterator_type temp = this->my_pointer;
                return ++temp;
            }

            
            reference operator*() const 
            { 
                iterator_type	tmp = my_pointer;
                return *tmp;
            };
            reverse_iterator operator+ (difference_type n) const{
                
                reverse_iterator tmp(this->base());
                tmp.my_pointer-= n;
                return (tmp);}
            reverse_iterator operator- (difference_type n) const
            {
                reverse_iterator tmp(this->base());
                tmp.my_pointer+= n;
                return (tmp);}

            /*--------------------ASSIGNMENT/----------------------*/
            pointer operator->() const {
            return &(operator*());
            }
            reference & operator [](difference_type rhs) const {return my_pointer[rhs];}
            reverse_iterator &operator=(reverse_iterator const & t)
            {

                this->my_pointer = --t.base();
                return (*this);
            }
            reverse_iterator &operator+=(difference_type  t)
            {
                this->my_pointer -= t;
                return (*this);
            }
            reverse_iterator &operator-=(difference_type  t)
            {
                this->my_pointer += t;
                return (*this);
            }


            /*--------------------INCREMENTATION/DECREMENTATION----------------------*/
            
            reverse_iterator operator++()
            {
                this->my_pointer--;
                return (*this);
            }
            reverse_iterator operator--()
            {
                this->my_pointer++;
                return (*this);
            }
            reverse_iterator operator++(int) 
            {
                reverse_iterator temp = *this;
                ++(*this);
                return temp;
            }
            reverse_iterator operator--(int)
            {
                reverse_iterator temp = *this;
                --(*this);
                return temp;
            }
            
            /*--------------------MATH_OPTIONS----------------------*/
            // reverse_iterator &operator+(difference_type n) const
            // {
            //     reverse_iterator tmp(this->my_pointer + n);
            //     return (tmp);
            // }

            virtual ~reverse_iterator(){}

            operator reverse_iterator<const iterator_type>() const
            {
                 return reverse_iterator<const iterator_type>(my_pointer);
            }

        protected:
			iterator_type	my_pointer;
    };
    template <class Iterator>
    /*--------------------COMPARAISON----------------------*/
    
    bool operator==(const reverse_iterator<Iterator> & first, const reverse_iterator<Iterator> & second)
    {
        return (first.base() == second.base());
    }

    template <class Iterator>
    bool operator!=(const reverse_iterator<Iterator> & first, const reverse_iterator<Iterator> & second)
    {
        return (first.base() != second.base());
    }
    
    template <class Iterator>
    bool operator>(const reverse_iterator<Iterator> & first, const reverse_iterator<Iterator> & second)
    {
        return (first.base() < second.base());
    }
    
    template <class Iterator>
    bool operator<(const reverse_iterator<Iterator> & first, const reverse_iterator<Iterator> & second)
    {
        return (first.base() > second.base());
    }
    
    template <class Iterator>
    bool operator>=(const reverse_iterator<Iterator> & first, const reverse_iterator<Iterator> & second)
    {
        return (first.base() <= second.base());
    }

    template <class Iterator>
    bool operator<=(const reverse_iterator<Iterator> & first, const reverse_iterator<Iterator> & second)
    {
        return (first.base() >= second.base());
    }

    template <class Iterator>
    reverse_iterator<Iterator> operator+(
             typename reverse_iterator<Iterator>::difference_type n,
             const reverse_iterator<Iterator>& rev_it)
    {
        return (rev_it + n);
    }
    template<class Iterator>
    typename reverse_iterator<Iterator>::difference_type operator- ( const reverse_iterator<Iterator>& lhs,
               const reverse_iterator<Iterator>& rhs )
    {
        return (rhs.base() - lhs.base());
    }
}