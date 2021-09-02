#pragma once
// a class for test.

#include <iostream>
using std::cout;
using std::endl;

class Widget {
 public:
  Widget() { cout << "Widget()" << endl; }
  Widget(const Widget& rhs) { cout << "Widget(const Widget&)" << endl; }
  Widget(Widget&& rhs) { cout << "Widget(Widget&&)" << endl; }
  ~Widget() { cout << "~Widget()" << endl; }
  Widget& operator=(const Widget&) {
    cout << "operator=(const Widget&)" << endl;
    return *this;
  }
  Widget& operator=(Widget&&) {
    cout << "operator=(Widget&&)" << endl;
    return *this;
  }
};