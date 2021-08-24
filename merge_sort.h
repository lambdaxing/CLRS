#pragma once

// merge
// 合并两个已有序的部分
template <typename T>
void merge(T* const A, unsigned N, unsigned p, unsigned q, unsigned r) {
  unsigned n1 = q - p + 1;
  unsigned n2 = r - q;
  T L[n1], R[n2];
  for (unsigned i = 0; i < n1; i++) L[i] = A[p + i];
  for (unsigned i = 0; i < n2; i++) R[i] = A[q + i + 1];
  unsigned i = 0, j = 0;
  for (unsigned k = p; k <= r;
       k++) {  // 循环执行 r - p + 1 次，刚好使得 i = n1 , j = n2 。
    if ((i < n1 && (j < n2 && L[i] <= R[j])) ||
        j >= n2) {  // j 溢出或 L[i] <= R[j]
      A[k] = L[i];
      i++;
    } else {  // i 溢出或 L[i] > R[j]
      A[k] = R[j];
      j++;
    }
  }
}

template <typename T>
void merge_sort(T* const A, unsigned N, unsigned p, unsigned r) {
  if (p < r) {
    unsigned q = (p + r) / 2;
    merge_sort<T>(A, N, p, q);
    merge_sort<T>(A, N, q + 1, r);
    merge<T>(A, N, p, q, r);
  }
}

// merge_sort interface
// 委托其他函数实现归并排序
template <typename T>
void merge_sort(T* const A, unsigned N) {
  merge_sort<T>(A, N, 0, N - 1);
}
