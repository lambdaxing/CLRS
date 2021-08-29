#pragma once

#include "randomized_quick_sort.h"

template <typename T>
T& randomized_select(T* const A, unsigned p, unsigned r, unsigned i) {
  if (p == r) return A[p];
  auto q = randomized_partition(A, p, r);
  auto k = q - p + 1;
  if (i == k)  // the pivot value is the answer
    return A[q];
  else if (i < k)
    return randomized_select(A, p, q - 1, i);
  else
    return randomized_select(A, q + 1, r, i - k);
}

template <typename T>
T& randomized_select(T* const A, unsigned N, unsigned i) {
  return randomized_select(A, 0, N - 1, i);
}

template <typename T, unsigned N>
T& randomized_select(T (&A)[N], unsigned i) {
  return randomized_select(A, N, i);
}