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
#include "../vector/vector.hpp"

#pragma once

namespace ft
{
    template < typename Key, typename T, class Compare = std::less<Key>, class Alloc = std::allocator< ft::pair<const Key,T> > >

    class map
    {
        public :
            typedef Key                             key_type;
            typedef T                               mapped_type;
            typedef ft::pair<const key_type, mapped_type>    value_type;
            typedef Compare                         key_compare;
            
            typedef Alloc                           allocator_type;

            typedef typename allocator_type::pointer             pointer;
            typedef typename allocator_type::const_pointer       const_pointer;
            typedef typename allocator_type::reference           reference;
            typedef typename allocator_type::const_reference     const_reference;

            typedef typename ft::RBTree<value_type, Compare, Alloc>::iterator            iterator;
            typedef typename ft::RBTree<value_type, Compare, Alloc>::const_iterator      const_iterator;
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
                            const allocator_type& alloc = allocator_type()) : my_tree(), _comp(comp), _alloc(alloc)
            {
                my_tree.initialize_my_tree(comp, alloc);
            }   

            template <class InputIterator>
            map (InputIterator first, InputIterator last,
                    const key_compare& comp = key_compare(),
                    const allocator_type& alloc = allocator_type()) : _comp(comp), _alloc(alloc)
            {
                 size_t my_distance = std::distance(first, last);
                for(size_type i=0; i < my_distance ; i++)
                {
                    my_tree.insert(my_tree.get_new_node(*first));
                    first++;
                }
            }

            map (const map& x) : _comp(x._comp), _alloc(x._alloc)
            {
                iterator it;

                it = x.get_tree().begin();
                for(; it != x.get_tree().end();it++)
                    my_tree.insert(my_tree.get_new_node(*it));
            }

            
            map& operator= (const map& x)
            {
                map k(x);
                iterator it;
                
                
                this->my_tree.clear_my_tree(this->my_tree.get_root());
                this->my_tree.set_size();
                _comp = x._comp;
                _alloc = x._alloc;
                it = k.begin();
                for(; it != k.end();it++)
                    this->insert((*it));                    

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
                if (this->size() == 0)
                    return true;
                return false;
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
                return ((*((this->insert(ft::make_pair(k,mapped_type()) )).first)).second);
            }

            ft::pair<iterator,bool> insert(const value_type& val)
            {
                iterator it = this->my_tree.find_key(val.first);
                if (!it.base())
                {
                    this->my_tree.insert(this->my_tree.get_new_node(val));
                    it = this->my_tree.find_key(val.first);
                    return ft::pair<iterator, bool>(it, true);
                }
                return ft::pair<iterator, bool>(it, false);
                    

            }
            iterator insert (iterator position, const value_type& val)
            {
                this->my_tree.insert(this->my_tree.get_new_node(val));
                return position;
            }

            template <class InputIterator>
            void insert (InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = InputIterator())
            {
                for(InputIterator it=first; it != last;it++)
                {
                    this->insert(ft::make_pair((*it).first, (*it).second));
                    first++;
                }
                return;
            }

            void erase (iterator position)
            {
                iterator it;
                
                it = this->my_tree.find_key((*position).first);
                if (it.base())
                {
                    this->my_tree.remove(it.base());
                }
                    
                this->my_tree.decrement_size();
            }
            size_type erase (const key_type& k)
            {
                iterator it;
                
                it = this->my_tree.find_key(k);
                if (it.base())
                {
                    this->my_tree.erase(it);
                    this->my_tree.decrement_size();
                    return 1;
                }
                return 0;
            }
            void erase (iterator first, iterator last)
            {
                size_t i=0;
                iterator it(first);
                ft::vector<int> my_Vec;
                for(; it != last;it++)
                {
                    my_Vec.push_back(it->first);
                    i++;
                }   
                for(size_t t = 0; t < i; t++)
                {
                    this->erase(my_Vec[t]);
                }
            }

            void swap (map& x)
            {

                this->my_tree.swap(x.my_tree);
                std::swap(x._alloc, _alloc);
                std::swap(x._comp, _comp);
            }

            void clear()
            {
                this->my_tree.clear_my_tree(my_tree.get_root());
                this->my_tree.set_size();
                return ;
            }

            key_compare key_comp() const
            {
                key_compare k;
                return k;
            }
            value_compare value_comp() const
            {
                key_compare k;
                return k;
            }

            iterator find (const key_type& k) 
            {
                iterator it;

                it = my_tree.find_key(k);
                return it;
            }
            const_iterator find (const key_type& k) const
            {
                iterator it;

                it = my_tree.find_key(k);
                return it;
            }

            ft::RBTree<value_type, Compare, Alloc> get_tree() const
            {
                
                return this->my_tree;
            }
            value_type *get_pair()
            {
                return this->my_tree.get_root()->data;
            }
            size_type count (const key_type& k) const
            {
                iterator it = my_tree.find_key(k);
                if (it.base())
                    return 1;
                return 0;
            }

            iterator lower_bound (const key_type& k){
                 
                return my_tree.lower_bound(k);
            }
            const_iterator lower_bound (const key_type& k) const
            {
                return my_tree.lower_bound(k);
            }


            iterator upper_bound (const key_type& k)
            {
                 return my_tree.upper_bound(k);
            }
            const_iterator upper_bound (const key_type& k) const
            {
                return my_tree.upper_bound(k);
            }


            ft::pair<const_iterator,const_iterator> equal_range (const key_type& k) const
            {
                 //iterator it;
                ft::pair<const_iterator,const_iterator> ok;

                //it = 
                ok.first = lower_bound(k);
                //it++;
                ok.second = upper_bound(k);
                return ok;
            }
            ft::pair<iterator,iterator>             equal_range (const key_type& k)
            {
                //iterator it;
                ft::pair<iterator,iterator> ok;

                //it = 
                ok.first = lower_bound(k);
                //it++;
                ok.second = upper_bound(k);
                return ok;
            }


            allocator_type get_allocator() const
            {
                return _alloc;
            }

            virtual ~map(){
                if (my_tree.get_root())
                {
                    this->my_tree.clear_my_tree(my_tree.get_root());
                    this->my_tree.set_size();
                }
            };
        private:
            ft::RBTree<value_type, Compare, Alloc> my_tree;
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