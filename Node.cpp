#include <string>
#include "Node.h"

template <typename T>
Node<T>::Node(T v) {
  value = v;
  leftChild = 0;
  rightChild = 0;
  balance = 0;
}

template <typename T>
T Node<T>::getValue() {
  return value;
}

template <typename T>
Node<T>*& Node<T>::getLeftChild() {
  return leftChild;
}

template <typename T>
void Node<T>::setLeftChild(Node<T>& lc) {
  leftChild = &lc;
}

template <typename T>
Node<T>*& Node<T>::getRightChild() {
  return rightChild;
}

template <typename T>
void Node<T>::setRightChild(Node<T>& rc) {
  rightChild = &rc;
}

template <typename T>
int Node<T>::getBalance() {
  return balance;
}

template <typename T> 
void Node<T>::setBal(int b) {
  balance = b;
}

template <typename T>
void Node<T>::incBal() {
  balance += 1;
}

template <typename T>
void Node<T>::decBal() {
  balance -=1;
}

template class Node<int>;
template class Node<double>;
template class Node<std::string>;
template class Node<char>;
