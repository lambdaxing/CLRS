#include <iostream>

#include "radix_sort.h"

using namespace std;

int main() {
  constexpr int num = 6;
  int n[1]{6};
  shared_ptr<int> dn(new int[num]{15, 4561, 53, 252, 72, 6},
                     default_delete<int[]>());

  for (unsigned i = 0; i < num; i++) {
    cout << dn.get()[i] << " ";
  }
  cout << endl;
  for (unsigned i = 0; i < 1; i++) {
    cout << n[i] << " ";
  }
  cout << endl;

  radix_sort(dn.get(), num, 4);
  radix_sort(n, 1);

  for (unsigned i = 0; i < num; i++) {
    cout << dn.get()[i] << " ";
  }
  cout << endl;
  for (unsigned i = 0; i < 1; i++) {
    cout << n[i] << " ";
  }
  cout << endl;
}