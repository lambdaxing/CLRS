#pragma once

#include "linkedList.h"

template <typename T>
class listQueue : protected linkedList<T> {
 public:
  listQueue() = default;
  listQueue(const listQueue& rhs) = default;
  listQueue(listQueue&& rhs) = default;
  listQueue& operator=(const listQueue& rhs) = default;
  listQueue& operator=(listQueue&& rhs) = default;
  ~listQueue() {}

  using linkedList<T>::empty;
  //   void enqueue(const T& x);
  template <typename... Ts>
  void enqueue(Ts&&... params);
  T dequeue();

 protected:
  using linkedList<T>::head;
  using typename linkedList<T>::pNode;
  pNode tail() const {  // return tail node;
    auto c = head;
    while (c != nullptr && c->next != nullptr) c = c->next;
    return c;
  }
};

template <typename T>
template <typename... Ts>
void listQueue<T>::enqueue(Ts&&... params) {
  auto c = tail();
  if (c == nullptr)  // queue is empty.
    this->list_insert(nullptr, std::forward<Ts>(params)...);
  else  // queue is not empty,insert tail of queue.
    this->list_insert(c, std::forward<Ts>(params)...);
}

template <typename T>
T listQueue<T>::dequeue() {
  if (empty()) {
    throw illegalIndex("Underflow. queue is empty!");
  }
  auto x = head->key;
  this->list_delete(head);
  return x;
}