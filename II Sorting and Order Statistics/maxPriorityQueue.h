#pragma once

#include "maxHeap.h"

template <typename T>
class maxPriorityQueue : private maxHeap<T> {
  using maxHeap<T>::A;
  using typename maxHeap<T>::size_t;
  using maxHeap<T>::max_heapify;
  using maxHeap<T>::build_max_heap;
  using maxHeap<T>::empty;
  using maxHeap<T>::enlarge;
  using maxHeap<T>::parent;
  using maxHeap<T>::left;
  using maxHeap<T>::right;
  using maxHeap<T>::length;
  using maxHeap<T>::heap_size;

 public:
  maxPriorityQueue(const std::initializer_list<T>& list = {})
      : maxHeap<T>(list) {}
  ~maxPriorityQueue() = default;
  maxPriorityQueue(const maxPriorityQueue& rhs) = default;
  maxPriorityQueue(maxPriorityQueue&& rhs) = default;
  maxPriorityQueue& operator=(const maxPriorityQueue& rhs) = default;
  maxPriorityQueue& operator=(maxPriorityQueue&& rhs) = default;

  T heap_maximum();                                // Theta(1)
  T heap_extract_max();                            // O(lgn)
  void heap_increase_key(size_t i, const T& key);  // O(lgn)
  void max_heap_insert(const T& key);              // O(lgn)
};

template <typename T>
void maxPriorityQueue<T>::max_heap_insert(const T& key) {
  enlarge();
  heap_size++;
  A[heap_size] = key;
  heap_increase_key(heap_size, key);
}

template <typename T>
void maxPriorityQueue<T>::heap_increase_key(size_t i, const T& key) {
  if (key < A[i])
    throw illegalParameterValue("New key is smaller than current key");
  A[i] = key;
  while (i > 1 && A[parent(i)] < A[i]) {
    using std::swap;
    swap(A[i], A[parent(i)]);
    i = parent(i);
  }
}

template <typename T>
T maxPriorityQueue<T>::heap_extract_max() {
  if (empty()) throw illegalIndex("Heap underflow");
  T max = A[1];
  A[1] = A[heap_size];
  heap_size--;
  max_heapify(1);
  return max;
}

template <typename T>
T maxPriorityQueue<T>::heap_maximum() {
  if (empty()) throw illegalIndex("Heap underflow");
  return A[1];
}
