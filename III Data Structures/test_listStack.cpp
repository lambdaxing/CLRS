#include <iostream>

#include "Widget.h"
#include "listStack.h"

int main() {
  listStack<Widget> aW;
  listStack<int> aI;
  Widget a;
  for (int i = 1; i < 11; i++) aW.push(Widget());
  for (int i = 1; i < 11; i++) aW.push(a);
  for (int i = 1; i < 11; i++) aI.push();
  for (int i = 1; i < 11; i++) aI.push(1);
  //   listStack<Widget> bW = aW;
  //   listStack<Widget> cW = std::move(aW);
  //   bW = cW;
}