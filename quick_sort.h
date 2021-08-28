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

// p <= q <= t <= r
// A[p..q-1] < A[q] == A[q..t] < A[t+1..r]
template <typename T>
unsigned partition_plus(T* const A, unsigned p, unsigned r, unsigned& t) {
  auto x = A[r];
  auto i = p - 1;  // 若 p = 0 ，这儿虽然溢出了，但后面均是使用 i + 1 。
  t = 0;
  using std::swap;
  for (auto j = p; j < r; j++) {
    if (A[j] <= x) {
      if (A[j] == x) t++;
      i++;
      swap(A[i], A[j]);
    }
  }
  swap(A[i + 1], A[r]);
  auto q = i + 1 - t;
  t = i + 1;
  return q;
}

template <typename T>
unsigned hoare_partition(T* const A, unsigned p, unsigned r) {
  auto x = A[p];
  auto i = p - 1;
  auto j = r + 1;

  while (true) {
    do {
      j = j - 1;
    } while (A[j] > x);
    do {
      i = i + 1;
    } while (A[i] < x);
    if (i < j) {
      using std::swap;
      swap(A[i], A[j]);
    } else
      return j;
  }
}

template <typename T>
void quick_sort(T* const A, unsigned p, unsigned r) {
  if (p < r) {
    auto q = partition(A, p, r);
    quick_sort(A, p, (q == 0 ? q : q - 1));
    quick_sort(A, q + 1, r);
  }

  // // Hoare_partition 版本
  // if (p < r) {
  //   auto q = hoare_partition(A, p, r);
  //   quick_sort(A, p, q);
  //   quick_sort(A, q + 1, r);
  // }

  // // partition_plus
  // if (p < r) {
  //   unsigned t;
  //   auto q = partition_plus(A, p, r, t);
  //   quick_sort(A, p, (q == 0 ? q : q - 1));
  //   quick_sort(A, t + 1, r);
  // }
}

template <typename T>
void quick_sort(T* const A, unsigned N) {
  quick_sort(A, 0, N - 1);
}

template <typename T, unsigned N>
void quick_sort(T (&A)[N]) {
  quick_sort(A, 0, N - 1);
}
