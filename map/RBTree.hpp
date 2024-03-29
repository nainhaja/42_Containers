#include<iostream>
#include "../enable_if.hpp"
#include "../is_integral.hpp"
#include "../equal.hpp"
#include "../iterator/RBT_iterator.hpp"
#include "../iterator/reverse_iterator.hpp"

#pragma once



namespace ft
{
    template < typename Pair, typename Compare, typename Alloc>

    class RBTree
    {
        private :
            struct my_node
            {
                Pair *data;
                // Key first;
                // T second;
                my_node *left;
                my_node *right;
                int color;
                my_node *parent;
            };
        public:
            typedef typename Pair::first_type                          my_first_type;
            typedef my_node                                   my_node;
            typedef ft::RBT_iterator<Pair, my_node,RBTree>                     iterator;
            typedef ft::RBT_iterator<const Pair, my_node, RBTree>               const_iterator;
            typedef ft::reverse_iterator<iterator>               reverse_iterator;
            typedef ft::reverse_iterator<const_iterator>         const_reverse_iterator;
            typedef size_t                                       size_type;
            
            RBTree():_root(nullptr), _size(0) 
            {
            }
            RBTree(my_node *root, Alloc alloc, Compare comp, size_type size):_root(root), _alloc(alloc), _comp(comp), _size(size)
            {}
            RBTree(RBTree const & x) :_root(x._root), _size(x._size){};
            ~RBTree(){}
            void    swap(RBTree &x)  
            {
                std::swap(_root, x._root);
                std::swap(_size, x._size);  
            }
            my_node *get_root() const
            {
                return this->_root;
            }
            iterator            begin() {return iterator(min_on_right(_root), (this));}
            const_iterator            begin() const {return iterator(min_on_right(_root), (this));}
            iterator            end() {return iterator(NULL, (this));}
            const_iterator            end() const {return iterator(NULL, (this));}
            reverse_iterator rbegin() 
            {
                //std::cout << "xDDDDDDO " << std::endl; 
                return reverse_iterator(this->end());
            }
            const_reverse_iterator rbegin() const
            {
                //iterator it;

                //it = this->begin();
                
                return const_reverse_iterator(const_iterator(this->end()));
            }
            reverse_iterator rend()
            {
                //std::cout << "xDDD" << std::endl;
                return reverse_iterator(this->begin());
            }
            const_reverse_iterator rend() const
            {
                //std::cout << "xDDDOO" << std::endl;
                return const_reverse_iterator((begin()));
            }
            void    initialize_my_tree( Compare new_comp,  Alloc new_alloc)
            {
                this->_alloc = new_alloc;
                this->_comp = new_comp;
            }
            iterator get_iterator(my_node *node)
            {
                //std::cout << "NOde first and second" << node->data->first << "|" << node->data->second << std::endl;

                return iterator(node, (this));
            }
            my_node *get_new_node(Pair const &data)
            {
                my_node *new_node = _nodeAlloc.allocate(1);
                
                new_node->data = _alloc.allocate(1);
                _alloc.construct(new_node->data, data);
                // new_node->data->first = data.first;
                // new_node->data->second = data.second;
                // new_node->first = data.first;
                // new_node->second = data.second;
                new_node->left = NULL; // left subtree
                new_node->right = NULL; // right subtree
                new_node->color = false; // colour . either 'R' or 'B'
                new_node->parent = NULL; // required at time of rechecking.
                
                return new_node;
            }
            my_node *rotateLeft(my_node *node)
            {
                my_node *right_node = node->right;

                node->right = right_node->left;
                if (node->right)
                    node->right->parent = node;
                
                right_node->parent = node->parent;
                
                
                if (node->parent)
                {
                    if (node->parent->left == node)
                        node->parent->left = right_node;
                    else if (node->parent->right == node)
                        node->parent->right = right_node;  
                // std::cout << "HERE" << std::endl;      
                }
                else 
                    _root = right_node;
                right_node->left = node;
                node->parent = right_node;

                return(right_node);
            } 
            bool operator==(const RBTree & second)
            {
                return (this->_root == second.base());
            }
            operator RBTree<const Pair, Compare, Alloc>() const
            {
                return RBTree<const Pair, Compare, Alloc>(_root, _alloc, _comp, _size);
            }
            RBTree& operator= (const RBTree& x)
            {
                this->_alloc = x._alloc;
                this->_comp = x._comp;
                this->_size = x._size;
                this->_root = x._root;
                return (*this);
            }
            my_node *rotateRight(my_node *node)
            {
                my_node *left_node = node->left;

                node->left = left_node->right;

                if (node->left)
                    node->left->parent = node;
                left_node->parent = node->parent;
                if (node->parent)
                {
                    if (node->parent->right == node)
                        node->parent->right = left_node;
                    else if (node->parent->left == node)
                        node->parent->left = left_node;        
                }
                else
                    _root = left_node; 
                left_node->right = node;
                node->parent = left_node;
                return(left_node);
            }
            void clear_my_tree(my_node *root)
            {
                if (root)
                {
                    clear_my_tree(root->left);
                    this->delete_node(root->left);
                    this->balance_my_tree_after_del(root->left);
                    clear_my_tree(root->right);
                    this->delete_node(root->right);
                    this->balance_my_tree_after_del(root->right);
                    this->delete_node(root);                  
                }
                
            }
            void    set_size()
            {
                this->_size = 0;
            }
            void printHelper(my_node *root, std::string indent, bool last) const
            {
                if (root != NULL) 
                {
                    std::cout << indent;
                    if (last) 
                    {
                        if (!root->parent)
                        {
                            std::cout << "|____";
                            indent += "   ";
                        }
                        else
                        {
                            std::cout << "R----";
                            indent += "   ";            
                        }
                    } 
                    else
                    {
                        std::cout << "L----";
                        indent += "|  ";
                    }
                    std::string sColor = root->color == 1 ? "BLACK" : "RED";
                    if (root->color == -1)
                        sColor = "Double_Black";
                    std::cout << root->data->first << "(" << sColor << ")" << std::endl;
                    printHelper(root->left, indent, false);
                    printHelper(root->right, indent, true);
                }
            }
            iterator find_key(my_first_type  const & key) const
            {
                my_node * node = _root;


                if (node == NULL)
                    return iterator(NULL, this);
                while(node)
                {
                    if (!_comp(node->data->first, key) && !_comp(key,node->data->first))
                        return iterator(node, this);
                    else if (!_comp(node->data->first, key))
                        node = node->left;
                    else
                        node = node->right;
                }
                return iterator(NULL, this);
            }
            size_type size() const
            {
                return this->_size;
            }
            my_node *    insert_node(my_node *root, my_node *new_node)
            {
                
                if (root == NULL)
                {
                    
                    //_root = new_node;
                    return new_node;
                }
                if (new_node->data->first > root->data->first)
                {
                    //std::cout << "HH" << new_node->data->first << " xD " << root->data->first << std::endl;
                    root->right = insert_node(root->right, new_node);
                    root->right->parent = root;
                }
                else if (new_node->data->first < root->data->first)
                {
                    //std::cout << "HH" << new_node->data->second << " xD " << root->data->second << std::endl;
                    root->left = insert_node(root->left, new_node);
                    root->left->parent = root;
                }
                return root;
            }
            my_node *    insert(my_node *new_node)
            {
                if (_root == NULL)
                    _root = new_node;
                else
                    this->insert_node(_root, new_node);

                this->balance_my_tree(new_node);    
                _size++;
                return new_node;
            }
            
            
            my_node * delete_node(my_node *node)
            {
                if (node)
                {
                    my_node *parent;
                    if (node == _root && !node->right && !node->left)
                    {
                        node = NULL;
                        _root = NULL;
                        delete node;
                        

                        return NULL;
                    }
                    else if (!node->left && !node->right)
                    {
                       // std::cout << "losos" << std::endl;
                        //this->printHelper(this->get_root(), "", true);
                        parent = node->parent;
                        if (parent->left == node)
                            parent->left = NULL;
                        else
                            parent->right = NULL;
                        //std::cout << std::endl;
                        
                        //
                        //std::cout << sizeof(node) << std::endl;
                        _alloc.destroy(node->data);
                        _alloc.deallocate(node->data, 1);
                        _nodeAlloc.deallocate(node, 1);
                        //delete node;
                        //node = NULL;
                        
                        //this->printHelper(this->get_root(), "", true);
                        //delete node;
                        //std::cout << "Here again" << std::endl;
                        //delete node;
                    }
                }
                return node;
            }
            void  balance_my_tree_after_del(my_node *node)
            {
                if (node)
                {
                    if (!node->color)
                    {
                        return ;
                    }
                    else if (node == this->get_root())
                    {
                        node->color = 1;
                        return ;
                    }
                    else 
                    {
                        my_node *sibling = (node == node->parent->right) ? (sibling = node->parent->left) : (sibling = node->parent->right);
                        //std::cout << "SIBLING IS :" <<  sibling->data << std::endl;
                        //std::cout  << sibling->data << std::endl;
                        // std::cout << "SIBLING : " << sibling->data << std::endl;
                        // std::cout << "node : " << node->data << std::endl;
                        // std::cout << "Parent : " << node->parent->data << std::endl << std::endl;
                        //delete_node(node);
                        //case 1 : sibling is black
                        if (sibling && sibling->color)
                        {
                            
                            // case1.1 : sibling is black and its children are black as well
                            if ((!sibling->left || sibling->left->color) && (!sibling->right || sibling->right->color))
                            {
                                // make parent more black ; make sibling red; make node red ; rebalance parent if he's db
                                my_node *parent;
                                parent = node->parent;
                                parent->color = (parent->color == 1) ? (parent->color = -1) : (parent->color = 1);
                                sibling->color = 0;
                                node->color = 1;
                                if (parent->color == -1)
                                    balance_my_tree_after_del(parent);
                                return ;
                            }
                            if (node == node->parent->left)
                            {
                                
                                my_node *parent;
                                parent = node->parent;
                                // node is left far sibling child is black and closest sibling child is red
                                if ((!sibling->right || sibling->right->color) && (sibling->left && !sibling->left->color))
                                {
                                    std::swap(sibling->color, sibling->left->color);
                                    rotateRight(sibling);
                                    this->balance_my_tree_after_del(node);
                                }
                                // node is left far sibling child is Red and closest sibling child is Black
                                else if ( (sibling->right && !sibling->right->color) && (!sibling->left || sibling->left->color))
                                {
                                    std::swap(parent->color, sibling->color);
                                    rotateLeft(parent);
                                    sibling->right->color = 1;
                                    node->color = 1;
                                }
                            }
                            else 
                            {
                                my_node *parent;
                                parent = node->parent;
                                 // node is right far sibling child is black and closest sibling child is red
                                if ((!sibling->left || sibling->left->color) && !sibling->right->color)
                                {
                                    std::swap(sibling->color, sibling->right->color);
                                    rotateLeft(sibling);
                                    this->balance_my_tree_after_del(node);
                                }
                                 // node is right far sibling child is red and closest sibling child is black
                                else if (!sibling->left->color && (!sibling->right || sibling->right->color))
                                {
                                    std::swap(parent->color, sibling->color);
                                    rotateRight(parent);
                                    sibling->left->color = 1;
                                    node->color = 1;
                                }
                            }

                        }
                        //case 2: Sibling is red 
                        else if (sibling && !sibling->color)
                        {
                            
                            //steps are : 
                            //1)Swap color of sibling and parent 
                            //2)rotate parent to node direction (our db) and reapply cases 
                            my_node *parent;
                            parent = node->parent;

                            std::swap(sibling->color, parent->color);
                            if (parent->left == node)
                                rotateLeft(parent);
                            else
                                rotateRight(parent);
                            this->balance_my_tree_after_del(node);
                        }                    
                }

                }
                return;
            }
            void    decrement_size() 
            {
                this->_size--;
            }
            void    erase(iterator &it)
            {
                this->remove(it.base());
                
            }
            void    remove(my_node *node)
            {
                if (!node)
                    return ;
                if (node == _root && !node->right && !node->left)
                {
                    this->delete_node(node);
                    return ;
                }
                else if (!node->right && !node->left)
                {
                    //std::cout << "reached herex " << std::endl;
                    this->balance_my_tree_after_del(node);
                   
                    this->delete_node(node);
                    node = NULL;
                    
                   
                }
                else
                {

                    if (node->right)
                    {
                        my_node * my_successor = inorder_successor(node);
                        _alloc.destroy(node->data);
                        _alloc.construct(node->data, *(my_successor->data));
                        my_successor->color = (my_successor->color == 1) ? (my_successor->color = -1) : (my_successor->color = 1);
                        this->remove(my_successor);
                    }
                    else
                    {
                        my_node * my_predecessor = inorder_predecessor(node);
                        _alloc.destroy(node->data);
                        _alloc.construct(node->data, *(my_predecessor->data));
                        my_predecessor->color = (my_predecessor->color == 1) ? (my_predecessor->color = -1) : (my_predecessor->color = 1);
                        this->remove(my_predecessor);
                    }
                }
            }
            iterator lower_bound(my_first_type const &  key) const
            {
                my_node * node = _root;
                iterator it = find_key(key);
                my_node *my_successor = _root;

                if (node == NULL)
                    return iterator(NULL, this);
                else if (it.base())
                    return it;
                while(node)
                {
                    //t = node->data->first - key;
                    
                    if (!_comp(node->data->first, key))
                    {
                        my_successor = node;
                        node = node->left;
                    }
                        
                    else if (!_comp(key, node->data->first))
                        node = node->right;
                }
                return iterator(my_successor, this);
            }
            iterator upper_bound(my_first_type const &  key) const
            {
                my_node * node = _root;
                iterator it = find_key(key);
                my_node *my_successor = _root;

                if (node == NULL)
                    return iterator(NULL, this);
                else if (it.base())
                {
                    it++;
                    return it;
                }
                    //return it;
                while(node)
                {
                    //t = node->data->first - key;
                    
                    if (!_comp(node->data->first, key))
                    {
                        my_successor = node;
                        node = node->left;
                    }
                        
                    else if (!_comp(key, node->data->first))
                        node = node->right;
                }
                return iterator(my_successor, this);
            }
            my_node * max_tree() const
            {
                my_node * node = _root;
                while(node && node->right)
                {
                    node = node->right;
                }
                return node; 
            }

            my_node * min_tree() const
            {
                my_node * node = _root;
                while(node && node->left)
                {
                    node = node->left;
                }
                return node; 
            }

            my_node *    max_on_left(my_node * node)
            {
                my_node * new_node = node;
                if (new_node)
                {
                    while(new_node->right)
                    {
                        new_node = new_node->right;
                    }
                    return new_node;                    
                }
                return NULL;

            }
            my_node *    min_on_right(my_node * node) const 
            {
                my_node * new_node = node;
                if (new_node)
                {
                    while(new_node->left)
                    {
                        new_node = new_node->left;
                    }
                    return new_node;                 
                }
                return NULL;
                
            }
            my_node *   inorder_predecessor(my_node * node)
            {
                if (!node)
                    return NULL;
                if (node->left)
                    return max_on_left(node->left);
                return node;
            }

            my_node *   inorder_successor(my_node * node)
            {
                if (!node)
                    return NULL;
                if (node->right)
                    return min_on_right(node->right);
                return node;
            }

            void    balance_my_tree(my_node *node)
            {
                
                if (node->parent)
                {
                    my_node *parent = NULL;
                    my_node *gp = NULL;
                    // my_node *uncle = NULL;
                    while(node->parent && (!node->color) && (!node->parent->color))
                    { 
                        //std::cout << "LOL" << std::endl;
                        parent = node->parent;
                        gp = node->parent->parent;
                    
                        if (parent == gp->left)
                        {
                            my_node *uncle = gp->right;
                            if (uncle && !uncle->color)
                            {
                                //std::cout << "LOL1" << std::endl;
                                uncle->color = 1;
                                parent->color = 1;
                                if (gp->parent)
                                    gp->color = 0;
                                node = gp;    
                            }
                            else 
                            {
                                //std::cout << "LOL2" << std::endl;
                                if (node == parent->right)
                                {
                                    rotateLeft(parent);
                                    node = parent;
                                    parent = node->parent;
                                }
                                
                                rotateRight(gp);
                                std::swap(gp->color, parent->color);
                                node = parent;
                                
                            }
                        }
                        else
                        {
                            my_node *uncle = gp->left;
                            if (uncle && !uncle->color)
                            {
                                //std::cout << "LOL3" << std::endl;
                                uncle->color = 1;
                                parent->color = 1;
                                if (gp->parent)
                                    gp->color = 0;
                                node = gp;   
                            }
                            else 
                            {
                                //std::cout << "LOL4" << std::endl;
                                if (node == parent->left)
                                {
                                    rotateRight(parent);
                                    node = parent;
                                    parent = node->parent;
                                }
                                rotateLeft(gp);
                                std::swap(gp->color, parent->color);
                                node = parent;
                            }
                        }

                    }
                }
                else 
                {
                    node->color = 1;
                }
            }
        private:
            my_node *_root;
            Alloc _alloc;
            typename	Alloc::template	rebind<my_node>::other	_nodeAlloc;
            Compare _comp;
            size_type _size;
    };
}