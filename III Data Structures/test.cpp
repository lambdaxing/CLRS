#include <string>

#include "binarySearchTree.h"

int main() {
  binarySearchTree<int> ti;
  binarySearchTree<std::string> ts;

  for (int i = 0; i < 11; i++) ti.insert(i);
  for (int i = 0; i < 11; i++) ts.insert(std::to_string(i) + std::string(" "));
  for (int i = 0; i < 11; i++) ti.del(i);
  for (int i = 0; i < 11; i++) ts.del(std::to_string(i) + std::string(" "));
}