#ifndef MXCPL_TYPE_TRAITS_HPP
#define MXCPL_TYPE_TRAITS_HPP
// C++ 17
// ==============================================================================
// COPYRIGHT NOTICE: This file is part of the Multi-X Computational Physics
// Libraries (mxCPL) Project Contact: Rami M Younis Copyright (c) 2020 The
// University of Tulsa, all rights reserved
// ==============================================================================
// //

/** @file mxcpl_type_traits.hpp
 */

#include <iterator>  // provides iterator_traits
#include <type_traits>

namespace mxcpl::type_traits {

// is_iterable
// is type T either i) a pointer to a type, or has all the following
// typedefs that are publicaly accessible:
// T::difference_type
// T::value_type
// T::pointer
// T::reference
// T::iterator_category
template <typename T, typename = void>
struct is_iterable : std::false_type {};

template <typename T>
struct is_iterable<
    T, std::void_t<typename std::iterator_traits<T>::difference_type> >
    : std::true_type {};

template <typename T>
constexpr bool is_iterable_v = is_iterable<T>::value;

// is_indexable_object
// test if type T has operator[]( S ) where S is an integral index type
// Note that T must have the operator publicaly accessible and defined
// as a member function. This therefore excludes pointers, so that for
// example is_indexable_object_v< double * > is false but
// is_indexable_object_v< std::vector<double> > is true, and
// is_indexable_object_v< std::vector<double>::iterator > is true
template <typename T, typename S, typename = void>
struct is_indexable_object : std::false_type {};

template <typename T, typename S>
struct is_indexable_object<
    T, S,
    std::void_t<decltype(std::declval<T>().operator[](std::declval<S>()))> >
    : std::true_type {};

template <typename T, typename S = int>
constexpr bool is_indexable_object_v = is_indexable_object<T, S>::value;

// is_indexable_object
// test if type T is_indexable_object by S, OR is a pointer type with
// S being an integral type
template <typename T, typename S = int>
constexpr bool is_indexable_v = is_indexable_object_v<T, S> ||
                                (std::is_pointer<T>::value &&
                                 std::is_integral<S>::value);
}  // namespace mxcpl::type_traits
#endif  // MXCPL_TYPE_TRAITS_HPP
