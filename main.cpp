#include <iostream>

using namespace std;

unsigned radix(const unsigned& n, unsigned j) {
  int i = 1;
  std::cout << i - 1;
  return (10 ^ i);
}

int main() {
  for (int i = 1; i < 100; i++) {
    std::cout << i << " " << radix(i, 1) << std::endl;
  }
}