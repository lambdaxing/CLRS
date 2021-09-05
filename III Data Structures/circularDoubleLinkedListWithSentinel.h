#pragma once

#include "myExceptions.h"

template <typename T>
class cDLWS {
 protected:
  struct node;
  using pNode = node*;
  struct node {
    node() = default;
    node(const T& k, pNode p, pNode n) : key(k), prev(p), next(n) {}
    node(const T& k) : key(k) {}
    T key = T{};
    pNode prev = this;
    pNode next = this;
  };

 public:
  cDLWS() : nil(createNode()) {}
  cDLWS(const cDLWS& rhs);
  cDLWS(cDLWS&& rhs);
  cDLWS& operator=(const cDLWS& rhs);
  cDLWS& operator=(cDLWS&& rhs);
  ~cDLWS();

  bool empty() const { return nil->next == nil; }
  pNode list_search(const T& k);
  template <typename... Ts>
  void list_insert(pNode p, Ts&&... params);
  void list_delete(const T& k);
  void list_delete(pNode x);

 protected:
  void check(pNode x) const;
  void clear();
  void swap(cDLWS& rhs);
  template <typename... Ts>
  pNode createNode(pNode p, pNode n, Ts&&... params);
  template <typename... Ts>
  pNode createNode(Ts&&... params);

  pNode nil;
};

template <typename T>
void cDLWS<T>::check(pNode x) const {
  if (x == nil) throw illegalIndex("Use nil, x is nil (= nullptr)!");
}

template <typename T>
void cDLWS<T>::list_delete(pNode x) {
  check(x);
  x->prev->next = x->next;
  x->next->prev = x->prev;
  delete x;
}

template <typename T>
void cDLWS<T>::list_delete(const T& k) {
  auto x = list_search(k);
  list_delete(x);
}

template <typename T>
template <typename... Ts>
auto cDLWS<T>::createNode(pNode p, pNode n, Ts&&... params) -> pNode {
  return new node(T(std::forward<Ts>(params)...), p, n);
}
template <typename T>
template <typename... Ts>
auto cDLWS<T>::createNode(Ts&&... params) -> pNode {
  if (sizeof...(params) == 0) return new node();
  auto x = new node(T(std::forward<Ts>(params)...));
  x->next = x->prev = x;
  return x;
}

template <typename T>
template <typename... Ts>
void cDLWS<T>::list_insert(pNode p, Ts&&... params) {
  auto c = createNode(p, p->next, std::forward<Ts>(params)...);
  p->next->prev = c;
  p->next = c;
}

template <typename T>
auto cDLWS<T>::list_search(const T& k) -> pNode {
  auto c = nil->next;
  while (c != nil && c->key != k) c = c->next;
  return c;
}
// template <typename T>
// auto cDLWS<T>::list_search(const T& k) -> pNode {
//   nil->key = k;
//   auto c = nil->next;
//   while (c->key != k) c = c->next;
//   return c;
// }

template <typename T>
void cDLWS<T>::clear() {
  // 只是 delete 掉元素，变为空链表，哨兵 nil 的空间依然未释放。
  while (nil->next != nil) {
    auto c = nil->next;
    nil->next = c->next;
    delete c;
  }
  nil->prev = nil;
}

template <typename T>
cDLWS<T>::cDLWS(const cDLWS& rhs) {
  auto rhsNode = rhs.nil;
  nil = createNode(rhsNode->key);
  auto preNode = nil;
  rhsNode = rhsNode->next;
  auto c = nil;
  while (rhsNode != rhs.nil) {
    c = createNode(preNode, nil, rhsNode->key);
    preNode->next = c;
    preNode = preNode->next;
    rhsNode = rhsNode->next;
  }
  nil->prev = c;
}

template <typename T>
cDLWS<T>::cDLWS(cDLWS&& rhs) {  // 移后源虽不能再使用，也需保证其正确析构。
  nil = rhs.nil;
  rhs.nil = createNode(nil->key);
}

template <typename T>
void cDLWS<T>::swap(cDLWS& rhs) {
  using std::swap;
  swap(nil, rhs.nil);
}

template <typename T>
cDLWS<T>& cDLWS<T>::operator=(const cDLWS& rhs) {
  if (this != &rhs) {
    auto t = rhs;
    swap(t);
  }
  return *this;
}

template <typename T>
cDLWS<T>& cDLWS<T>::operator=(cDLWS&& rhs) {
  swap(rhs);
  return *this;
}

template <typename T>
cDLWS<T>::~cDLWS() {
  clear();     // 释放链表元素
  delete nil;  // 释放哨兵空间
}

template <typename T>
class listQueue : protected cDLWS<T> {
 public:
  listQueue() = default;
  listQueue(const listQueue& rhs) = default;
  listQueue(listQueue&& rhs) = default;
  listQueue& operator=(const listQueue& rhs) = default;
  listQueue& operator=(listQueue&& rhs) = default;
  ~listQueue() {}

  using cDLWS<T>::empty;
  //   void enqueue(const T& x);
  template <typename... Ts>
  void enqueue(Ts&&... params);
  T dequeue();

 protected:
  using typename cDLWS<T>::pNode;
  using cDLWS<T>::nil;
  pNode tail() const {  // return tail node;
    return nil->prev;
  }
  pNode head() const {  // return head node;
    return nil->next;
  }
};

template <typename T>
template <typename... Ts>
void listQueue<T>::enqueue(Ts&&... params) {
  auto c = tail();
  this->list_insert(c, std::forward<Ts>(params)...);
}

template <typename T>
T listQueue<T>::dequeue() {
  if (empty()) {
    throw illegalIndex("Underflow. queue is empty!");
  }
  auto x = head()->key;
  this->list_delete(head());
  return x;
}