#pragma once

#include "linkedList.h"

template <typename T>
class listStack : private linkedList<T> {
 public:
  listStack() = default;
  listStack(const listStack& rhs) = default;
  listStack(listStack&& rhs) = default;
  listStack& operator=(const listStack& rhs) = default;
  listStack& operator=(listStack&& rhs) = default;
  ~listStack() {}

  using linkedList<T>::empty;
  // void push(const T& x);
  template <typename... Ts>
  void push(Ts&&... params);
  T pop();

 private:
  using linkedList<T>::head;
};

// template <typename T>
// void listStack<T>::push(const T& x) {
//   this->list_insert(nullptr, x);
// }

template <typename T>
template <typename... Ts>
void listStack<T>::push(Ts&&... params) {
  this->list_insert(nullptr, std::forward<Ts>(params)...);
}

template <typename T>
T listStack<T>::pop() {
  if (empty()) {
    throw illegalIndex("Underflow. stack is empty!");
  }
  auto x = head->key;
  this->list_delete(head);
  return x;
}