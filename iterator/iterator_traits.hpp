#include <iostream>
#include <stddef.h>

#pragma once

namespace ft
{


    
    template <class T>

    struct iterator_traits {
    typedef typename T::value_type          value_type;
    typedef typename T::difference_type     difference_type;
    typedef typename T::pointer             pointer;
    typedef typename T::reference           reference;
    typedef typename T::iterator_category            iterator_category;
    };

    template <class T>

    struct iterator_traits<T*> {
    typedef T                      value_type;
    typedef ptrdiff_t              difference_type;
    typedef T*                     pointer;
    typedef T&                     reference;
    typedef typename std::random_access_iterator_tag iterator_category;
    };

    template <class T>

    struct iterator_traits<const T*> {
    typedef T                              value_type;
    typedef ptrdiff_t                      difference_type;
    typedef const T*                        pointer;
    typedef const T&                        reference;
    typedef typename std::random_access_iterator_tag iterator_category;
    };
    
    template <class Category, class T, class Distance = ptrdiff_t,
          class Pointer = T*, class Reference = T&>

    struct iterator {
    typedef T         value_type;
    typedef Distance  difference_type;
    typedef Pointer   pointer;
    typedef Reference reference;
    typedef Category  iterator_category;
  };
}