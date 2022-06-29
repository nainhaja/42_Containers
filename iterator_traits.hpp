#include <iostream>

#pragma once

namespace ft
{
    
    template <class T>

    struct iterator_traits {
    typedef typename T::value_type          value_type;
    typedef typename T::Distance            difference_type;
    typedef typename T::Pointer             pointer;
    typedef typename T::Reference           reference;
    };

    template <class T>

    struct iterator_traits<T*> {
    typedef typename T::value_type          value_type;
    typedef T                      difference_type;
    typedef T*                     pointer;
    typedef T&                     reference;
    };

    template <class T>

    struct iterator_traits<const T*> {
    typedef typename T::value_type          value_type;
    typedef T                      difference_type;
    typedef const T*                        pointer;
    typedef const T&                        reference;
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