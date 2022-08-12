#include <iostream>
#include <memory.h>
#include "../iterator/iterator_traits.hpp"
#include "../iterator/random_access_iterator.hpp"
#include "../iterator/reverse_iterator.hpp"
#include "../iterator/RBT_iterator.hpp"
#include "RBTree.hpp"

#include <iostream>     // std::cout
#include "../enable_if.hpp"
#include "../is_integral.hpp"
#include "../equal.hpp"

#pragma once

namespace ft
{
    template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<pair<const Key,T> > >

    class map
    {
        public :
            typedef Key                             key_type;
            typedef T                               mapped_type;
            typedef pair<const Key, mapped_type>    value_type;
            typedef Compare                         key_compare;
            
            typedef Alloc                           allocator_type;

            typedef typename allocator_type::pointer             pointer;
            typedef typename allocator_type::const_pointer       const_pointer;
            typedef typename allocator_type::reference           reference;
            typedef typename allocator_type::const_reference     const_reference;

            typedef typename ft::RBTree<key_type, mapped_type, Compare, Alloc>::iterator            iterator;
            typedef typename ft::RBTree<key_type, mapped_type, Compare, Alloc>::const_iterator      const_iterator;
            typedef ft::reverse_iterator<iterator>               reverse_iterator;
            typedef ft::reverse_iterator<const_iterator>         const_reverse_iterator;

            typedef size_t                                       size_type;
            typedef class value_compare
            {
                friend class map;
                protected:
                    Compare comp;
                    value_compare (Compare c) : comp(c) {} 
                public:
                    typedef bool result_type;
                    typedef value_type first_argument_type;
                    typedef value_type second_argument_type;
                    bool operator() (const value_type& x, const value_type& y) const
                    {
                        return comp(x.first, y.first);
                    }
            }value_compare;

            explicit map (const key_compare& comp = key_compare(),
                            const allocator_type& alloc = allocator_type()) : _comp(comp), _alloc(alloc)
            {

            }   

            template <class InputIterator>
            map (InputIterator first, InputIterator last,
                    const key_compare& comp = key_compare(),
                    const allocator_type& alloc = allocator_type()) : _comp(comp), _alloc(alloc)
            {
                first = last;
            }

            map (const map& x) : my_tree(x.my_tree), _comp(x._comp), _alloc(x._alloc)
            {
            }

            map& operator= (const map& x)
            {
                my_tree =  x.my_tree;
                _comp = x._comp;
                _alloc = x._alloc;
                return (*this);
            }


            iterator begin()
            {
                return this->my_tree.begin();
            }
            const_iterator begin() const
            {
                return this->my_tree.begin();
            }
            iterator end(){return this->my_tree.end();};
            const_iterator end() const {return this->my_tree.end();};
            reverse_iterator rbegin()
            {
                return this->my_tree.rbegin();
            }
            const_reverse_iterator rbegin() const
            {
                return this->my_tree.rbegin();
            }
            reverse_iterator rend()
            {
                return this->my_tree.rend();
            }
            const_reverse_iterator rend() const
            {
                return this->my_tree.rend();
            }

            bool empty() const
            {
                if (this->my_tree.get_root())
                    return false;
                return true;
            }
            size_type size() const
            {
                return this->my_tree.size();
            }
            size_type max_size() const
            {
                return _alloc.max_size();
            }

            mapped_type& operator[] (const key_type& k)
            {
                return ((*((this->insert(make_pair(k,mapped_type()))).first)).second);
            }

            pair<iterator,bool> insert (const value_type& val);
            iterator insert (iterator position, const value_type& val);

            template <class InputIterator>
            void insert (InputIterator first, InputIterator last);


            void erase (iterator position);
            size_type erase (const key_type& k);
            void erase (iterator first, iterator last);

            void swap (map& x);

            void clear();

            key_compare key_comp() const;
            //DONT FORGET THIS
            value_compare value_comp() const; 

            iterator find (const key_type& k);
            const_iterator find (const key_type& k) const;


            size_type count (const key_type& k) const;

            iterator lower_bound (const key_type& k);
            const_iterator lower_bound (const key_type& k) const;


            iterator upper_bound (const key_type& k);
            const_iterator upper_bound (const key_type& k) const;


            pair<const_iterator,const_iterator> equal_range (const key_type& k) const;
            pair<iterator,iterator>             equal_range (const key_type& k);


            allocator_type get_allocator() const;

            ~map();
        private:
            ft::RBTree<Key, value_type> my_tree;
            Compare                     _comp;
            Alloc                       _alloc;

    };


    template < class Key, class T >
    bool operator== (const ft::map<Key, T>& lhs, const ft::map<Key, T>& rhs)
    {
        if (lhs.size() == rhs.size())
        {
            return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
        }
        return false;
    }

    template < class Key, class T >
    bool operator!= (const ft::map<Key, T>& lhs, const ft::map<Key, T>& rhs)
    {
        return !ft::operator==(rhs,lhs);
    }

    template < class Key, class T >
    bool operator<  (const ft::map<Key, T>& lhs, const ft::map<Key, T>& rhs)
    {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(),rhs.begin(), rhs.end());
    }

    template < class Key, class T >
    bool operator<= (const ft::map<Key, T>& lhs, const ft::map<Key, T>& rhs)
    {
        if (ft::operator<(lhs,rhs) || ft::operator==(rhs,lhs))
            return true;
        return false;
    }

    template < class Key, class T >
    bool operator>  (const ft::map<Key, T>& lhs, const ft::map<Key, T>& rhs)
    {
        return !(ft::operator<=(lhs,rhs));
    }

    template < class Key, class T >
    bool operator>= (const ft::map<Key, T>& lhs, const ft::map<Key, T>& rhs)
    {
        return !(ft::operator<(lhs,rhs));
    }


}