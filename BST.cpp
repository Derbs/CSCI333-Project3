#include "BST.h"
#include <iostream>
#include <list>

template <typename T>
BST<T>::BST() {
  root = 0;
}

template <typename T>
BST<T>::~BST() {
  destructorHelper(root);
}

template <typename T>
void BST<T>::destructorHelper(Node<T>* curr) { 
  if(curr!=0) {
    destructorHelper(curr->getLeftChild());
    destructorHelper(curr->getRightChild());
  }
  delete curr;
}

template <typename T>
void BST<T>::leftRotation(Node<T>** crit) {
  if(crit == 0) crit = &root;
  Node<T>* temp = *crit;  
  Node<T>* holder = (temp->getRightChild())->getLeftChild();
  *crit = temp->getRightChild();
  (*crit)->setLeftChild(*temp);
  (temp)->setRightChild(*holder);
}

template <typename T>
void BST<T>::rightRotation(Node<T>** crit) {
  if(crit == 0) crit = &root;
  Node<T>* temp = *crit;  
  Node<T>* holder = (temp->getLeftChild())->getRightChild();
  *crit = temp->getLeftChild();
  (*crit)->setRightChild(*temp);
  (temp)->setLeftChild(*holder);
}

template <typename T>
bool BST<T>::find(T v) {
  Node<T>** finder = &root;
  while((*finder)!=0 && (*finder)->getValue()!=v) {
    if((*finder)->getValue()<v) {
      finder = &((*finder)->getRightChild());
    }
    else {
      finder = &((*finder)->getLeftChild());
    }
  }  
  if((*finder)==0) {
    return false;
  }
  else {
    return true;
  }
  return true;
}

template <typename T>
void BST<T>::insert(T v) {
  Node<T>** P = &root;
  Node<T>* toBeAdded = new Node<T>(v);
  if(root==0) {
    root = new Node<T>(v);
    return;
  }
  bool critNodeFound = false;
  Node<T>** critNode;
  Node<T>* R;
  int d1,d2,d3;
  d1=d2=d3=0;

  while((*P)!=0 && (*P)->getValue() != v) {
    if((*P)->getBalance()!=0) {
      critNodeFound = true;
      critNode = P;
    }
    if(v<(*P)->getValue()) P = &((*P)->getLeftChild());
    else P = &((*P)->getRightChild());
  }

  if((*P)!=0) return;  //already in tree.
  (*P) = toBeAdded;

  if(!critNodeFound) {
    R = root;
  }
  else {
    //d,Q <-K :: P compares key K to the key stored at node P of a bst.  Sets Q to left or right child, and sets d to -1 if left and +1 if right.
    Node<T>** child;
    Node<T>** grandChild;
    
    if(v > (*critNode)->getValue()) {
      d1 = 1;
      child = &((*critNode)->getRightChild());
    }
    else if (v < (*critNode)->getValue()) {
      d1 = -1;
      child = &((*critNode)->getLeftChild());
    }
    if((*critNode)->getBalance() != d1) {
      (*critNode)->setBal(0);      
      R = (*P);
    }
    else {  //time to do a rotation...
      if(v > (*child)->getValue()) {
        d2 = 1;
        grandChild = &((*child)->getRightChild());
      }
      else if (v < (*child)->getValue()) {
        d2 = -1;
        grandChild = &((*child)->getLeftChild());
      }
      if(d2==d1) { //single rotation
	(*critNode)->setBal(0);
        R = *grandChild;
        if(d1 == 1) leftRotation(critNode);
        else if(d1 == -1) rightRotation(critNode);
      }
      else {
        if(v>(*grandChild)->getValue()) {
          d3 = 1;
          R = (*grandChild)->getRightChild();
        }
        else if(v<(*grandChild)->getValue()) {
          d3 = -1;
          R = (*grandChild)->getLeftChild();
        }

        if(d3==d2) {
          (*critNode)->setBal(0);
          (*child)->setBal(d1);
        }
        else if(d3==-d2){
          (*critNode)->setBal(d2);
        }
        else {
          (*critNode)->setBal(0);
        }

	if(d2==1) {
          leftRotation(child);
        }
        else {
	  rightRotation(child);
        }
        if(d1==1) {
	  leftRotation(critNode);
        }
        else{
	  rightRotation(critNode);
        }
      }
    }
    
  }

  while(R->getValue() != v) {
    if(R->getValue()<v) {
      R->setBal(1);
      R = R->getRightChild();
    }
    else if(R->getValue()>v) {
      R->setBal(-1);
      R = R->getLeftChild();
    }
  }
}

template <typename T>
void BST<T>::remove(T v) {
  Node<T>** curr = &root; 
  while(*curr!=0 && (*curr)->getValue()!=v) {
    if(v<(*curr)->getValue()) {
      curr = &(*curr)->getLeftChild();
    }
    else if (v>(*curr)->getValue()) {
      curr = &(*curr)->getRightChild();
    }
  }
  if(*curr!=0) {
    Node<T>* nodeToRemove = *curr;
    if(nodeToRemove->getRightChild() == 0 && nodeToRemove->getLeftChild() == 0) {
      *curr = 0;
    }
    else if(nodeToRemove->getRightChild() == 0) {
      *curr = (*curr)->getLeftChild();  //and we're done (no right children, so no ios)
    }
    else if(nodeToRemove->getLeftChild() == 0) {
      *curr = (*curr)->getRightChild(); //and we're done (we don't need the ios)
    }
    else {
      Node<T>* ios = nodeToRemove->getRightChild();
      while(ios->getLeftChild()!=0) {
        ios = ios->getLeftChild();
      }
      ios->setLeftChild(*(nodeToRemove->getLeftChild()));
      *curr = (*curr)->getRightChild();
    }
    delete nodeToRemove;
  }
}

template <typename T>
void BST<T>::inOrderTraversal() {
  traversalPrint(root);
}

template <typename T> 
void BST<T>::traversalPrint(Node<T>* curr) { //inOrderTraversalPrinting.  recursive.
  if(curr != 0) {
    traversalPrint(curr->getLeftChild());
    std::cout << curr->getValue() << std::endl;
    traversalPrint(curr->getRightChild());
  }
}

template <typename T>
void BST<T>::postOrderTraversal() {
  postPrint(root);  
}

template <typename T>
void BST<T>::postPrint(Node<T>* curr) {
  if(curr!=0) {
    postPrint(curr->getLeftChild());
    postPrint(curr->getRightChild());
    std::cout<<curr->getValue()<<std::endl;
  }
}

template <typename T>
void BST<T>::print() {
  std::list< Node<T>* >* topLevel = new std::list< Node<T>* >();
  topLevel->push_back(root);
  levelTraversal(topLevel,0);
}

template <typename T>
int BST<T>::pow(int a, int p) {  //helper function for breadthPrint
  if(p == 0) return 1;
  else return a*pow(a, p-1);
}

template <typename T>
int BST<T>::depth(Node<T>* curr, int dpth, int maxDepth) {  //helper function for breadthPrint
  if(curr != 0 && (curr->getLeftChild()!=0 || curr->getRightChild() != 0)) {
    int leftDepth = depth(curr->getLeftChild(),dpth+1,maxDepth);
    int rightDepth = depth(curr->getRightChild(),dpth+1,maxDepth);
    if(leftDepth > rightDepth)  return leftDepth; 
    else return rightDepth;
  }
  else {
    return dpth;
  }
  
}

//this is the actual breadthPrint - it is recursive, so this will print one level at a time.
template <typename T>
void BST<T>::levelTraversal(std::list< Node<T>* >* parents, int level) {
  bool keepGoing = false;
  int treeDepth = depth(root,0,0);
  int width = pow(2,treeDepth)*3;
  std::list< Node<T>* >* holder = new std::list< Node<T>* >();
  //determine starting spacing
  int startSpace = width-1;
  for(int i = 0; i<level+1; i++) {
    startSpace = startSpace/2;
  }
  int numEls = pow(2,level);
  if(treeDepth != level) { 
    for(int i = 0; i<startSpace; i++) { std::cout<<" "; } //initial spacing before any elements.
  }
  for(int i = 0; i<numEls; i++) {
    Node<T>* temp = parents->front();
    parents->pop_front(); 
    if(temp==0) {
      holder->push_back((Node<T>*)0);
      holder->push_back((Node<T>*)0);
      std::cout<<"-";
    }
    else if(temp->getLeftChild() == 0 && temp->getRightChild() == 0) {
      //do nothing
      holder->push_back((Node<T>*)0);
      holder->push_back((Node<T>*)0);
      std::cout<<temp->getValue();
    }
    else if(temp->getLeftChild() == 0) {
      holder->push_back((Node<T>*)0);
      holder->push_back(temp->getRightChild());
      std::cout<<temp->getValue();
      keepGoing = true;
    }
    else if(temp->getRightChild() == 0) {
      holder->push_back(temp->getLeftChild());
      holder->push_back((Node<T>*)0);
      std::cout<<temp->getValue();
      keepGoing = true;
    }
    else {
      holder->push_back(temp->getLeftChild());
      holder->push_back(temp->getRightChild());
      std::cout<<temp->getValue();
      keepGoing = true;
    }
    if(!parents->empty()) {
      int spacing = (width/numEls)-1;
      if(spacing!=2) {
        for(int i = 0; i<spacing; i++) { std::cout<<" ";}
      }
      else {
        if(i%2==0) std::cout<<"   ";
        else std::cout<<" ";
      }
    }
  }
  if(keepGoing) {
    delete parents;  //don't need it anymore!

    int lines = (width/4)-1;  //the number of branches needed between this level and next level needed
    for(int i = 0; i<level; i++) { lines = lines/2; }  //lines are based on level. (half prvLevels)
    int inBetweenSpacing = 1;     //spacing in between slashes (branches) starts at 1.
    int spacing = (width/numEls)-1;  //spacing relates to width and the number of elements.  
    for(int i = 0; i<lines; i++) {   //for every single line we make for a branch...
      std::cout<<std::endl;          //lets start on a new line.
      spacing = spacing-2;            //spacing between a right branch and the next left branch decreases by 2 as you continue along.  
      startSpace = startSpace - 1;    //remember startSpace?  subtract 1 from it and then indent.
      for(int j = 0; j<startSpace; j++) {
        std::cout<<" ";   //creating starting space before any slashes
      }
      for(int j = 0; j<numEls; j++) {  //now lets create the branches.
        std::cout<<"/"; //initial backslash for el_j
        for(int m = 0; m<inBetweenSpacing; m++) {  
          std::cout<<" ";  //now, the spacing between the left and right branch for el_j
        }
        std::cout<<"\\"; //ending forward slash for el_j
        if(numEls!=j+1) {
          for(int n = 0; n<spacing; n++) {
            std::cout<<" ";  //spacing between el_j and el_j+1
          }
        }
      }
      inBetweenSpacing = inBetweenSpacing+2;  //in between spacing increases by 2 as you go down.
    }
    std::cout<<std::endl;  //create a new line at the very very end of the branches for the next el.
    levelTraversal(holder, level+1);  //recursively go to the next level.  
  }
  else {
    std::cout<<std::endl;  //base case.  new line and finish it off.
  } 
}

template class BST<int>;
template class BST<double>;
template class BST<std::string>;
template class BST<char>;
