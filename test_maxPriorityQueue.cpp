#include "maxPriorityQueue.h"

int main() {
  maxPriorityQueue<int> a;
  maxPriorityQueue<int> b{7, 32, 6, 2, 89, 1, 3, 6, 90, 3, 0};
  maxPriorityQueue<int> c(a);
  maxPriorityQueue<int> d = c;
  a = b = c = d;

  std::cout << std::endl;
  std::cout << std::endl;

  maxPriorityQueue<int> e(std::move(a));
  maxPriorityQueue<int> fb{7, 32, 6, 2, 89, 1, 3, 6, 90, 3, 0};
  maxPriorityQueue<int> f = std::move(fb);
  maxPriorityQueue<int> g{};
  g = std::move(f);
  e = b = c = d = g;
}