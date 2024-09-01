#include"RBTreeNode.h"
#include<memory>
template<class T>
RBTNode<T> RBTNode<T>::nil = std::move(RBTNode(BLACK));

template<class T>
RBTNode<T>::RBTNode(T val):leftChild(&nil),rightChild(&nil),father(nullptr),val(val),c(RED)
{

}

template<class T>
RBTNode<T>::RBTNode(color c):leftChild(&nil), rightChild(&nil), father(&nil), c(c)
{
	
}

template<class T>
RBTNode<T>::~RBTNode(void)
{

}