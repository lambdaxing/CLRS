#pragma once

#include "arrayList.h"
#include "myExceptions.h"

template <typename T>
class queue : protected arrayList<T> {
 public:
  using typename arrayList<T>::size_t;
  queue();
  queue(const queue& rhs);
  queue(queue&& rhs);
  queue& operator=(const queue& rhs);
  queue& operator=(queue&& rhs);
  ~queue() {}

  bool empty() const;
  //   void enqueue(const T& x);
  template <typename... Ts>
  void enqueue(Ts&&... params);
  T dequeue();

 protected:
  using arrayList<T>::length;
  using arrayList<T>::p;
  size_t head;
  size_t size;
  void enlarge();
  size_t tail() const { return (head + size) % length; }
};

// template <typename T>
// void queue<T>::enqueue(const T& x) {
//   enlarge();
//   p[tail()] = x;
//   size++;
// }

template <typename T>
template <typename... Ts>
void queue<T>::enqueue(Ts&&... params) {
  enlarge();
  p[tail()] = T(std::forward<Ts>(params)...);
  // 对于 local objects，上一步中的拷贝赋值可能会优化为移动赋值。
  size++;
}

template <typename T>
T queue<T>::dequeue() {
  if (empty()) {
    throw illegalIndex("Underflow. queue is empty!");
  }
  auto x = p[head++];
  head %= length;
  size--;
  return x;
}

template <typename T>
queue<T>::queue() : arrayList<T>(), head(0), size(0) {}

template <typename T>
queue<T>::queue(const queue& rhs)
    : arrayList<T>(rhs), head(rhs.head), size(rhs.size) {}

template <typename T>
queue<T>::queue(queue&& rhs)
    : arrayList<T>(std::move(rhs)), head(rhs.head), size(rhs.size) {}

template <typename T>
queue<T>& queue<T>::operator=(const queue& rhs) {
  if (this != &rhs) {
    arrayList<T>::operator=(rhs);
    head = rhs.head;
    size = rhs.size;
  }
  return *this;
}

template <typename T>
queue<T>& queue<T>::operator=(queue&& rhs) {
  arrayList<T>::operator=(std::move(rhs));
  head = rhs.head;
  size = rhs.size;
  return *this;
}

template <typename T>
bool queue<T>::empty() const {
  return size == 0;
}

template <typename T>
void queue<T>::enlarge() {
  if (size == length) {
    T* tp = new T[length * 2];
    for (size_t i = 0; i < size; i++) tp[i] = p[(head + i) % length];
    delete[] p;
    p = tp;
    length *= 2;
    head = 0;
  }
}
