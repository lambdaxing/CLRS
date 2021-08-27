#pragma once

#include <initializer_list>

#include "myExceptions.h"

template <typename T>
class minHeap {
 public:
  typedef std::size_t size_t;

  minHeap(const std::initializer_list<T>& list = {});
  ~minHeap();
  minHeap(const minHeap& rhs);
  minHeap(minHeap&& rhs);
  minHeap& operator=(const minHeap& rhs);
  minHeap& operator=(minHeap&& rhs);

 protected:
  size_t parent(size_t i) { return (i / 2); }
  size_t left(size_t i) { return 2 * i; }
  size_t right(size_t i) { return 2 * i + 1; }

  void min_heapify(size_t i);
  void build_min_heap();
  bool empty() const { return heap_size == 0; }
  void enlarge();

  size_t length;
  size_t heap_size;
  T* A;
};

template <typename T>
minHeap<T>::minHeap(const std::initializer_list<T>& list)
    : length(list.size() + 10), heap_size(list.size()), A(new T[length]()) {
  std::cout << "minHeap<T>::minHeap()" << std::endl;
  size_t i = 1;
  for (const auto& k : list) A[i++] = k;
  build_min_heap();
}
template <typename T>
minHeap<T>::~minHeap() {
  std::cout << "minHeap<T>::~minHeap()" << std::endl;
  delete[] A;
}

template <typename T>
minHeap<T>::minHeap(const minHeap& rhs)
    : length(rhs.length), heap_size(rhs.heap_size), A(new T[length]) {
  std::cout << "minHeap<T>::minHeap(const minHeap&)" << std::endl;
  for (size_t i = 0; i < length; i++) A[i] = rhs.A[i];
}

template <typename T>
minHeap<T>::minHeap(minHeap&& rhs)
    : length(rhs.length), heap_size(rhs.heap_size), A(rhs.A) {
  std::cout << "minHeap<T>::minHeap(minHeap&&)" << std::endl;
  rhs.A = nullptr;
}

template <typename T>
minHeap<T>& minHeap<T>::operator=(const minHeap& rhs) {
  std::cout << "minHeap<T>::operator=(const minHeap&)" << std::endl;
  *this = minHeap(rhs);
  return *this;
}

template <typename T>
minHeap<T>& minHeap<T>::operator=(minHeap&& rhs) {
  std::cout << "minHeap<T>::operator=(minHeap&&)" << std::endl;
  using std::swap;
  swap(A, rhs.A);
  swap(length, rhs.length);
  swap(heap_size, rhs.heap_size);
  return *this;
}

// A[i] 违背了最小堆的性质，假定 left 和 right 都是最小堆，
// 让 A[i] 逐级下降，使以下标 i 为根结点的子树重新遵循最小堆的性质。
// T(n) = O(lgn)：对于一个树高为 h 的节点，T(h) = O(h);
template <typename T>
void minHeap<T>::min_heapify(size_t i) {
  while (true) {
    auto l = left(i);
    auto r = right(i);
    size_t smallest;
    if (l <= heap_size && A[l] < A[i])
      smallest = l;
    else
      smallest = i;
    if (r <= heap_size && A[r] < A[smallest]) smallest = r;
    if (smallest != i) {
      using std::swap;
      swap(A[i], A[largest]);
      i = smallest;
    } else
      break;
  };
}

// 自底向上利用 min_heapify 把 A[1..n] 转换为最小堆
// T(n) = O(n)
template <typename T>
void minHeap<T>::build_min_heap() {
  heap_size = length;
  for (auto i = length / 2; i >= 1; i--) {
    min_heapify(i);
  }
}

template <typename T>
void minHeap<T>::enlarge() {
  if (heap_size + 1 == length) {
    length *= 2;
    T* B = new T[length];
    for (size_t i = 1; i <= heap_size; i++) {
      B[i] = std::move(A[i]);
    }
    delete[] A;
    A = B;
  }
}
