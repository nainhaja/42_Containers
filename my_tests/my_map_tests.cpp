#include<iostream>
#include "../map/RBTree.hpp"
#include "../equal.hpp"
#include "../map/map.hpp"
#include <map>
#include <random>
#include <vector>

int main()
{
    {
        std::map<int, int> m;
        ft::map<int, int> ft_m;

        for(size_t i=0; i < 5;i++)
        {
            m.insert(std::make_pair(i, i+10));
            ft_m.insert(ft::make_pair(i, i+10));
        }
        std::map<int, int>::iterator m_it=m.begin();
        ft::map<int, int>::iterator ft_mit = ft_m.begin();

        for(size_t i=0; i < 5;i++)
        {
            std::cout << "M    : Key: " << m_it->first << "| value: " << m_it->second << std::endl;
            std::cout << "FT_M : Key: " << ft_mit->first << "| value: " << ft_mit->second << std::endl;
            std::cout << std::endl;
            m_it++;
            ft_mit++;
        }

        std::map<int, int>::iterator m_it2=m.find(2);
        ft::map<int, int>::iterator ft_mit2 = ft_m.find(2);

        std::cout << "Element found : " << std::endl; 
        std::cout << "M    : Key: " << m_it2->first << "| value: " << m_it2->second << std::endl;
        std::cout << "FT_M : Key: " << ft_mit2->first << "| value: " << ft_mit2->second << std::endl;
        m.erase(m_it2);
        ft_m.erase(ft_mit2);

        m_it2=m.find(1);
        ft_mit2 = ft_m.find(1);
        m_it2++;
        ft_mit2++;

        std::cout << "Checking if Elements are erased " << std::endl;
        std::cout << "M    : Key: " << m_it2->first << "| value: " << m_it2->second << std::endl;
        std::cout << "FT_M : Key: " << ft_mit2->first << "| value: " << ft_mit2->second << std::endl; 
        std::cout << std::endl;      
    }

    {
        std::map<int, int> m;
        ft::map<int, int> ft_m;

        m.insert(std::make_pair(0, 10));
        ft_m.insert(ft::make_pair(0, 10));

        m.insert(std::make_pair(0, 21));
        ft_m.insert(ft::make_pair(0, 21));

        std::map<int, int>::iterator m_it=m.begin();
        ft::map<int, int>::iterator ft_mit = ft_m.begin();

        std::cout << "M    : Key: " << m_it->first << "| value: " << m_it->second << std::endl;
        std::cout << "FT_M : Key: " << ft_mit->first << "| value: " << ft_mit->second << std::endl;  
         std::cout << std::endl;      
    }

    {
        std::map<int, int> m;
        ft::map<int, int> ft_m;

        for(size_t i=0; i < 5;i++)
        {
            m.insert(std::make_pair(i, i+10));
            ft_m.insert(ft::make_pair(i, i+10));
        }
        std::map<int, int>::iterator m_it=m.find(1);
        ft::map<int, int>::iterator ft_mit = ft_m.find(1);

        std::map<int, int>::iterator m_it2=m.find(3);
        ft::map<int, int>::iterator ft_mit2 = ft_m.find(3);

        m.erase(m_it, m_it2);
        ft_m.erase(ft_mit, ft_mit2);
        std::cout << "ERASING ELEMENTS " << std::endl;
        std::map<int, int>::iterator m_it3=m.begin();
        ft::map<int, int>::iterator ft_mit3 = ft_m.begin();
        for(size_t i=0; i < 3;i++)
        {
            std::cout << "M    : Key: " << m_it3->first << "| value: " << m_it3->second << std::endl;
            std::cout << "FT_M : Key: " << ft_mit3->first << "| value: " << ft_mit3->second << std::endl;
            std::cout << std::endl;
            m_it3++;
            ft_mit3++;
        }
        m.clear();
        ft_m.clear();
        std::cout << "ERASING ALL ELEMENTS " << std::endl;
        for(size_t i=0; i < m.size();i++)
        {
            std::cout << "M    : Key: " << m_it3->first << "| value: " << m_it3->second << std::endl;
            std::cout << "FT_M : Key: " << ft_mit3->first << "| value: " << ft_mit3->second << std::endl;
            std::cout << std::endl;
            m_it3++;
            ft_mit3++;
        }
    }

}