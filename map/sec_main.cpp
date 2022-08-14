#include<iostream>
#include "RBTree.hpp"
#include "../equal.hpp"
#include "map.hpp"
#include <map>
struct classcomp
{
    bool operator()(const char &lhs, const char &rhs) const
    {
        return lhs < rhs;
    }
};
int main()
{
    std::map<char, int, classcomp> fourth;  // class as Compare
    ft::map<char, int, classcomp> m_fourth; // class as Compare



    std::map<char, int, classcomp>::iterator it_fourth=fourth.begin();  // class as Compare
    ft::map<char, int, classcomp>::iterator it_m_fourth = m_fourth.begin(); // class as Compare

    // std::cout << (*it_fourth).first << std::endl;
    // std::cout << (*it_m_fourth).first << std::endl;
    //cond = first.size() == m_first.size() && comparemaps(first.begin(), first.end(), m_first.begin(), m_first.end());
}