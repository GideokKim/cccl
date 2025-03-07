//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// test numeric_limits

// max_exponent

#include <cuda/std/cfloat>
#include <cuda/std/limits>

#include "test_macros.h"

template <class T, int expected>
__host__ __device__ void test()
{
  static_assert(cuda::std::numeric_limits<T>::max_exponent == expected, "max_exponent test 1");
  static_assert(cuda::std::numeric_limits<const T>::max_exponent == expected, "max_exponent test 2");
  static_assert(cuda::std::numeric_limits<volatile T>::max_exponent == expected, "max_exponent test 3");
  static_assert(cuda::std::numeric_limits<const volatile T>::max_exponent == expected, "max_exponent test 4");
}

int main(int, char**)
{
  test<bool, 0>();
  test<char, 0>();
  test<signed char, 0>();
  test<unsigned char, 0>();
  test<wchar_t, 0>();
#if TEST_STD_VER > 2017 && defined(__cpp_char8_t)
  test<char8_t, 0>();
#endif
#ifndef _LIBCUDACXX_HAS_NO_UNICODE_CHARS
  test<char16_t, 0>();
  test<char32_t, 0>();
#endif // _LIBCUDACXX_HAS_NO_UNICODE_CHARS
  test<short, 0>();
  test<unsigned short, 0>();
  test<int, 0>();
  test<unsigned int, 0>();
  test<long, 0>();
  test<unsigned long, 0>();
  test<long long, 0>();
  test<unsigned long long, 0>();
#ifndef _LIBCUDACXX_HAS_NO_INT128
  test<__int128_t, 0>();
  test<__uint128_t, 0>();
#endif
  test<float, FLT_MAX_EXP>();
  test<double, DBL_MAX_EXP>();
#ifndef _LIBCUDACXX_HAS_NO_LONG_DOUBLE
  test<long double, LDBL_MAX_EXP>();
#endif
#if defined(_LIBCUDACXX_HAS_NVFP16)
  test<__half, 16>();
#endif // _LIBCUDACXX_HAS_NVFP16
#if defined(_LIBCUDACXX_HAS_NVBF16)
  test<__nv_bfloat16, 128>();
#endif // _LIBCUDACXX_HAS_NVBF16

  return 0;
}
