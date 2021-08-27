#pragma once
#include "myExceptions.h"

// 书上假定数组第一个元素从 1 开始，这儿为了保持排序真实数组的一致性，
// 数组第一个元素恢复成从 0 开始，因此堆的某些操作做了点改变。

inline std::size_t parent(std::size_t i) { return (i - 1) / 2; }
inline std::size_t left(std::size_t i) { return 2 * i + 1; }
inline std::size_t right(std::size_t i) { return 2 * i + 2; }

// A[i] 违背了最大堆的性质，假定 left 和 right 都是最大堆，
// 让 A[i] 逐级下降，使以下标 i 为根结点的子树重新遵循最大堆的性质。
// T(n) = O(lgn)：对于一个树高为 h 的节点，T(i) = O(h);
template <typename T>
void max_heapify(T* const A, std::size_t i, std::size_t heap_size) {
  auto l = left(i);
  auto r = right(i);
  size_t largest;
  if (l < heap_size && A[l] > A[i])
    largest = l;
  else
    largest = i;
  if (r < heap_size && A[r] > A[largest]) largest = r;
  if (largest != i) {
    using std::swap;
    swap(A[i], A[largest]);
    max_heapify(A, largest, heap_size);
  }
}

// 自底向上利用 max_heapify 把 A[1..n] 转换为最大堆
// T(n) = O(n)
template <typename T>
void build_max_heap(T* const A, std::size_t length) {
  for (auto i = length / 2 - 1; i >= 0; i--) {
    max_heapify(A, i, length);
    if (i == 0) break;
  }
}

template <typename T>
void min_heapify(T* const A, std::size_t i, std::size_t heap_size) {
  auto l = left(i);
  auto r = right(i);
  size_t smallest;
  if (l < heap_size && A[l] < A[i])
    smallest = l;
  else
    smallest = i;
  if (r < heap_size && A[r] < A[smallest]) smallest = r;
  if (smallest != i) {
    using std::swap;
    swap(A[i], A[smallest]);
    min_heapify(A, smallest, heap_size);
  }
}

template <typename T>
void build_min_heap(T* const A, std::size_t length) {
  for (auto i = length / 2 - 1; i >= 0; i--) {
    min_heapify(A, i, length);
    if (i == 0) break;
  }
}