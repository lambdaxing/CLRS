#include <iostream>

#include "insertion_sort.h"

using namespace std;

int main() {
  int n[6] = {5, 4, 3, 2, 1, 6};
  for_each(cbegin(n), cend(n), [](int i) { cout << i << " "; });
  cout << endl;
  insertion_sort(n);
  for_each(cbegin(n), cend(n), [](int i) { cout << i << " "; });
  cout << endl;
}