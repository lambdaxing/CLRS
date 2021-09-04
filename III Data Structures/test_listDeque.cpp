#include <iostream>

#include "Widget.h"
#include "listDeque.h"

int main() {
  listDeque<Widget> aW;
  listDeque<int> aI;
  for (int i = 1; i < 11; i++) aW.push_back(Widget());
  for (int i = 1; i < 11; i++) aW.emplace_front();
  for (int i = 1; i < 11; i++) aI.push_front(i);
  for (int i = 1; i < 11; i++) aI.push_back(1);
  for (int i = 1; i < 11; i++) aI.emplace_back();
  listDeque<Widget> bW = aW;
  listDeque<Widget> cW = std::move(aW);
  bW = cW;
  cW = std::move(bW);

  listDeque<int> bI = aI;
  listDeque<int> cI = std::move(aI);
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