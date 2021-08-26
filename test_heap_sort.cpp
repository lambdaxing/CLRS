#include <iostream>

#include "heap_sort.h"

using namespace std;

int main() {
  constexpr int num = 6;
  int n[num]{5, 4, 3, 2, 1, 6};
  shared_ptr<int> dn(new int[num]{5, 4, 3, 2, 1, 6}, default_delete<int[]>());

  for (unsigned i = 0; i < num; i++) {
    cout << dn.get()[i] << " ";
  }
  cout << endl;
  for (unsigned i = 0; i < num; i++) {
    cout << n[i] << " ";
  }
  cout << endl;

  heap_sort(dn.get(), num);
  heap_sort(n);

  for (unsigned i = 0; i < num; i++) {
    cout << dn.get()[i] << " ";
  }
  cout << endl;
  for (unsigned i = 0; i < num; i++) {
    cout << n[i] << " ";
  }
  cout << endl;
}