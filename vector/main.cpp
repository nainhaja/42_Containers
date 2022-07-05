
#include "vector.hpp"


int main()
{
    ft::vector<int> k(5, 3);
    k.push_back(2);
    k.push_back(7);
    k.pop_back();
    
    ft::vector<int>::iterator it = k.begin();
    k.insert(it+2, 4);
    for(; it != k.end(); it++)
        std::cout << *it << std::endl;
    
}