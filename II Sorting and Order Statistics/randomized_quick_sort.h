#pragma once

#include <random>

#include "quick_sort.h"

inline unsigned random(unsigned p, unsigned r) {
  std::random_device seed;  //生成 random_device 对象做种子
  std::mt19937 e(seed());
  std::uniform_int_distribution<unsigned> u(p, r);
  return u(e);
}

template <typename T>
unsigned randomized_partition(T* const A, unsigned p, unsigned r) {
  auto i = random(p, r);
  using std::swap;
  swap(A[r], A[i]);
  return partition(A, p, r);
}

template <typename T>
unsigned randomized_partition_plus(T* const A, unsigned p, unsigned r,
                                   unsigned& t) {
  auto i = random(p, r);
  using std::swap;
  swap(A[r], A[i]);
  return partition_plus(A, p, r, t);
}

template <typename T>
void randomized_quick_sort(T* const A, unsigned p, unsigned r) {
  //   if (p < r) {
  //     auto q = randomized_partition(A, p, r);
  //     randomized_quick_sort(A, p, (q == 0 ? q : q - 1));
  //     randomized_quick_sort(A, q + 1, r);
  //   }

  // randomized_partition_plus
  if (p < r) {
    unsigned t;
    auto q = randomized_partition_plus(A, p, r, t);
    quick_sort(A, p, (q == 0 ? q : q - 1));
    quick_sort(A, t + 1, r);
  }
}

template <typename T>
void randomized_quick_sort(T* const A, unsigned N) {
  randomized_quick_sort(A, 0, N - 1);
}

template <typename T, unsigned N>
void randomized_quick_sort(T (&A)[N]) {
  randomized_quick_sort(A, 0, N - 1);
}