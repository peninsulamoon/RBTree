#pragma once
#include"RBTreeNode.h"
#include"RBTreeNode.cpp"

template<class T>
class RBTree
{
public:
	RBTree();
	RBTree(T RootData);
	~RBTree();
	void Print();
	void LeftRotate(RBTNode<T>* currentNode);
	void RightRotate(RBTNode<T>* currentNode);

	void InsertFix(RBTNode<T>* currentNode);
	void InsertNode(T insertData);

	void Transplant(RBTNode<T>* u, RBTNode<T>* v);
	void DeleteFix(RBTNode<T>* currentNode);
	int DeleteNode(T deleteData);
	
	
	RBTNode<T>* Find(T findData);
	
	RBTNode<T>* root;
};