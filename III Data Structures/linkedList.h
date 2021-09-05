#pragma once
// double linked list
#include "myExceptions.h"

template <typename T>
class linkedList {
 protected:
  struct node;
  using pNode = node*;
  struct node {
    node(const T& k, pNode p = nullptr, pNode n = nullptr)
        : key(k), prev(p), next(n) {}
    T key;
    pNode prev;
    pNode next;
  };

 public:
  linkedList() = default;
  linkedList(const linkedList& rhs);
  linkedList(linkedList&& rhs);
  linkedList& operator=(const linkedList& rhs);
  linkedList& operator=(linkedList&& rhs);
  ~linkedList();

  bool empty() const { return head == nullptr; }
  pNode list_search(const T& k);
  template <typename... Ts>
  void list_insert(pNode p, Ts&&... params);
  void list_delete(const T& k);
  void list_delete(pNode x);

 protected:
  void check(pNode x) const;
  void clear();
  void swap(linkedList& rhs);
  template <typename... Ts>
  pNode createNode(pNode p, pNode n, Ts&&... params);

  pNode head = nullptr;
};
template <typename T>
void linkedList<T>::check(pNode x) const {
  if (x == nullptr) throw illegalIndex("Use nullptr, pNode is nullptr!");
}
template <typename T>
void linkedList<T>::list_delete(pNode x) {
  check(x);
  if (x->prev != nullptr)
    x->prev->next = x->next;
  else
    head = x->next;
  if (x->next != nullptr) x->next->prev = x->prev;
  delete x;
}

template <typename T>
void linkedList<T>::list_delete(const T& k) {
  auto x = list_search(k);
  list_delete(x);
}

template <typename T>
template <typename... Ts>
auto linkedList<T>::createNode(pNode p, pNode n, Ts&&... params) -> pNode {
  return new node(T(std::forward<Ts>(params)...), p, n);
}

template <typename T>
template <typename... Ts>
void linkedList<T>::list_insert(pNode p, Ts&&... params) {
  if (p == nullptr) {  // insert pre of head
    auto c = createNode(nullptr, head, std::forward<Ts>(params)...);
    head->prev = c;
    head = c;
  } else {  // insert next of p
    auto c = createNode(p, p->next, std::forward<Ts>(params)...);
    if (p->next != nullptr) p->next->prev = c;
    p->next = c;
  }
}

template <typename T>
auto linkedList<T>::list_search(const T& k) -> pNode {
  auto c = head;
  while (c != nullptr && c->key != k) c = c->next;
  return c;
}

template <typename T>
void linkedList<T>::clear() {
  while (head != nullptr) {
    auto nextNode = head->next;
    delete head;
    head = nextNode;
  }
}

template <typename T>
linkedList<T>::linkedList(const linkedList& rhs) {
  if (rhs.head == nullptr) {  // 从空链表拷贝构造
    head = nullptr;
    return;
  }
  auto rhsNode = rhs.head;
  head = createNode(nullptr, nullptr, rhsNode->key);
  auto preNode = head;
  rhsNode = rhsNode->next;
  while (rhsNode != nullptr) {
    auto currentNode = createNode(preNode, nullptr, rhsNode->key);
    preNode->next = currentNode;
    preNode = preNode->next;
    rhsNode = rhsNode->next;
  }
}

template <typename T>
linkedList<T>::linkedList(linkedList&& rhs) {
  head = rhs.head;
  rhs.head = nullptr;
}

template <typename T>
void linkedList<T>::swap(linkedList& rhs) {
  using std::swap;
  swap(head, rhs.head);
}

template <typename T>
linkedList<T>& linkedList<T>::operator=(const linkedList& rhs) {
  if (this != &rhs) {
    auto t = rhs;
    swap(t);
  }
  return *this;
}

template <typename T>
linkedList<T>& linkedList<T>::operator=(linkedList&& rhs) {
  swap(rhs);
  return *this;
}

template <typename T>
linkedList<T>::~linkedList() {
  clear();
}
