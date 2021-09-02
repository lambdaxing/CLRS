#include <iostream>

#include "Widget.h"
#include "queue.h"

int main() {
  queue<Widget> aW;
  queue<int> aI;
  for (int i = 1; i < 11; i++) aW.enqueue(Widget());
  for (int i = 1; i < 11; i++) aI.enqueue();
  for (int i = 1; i < 11; i++) aI.enqueue(1);
  queue<Widget> bW = aW;
  queue<Widget> cW = std::move(aW);
  bW = cW;
  cW = std::move(bW);

  queue<int> bI = aI;
  queue<int> cI = std::move(aI);
  bI = cI;
  cI = std::move(bI);

  for (int i = 1; i < 11; i++) cW.dequeue();
  for (int i = 1; i < 11; i++) cI.dequeue();
  for (int i = 1; i < 11; i++) cI.dequeue();
}