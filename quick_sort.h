#pragma once

// partition 选择一个主元 x = A[r]，并围绕它划分子数组 A[p..r] ，
// 使得 A[p..q-1] <= A[q] < A[q+1..r] 。
// T(n) = Theta(n)，n = r - p + 1 。
template <typename T>
unsigned partition(T* const A, unsigned p, unsigned r) {
  auto x = A[r];
  auto i = p - 1;  // 若 p = 0 ，这儿虽然溢出了，但后面均是使用 i + 1 。

  using std::swap;
  for (auto j = p; j < r; j++) {
    if (A[j] <= x) {
      i++;
      swap(A[i], A[j]);
    }
  }
  swap(A[i + 1], A[r]);
  return i + 1;
}

template <typename T>
void quick_sort(T* const A, unsigned p, unsigned r) {
  if (p < r) {
    auto q = partition(A, p, r);
    quick_sort(A, p, (q == 0 ? q : q - 1));
    quick_sort(A, q + 1, r);
  }
}

template <typename T>
void quick_sort(T* const A, unsigned N) {
  quick_sort(A, 0, N - 1);
}

template <typename T, unsigned N>
void quick_sort(T (&A)[N]) {
  quick_sort(A, 0, N - 1);
}
