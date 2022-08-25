#pragma once

#include "iterator_traits.hpp"


namespace ft
{
    template <typename Pair, typename Node, typename Tree_type>
    class RBT_iterator
    {
        public:
            typedef          Pair                               value_type;
            typedef          ptrdiff_t                          difference_type;
            typedef          Pair*                              pointer;
            typedef          Pair&                              reference;
            typedef typename std::bidirectional_iterator_tag    iterator_category;

            RBT_iterator() : my_node(NULL), my_tree(NULL){}
            RBT_iterator(Node* ptr, Tree_type const *tree) : my_node(ptr), my_tree(tree)
            {

            }
            RBT_iterator(RBT_iterator const & t) : my_node(t.base()), my_tree(t.my_tree){}


            operator RBT_iterator<const value_type, Node, Tree_type>() const
            {
                return RBT_iterator<const value_type, Node, Tree_type>(my_node, my_tree);
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

            bool operator!=(const RBT_iterator & second)
            {
                return (this->my_node != second.base());
            }


            Node *    max_on_left(Node * node)
            {
                Node *new_node = node;
                while(new_node->right)
                {
                    new_node = new_node->right;
                }
                return new_node;
            }
            Node *    min_on_right(Node * node)
            {
                Node *new_node = node;
                while(new_node->left)
                {
                    new_node = new_node->left;
                }
                return new_node;
            }


            Node *   inorder_predecessor(Node * node)
            {
                
                if (!node)
                    return this->my_tree->max_tree();
                if (node->left)
                    return max_on_left(node->left);
                Node *new_node = node;
                Node *parent = new_node->parent;
                while(parent != NULL  && new_node == parent->left)
                {
                    new_node = parent;
                    parent = parent->parent;
                }
                return parent;
            }

            Node *   inorder_successor(Node * node)
            {
                if (!node)
                    return this->my_tree->min_tree();
                if (node->right)
                    return min_on_right(node->right);
                Node *new_node = node;
                Node *parent = new_node->parent;
                while(parent != NULL  && new_node == parent->right)
                {
                    new_node = parent;
                    parent = parent->parent;
                }

                return parent;
            }
            RBT_iterator operator++()
            {
                this->my_node = this->inorder_successor(this->my_node);
                return (*this);
            }
            RBT_iterator &operator--()
            {
                
               // std::cout << "HEREe" << std::endl;
                if (!this->my_node && my_tree)
                {
                    this->my_node = this->max(this->my_tree->get_root());                    
                    return (*this);
                }
                //std::cout << "okk" << std::endl;
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

                this->my_tree = t.my_tree;
                this->my_node = t.base();
                return (*this);
            }
            bool operator==(const RBT_iterator & second)
            {
                return (this->my_node == second.base());
            }


        private:
            Node * max( Node * node )
            {
                Node *t = node;

                while(t->right != NULL)
                {
                    t = t->right;
                }
                return t;
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
            Tree_type   const *my_tree;
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


}