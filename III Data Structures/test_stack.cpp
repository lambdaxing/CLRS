#include <iostream>

#include "Widget.h"
#include "stack.h"

int main() {
  stack<Widget> aW;
  stack<int> aI;
  Widget a;
  for (int i = 1; i < 11; i++) aW.push(Widget());
  for (int i = 1; i < 11; i++) aW.push(a);
  for (int i = 1; i < 11; i++) aI.push();
  for (int i = 1; i < 11; i++) aI.push(1);
  //   stack<Widget> bW = aW;
  //   stack<Widget> cW = std::move(aW);
  //   bW = cW;
}