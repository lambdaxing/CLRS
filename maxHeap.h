#pragma once

#include <initializer_list>

#include "myExceptions.h"

template <typename T>
class maxHeap {
 public:
  typedef std::size_t size_t;

  maxHeap(const std::initializer_list<T>& list = {});
  ~maxHeap();
  maxHeap(const maxHeap& rhs);
  maxHeap(maxHeap&& rhs);
  maxHeap& operator=(const maxHeap& rhs);
  maxHeap& operator=(maxHeap&& rhs);

 protected:
  size_t parent(size_t i) { return (i / 2); }
  size_t left(size_t i) { return 2 * i; }
  size_t right(size_t i) { return 2 * i + 1; }

  void max_heapify(size_t i);
  void build_max_heap();
  bool empty() const { return heap_size == 0; }
  void alloc() { A = new T[length]; }
  void enlarge();

  size_t length;
  size_t heap_size;
  T* A;
};

template <typename T>
maxHeap<T>::maxHeap(const std::initializer_list<T>& list)
    : length(list.size() + 10), heap_size(list.size()), A(new T[length]()) {
  std::cout << "maxHeap<T>::maxHeap()" << std::endl;
  size_t i = 1;
  for (const auto& k : list) A[i++] = k;
  build_max_heap();
}
template <typename T>
maxHeap<T>::~maxHeap() {
  std::cout << "maxHeap<T>::~maxHeap()" << std::endl;
  delete[] A;
}

template <typename T>
maxHeap<T>::maxHeap(const maxHeap& rhs)
    : length(rhs.length), heap_size(rhs.heap_size), A(new T[length]) {
  std::cout << "maxHeap<T>::maxHeap(const maxHeap&)" << std::endl;
  for (size_t i = 0; i < length; i++) A[i] = rhs.A[i];
}

template <typename T>
maxHeap<T>::maxHeap(maxHeap&& rhs)
    : length(rhs.length), heap_size(rhs.heap_size), A(rhs.A) {
  std::cout << "maxHeap<T>::maxHeap(maxHeap&&)" << std::endl;
  rhs.A = nullptr;
}

template <typename T>
maxHeap<T>& maxHeap<T>::operator=(const maxHeap& rhs) {
  std::cout << "maxHeap<T>::operator=(const maxHeap&)" << std::endl;
  *this = maxHeap(rhs);
  return *this;
}

template <typename T>
maxHeap<T>& maxHeap<T>::operator=(maxHeap&& rhs) {
  std::cout << "maxHeap<T>::operator=(maxHeap&&)" << std::endl;
  using std::swap;
  swap(A, rhs.A);
  swap(length, rhs.length);
  swap(heap_size, rhs.heap_size);
  return *this;
}

// A[i] 违背了最大堆的性质，假定 left 和 right 都是最大堆，
// 让 A[i] 逐级下降，使以下标 i 为根结点的子树重新遵循最大堆的性质。
// T(n) = O(lgn)：对于一个树高为 h 的节点，T(h) = O(h);
template <typename T>
void maxHeap<T>::max_heapify(size_t i) {
  while (true) {
    auto l = left(i);
    auto r = right(i);
    size_t largest;
    if (l <= heap_size && A[l] > A[i])
      largest = l;
    else
      largest = i;
    if (r <= heap_size && A[r] > A[largest]) largest = r;
    if (largest != i) {
      using std::swap;
      swap(A[i], A[largest]);
      i = largest;
    } else
      break;
  };
}

// 自底向上利用 max_heapify 把 A[1..n] 转换为最大堆
// T(n) = O(n)
template <typename T>
void maxHeap<T>::build_max_heap() {
  heap_size = length;
  for (auto i = length / 2; i >= 1; i--) {
    max_heapify(i);
  }
}

template <typename T>
void maxHeap<T>::enlarge() {
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
