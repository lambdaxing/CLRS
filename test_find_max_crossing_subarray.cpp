#include <iostream>
#include <memory>

#include "find_maximum_subarray.h"

using namespace std;

int main() {
  constexpr unsigned num = 16;
  int n1[2]{-1, 1};
  int n2[num]{13, -3, -25, 20, -3,  -16, -23, 18,
              20, -7, 12,  -5, -22, 15,  -4,  7};
  shared_ptr<int> dn(new int[num]{13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12,
                                  -5, -22, 15, -4, 7},
                     default_delete<int[]>());

  auto maxn1 = find_maximum_subarray(n1);
  auto maxn2 = find_maximum_subarray(n2);
  auto maxdn = find_maximum_subarray(dn.get(), num);
  cout << maxn1 << endl << maxn2 << endl << maxdn << endl;
}