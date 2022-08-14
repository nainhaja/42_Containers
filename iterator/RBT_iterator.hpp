#pragma once

#include "iterator_traits.hpp"


namespace ft
{
    template <typename Pair, typename Node, typename Tree_type>
    class RBT_iterator
    {
        public:
            typedef          Node                               value_type;
            typedef          ptrdiff_t                          difference_type;
            typedef          Pair*                              pointer;
            typedef          Pair&                              reference;
            typedef typename std::bidirectional_iterator_tag    iterator_category;

            RBT_iterator() : my_node(NULL){}
            RBT_iterator(Node* ptr, Tree_type tree) : my_node(ptr), my_tree(tree)
            {
            }
            RBT_iterator(RBT_iterator const & t) : my_node(t.base()), my_tree(t.my_tree){}


            operator RBT_iterator<const Pair, Node, Tree_type>() const
            {
                return RBT_iterator<const Pair, Node, Tree_type>(my_node, my_tree);
            }
            pointer get_node() const {return this->my_node->data;}
            Node *base() const {return this->my_node;}
            reference operator*() const{
                 return *(my_node->data);
                 };
            pointer operator->() const {
                return &(operator*());
            }

            virtual ~RBT_iterator(){}


            // Node* operator *() const{
            //     return *my_node;
            // } 
            // Node* operator ->() const {
            //     return &(*my_node);
            // }



            // bool operator==(const RBT_iterator & second)
            // {
            //     return (this->my_node == second.get_node());
            // }
            bool operator!=(const RBT_iterator & second)
            {
                return (this->my_node != second.base());
            }


            Node *    max_on_left(Node * node)
            {
                while(node->right)
                {
                    node = node->right;
                }
                return node;
            }
            Node *    min_on_right(Node * node)
            {
                while(node->left)
                {
                    node = node->left;
                }
                return node;
            }

            Node *   inorder_predecessor(Node * node)
            {
                if (node->left)
                    return max_on_left(node->left);
                Node *parent = node->parent;
                while(parent != NULL  && node == parent->left)
                {
                    node = parent;
                    parent = parent->parent;
                }
                return parent;
            }

            Node *   inorder_successor(Node * node)
            {

                if (node->right)
                    return min_on_right(node->right);
                Node *parent = node->parent;
                while(parent != NULL  && node == parent->right)
                {
                    node = parent;
                    parent = parent->parent;
                }

                return parent;
            }
            RBT_iterator operator++()
            {
                this->my_node = this->inorder_successor(this->my_node);
                return (*this);
            }
            RBT_iterator operator--()
            {
                //std::cout << "HEREe" << std::endl;
                if (!this->my_node && my_tree.get_root())
                {
                  //  std::cout << "HERE" << std::endl;
                    this->my_node = this->max(this->my_tree.get_root());
                    //std::cout <<  this->my_node->data->second << std::endl;
                    return (*this);
                }
                this->my_node = this->inorder_predecessor(this->my_node);
                return (*this);
            }
            RBT_iterator operator++(int) 
            {
                RBT_iterator tmp = *this;
                ++(*this);
                
                return (tmp);
            }
            RBT_iterator operator--(int)
            {
                RBT_iterator tmp = *this;
                --(*this);
                
                return (tmp);
            }


            RBT_iterator &operator=(RBT_iterator const & t)
            {
                this->my_node = t.base();
                this->my_tree = t.my_tree;
                return (*this);
            }
            bool operator==(const RBT_iterator & second)
            {
                return (this->my_node == second.base());
            }


        private:
            Node * max( Node * node )
            {
                while(node->right)
                {
                    node = node->right;
                }
                return node;
            }
            Node * min( Node * node )
            {
                while(node->left)
                {
                    node = node->left;
                }
                return node;
            }
            Node * predecessor( Node * node )
            {
                if (!node)
                    return NULL;
                if (node->left)
                    return max(node->left);
                return node;
            }
            Node * successor( Node * node )
            {
                if (!node)
                    return NULL;
                if (node->right)
                    return min(node->right);
                return node;
            }
            

        protected:
			Node*	    my_node;
            Tree_type   my_tree;
    };
    template <class Pair, class Node, class Tree_type>
    bool operator==(const RBT_iterator<Pair, Node, Tree_type> & first, const RBT_iterator<Pair, Node, Tree_type> & second)
    {
        return (first.base() == second.base());
    }



    template <class Pair, class Node, class Tree_type>
    bool operator!=(const RBT_iterator<Pair, Node, Tree_type> & first, const RBT_iterator<Pair, Node, Tree_type> & second)
    {
        return (first.base() != second.base());
    }
    
    template <class Pair, class Node, class Tree_type>
    bool operator>(const RBT_iterator<Pair, Node, Tree_type> & first, const RBT_iterator<Pair, Node, Tree_type> & second)
    {
        return (first.base() > second.base());
    }
    
    template <class Pair, class Node, class Tree_type>
    bool operator<(const RBT_iterator<Pair, Node, Tree_type> & first, const RBT_iterator<Pair, Node, Tree_type> & second)
    {
        return (first.base() < second.base());
    }
    
    template <class Pair, class Node, class Tree_type>
    bool operator>=(const RBT_iterator<Pair, Node, Tree_type> & first, const RBT_iterator<Pair, Node, Tree_type> & second)
    {
        return (first.base() >= second.base());
    }

    template <class Pair, class Node, class Tree_type>
    bool operator<=(const RBT_iterator<Pair, Node, Tree_type> & first, const RBT_iterator<Pair, Node, Tree_type> & second)
    {
        return (first.base() <= second.base());
    }
//     template <class Pair, class Node, class Tree_type>
//    typename RBT_iterator<Pair, Node, Tree_type>::difference_type operator- ( const RBT_iterator<Pair, Node, Tree_type> & first, const random_access_iterator<pair, Node, Tree_type> & second)
//     {
//         return (first.get_node() - second.get_node());
//     }

}