#include <iostream>

#include "Widget.h"
#include "deque.h"

int main() {
  deque<Widget> aW;
  deque<int> aI;
  for (int i = 1; i < 11; i++) aW.push_back(Widget());
  for (int i = 1; i < 11; i++) aW.emplace_front();
  for (int i = 1; i < 11; i++) aI.push_front(i);
  for (int i = 1; i < 11; i++) aI.push_back(1);
  for (int i = 1; i < 11; i++) aI.emplace_back();
  deque<Widget> bW = aW;
  deque<Widget> cW = std::move(aW);
  bW = cW;
  cW = std::move(bW);

  deque<int> bI = aI;
  deque<int> cI = std::move(aI);
  bI = cI;
  cI = std::move(bI);
  cI.front();
  cI.back();
  cW.back();
  cW.front();
  for (int i = 1; i < 11; i++) cW.pop_front();
  for (int i = 1; i < 11; i++) cI.pop_back();
  for (int i = 1; i < 11; i++) cI.pop_front();
}