#include "maxPriorityQueue.h"

int main() {
  maxPriorityQueue<int> a{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
  for (unsigned i = 1; i < 13; i++) {
    std::cout << a.heap_maximum() << " " << a.heap_extract_max() << " ";
  }
  std::cout << std::endl;
  for (unsigned i = 1; i < 13; i++) {
    a.max_heap_insert(i);
    a.heap_increase_key(1, i + 1);
  }
  std::cout << std::endl;
  maxPriorityQueue<int> b(a);
  maxPriorityQueue<int> c(std::move(a));
  for (unsigned i = 1; i < 13; i++) {
    std::cout << b.heap_extract_max() << " ";
  }
  std::cout << std::endl;
  for (unsigned i = 1; i < 13; i++) {
    std::cout << c.heap_extract_max() << " ";
  }
  std::cout << std::endl;
}