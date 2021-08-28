#pragma once

#include <memory>

template <typename T>
void counting_sort(T* const A, unsigned N, unsigned K) {
  std::unique_ptr<T[]> C(new T[K + 1]{});
  std::unique_ptr<T[]> B(new T[N]);
  for (unsigned j = 0; j < N; j++)
    C[A[j]]++;  // C[i] now contains the number of elements equal to i.
  for (unsigned i = 1; i <= K; i++)
    C[i] += C[i - 1];  // C[i] now contains the number of elements less than or
  // equal to i.
  for (unsigned j = N - 1; j >= 0; j--) {
    B[C[A[j]] - 1] = A[j];
    C[A[j]]--;
    if (j == 0) break;
  }
  for (unsigned i = 0; i < N; i++) {
    A[i] = B[i];
  }
}

template <typename T, unsigned N>
void counting_sort(T (&A)[N], unsigned K) {
  counting_sort(A, N, K);
}
