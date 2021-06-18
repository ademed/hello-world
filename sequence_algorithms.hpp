#ifndef SEQUENCE_ALGORITHMS_HPP
#define SEQUENCE_ALGORITHMS_HPP
 //C++ 17
 //==============================================================================
 //COPYRIGHT NOTICE: This file is part of the Multi-X Computational Physics
 //Libraries (mxCPL) Project Contact: Rami M Younis Copyright (c) 2020 The
 //University of Tulsa, all rights reserved
 //==============================================================================
 //

/** @file sequence_algorithms.hpp
 */

#include <type_traits>

#include "mxcpl_type_traits.hpp"

namespace mxcpl::utilities {
 //execution policy functors for algorithms on sequences

template <typename Policy = void>
struct copy_n {
  template <typename SizeType, typename ForwardIt, typename InputIt>
  static inline void apply(SizeType _N, ForwardIt&& _a, InputIt&& _b) noexcept {
    if constexpr (mxcpl::type_traits::is_iterable_v<
                      std::remove_reference_t<ForwardIt> >) 
    {
      if constexpr (mxcpl::type_traits::is_iterable_v<
                        std::remove_reference_t<InputIt> >) 
      {
        for (; _N > 0; --_N) {
          *_a = *_b;
          ++_a;
          ++_b;
        }
      } 
      else if constexpr (mxcpl::type_traits::is_indexable_v<
                               std::remove_reference_t<InputIt> >) 
      {
        for (SizeType i{0}; i < _N; ++i) {
          *_a = _b[i];
          ++_a;
        }
      } 
      else 
      {
        for (; _N > 0; --_N) {
          *_a = _b;
          ++_a;
        }
      }
    } 
    else if constexpr (mxcpl::type_traits::is_indexable_v<ForwardIt>) 
    {
      if constexpr (mxcpl::type_traits::is_iterable_v<
                        std::remove_reference_t<InputIt> >) 
      {
        for (SizeType i{0}; i < _N; ++i) {
          _a[i] = *_b;
          ++_b;
        }
      }
      else if constexpr (mxcpl::type_traits::is_indexable_v<
                               std::remove_reference_t<InputIt> >) 
      {
        for (SizeType i{0}; i < _N; ++i) {
          _a[i] = _b[i];
        }
      }
      else 
      {
        for (SizeType i{0}; i < _N; ++i) {
          _a[i] = _b;
        }
      }
    } 
    else 
    {
      _a = _b;
    }
  }
};  // namespace mxcpl::utilities

template <typename Policy = void>
struct copy_transformed_n {
  template <typename SizeType, typename Callable, typename ForwardIt,
            typename... InputIt>
  static inline void apply(SizeType _N, Callable&& _F, ForwardIt _a,
                           InputIt... _iters) noexcept {
    if constexpr (mxcpl::type_traits::is_iterable_v<ForwardIt> &&
                  mxcpl::type_traits::is_iterable_v<InputIt...>) {
      for (; _N > 0; --_N) {
        *_a = _F((*_iters++)...);
        ++_a;
      }
    } else if constexpr (mxcpl::type_traits::is_indexable_v<ForwardIt> &&
                         (mxcpl::type_traits::is_indexable_v<InputIt...>)) {
      for (SizeType i{0}; i < _N; ++i) {
        _a[i] = _F((_iters[i])...);
      }
    } else {
    }
  }
};

template <typename Policy = void>
struct transform_n {
  template <typename SizeType, typename Callable, typename ForwardIt,
            typename... InputIt>
  static inline void apply(SizeType _N, Callable&& _F, ForwardIt _a,
                           InputIt... _iters) noexcept {
    if constexpr (mxcpl::type_traits::is_iterable_v<ForwardIt> &&
                  mxcpl::type_traits::is_iterable_v<InputIt...>) {
      if constexpr (sizeof...(_iters) > 0) {
        for (; _N > 0; --_N) {
          _F(*_a, (*_iters++)...);
          ++_a;
        }
      } else {
        for (; _N > 0; --_N) {
          _F(*_a);
          ++_a;
        }
      }
    } else if constexpr (mxcpl::type_traits::is_indexable_v<ForwardIt> &&
                         mxcpl::type_traits::is_indexable_v<InputIt...>) {
      if constexpr (sizeof...(_iters) > 0) {
        for (SizeType i{0}; i < _N; ++i) {
          _F(_a[i], (_iters[i])...);
        }
      } else {
        for (SizeType i{0}; i < _N; ++i) {
          _F(_a[i]);
        }
      }
    } else {
    }
  }
};

////###################################################################
//// POLICY: Use OpenMP "omp parallel for simd construct"
////###################################################################
//
//template <std::size_t Align, std::size_t SIMD_vec_len>
//struct OMP_ParallelForSIMD {};
//
//template <>
//template <std::size_t Align, std::size_t SIMD_vec_len>
//struct fill_n<OMP_ParallelForSIMD<Align, SIMD_vec_len> > {
//  template <typename SizeType, typename ForwardIt, typename T>
//  static inline void apply(SizeType _N, ForwardIt _a, T&& _b) noexcept {
// TODO: I modified it, reverse it finally
//#pragma vector nontemporal
//#pragma omp parallel for simd schedule(static) num_threads(NCORES) \
//    simdlen(SIMD_vec_len) aligned(_a                               \
//                                  : Align)
//     for ( ; _N > 0; --_N ) {
//       *_a = _b;
//       ++_a;
//     }
//    for (std::size_t i = 0; i < N; i++) {
//      *_a = _b;
//      ++_a;
//    }
//  }
//};
//
//template <>
//template <std::size_t Align, std::size_t SIMD_vec_len>
//struct copy_n<OMP_ParallelForSIMD<Align, SIMD_vec_len> > {
//  template <typename SizeType, typename ForwardIt, typename InputIt>
//  static inline void apply(SizeType _N, ForwardIt _a, InputIt _b) noexcept {
//#pragma vector nontemporal
//#pragma omp parallel for simd schedule(static) num_threads(NCORES) \
//    simdlen(SIMD_vec_len) aligned(_a, _b                           \
//                                  : Align)
//    for (; _N > 0; --_N) {
//      *_a = *_b;
//      ++_a;
//      ++_b;
//    }
//  }
//};
//
//template <>
//template <std::size_t Align, std::size_t SIMD_vec_len>
//struct copy_transformed_n<OMP_ParallelForSIMD<Align, SIMD_vec_len> > {
//  template <typename SizeType, typename Callable, typename ForwardIt,
//            typename... InputIt>
//  static inline void apply(SizeType _N, Callable&& _F, ForwardIt _a,
//                           InputIt... _iters) noexcept {
//#pragma vector nontemporal
//#pragma omp parallel for simd schedule(static) num_threads(NCORES) \
//    simdlen(SIMD_vec_len) aligned(_a, _iters...                    \
//                                  : Align)
//    for (; _N > 0; --_N) {
//      *_a = _F(_iters...);
//      (++_iters)...;
//      ++_a;
//    }
//  };
//};
//
//template <>
//template <std::size_t Align, std::size_t SIMD_vec_len>
//struct transform_n<OMP_ParallelForSIMD<Align, SIMD_vec_len> > {
//  template <typename SizeType, typename Callable, typename ForwardIt,
//            typename... InputIt>
//  static inline void apply(SizeType _N, Callable&& _F, ForwardIt _a,
//                           InputIt... _iters) noexcept {
//#pragma omp parallel for simd schedule(static) num_threads(NCORES) \
//    simdlen(SIMD_vec_len) aligned(_a, _iters...                    \
//                                  : Align)
//    for (; _N > 0; --_N) {
//      _F(_a, _iters...);
//      (++_iters)...;
//      ++_a;
//    }
//  };
//};
//
//template <>
//template <std::size_t Align, std::size_t SIMD_vec_len>
//struct transform_noparam_n<OMP_ParallelForSIMD<Align, SIMD_vec_len> > {
//  template <typename SizeType, typename Callable, typename ForwardIt>
//  static inline void apply(SizeType _N, Callable&& _F, ForwardIt _a) noexcept {
//#pragma omp parallel for simd schedule(static) num_threads(NCORES) \
//    simdlen(SIMD_vec_len) aligned(_a, _iters...                    \
//                                  : Align)
//    for (; _N > 0; --_N) {
//      _F(_a);
//      ++_a;
//    }
//  };
//};
//
//template <>
//template <std::size_t Align, std::size_t SIMD_vec_len>
//struct i_fill_n<OMP_ParallelForSIMD<Align, SIMD_vec_len> > {
//  template <typename SizeType, typename Indexable, typename T>
//  static inline void apply(SizeType _N, Indexable& _a, T&& _b) noexcept {
//    const SizeType NCH = _N / SIMD_vec_len;
//#pragma omp parallel for schedule(static) num_threads(NCORES)
//    for (SizeType ch{0}; ch < NCH; ++ch) {
//      const SizeType offs = ch * SIMD_vec_len;
//      const SizeType NOFFS = offs + SIMD_vec_len;
//#pragma vector aligned nontemporal
//#pragma omp simd simdlen(SIMD_vec_len)
//      for (SizeType i{offs}; i < NOFFS; ++i) _a[i] = _b;
//    }
//    for (SizeType i{NCH * SIMD_vec_len}; i < _N; ++i) _a[i] = _b;
//  }
//};
//
//template <>
//template <std::size_t Align, std::size_t SIMD_vec_len>
//struct i_copy_n<OMP_ParallelForSIMD<Align, SIMD_vec_len> > {
//  template <typename SizeType, typename Indexable1, typename Indexable2>
//  static inline void apply(SizeType _N, Indexable1& _a,
//                           const Indexable2& _b) noexcept {
//    const SizeType NCH = _N / SIMD_vec_len;
//#pragma omp parallel for schedule(static) num_threads(NCORES)
//    for (SizeType ch{0}; ch < NCH; ++ch) {
//      const SizeType offs = ch * SIMD_vec_len;
//      const SizeType NOFFS = offs + SIMD_vec_len;
//#pragma vector aligned nontemporal
//#pragma omp simd simdlen(SIMD_vec_len)
//      for (SizeType i{offs}; i < NOFFS; ++i) _a[i] = _b[i];
//    }
//    for (SizeType i{NCH * SIMD_vec_len}; i < _N; ++i) _a[i] = _b[i];
//  }
//};
//
//template <>
//template <std::size_t Align, std::size_t SIMD_vec_len>
//struct i_copy_transformed_n<OMP_ParallelForSIMD<Align, SIMD_vec_len> > {
//  template <typename SizeType, typename Callable, typename Indexable,
//            typename... ARGS>
//  static inline void apply(SizeType _N, Callable&& _F, Indexable& _a,
//                           const ARGS&... _args) noexcept {
//    const SizeType NCH = _N / SIMD_vec_len;
//#pragma omp parallel for schedule(static) num_threads(NCORES)
//    for (SizeType ch{0}; ch < NCH; ++ch) {
//      const SizeType offs = ch * SIMD_vec_len;
//      const SizeType NOFFS = offs + SIMD_vec_len;
//#pragma vector aligned nontemporal
//#pragma omp simd simdlen(SIMD_vec_len)
//      for (SizeType i{offs}; i < NOFFS; ++i) _a[i] = _F((_args[i])...);
//    }
//    for (SizeType i{NCH * SIMD_vec_len}; i < _N; ++i) _a[i] = _F((_args[i])...);
//  };
//};
//
//template <>
//template <std::size_t Align, std::size_t SIMD_vec_len>
//struct i_transform_n<OMP_ParallelForSIMD<Align, SIMD_vec_len> > {
//  template <typename SizeType, typename Callable, typename Indexable,
//            typename... ARGS>
//  static inline void apply(SizeType _N, Callable&& _F, Indexable& _a,
//                           const ARGS&... _args) noexcept {
//    const SizeType NCH = _N / SIMD_vec_len;
//#pragma omp parallel for schedule(static) num_threads(NCORES)
//    for (SizeType ch{0}; ch < NCH; ++ch) {
//      const SizeType offs = ch * SIMD_vec_len;
//      const SizeType NOFFS = offs + SIMD_vec_len;
//#pragma vector aligned
//#pragma omp simd simdlen(SIMD_vec_len)
//      for (SizeType i{offs}; i < NOFFS; ++i) _F(_a[i], (_args[i])...);
//    }
//    for (SizeType i{NCH * SIMD_vec_len}; i < _N; ++i) _F(_a[i], (_args[i])...);
//  };
//};
//
//template <>
//template <std::size_t Align, std::size_t SIMD_vec_len>
//struct i_transform_noparam_n<OMP_ParallelForSIMD<Align, SIMD_vec_len> > {
//  template <typename SizeType, typename Callable, typename Indexable>
//  static inline void apply(SizeType _N, Callable&& _F, Indexable& _a) noexcept {
//    const SizeType NCH = _N / SIMD_vec_len;
//#pragma omp parallel for schedule(static) num_threads(NCORES)
//    for (SizeType ch{0}; ch < NCH; ++ch) {
//      const SizeType offs = ch * SIMD_vec_len;
//      const SizeType NOFFS = offs + SIMD_vec_len;
//#pragma vector aligned
//#pragma omp simd simdlen(SIMD_vec_len)
//      for (SizeType i{offs}; i < NOFFS; ++i) _F(_a[i]);
//      for (SizeType i{NCH * SIMD_vec_len}; i < _N; ++i) _F(_a[i]);
//    }
//  };
//};

}  // namespace mxcpl::utilities

#endif  // SEQUENCE_ALGORITHMS_HPP
