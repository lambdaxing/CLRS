#pragma once
#include <iostream>

template <typename T>
class arrayList {
 public:
  typedef std::size_t size_t;
  arrayList(size_t n = 10);
  arrayList(const arrayList& rhs);
  arrayList(arrayList&& rhs);
  ~arrayList();
  arrayList& operator=(const arrayList& rhs);
  arrayList& operator=(arrayList&& rhs);
  void swap(arrayList& rhs);

 protected:
  size_t length;
  T* p;
};

template <typename T>
arrayList<T>::arrayList(size_t n) : length(n), p(new T[length]) {}

template <typename T>
arrayList<T>::arrayList(const arrayList& rhs)
    : length(rhs.length), p(new T[length]) {
  for (size_t i = 0; i < length; i++) p[i] = rhs.p[i];
}

template <typename T>
arrayList<T>::arrayList(arrayList&& rhs) : length(rhs.length), p(rhs.p) {
  rhs.p = nullptr;
}

template <typename T>
arrayList<T>::~arrayList() {
  delete[] p;
}

template <typename T>
arrayList<T>& arrayList<T>::operator=(const arrayList& rhs) {
  if (this != &rhs) {
    arrayList t = rhs;
    swap(t);
  }  // t is destroyed, including old elments of this.
  return *this;
}

template <typename T>
arrayList<T>& arrayList<T>::operator=(arrayList&& rhs) {
  swap(rhs);
  return *this;
}

template <typename T>
void arrayList<T>::swap(arrayList& rhs) {
  using std::swap;
  swap(p, rhs.p);
  swap(length, rhs.length);
}