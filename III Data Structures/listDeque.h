#pragma once
// listDeque 继承自 listQueue

#include "listQueue.h"

template <typename T>
class listDeque : private listQueue<T> {
 public:
  listDeque() = default;
  listDeque(const listDeque& rhs) = default;
  listDeque(listDeque&& rhs) = default;
  listDeque& operator=(const listDeque& rhs) = default;
  listDeque& operator=(listDeque&& rhs) = default;
  ~listDeque() = default;

  using listQueue<T>::empty;

  T front() const;
  T back() const;

  T pop_back();
  T pop_front();

  void push_front(T&& x);  // 这儿区分左值和右值使得实现代码有些重复。
  void push_front(const T& x);  // 类似 queue 实现的万能引用或许能解决，
  void push_back(const T& x);  // 但后面增加了 emplace 方法用于构造值，
  void push_back(T&& x);       //"copy-swap" 技术值得斟酌。

  template <typename... Ts>
  void emplace_front(Ts&&... params);
  template <typename... Ts>
  void emplace_back(Ts&&... params);

 private:
  void check() const {
    if (empty()) {
      throw illegalIndex("Underflow. listDeque is empty!");
    }
  }
  using listQueue<T>::tail;
  using listQueue<T>::head;
};

template <typename T>
T listDeque<T>::pop_front() {
  return this->dequeue();
}

template <typename T>
void listDeque<T>::push_back(T&& x) {
  this->enqueue(std::move(x));
}
template <typename T>
void listDeque<T>::push_back(const T& x) {
  this->enqueue(x);
}
template <typename T>
template <typename... Ts>
void listDeque<T>::emplace_back(Ts&&... params) {
  this->enqueue(std::forward<Ts>(params)...);
}

template <typename T>
T listDeque<T>::pop_back() {
  check();
  auto c = tail();
  auto x = c->key;
  this->list_delete(c);
  return x;
}

template <typename T>
void listDeque<T>::push_front(T&& x) {
  this->list_insert(nullptr, std::move(x));
}
template <typename T>
void listDeque<T>::push_front(const T& x) {
  this->list_insert(nullptr, x);
}

template <typename T>
template <typename... Ts>
void listDeque<T>::emplace_front(Ts&&... params) {
  this->list_insert(nullptr, std::forward<Ts>(params)...);
}

template <typename T>
T listDeque<T>::front() const {
  check();
  return head->key;
}
template <typename T>
T listDeque<T>::back() const {
  check();
  return tail()->key;
}
