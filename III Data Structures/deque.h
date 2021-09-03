#pragma once
// deque（双端队列）继承自 queue 。

#include "queue.h"

template <typename T>
class deque : private queue<T> {
 public:
  using typename queue<T>::size_t;
  deque() = default;
  deque(const deque& rhs) = default;
  deque(deque&& rhs) = default;
  deque& operator=(const deque& rhs) = default;
  deque& operator=(deque&& rhs) = default;
  ~deque() = default;

  using queue<T>::empty;

  T front() const;
  T back() const;

  T pop_back();
  T pop_front();

  void push_front(T&& x);  // 这儿区分左值和右值使得实现代码有些重复。
  void push_front(const T& x);  // 万能引用或许能解决，
  void push_back(const T& x);  //但这儿的 T 并非一个被推导的型别。
  void push_back(T&& x);       //"copy-swap" 技术值得斟酌。

  template <typename... Ts>
  void emplace_front(Ts&&... params);
  template <typename... Ts>
  void emplace_back(Ts&&... params);

 private:
  using queue<T>::length;
  using queue<T>::p;
  using queue<T>::head;  // front = head
  using queue<T>::size;  // back = (head + size) % length = tail
  using queue<T>::enlarge;
  using queue<T>::tail;

  void head_decrease() {
    if (head == 0)
      head = length - 1;
    else
      head--;
  }
  void check() const {
    if (empty()) {
      throw illegalIndex("Underflow. deque is empty!");
    }
  }
};

template <typename T>
T deque<T>::pop_front() {
  return this->dequeue();
}
template <typename T>
void deque<T>::push_back(T&& x) {
  this->enqueue(std::move(x));
}
template <typename T>
void deque<T>::push_back(const T& x) {
  this->enqueue(x);
}
template <typename T>
template <typename... Ts>
void deque<T>::emplace_back(Ts&&... params) {
  this->enqueue(std::forward<Ts>(params)...);
}

template <typename T>
T deque<T>::pop_back() {
  check();
  auto x = p[tail()];
  size--;
  return x;
}
template <typename T>
void deque<T>::push_front(T&& x) {
  enlarge();
  head_decrease();
  p[head] = std::move(x);
  size++;
}
template <typename T>
void deque<T>::push_front(const T& x) {
  enlarge();
  head_decrease();
  p[head] = x;
  size++;
}

template <typename T>
template <typename... Ts>
void deque<T>::emplace_front(Ts&&... params) {
  enlarge();
  head_decrease();
  p[head] = T(std::forward<Ts>(params)...);
  size++;
}

template <typename T>
T deque<T>::front() const {
  check();
  return p[head];
}
template <typename T>
T deque<T>::back() const {
  check();
  return p[tail()];
}
