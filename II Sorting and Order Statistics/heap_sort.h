#pragma once

#include "heap.h"

template <typename T, unsigned N>
void heap_sort(T (&A)[N]) {
  if (N == 0 || N == 1) return;
  auto n = N;
  build_max_heap(A, N);
  for (std::size_t i = N - 1; i >= 1; i--) {
    using std::swap;
    swap(A[0], A[i]);
    n--;  // 这一步从堆中去掉结点 i 。
    max_heapify(A, 0, n);
  }
}

template <typename T>
void heap_sort(T* const A, unsigned N) {
  if (N == 0 || N == 1) return;
  build_max_heap(A, N);
  for (std::size_t i = N - 1; i >= 1; i--) {
    using std::swap;
    swap(A[0], A[i]);
    N--;  // 这一步从堆中去掉结点 i 。
    max_heapify(A, 0, N);
  }
}
