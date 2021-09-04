#include <iostream>

#include "Widget.h"
#include "listQueue.h"

int main() {
  listQueue<Widget> aW;
  listQueue<int> aI;
  Widget a;
  for (int i = 1; i < 11; i++) aW.enqueue(Widget());
  for (int i = 1; i < 11; i++) aW.enqueue(a);
  for (int i = 1; i < 11; i++) aI.enqueue();
  for (int i = 1; i < 11; i++) aI.enqueue(1);
  listQueue<Widget> bW = aW;
  listQueue<Widget> cW = std::move(aW);
  bW = cW;
  cW = std::move(bW);

  listQueue<int> bI = aI;
  listQueue<int> cI = std::move(aI);
  bI = cI;
  cI = std::move(bI);

  for (int i = 1; i < 11; i++) cW.dequeue();
  for (int i = 1; i < 11; i++) cI.dequeue();
  for (int i = 1; i < 11; i++) cI.dequeue();
}