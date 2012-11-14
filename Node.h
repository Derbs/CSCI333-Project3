#ifndef __NODE_H__
#define __NODE_H__

template <typename T>
class Node {
 private:
  T value;
  Node<T>* leftChild;
  Node<T>* rightChild;
  int balance;
 public:
  Node<T>(T v);
  T getValue();

  Node<T>*& getLeftChild();
  void setLeftChild(Node<T>& n);

  Node<T>*& getRightChild();
  void setRightChild(Node<T>& n);  
  int getBalance();
  void incBal();  //increment balance by 1.
  void decBal();  //decrement balance by 1.
  void setBal(int b);
};
#endif
