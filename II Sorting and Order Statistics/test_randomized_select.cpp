#include <iostream>
#include <memory>

#include "randomized_select.h"

using namespace std;

int main() {
  constexpr int num = 6;
  int n[num]{6, 5, 4, 3, 2, 1};
  shared_ptr<int> dn(new int[num]{5, 4, 3, 2, 1, 6}, default_delete<int[]>());

  for (unsigned i = 0; i < num; i++) {
    cout << dn.get()[i] << " ";
  }
  cout << endl;
  for (unsigned i = 0; i < num; i++) {
    cout << n[i] << " ";
  }
  cout << endl;

  cout << randomized_select(dn.get(), num, 3) << endl;
  cout << randomized_select(n, 3) << endl;
