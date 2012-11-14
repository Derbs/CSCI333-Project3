#include <iostream>
#include "BST.h"

int main() {
  BST<int>* test = new BST<int>();
  for(int i = 0; i<11; i++) {
    test->insert(i);
    test->print();
  }
  std::cout<<test->find(10)<<" "<<test->find(12)<<std::endl;
  test->remove(5);
  test->remove(4);
  test->remove(7);
  test->remove(10);
  test->print();
  delete test;
  //test->breadthPrint();
  //test->leftRotation((Node<int>**)0);
  //test->insert(4);
  //test->insert(2);
  /*test->insert(6);
  test->insert(8);
  test->insert(2);
  test->insert(9);
  test->insert(10);
  test->insert(11);
  test->insert(12);*/
  
  //test->breadthPrint();
  //test->rightRotation((Node<int>**)0);
  //test->breadthPrint();
  //test->rightRotation((Node<int>**)0);
  return 0;
}
