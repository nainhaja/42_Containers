#include <iostream>
#include <memory.h>

#include <iostream>    
#include <type_traits>


#ifndef ENABLE_IF_HPP
# define ENABLE_IF_HPP

namespace ft
{
    template<bool Cond, class T = void>
        struct enable_if {};
    template<class T>
        struct enable_if<true, T> { typedef T type; };
}

#endif