

#include "vector.hpp"
#include <vector>
#include <iostream>

#define EQUAL(x) ((x) ? (std::cout << "\033[1;32mAC\033[0m\n") : (std::cout << "\033[1;31mWA\033[0m\n"))
int main()
{

    // ft::vector<int> k(3, 3);
    // ft::vector<int> kk(5, 99);
    // k.push_back(2);
    // k.push_back(7);
    // k.pop_back();
        ft::vector<int> v(4, 5);
        ft::vector<int>::reverse_iterator my_rit2(v.end()), ok;
        ft::vector<int>::const_reverse_iterator c_it, c_ob(v.end());
        c_it = my_rit2;
        ok = my_rit2;
        std::cout << *c_it << " | " << *my_rit2 << "|" << *ok << std::endl;
            //         std::vector<std::string> v;
            // ft::vector<std::string> ft_v;
            // v.insert(v.begin(), 100, "hello");
            // ft_v.insert(ft_v.begin(), 100, "hello");
            //ft_v.begin()->length();
        // ft::vector<int> v(4, 5);
        // ft::vector<int>::reverse_iterator my_rit2(v.end());
        // ft::vector<int>::const_reverse_iterator c_it, c_ob(v.end());
        // //ft::vector<int>::reverse_iterator t(c_it);
        // c_it = my_rit2;

    // std::cout << *rit_1 << std::endl;
    //std::cout << c_ob[1] << std::endl;
        //     std::vector<std::string> v(3, "hello");
        // std::vector<std::string>::iterator it = v.begin();
    // ft::vector<int>::iterator it = k.begin();
    // std::cout << "My size is : " << k.size() << std::endl;
    // for(; it != k.end(); it++)
    //     std::cout << *it << std::endl;
    // ft::vector<int> sec(5, 88);
    // if (sec > k)
    //     std::cout << "nadi";
        // ft::vector<std::string> my_v(3, "hello");
        // ft::vector<std::string>::iterator my_it = my_v.begin();
        // /*---------------------------------------------- */
        // EQUAL(it->length() == my_it->length());
    // ft::vector<int> k;

    // k.assign(5, 2);
    // ft::vector<int>::iterator it = k.begin();
    // ft::vector<int> a;
    // a.assign(it +1, it+3);
    // ft::vector<int>::iterator it2 = a.begin();
    // std::cout << "My size is : " << a.size() << std::endl;
    // for(; it2 != a.end(); it2++)
    //     std::cout << *it2 << std::endl;
    
    // sec = k;
    // it = sec.begin();
    // std::cout << "My size is : " << sec.size() << std::endl;
    // for(; it != sec.end(); it++)
    //     std::cout << *it << std::endl;
    
    // ft::vector<int>::iterator itt = kk.begin();
    // ft::vector<int>::iterator itt2 = k.begin();
    // k.insert(itt2 + 2,itt + 1, itt + 3 );
    // std::cout << "My size is : " << k.size() << std::endl;
    // for(it = k.begin(); it != k.end(); it++)
    //     std::cout << *it << std::endl;

    
    // k.erase(itt + 2, itt+4);
    // //k.insert(it+1, kk.begin(), kk.end());
    // std::cout << "My size is : " << k.size() << std::endl;
    //  for(; itt != k.end(); itt++)
    //     std::cout << *itt << std::endl;
    
}