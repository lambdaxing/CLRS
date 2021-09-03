#pragma once

#include "arrayList.h"
#include "myExceptions.h"

template <typename T>
class stack : private arrayList<T> {
 public:
  using typename arrayList<T>::size_t;
  stack();
  stack(const stack& rhs);
  stack(stack&& rhs);
  stack& operator=(const stack& rhs);
  stack& operator=(stack&& rhs);
  ~stack() {}

  bool empty() const;
  void push(const T& x);
  //   void push(T&& x);
  template <typename... Ts>
  void push(Ts&&... params);
  T pop();

 private:
  using arrayList<T>::length;
  using arrayList<T>::p;
  size_t top;
  void enlarge();
};

template <typename T>
stack<T>::stack() : arrayList<T>(), top(0) {}  // empty stack

template <typename T>
stack<T>::stack(const stack& rhs) : arrayList<T>(rhs), top(rhs.top) {}

template <typename T>
stack<T>::stack(stack&& rhs)
    : arrayList<T>(std::move(rhs)), top(std::move(rhs.top)) {}

template <typename T>
stack<T>& stack<T>::operator=(const stack& rhs) {
  if (this != &rhs) {
    arrayList<T>::operator=(rhs);
    top = rhs.top;
  }
  return *this;
}

template <typename T>
stack<T>& stack<T>::operator=(stack&& rhs) {
  arrayList<T>::operator=(std::move(rhs));
  top = std::move(rhs.top);
  return *this;
}

template <typename T>
void stack<T>::enlarge() {
  if (top + 1 == length) {
    T* tp = new T[length * 2];
    for (size_t i = 0; i < length; i++) tp[i] = std::move(p[i]);
    delete[] p;
    length *= 2;
    p = tp;
  }
}

template <typename T>
bool stack<T>::empty() const {
  if (top == 0)
    return true;
  else
    return false;
}

template <typename T>
void stack<T>::push(const T& x) {
  enlarge();
  p[++top] = x;
}

// template <typename T>
// void stack<T>::push(T&& x) {
//   enlarge();
//   p[++top] = std::move(x);
// }

template <typename T>
template <typename... Ts>
void stack<T>::push(Ts&&... params) {
  enlarge();
  p[++top] = T(std::forward<Ts>(params)...);
}

template <typename T>
T stack<T>::pop() {
  if (empty()) {
    throw illegalIndex("Underflow. stack is empty!");
  }
  return p[top--];
}