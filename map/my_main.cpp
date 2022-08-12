#include<iostream>
#include "RBTree.hpp"
#include "../equal.hpp"
#include "map.hpp"
// typedef struct my_node
// {
//     int data;
//     my_node *left;
//     my_node *right;
//     int color;
//     my_node *parent;
// }my_node;

// namespace ft
// {
//     class rbt
//     {
//         public:
//             rbt():_root(nullptr)
//             {
//             }
//             rbt(int data)
//             {
//                 //super();
//                 this->_root = new my_node();
//                 this->_root->data = data;   // only including data. not key
//                 this->_root->left = NULL; // left subtree
//                 this->_root->right = NULL; // right subtree
//                 this->_root->color = false; // colour . either 'R' or 'B'
//                 this->_root->parent = NULL; // required at time of rechecking.
//             }
//             my_node *get_root()
//             {
//                 return this->_root;
//             }
//             my_node *get_new_node(int data)
//             {
//                 my_node *new_node = new my_node;
//                 new_node->data = data;
//                 new_node->left = NULL; // left subtree
//                 new_node->right = NULL; // right subtree
//                 new_node->color = false; // colour . either 'R' or 'B'
//                 new_node->parent = NULL; // required at time of rechecking.
//                 return new_node;
//             }
//             my_node *rotateLeft(my_node *node)
//             {
//                 my_node *right_node = node->right;

//                 node->right = right_node->left;
//                 if (node->right)
//                     node->right->parent = node;
                
//                 right_node->parent = node->parent;
                
                
//                 if (node->parent)
//                 {
//                     if (node->parent->left == node)
//                         node->parent->left = right_node;
//                     else if (node->parent->right == node)
//                         node->parent->right = right_node;  
//                 // std::cout << "HERE" << std::endl;      
//                 }
//                 else 
//                     _root = right_node;
//                 right_node->left = node;
//                 node->parent = right_node;

//                 return(right_node);
//             } 

//             my_node *rotateRight(my_node *node)
//             {
//                 my_node *left_node = node->left;

//                 node->left = left_node->right;

//                 if (node->left)
//                     node->left->parent = node;
//                 left_node->parent = node->parent;
//                 if (node->parent)
//                 {
//                     if (node->parent->right == node)
//                         node->parent->right = left_node;
//                     else if (node->parent->left == node)
//                         node->parent->left = left_node;        
//                 }
//                 else
//                     _root = left_node; 
//                 left_node->right = node;
//                 node->parent = left_node;
//                 return(left_node);
//             }

//             void printHelper(my_node *root, std::string indent, bool last) 
//             {
//                 if (root != NULL) 
//                 {
//                     std::cout << indent;
//                     if (last) 
//                     {
//                         if (!root->parent)
//                         {
//                             std::cout << "|____";
//                             indent += "   ";
//                         }
//                         else
//                         {
//                             std::cout << "R----";
//                             indent += "   ";            
//                         }
//                     } 
//                     else
//                     {
//                         std::cout << "L----";
//                         indent += "|  ";
//                     }
//                     std::string sColor = root->color == 1 ? "BLACK" : "RED";
//                     if (root->color == -1)
//                         sColor = "Double_Black";
//                     std::cout << root->data << "(" << sColor << ")" << std::endl;
//                     printHelper(root->left, indent, false);
//                     printHelper(root->right, indent, true);
//                 }
//             }

//             my_node *    insert_node(my_node *root, my_node *new_node)
//             {
//                 if (root == NULL)
//                 {
//                     return new_node;
//                 }
                
//                 if (new_node->data > root->data)
//                 {
//                     root->right = insert_node(root->right, new_node);
//                     root->right->parent = root;
//                 }
//                 else if (new_node->data < root->data)
//                 {
//                     root->left = insert_node(root->left, new_node);
//                     root->left->parent = root;
//                 }
//                 return root;
//             }
            
//             my_node * delete_node(my_node *node)
//             {
//                 my_node *parent;
//                 if (node == _root && !node->right && !node->left)
//                 {
//                     node = NULL;
//                     _root = NULL;
//                     delete node;
//                     return NULL;
//                 }
//                 else if (!node->left && !node->right)
//                 {
//                     parent = node->parent;
//                     if (parent->left == node)
//                         parent->left = NULL;
//                     else
//                         parent->right = NULL;
//                     delete node;
//                 }
//                 return node;
//             }
//             void  balance_my_tree_after_del(my_node *node)
//             {

//                 if (!node->color)
//                 {
//                     return ;
//                 }
//                 else if (node == this->get_root())
//                 {
//                     node->color = 1;
//                     return ;
//                 }
//                 else 
//                 {
//                     my_node *sibling = (node == node->parent->right) ? (sibling = node->parent->left) : (sibling = node->parent->right);
//                     //std::cout << "SIBLING IS :" <<  sibling->data << std::endl;
//                     //std::cout  << sibling->data << std::endl;
//                     // std::cout << "SIBLING : " << sibling->data << std::endl;
//                     // std::cout << "node : " << node->data << std::endl;
//                     // std::cout << "Parent : " << node->parent->data << std::endl << std::endl;
//                     //delete_node(node);
//                     //case 1 : sibling is black
//                     if (sibling && sibling->color)
//                     {
//                         // case1.1 : sibling is black and its children are black as well
//                         if ((!sibling->left || sibling->left->color) && (!sibling->right || sibling->right->color))
//                         {
//                             //std::cout << "?";
//                             my_node *parent;
//                             parent = node->parent;
//                             parent->color = (parent->color == 1) ? (parent->color = -1) : (parent->color = 1);
//                             sibling->color = 0;
//                             node->color = 1;
//                             if (parent->color == -1)
//                                 balance_my_tree_after_del(parent);
//                             return ;
//                         }
//                         if (node == node->parent->left)
//                         {
//                             my_node *parent;
//                             parent = node->parent;
//                             if ((!sibling->right || sibling->right->color) && (sibling->left && !sibling->left->color))
//                             {
//                                 std::swap(sibling->color, sibling->left->color);
//                                 rotateRight(sibling);
//                                 this->balance_my_tree_after_del(node);
//                             }
//                             else if ( (sibling->right && !sibling->right->color) && (!sibling->left || sibling->left->color))
//                             {
//                                 std::swap(parent->color, sibling->color);
//                                 rotateLeft(parent);
//                                 sibling->right->color = 1;
//                                 node->color = 1;
//                             }
//                         }
//                         else 
//                         {
//                             my_node *parent;
//                             parent = node->parent;

//                             if ((!sibling->left || sibling->left->color) && !sibling->right->color)
//                             {
//                                 std::swap(sibling->color, sibling->right->color);
//                                 rotateLeft(sibling);
//                                 this->balance_my_tree_after_del(node);
//                             }
//                             else if (!sibling->left->color && (!sibling->right || sibling->right->color))
//                             {
//                                 std::swap(parent->color, sibling->color);
//                                 rotateRight(parent);
//                                 sibling->left->color = 1;
//                                 node->color = 1;
//                             }
//                         }

//                     }
//                     //case 2: Sibling is red and children are black
//                     else if (sibling && !sibling->color)
//                     {
//                         //steps are : 
//                         //1)Swap color of sibling and parent 
//                         //2)rotate parent to node direction (our db) and reapply cases 
//                         my_node *parent;
//                         parent = node->parent;

//                         std::swap(sibling->color, parent->color);
//                         if (parent->left == node)
//                             rotateLeft(parent);
//                         else
//                             rotateRight(parent);
//                         this->balance_my_tree_after_del(node);
//                     }
//                 }
//                 return;
//             }
//             void    remove(my_node *node)
//             {
//                 if (node == _root && !node->right && !node->left)
//                 {
//                     this->delete_node(node);
//                     return ;
//                 }
//                 else if (!node->right && !node->left)
//                 {
//                     this->balance_my_tree_after_del(node);
//                     this->delete_node(node);
//                 }
//                 else
//                 {
//                     if (node->right)
//                     {
//                         my_node * my_successor = inorder_successor(node);
//                         node->data = my_successor->data;
//                         my_successor->color = (my_successor->color == 1) ? (my_successor->color = -1) : (my_successor->color = 1);
//                         this->remove(my_successor);
//                     }
//                     else
//                     {
//                         my_node * my_predecessor = inorder_predecessor(node);
//                         node->data = my_predecessor->data;
//                         my_predecessor->color = (my_predecessor->color == 1) ? (my_predecessor->color = -1) : (my_predecessor->color = 1);
//                         this->remove(my_predecessor);
//                     }
//                 }
//             }
//             my_node *    max_on_left(my_node * node)
//             {
//                 while(node->right)
//                 {
//                     node = node->right;
//                 }
//                 return node;
//             }
//             my_node *    min_on_right(my_node * node)
//             {
//                 while(node->left)
//                 {
//                     node = node->left;
//                 }
//                 return node;
//             }
//             my_node *   inorder_predecessor(my_node * node)
//             {
//                 if (!node)
//                     return NULL;
//                 if (node->left)
//                     return max_on_left(node->left);
//                 return node;
//             }

//             my_node *   inorder_successor(my_node * node)
//             {
//                 if (!node)
//                     return NULL;
//                 if (node->right)
//                     return min_on_right(node->right);
//                 return node;
//             }

//             void    balance_my_tree(my_node *node)
//             {
                
//                 if (node->parent)
//                 {
//                     my_node *parent = NULL;
//                     my_node *gp = NULL;
//                     // my_node *uncle = NULL;
//                     while(node->parent && (!node->color) && (!node->parent->color))
//                     { 
//                         //std::cout << "LOL" << std::endl;
//                         parent = node->parent;
//                         gp = node->parent->parent;
                    
//                         if (parent == gp->left)
//                         {
//                             my_node *uncle = gp->right;
//                             if (uncle && !uncle->color)
//                             {
//                                 //std::cout << "LOL1" << std::endl;
//                                 uncle->color = 1;
//                                 parent->color = 1;
//                                 if (gp->parent)
//                                     gp->color = 0;
//                                 node = gp;    
//                             }
//                             else 
//                             {
//                                 //std::cout << "LOL2" << std::endl;
//                                 if (node == parent->right)
//                                 {
//                                     rotateLeft(parent);
//                                     node = parent;
//                                     parent = node->parent;
//                                 }
                                
//                                 rotateRight(gp);
//                                 std::swap(gp->color, parent->color);
//                                 node = parent;
                                
//                             }
//                         }
//                         else
//                         {
//                             my_node *uncle = gp->left;
//                             if (uncle && !uncle->color)
//                             {
//                                 //std::cout << "LOL3" << std::endl;
//                                 uncle->color = 1;
//                                 parent->color = 1;
//                                 if (gp->parent)
//                                     gp->color = 0;
//                                 node = gp;   
//                             }
//                             else 
//                             {
//                                 //std::cout << "LOL4" << std::endl;
//                                 if (node == parent->left)
//                                 {
//                                     rotateRight(parent);
//                                     node = parent;
//                                     parent = node->parent;
//                                 }
//                                 rotateLeft(gp);
//                                 std::swap(gp->color, parent->color);
//                                 node = parent;
//                             }
//                         }

//                     }
//                 }
//                 else 
//                 {
//                     node->color = 1;
//                 }
//             }
//         private:
//             my_node *_root;
//     };
// }




// bool ll = false;
// bool rr = false;
// bool lr = false;
// bool rl = false;

int main()
{
    //ft::map<int, char>::iterator my_it, my_it1, tmp;

     //std::cout << (*my_it).data->second
    ft::pair<int, int> nice0(0,50);
    ft::pair<int, int> nice1(1,30);
    ft::pair<int, int> nice2(2,15);
    ft::pair<int, int> nice3(3,35);
    ft::pair<int, int> nice4(4,65);
    ft::pair<int, int> nice5(5,70);
    ft::pair<int, int> nice6(6,68);
    ft::pair<int, int> nice7(7,80);
    ft::pair<int, int> nice8(8,90);
    ft::pair<int, int> nice9(9,55);
    ft::RBTree<int, int> ok;

    ft::RBTree<int, int>::my_node *test;
    //test = ok.get_root();
    test =  ok.insert(ok.get_new_node(nice0));
//     // std::cout << test->data->second << std::endl;
//     //std::cout << ok.get_root()->data->second << std::endl;
//     //ok.balance_my_tree(ok.get_root());
//     ok.printHelper(ok.get_root(), "", true);
    
//     //my_node *okk_1 = ok.get_new_node(50);
    ft::RBTree<int, int>::my_node *okk_2 = ok.get_new_node(nice1);
    ft::RBTree<int, int>::my_node *okk_3 = ok.get_new_node(nice2);
    ft::RBTree<int, int>::my_node *okk_4 = ok.get_new_node(nice3);
    ft::RBTree<int, int>::my_node *okk_5 = ok.get_new_node(nice4);
    ft::RBTree<int, int>::my_node *okk_6 = ok.get_new_node(nice5);
    ft::RBTree<int, int>::my_node *okk_7 = ok.get_new_node(nice6);
    ft::RBTree<int, int>::my_node *okk_8 = ok.get_new_node(nice7);
    ft::RBTree<int, int>::my_node *okk_9 = ok.get_new_node(nice8);
    ft::RBTree<int, int>::my_node *okk_10 = ok.get_new_node(nice9);


// // //     // my_node *okk_9 = ok.get_new_node(28);
// // //     // my_node *okk_10 = ok.get_new_node(1);
// // //     // my_node *okk_11 = ok.get_new_node(70);
// // //     // ok.insert_node(ok.get_root(), okk_1);
// //    // std::cout << ok.get_new_node(nice1)->data->second << std::endl;
//     //ok.insert_node(ok.get_root(), ok.get_new_node(nice1));
//     std::cout << std::endl << std::endl << std::endl;
//     ok.insert(okk_2);
    
    ok.insert(okk_3);
    ok.insert(okk_4);
    ok.insert(okk_5);
    ok.insert(okk_6);
    ok.insert(okk_7);
    ok.insert(okk_8);
    ok.insert(okk_9);
    ok.insert(okk_10);
    ok.printHelper(ok.get_root(), "", true);


    ft::RBTree<int, int>::iterator it;
    
    it = ok.begin();
    size_t i = ok.size();
    // for(; it != ok.end();it++)
    //     i++;
    std::cout << "SIZE IS " << i << std::endl;

        //std::cout << *it << std::endl;
    // std::cout << "HI "<< std::endl;
    // it--;
    // std::cout << "FIRST ITER : " << (*it).data->second << std::endl;
    // it--;
    // std::cout << "FIRST ITER : " << (*it).data->second << std::endl;
    // it--;
    // std::cout << "FIRST ITER : " << (*it).data->second << std::endl;
    // it++;
    // std::cout << "FIRST ITER : " << (*it).data->second << std::endl;
    // it++;
    // std::cout << "FIRST ITER : " << (*it).data->second << std::endl;
    // for(; it != ok.begin() ; it--)
    // {
    //     std::cout << "FIRST ITER : " << (*it).second << std::endl;
    // }


    
    //ft::map<int, char>::iterator my_it, my_it1, tmp;
//     // okk_1->color = 1;
//     okk_2->color = 1;
//     okk_3->color = 1;
//     okk_4->color = 1;
//     okk_5->color = 1;
//     //okk_6->color = 1;
//     okk_7->color = 1;
//     okk_8->color = 1;
//     okk_10->color = 1;

// //     ok.balance_my_tree(ok.get_root());
// //    // ok.printHelper(ok.get_root(), "", true);
// //     ok.insert_node(ok.get_root(), okk_2);
// //     ok.balance_my_tree(okk_2);

// //     ok.insert_node(ok.get_root(), okk_3);
// //     ok.balance_my_tree(okk_3);

// //     ok.insert_node(ok.get_root(), okk_4);
// //     ok.balance_my_tree(okk_4);

// //     ok.insert_node(ok.get_root(), okk_5);
// //     ok.balance_my_tree(okk_5);

// //     ok.insert_node(ok.get_root(), okk_6);
// //     ok.balance_my_tree(okk_6);

// //     okk_3->color = 1;
// //     okk_4->color = 1;
// //     okk_5->color = 1;
// //     // okk_6->color = 1;
    
// //     ok.insert_node(ok.get_root(), okk_7);
// //     okk_7->color = 1;
// //     // ok.balance_my_tree(okk_7);

// //     ok.insert_node(ok.get_root(), okk_8);
// //     okk_8->color = 1;
//     // ok.balance_my_tree(okk_8);
//     // okk_6->color = 0;
//     // okk_7->color = 1;
//     // okk_8->color = 1;
//     // ok.insert_node(ok.get_root(), okk_9);
//     // ok.balance_my_tree(okk_9);

//     // ok.insert_node(ok.get_root(), okk_10);
//     // ok.balance_my_tree(okk_10);

//     // ok.insert_node(ok.get_root(), okk_11);
//     // ok.balance_my_tree(okk_11);
    
//     // ok.insert_node(ok.get_root(), ok.get_new_node(16));
//     // ok.balance_my_tree(ok.get_root());

//     // ok.insert_node(ok.get_root(), ok.get_new_node(30));
//     // ok.balance_my_tree(ok.get_root());

//     // ok.insert_node(ok.get_root(), ok.get_new_node(25));
//     // ok.balance_my_tree(ok.get_root());
    
//     ok.printHelper(ok.get_root(), "", true);
//     std::cout << std::endl << std::endl << std::endl;
    
//     ok.remove(okk_10);
//     ok.remove(okk_2);
//     ok.remove(okk_9);
//     ok.remove(okk_8);
//     ok.remove(ok.get_root());
//     ok.remove(ok.get_root()->left);
//     std::cout << ok.get_root()->left->data << std::endl; 
//     ok.remove(ok.get_root()->left);
//     ok.remove(ok.get_root()->left);
//     ok.remove(ok.get_root());
//     ok.remove(ok.get_root());
//     //std::cout <<  ok.get_root()->left->data << std::endl;
//     ok.printHelper(ok.get_root(), "", true);
//     //  ok.remove(ok.get_root()->left);
//     // //  ok.balance_my_tree_after_del(okk_10);
//     // //  ok.delete_node(okk_10);

//     // // std::cout << okk_2->data << std::endl;
//     // // ok.balance_my_tree_after_del(okk_2);
//     // //  ok.delete_node(okk_2);
    
//     //  ok.printHelper(ok.get_root(), "", true);
//     //std::cout << okk_11->data << std::endl;
//     // my_node * pt =  ok.max_on_left(ok.get_root()->left);
//     // my_node * pt2 =  ok.min_on_right(ok.get_root()->right);
//     // std::cout << pt->data << std::endl;
//     // std::cout << pt2->data << std::endl;

//     // insert_node(&ok, &okk);
//     // insert_node(&ok, &okk_2);
//     // insert_node(&ok, &okk_3);
//     //  //printHelper(&ok, "", false);
//     //  balance_my_tree(&okk_3);

//     //  insert_node(&ok, &okk_4);
//     //  //printHelper(&ok, "", false);
//     //       std::cout <<  std::endl;
//     //  std::cout <<  std::endl;
//     //  std::cout <<  std::endl;
//     //  balance_my_tree(&okk_4);
//     //  //printHelper(&ok, "", false);
//     //  insert_node(&ok, &okk_5);
//     //  balance_my_tree(&okk_5);
//     // insert_node(&ok, &okk_6);
//     // balance_my_tree(&okk_6);
//     // insert_node(&ok, &okk_7);
//     // std::cout << "XDD" << std::endl << std::endl;
//     // //balance_my_tree(&okk_7);
//     //  printHelper(&ok, "", true);
}
