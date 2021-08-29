#include <iostream>

#include "counting_sort.h"

using namespace std;

int main() {
  constexpr int num = 6;
  int n[1]{6};
  shared_ptr<int> dn(new int[num]{5, 3, 3, 1, 1, 6}, default_delete<int[]>());

  for (unsigned i = 0; i < num; i++) {
    cout << dn.get()[i] << " ";
  }
  cout << endl;
  for (unsigned i = 0; i < 1; i++) {
    cout << n[i] << " ";
  }
  cout << endl;

  counting_sort(dn.get(), num, 6);
  counting_sort(n, 6);

  for (unsigned i = 0; i < num; i++) {
    cout << dn.get()[i] << " ";
  }
  cout << endl;
  for (unsigned i = 0; i < 1; i++) {
    cout << n[i] << " ";
  }
  cout << endl;
}