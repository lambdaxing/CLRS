#include "orderStatisticTree.h"

int main() {
  orderStatisticTree<int> ostI;
  orderStatisticTree<double> ostD;

  for (int i = 1; i < 11; i++) {
    ostI.insert(i);
    ostD.insert(i);
  }
  for (int i = 20; i > 10; i--) {
    ostD.insert(i);
    ostI.insert(i);
  }
  for (int i = 1; i < 21; i++) {
    std::cout << ostI.select(i)->key << std::endl;
    std::cout << ostD.select(i)->key << std::endl;
  }
  for (int i = 20; i > 0; i--) {
    std::cout << ostI.rank(i) << std::endl;
    std::cout << ostD.rank(i) << std::endl;
  }
  for (int i = 5; i < 15; i++) {
    ostI.del(i);
    ostD.del(i);
  }
  for (int i = 1; i < 11; i++) {
    std::cout << ostI.select(i)->key << std::endl;
    std::cout << ostD.select(i)->key << std::endl;
  }
}