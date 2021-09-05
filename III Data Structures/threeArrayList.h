#pragma once
// 指针和对象的实现：三个数组实现链表

#include "myExceptions.h"

template <typename T>
class threeArrayList {
 public:
  using size_t = std::size_t;
  threeArrayList();
  threeArrayList(const threeArrayList& rhs);
  threeArrayList(threeArrayList&& rhs);
  threeArrayList& operator=(const threeArrayList& rhs);
  threeArrayList& operator=(threeArrayList&& rhs);
  ~threeArrayList();

  bool empty() const;
  size_t list_search(const T& k);
  template <typename... Ts>
  void list_insert(size_t p, Ts&&... params);
  void list_delete(const T& k);
  void list_delete(size_t x);

 protected:
  size_t length;  // 三个数组的长度
  // next 数组，next[i] 表示元素 key[i] 的 next 元素在数组 key 中的下标
  size_t* next;
  // prev 数组，prev[i] 表示元素 key[i] 的 prev 元素在数组 key 中的下标
  size_t* prev;
  T* key;      // 元素数组
  size_t nil;  // 链表哨兵下标

  size_t free;  // 自由表头下标，自由表相当于一个栈（单向链表），pop: 分配 ，
                // push: 释放。

  size_t allocate_object();    // 分配 - 自由表取出
  void free_object(size_t x);  // 释放 - 自由表放回
  void swap(threeArrayList& rhs);
  void check(size_t x) const;
  void enlarge();
};

template <typename T>
void threeArrayList<T>::enlarge() {
  size_t* nnext = new size_t[length * 2];
  size_t* nprev = new size_t[length * 2];
  T* nkey = new T[length * 2];
  for (size_t i = 0; i < length; i++) nnext[i] = std::move(next[i]);
  for (size_t i = 0; i < length; i++) nprev[i] = std::move(prev[i]);
  for (size_t i = 0; i < length; i++) nkey[i] = std::move(key[i]);

  delete[] key;
  delete[] prev;
  delete[] next;
  key = nkey;
  prev = nprev;
  next = nnext;

  for (size_t i = length * 2 - 1; i != length; i--) next[i] = i - 1;
  next[length] = nil;
  length *= 2;
  free = length - 1;
}

template <typename T>
void threeArrayList<T>::check(size_t x) const {
  if (x == nil) throw illegalIndex("Use nil, x is nil (= 0) !");
}
template <typename T>
void threeArrayList<T>::list_delete(size_t x) {
  check(x);
  next[prev[x]] = next[x];
  prev[next[x]] = prev[x];
  free_object(x);
}

template <typename T>
void threeArrayList<T>::list_delete(const T& k) {
  auto x = list_search(k);
  list_delete(x);
}

template <typename T>
template <typename... Ts>
void threeArrayList<T>::list_insert(size_t p, Ts&&... params) {
  auto x = allocate_object();
  key[x] = T(std::forward<Ts>(params)...);
  prev[x] = p;
  next[x] = next[p];
  prev[next[p]] = x;
  next[p] = x;
}

template <typename T>
bool threeArrayList<T>::empty() const {
  return next[nil] == nil;
}

template <typename T>
size_t threeArrayList<T>::list_search(const T& k) {
  key[nil] = k;
  auto c = next[nil];
  while (key[c] != k) c = next[c];
  return c;
}

template <typename T>
void threeArrayList<T>::swap(threeArrayList& rhs) {
  using std::swap;
  swap(length, rhs.length);
  swap(next, rhs.next);
  swap(prev, rhs.prev);
  swap(key, rhs.key);
  swap(free, rhs.free);
  swap(nil, rhs.nil);
}

template <typename T>
threeArrayList<T>::threeArrayList()
    : length(11),
      next(new size_t[length]),
      prev(new size_t[length]),
      key(new T[length]) {
  // 初始化自由表，初始时链表空，自由表满
  for (size_t i = length - 1; i != 0; i--) next[i] = i - 1;
  nil = 0;  // 初始化哨兵
  next[nil] = prev[nil] = nil;
  free = length - 1;  // 默认自由表从下标 length-1 到 1
}

template <typename T>
threeArrayList<T>::threeArrayList(const threeArrayList& rhs)
    : length(rhs.length),
      next(new size_t[length]),
      prev(new size_t[length]),
      key(new T[length]),
      free(rhs.free),
      nil(rhs.nil) {  // 直接物理上 copy ，逻辑上不管
  for (size_t i = 0; i < length; i++) next[i] = rhs.next[i];
  for (size_t i = 0; i < length; i++) prev[i] = rhs.prev[i];
  for (size_t i = 0; i < length; i++) key[i] = rhs.key[i];
}

template <typename T>
threeArrayList<T>::threeArrayList(threeArrayList&& rhs)
    : length(rhs.length),
      next(rhs.next),
      prev(rhs.prev),
      key(rhs.key),
      free(rhs.free),
      nil(rhs.nil) {  // 使用移后源 UB，保证正常析构
  rhs.next = rhs.prev = nullptr;
  rhs.key = nullptr;
}

template <typename T>
threeArrayList<T>& threeArrayList<T>::operator=(const threeArrayList& rhs) {
  if (this != &rhs) {
    auto t = rhs;
    swap(t);
  }
  return *this;
}

template <typename T>
threeArrayList<T>& threeArrayList<T>::operator=(threeArrayList&& rhs) {
  swap(rhs);
  return *this;
}

template <typename T>
threeArrayList<T>::~threeArrayList() {
  delete[] key;
  delete[] prev;
  delete[] next;
}

template <typename T>
size_t threeArrayList<T>::allocate_object() {
  if (free == 0)  // 自由表空，链表满
    enlarge();    // 扩容
  auto x = free;
  free = next[x];
  return x;
}
template <typename T>
void threeArrayList<T>::free_object(size_t x) {
  next[x] = free;
  free = x;
}

template <typename T>
class listQueue : protected threeArrayList<T> {
 public:
  listQueue() = default;
  listQueue(const listQueue& rhs) = default;
  listQueue(listQueue&& rhs) = default;
  listQueue& operator=(const listQueue& rhs) = default;
  listQueue& operator=(listQueue&& rhs) = default;
  ~listQueue() {}

  using threeArrayList<T>::empty;
  //   void enqueue(const T& x);
  template <typename... Ts>
  void enqueue(Ts&&... params);
  T dequeue();

 protected:
  using typename threeArrayList<T>::size_t;
  using threeArrayList<T>::next;
  using threeArrayList<T>::prev;
  using threeArrayList<T>::key;
  using threeArrayList<T>::nil;

  size_t tail() const {  // return tail node;
    return prev[nil];
  }
  size_t head() const {  // return head node;
    return next[nil];
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
  auto x = key[head()];
  this->list_delete(head());
  return x;
}