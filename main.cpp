#include <iostream>

using namespace std;

int main() {
  unsigned i = 0;
  auto j = i - 1;
  auto k = j + 1;
  cout << i << endl << j << endl << ++j << endl << k << endl;
}