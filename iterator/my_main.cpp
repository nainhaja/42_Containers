#include<iostream>

typedef struct node
{
    int data;
    node *left;
    node *right;
    bool color;
    node *parent;
}node;

class Node
{
    public:
        int data;
        Node *left;
        Node *right;
        bool color;
        Node *parent;

        Node()
        {
            this->left = NULL; // left subtree
            this->right = NULL; // right subtree
            this->color = false; // colour . either 'R' or 'B'
            this->parent = NULL; // required at time of rechecking.
        }
        Node(int data)
        {
            //super();
            this->data = data;   // only including data. not key
            this->left = NULL; // left subtree
            this->right = NULL; // right subtree
            this->color = false; // colour . either 'R' or 'B'
            this->parent = NULL; // required at time of rechecking.
        }
};

Node *rotateLeft(Node *node)
{
    Node *right_node = node->right;

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
        std::cout << "HERE" << std::endl;      
    }
    else
        std::cout << "HERE2" << node->data << std::endl; 
    right_node->left = node;
    node->parent = right_node;

    return(right_node);
} 

 Node *rotateRight(Node *node)
{
    Node *left_node = node->left;

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

    left_node->right = node;
    node->parent = left_node;
    return(left_node);
}

void printHelper(Node *root, std::string indent, bool last) 
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
        std::cout << root->data << "(" << sColor << ")" << std::endl;
        printHelper(root->left, indent, false);
        printHelper(root->right, indent, true);
    }
}

Node *    insert_node(Node *root, Node *new_node)
{
    if (!root)
    {
        return new_node;
    }
    
    if (new_node->data > root->data)
    {
        root->right = insert_node(root->right, new_node);
        root->right->parent = root;
    }
    else if (new_node->data < root->data)
    {
        root->left = insert_node(root->left, new_node);
        root->left->parent = root;
    }
    return root;
}

void    balance_my_tree(Node *my_node)
{
    
    if (my_node->parent)
    {
        Node *parent = NULL;
        Node *gp = NULL;
        // Node *uncle = NULL;
        while(my_node->parent && (!my_node->color) && (!my_node->parent->color))
        { 
            std::cout << "LOL" << std::endl;
            parent = my_node->parent;
            gp = my_node->parent->parent;
           
            if (parent == gp->left)
            {
                Node *uncle = gp->right;
                if (uncle && !uncle->color)
                {
                    std::cout << "LOL1" << std::endl;
                    uncle->color = 1;
                    parent->color = 1;
                    if (gp->parent)
                        gp->color = 0;
                    my_node = gp;    
                }
                else 
                {
                    std::cout << "LOL2" << std::endl;
                    if (my_node == parent->right)
                    {
                        rotateLeft(parent);
                        my_node = parent;
                        parent = my_node->parent;
                    }
                    
                    rotateRight(gp);
                    std::swap(gp->color, parent->color);
                    my_node = parent;
                    
                }
            }
            else
            {
                Node *uncle = gp->left;
                if (uncle && !uncle->color)
                {
                    std::cout << "LOL3" << std::endl;
                    uncle->color = 1;
                    parent->color = 1;
                    if (gp->parent)
                        gp->color = 0;
                    my_node = gp;   
                }
                else 
                {
                    std::cout << "LOL4" << std::endl;
                    if (my_node == parent->left)
                    {
                        rotateRight(parent);
                        my_node = parent;
                        parent = my_node->parent;
                    }
                    rotateLeft(gp);
                    std::swap(gp->color, parent->color);
                    my_node = parent;
                }
            }

        }
    }
    else 
    {
        my_node->color = 1;
    }
}

bool ll = false;
bool rr = false;
bool lr = false;
bool rl = false;

int main()
{
    Node ok(10);
    
    balance_my_tree(&ok);
    printHelper(&ok, "", true);
    Node okk(18);
    Node okk_2(7);
    Node okk_3(15);
    Node okk_4(16);
    Node okk_5(30);
    Node okk_6(25);
    Node okk_7(40);
    insert_node(&ok, &okk);
    insert_node(&ok, &okk_2);
    insert_node(&ok, &okk_3);
     //printHelper(&ok, "", false);
     balance_my_tree(&okk_3);

     insert_node(&ok, &okk_4);
     //printHelper(&ok, "", false);
          std::cout <<  std::endl;
     std::cout <<  std::endl;
     std::cout <<  std::endl;
     balance_my_tree(&okk_4);
     //printHelper(&ok, "", false);
     insert_node(&ok, &okk_5);
     balance_my_tree(&okk_5);
    insert_node(&ok, &okk_6);
    balance_my_tree(&okk_6);
    insert_node(&ok, &okk_7);
    std::cout << "XDD" << std::endl << std::endl;
    //balance_my_tree(&okk_7);
     printHelper(&ok, "", true);
}