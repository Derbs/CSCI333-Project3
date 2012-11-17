#ifndef __BST_H__
#define __BST_H__

#include "Node.h"
#include <string>
#include <list>

template <typename T>
class BST {
 private:
  Node<T>* root;
  void traversalPrint(Node<T>* curr);
  void levelTraversal(std::list< Node<T>* >* parents, int level);
  void postPrint(Node<T>* curr);
  void leftRotation(Node<T>** crit);
  void rightRotation(Node<T>** crit);
  int pow(int a, int p);
  int depth(Node<T>* curr, int dpth, int maxDepth);
  void destructorHelper(Node<T>* curr);  
 public:
  BST<T>();
  ~BST<T>();
  bool find(T v);
  void remove(T v);
  void insert(T v);
  void inOrderTraversal();
  void print();
  void postOrderTraversal();
};

#endif
