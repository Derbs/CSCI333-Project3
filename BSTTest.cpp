#include <iostream>
#include "BST.h"

int main() {
  BST<int>* test = new BST<int>();
  for(int i = 0; i < 6; i++) {
    test->insert(i);
    test->print();
  }

  for(int i = 9; i >= 6; i--) {
    test->insert(i);
    test->print();
  }
  test->remove(0);
  test->print();
  test->remove(3);
  test->print();
  test->remove(4);
  test->print();
  test->remove(7);
  test->print();
  delete test;

  
  return 0;
}
