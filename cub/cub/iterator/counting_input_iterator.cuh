/******************************************************************************
 * Copyright (c) 2011, Duane Merrill.  All rights reserved.
 * Copyright (c) 2011-2018, NVIDIA CORPORATION.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the NVIDIA CORPORATION nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NVIDIA CORPORATION BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************/

/**
 * \file
 * Random-access iterator types
 */

#pragma once

#include <cub/config.cuh>

#if defined(_CCCL_IMPLICIT_SYSTEM_HEADER_GCC)
#  pragma GCC system_header
#elif defined(_CCCL_IMPLICIT_SYSTEM_HEADER_CLANG)
#  pragma clang system_header
#elif defined(_CCCL_IMPLICIT_SYSTEM_HEADER_MSVC)
#  pragma system_header
#endif // no system header

#include <cub/thread/thread_load.cuh>
#include <cub/thread/thread_store.cuh>

#include <cuda/std/iterator>

#if !_CCCL_COMPILER(NVRTC)
#  include <thrust/iterator/iterator_facade.h>
#  include <thrust/iterator/iterator_traits.h>

#  include <ostream>
#endif // !_CCCL_COMPILER(NVRTC)

CUB_NAMESPACE_BEGIN

/**
 * @brief A random-access input generator for dereferencing a sequence of incrementing integer values.
 *
 * @par Overview
 * - After initializing a CountingInputIterator to a certain integer @p base, read references
 *   at @p offset will return the value @p base + @p offset.
 * - Can be constructed, manipulated, dereferenced, and exchanged within and between host and device
 *   functions.
 * - Compatible with Thrust API v1.7 or newer.
 *
 * @par Snippet
 * The code snippet below illustrates the use of @p CountingInputIterator to
 * dereference a sequence of incrementing integers.
 * @par
 * @code
 * #include <cub/cub.cuh>   // or equivalently <cub/iterator/counting_input_iterator.cuh>
 *
 * cub::CountingInputIterator<int> itr(5);
 *
 * printf("%d\n", itr[0]);      // 5
 * printf("%d\n", itr[1]);      // 6
 * printf("%d\n", itr[2]);      // 7
 * printf("%d\n", itr[50]);     // 55
 *
 * @endcode
 *
 * @tparam ValueType
 *   The value type of this iterator
 *
 * @tparam OffsetT
 *   The difference type of this iterator (Default: @p ptrdiff_t)
 */
template <typename ValueType, typename OffsetT = ptrdiff_t>
class CountingInputIterator
{
public:
  // Required iterator traits

  /// My own type
  using self_type = CountingInputIterator;

  /// Type to express the result of subtracting one iterator from another
  using difference_type = OffsetT;

  /// The type of the element the iterator can point to
  using value_type = ValueType;

  /// The type of a pointer to an element the iterator can point to
  using pointer = ValueType*;

  /// The type of a reference to an element the iterator can point to
  using reference = ValueType;

#if _CCCL_COMPILER(NVRTC)
  using iterator_category = ::cuda::std::random_access_iterator_tag;
#else // ^^^ _CCCL_COMPILER(NVRTC) ^^^ // vvv !_CCCL_COMPILER(NVRTC) vvv
  using iterator_category = typename THRUST_NS_QUALIFIER::detail::iterator_facade_category<
    THRUST_NS_QUALIFIER::any_system_tag,
    THRUST_NS_QUALIFIER::random_access_traversal_tag,
    value_type,
    reference>::type;
#endif // _CCCL_COMPILER(NVRTC)

private:
  ValueType val;

public:
  /**
   * @param val
   *   Starting value for the iterator instance to report
   */
  _CCCL_HOST_DEVICE _CCCL_FORCEINLINE CountingInputIterator(const ValueType& val)
      : val(val)
  {}

  /// Postfix increment
  _CCCL_HOST_DEVICE _CCCL_FORCEINLINE self_type operator++(int)
  {
    self_type retval = *this;
    val++;
    return retval;
  }

  /// Prefix increment
  _CCCL_HOST_DEVICE _CCCL_FORCEINLINE self_type operator++()
  {
    val++;
    return *this;
  }

  /// Indirection
  _CCCL_HOST_DEVICE _CCCL_FORCEINLINE reference operator*() const
  {
    return val;
  }

  /// Addition
  template <typename Distance>
  _CCCL_HOST_DEVICE _CCCL_FORCEINLINE self_type operator+(Distance n) const
  {
    self_type retval(val + (ValueType) n);
    return retval;
  }

  /// Addition assignment
  template <typename Distance>
  _CCCL_HOST_DEVICE _CCCL_FORCEINLINE self_type& operator+=(Distance n)
  {
    val += (ValueType) n;
    return *this;
  }

  /// Subtraction
  template <typename Distance>
  _CCCL_HOST_DEVICE _CCCL_FORCEINLINE self_type operator-(Distance n) const
  {
    self_type retval(val - (ValueType) n);
    return retval;
  }

  /// Subtraction assignment
  template <typename Distance>
  _CCCL_HOST_DEVICE _CCCL_FORCEINLINE self_type& operator-=(Distance n)
  {
    val -= n;
    return *this;
  }

  /// Distance
  _CCCL_HOST_DEVICE _CCCL_FORCEINLINE difference_type operator-(self_type other) const
  {
    return (difference_type) (val - other.val);
  }

  /// Array subscript
  template <typename Distance>
  _CCCL_HOST_DEVICE _CCCL_FORCEINLINE reference operator[](Distance n) const
  {
    return val + (ValueType) n;
  }

  /// Structure dereference
  _CCCL_HOST_DEVICE _CCCL_FORCEINLINE pointer operator->()
  {
    return &val;
  }

  /// Equal to
  _CCCL_HOST_DEVICE _CCCL_FORCEINLINE bool operator==(const self_type& rhs) const
  {
    return (val == rhs.val);
  }

  /// Not equal to
  _CCCL_HOST_DEVICE _CCCL_FORCEINLINE bool operator!=(const self_type& rhs) const
  {
    return (val != rhs.val);
  }

  /// ostream operator
#if !_CCCL_COMPILER(NVRTC)
  friend std::ostream& operator<<(std::ostream& os, const self_type& itr)
  {
    os << "[" << itr.val << "]";
    return os;
  }
#endif // !_CCCL_COMPILER(NVRTC)
};

CUB_NAMESPACE_END
