#pragma once

#include <memory>
#include <numeric>

// 返回 n 的第 i 位上的数（从低位到高位）
unsigned radix(const unsigned& n, unsigned i) {
  return (n / static_cast<unsigned>(std::pow(10, i - 1))) % 10;
}

// 将计数排序的排序关键字换为待排序元素第 r 位上的数字。
// T must be able to convert to unsigned or int ...
template <typename T>
void radix_counting_sort(T* const A, unsigned N, unsigned r) {
  constexpr unsigned K = 9;  // 0-9
  std::unique_ptr<T[]> C(new T[K + 1]{});
  std::unique_ptr<T[]> B(new T[N]);
  for (unsigned j = 0; j < N; j++)
    ++C[radix(A[j],
              r)];  // C[i] now contains the number of elements equal to i.
  for (unsigned i = 1; i <= K; i++)
    C[i] += C[i - 1];  // C[i] now contains the number of elements less than or
  // equal to i.
  for (unsigned j = N - 1; j >= 0; j--) {
    B[C[radix(A[j], r)] - 1] = A[j];
    C[radix(A[j], r)]--;
    if (j == 0) break;
  }
  for (unsigned i = 0; i < N; i++) {
    A[i] = B[i];
  }
}

// 基数排序，从低位到高位，依每一位实施计数排序。
// r 表示 T 的位数。
template <typename T>
void radix_sort(T* const A, unsigned N, unsigned r) {
  for (unsigned i = 1; i <= r; i++) radix_counting_sort(A, N, i);
}

template <typename T, unsigned N>
void radix_sort(T (&A)[N], unsigned r) {
  for (unsigned i = 1; i <= r; i++) radix_counting_sort(A, N, i);
}