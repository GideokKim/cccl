//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// test numeric_limits

// digits

#include <cuda/std/cfloat>
#include <cuda/std/limits>

#include "test_macros.h"

template <class T, int expected>
__host__ __device__ void test()
{
  static_assert(cuda::std::numeric_limits<T>::digits == expected, "digits test 1");
  static_assert(cuda::std::numeric_limits<const T>::digits == expected, "digits test 2");
  static_assert(cuda::std::numeric_limits<volatile T>::digits == expected, "digits test 3");
  static_assert(cuda::std::numeric_limits<const volatile T>::digits == expected, "digits test 4");
}

int main(int, char**)
{
  test<bool, 1>();
  test<char, cuda::std::numeric_limits<char>::is_signed ? 7 : 8>();
  test<signed char, 7>();
  test<unsigned char, 8>();
  test<wchar_t, cuda::std::numeric_limits<wchar_t>::is_signed ? sizeof(wchar_t) * 8 - 1 : sizeof(wchar_t) * 8>();
#if TEST_STD_VER > 2017 && defined(__cpp_char8_t)
  test<char8_t, 8>();
#endif
#ifndef _LIBCUDACXX_HAS_NO_UNICODE_CHARS
  test<char16_t, 16>();
  test<char32_t, 32>();
#endif // _LIBCUDACXX_HAS_NO_UNICODE_CHARS
  test<short, 15>();
  test<unsigned short, 16>();
  test<int, 31>();
  test<unsigned int, 32>();
  test<long, sizeof(long) == 4 ? 31 : 63>();
  test<unsigned long, sizeof(long) == 4 ? 32 : 64>();
  test<long long, 63>();
  test<unsigned long long, 64>();
#ifndef _LIBCUDACXX_HAS_NO_INT128
  test<__int128_t, 127>();
  test<__uint128_t, 128>();
#endif
  test<float, FLT_MANT_DIG>();
  test<double, DBL_MANT_DIG>();
#ifndef _LIBCUDACXX_HAS_NO_LONG_DOUBLE
  test<long double, LDBL_MANT_DIG>();
#endif
#if defined(_LIBCUDACXX_HAS_NVFP16)
  test<__half, 11>();
#endif // _LIBCUDACXX_HAS_NVFP16
#if defined(_LIBCUDACXX_HAS_NVBF16)
  test<__nv_bfloat16, 8>();
#endif // _LIBCUDACXX_HAS_NVBF16
  return 0;
}
