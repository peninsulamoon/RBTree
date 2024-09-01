#include"RBTree.h"
#include<iostream>
#include<queue>
 

template<class T>
RBTree<T>::RBTree(T RootData)
{
	root = new RBTNode<T>(RootData);
	root->c = BLACK; 
}

template<class T>
RBTree<T>::RBTree(void):root(nullptr)
{
}


template<class T>
RBTree<T>::~RBTree(void)
{

}

template<class T>
void RBTree<T>::Print(void)
{
	std::queue<RBTNode<T>*> que;
	std::queue<int> depth;
	//que.reserve(100);
	if (root == nullptr)
		return;
	que.push(root);
	depth.push(0);
	while (!que.empty())
	{
		RBTNode<T>* p = que.front();
		int d = depth.front();
		std::cout << p->val << "color" << p->c << "depth" << d << std::endl;
		depth.pop();
		if (p->leftChild != &RBTNode<T>::nil)
		{
			que.push(p->leftChild);
			depth.push(d + 1);
		}
		if (p->rightChild != &RBTNode<T>::nil)
		{
			que.push(p->rightChild);
			depth.push(d + 1);
		}
		que.pop();
	}
}

template<class T>
void RBTree<T>::LeftRotate(RBTNode<T>* currentNode)
{
	//assert(currentNode!=&RBTNode::nil)
	//RBTNode<T>* p = currentNode->leftChild;
	RBTNode<T>* q = currentNode->rightChild->leftChild;
	//RBTNode<T>* r = currentNode->rightChild->rightChild;
	if (currentNode->father!= nullptr) {
		if (currentNode->father->leftChild == currentNode)
		{
			currentNode->father->leftChild = currentNode->rightChild;
		}
		else
		{
			currentNode->father->rightChild = currentNode->rightChild;
		}
	}
	else 
		root = currentNode->rightChild;
	currentNode->rightChild->father = currentNode->father;
	currentNode->father = currentNode->rightChild;
	currentNode->rightChild->leftChild = currentNode;
	currentNode->rightChild = q;
	q->father = currentNode;
}

template<class T>
void RBTree<T>::RightRotate(RBTNode<T>* currentNode)
{
	//assert(currentNode!=&RBTNode::nil)
	//RBTNode<T>* p = currentNode->leftChild;
	RBTNode<T>* q = currentNode->leftChild->rightChild;
	//RBTNode<T>* r = currentNode->rightChild->rightChild;
	if (currentNode->father != nullptr) {
		if (currentNode->father->leftChild == currentNode)
		{
			currentNode->father->leftChild = currentNode->leftChild;
		}
		else
		{
			currentNode->father->rightChild = currentNode->leftChild;
		}
	}
	else
		root = currentNode->leftChild;
	currentNode->leftChild->father = currentNode->father;
	currentNode->father = currentNode->leftChild;
	currentNode->leftChild->rightChild = currentNode;
	currentNode->leftChild = q;
	q->father = currentNode;
}

template<class T>
void RBTree<T>::InsertFix(RBTNode<T>* currentNode)
{
	while (currentNode->father!= nullptr && currentNode->father->c==RED && currentNode->father->father!= nullptr)
	{
		RBTNode<T>* uncle;
		bool rightUncle = (currentNode->father == currentNode->father->father->leftChild);
		if (rightUncle) {
			uncle = currentNode->father->father->rightChild;
		}			
		else {
			uncle = currentNode->father->father->leftChild;
		}
		if (uncle->c == RED)
		{
			currentNode->father->c = BLACK;
			uncle->c = BLACK;
			currentNode = currentNode->father->father;
			currentNode->c = RED;
			continue;
		}
		if (rightUncle && currentNode->father->rightChild == currentNode)
		{
			LeftRotate(currentNode->father);
			currentNode = currentNode->leftChild;
		}
		if ((!rightUncle) && currentNode->father->leftChild == currentNode)
		{
			RightRotate(currentNode->father);
			currentNode = currentNode->rightChild;
		}
		if (rightUncle)
		{
			RightRotate(currentNode->father->father);
			currentNode->father->rightChild->c = RED;
		}
		else {
			LeftRotate(currentNode->father->father);
			currentNode->father->leftChild->c = RED;
		}
		currentNode->father->c = BLACK;
		break;
	}
	root->c = BLACK;
}

template<class T>
void RBTree<T>::InsertNode(T insertData)
{
	if (root == nullptr)
	{
		root = new RBTNode<T>(insertData);
		root->c = BLACK;
		return;
	}
	RBTNode<T>* pos = root;
	RBTNode<T>* temp = pos;
	while (pos!=&RBTNode<T>::nil)
	{
		temp = pos;
		if (insertData > pos->val)
			pos = pos->rightChild;
		else if (insertData < pos->val)
			pos = pos->leftChild;
		else
			return;
	}
	if (insertData >= temp->val)
	{
		temp->rightChild = new RBTNode<T>(insertData);
		temp->rightChild->father = temp;
		temp = temp->rightChild;
	}
	else
	{
		temp->leftChild = new RBTNode<T>(insertData);
		temp->leftChild->father = temp;
		temp = temp->leftChild;
	}
	if (temp->father->c == RED)
		InsertFix(temp);
	//std::cout << temp->val << std::endl;
}


template<class T>
RBTNode<T>* RBTree<T>::Find(T findData)
{
	if (root == nullptr)
		return nullptr;
	RBTNode<T>* pos = root;
	while (pos != &RBTNode<T>::nil)
	{
		if (findData == pos->val)
			return pos;
		if (findData > pos->val)
			pos = pos->rightChild;
		else if (findData < pos->val)
			pos = pos->leftChild;
	}
	return nullptr;
}

template<class T>
void RBTree<T>::Transplant(RBTNode<T>* u, RBTNode<T>* v)
{
	if (u->father==nullptr)
		root = (v== &RBTNode<T>::nil)?nullptr:v;
	else if (u == u->father->leftChild)
	{
		u->father->leftChild = v;
	}
	else
		u->father->rightChild = v;
	 v->father = u->father;
}

template<class T>
void RBTree<T>::DeleteFix(RBTNode<T>* currentNode)
{
	while (currentNode->father!=nullptr && currentNode->c == BLACK)
	{
		RBTNode<T>* p = currentNode->father;
		if (currentNode == p->leftChild)
		{
			RBTNode<T>* sibling = p->rightChild;
			if (sibling->c == RED)
			{
				LeftRotate(p);
				RBTNode<T>::nil.father = p;
				sibling = p->rightChild;
			}
			if (sibling->leftChild->c == BLACK && sibling->rightChild->c == BLACK)
			{
				sibling->c = RED;
				currentNode = p;
				continue;
			}
			else if (sibling->rightChild->c == BLACK)
			{
				RightRotate(sibling);
				RBTNode<T>::nil.father = p;
				sibling->c = RED;
				sibling = sibling->father;			
				sibling->c = BLACK;
			}
			LeftRotate(currentNode->father);
			RBTNode<T>::nil.father = p;
			sibling->c = currentNode->father->c;
			sibling->rightChild->c = BLACK;
			currentNode->father->c = BLACK;
			currentNode = root;
		}
		else
		{
			RBTNode<T>* sibling = p->leftChild;
			if (sibling->c == RED)
			{
				RightRotate(p);
				RBTNode<T>::nil.father = p;
				sibling = p->leftChild;
			}
			if (sibling->leftChild->c == BLACK && sibling->rightChild->c == BLACK)
			{   
				sibling->c = RED;
				currentNode = p;
				continue;
			}
			else if (sibling->leftChild->c == BLACK)
			{
				LeftRotate(sibling);
				RBTNode<T>::nil.father = p;
				sibling->c = RED;
				sibling = sibling->father;
				sibling->c = BLACK;
			}
			RightRotate(currentNode->father);
			RBTNode<T>::nil.father = p;
			sibling->c = currentNode->father->c;
			sibling->leftChild->c = BLACK;
			currentNode->father->c = BLACK;
			currentNode = root;
		}
	}
	currentNode->c = BLACK;
}

template<class T>
int RBTree<T>::DeleteNode(T deleteData)
{
	RBTNode<T>* dn = Find(deleteData);
	if (dn == nullptr)
		return -1;
	color orignalColor = dn->c;
	RBTNode<T>* y = dn;
	RBTNode<T>* x;
	if (dn->leftChild == &RBTNode<T>::nil)
	{
		x = dn->rightChild;
		Transplant(dn, dn->rightChild);
	}
	else if (dn->rightChild == &RBTNode<T>::nil)
	{
		x = dn->leftChild;
		Transplant(dn, dn->leftChild);
	}
	else
	{
		y = dn->rightChild;
		while (y->leftChild != &RBTNode<T>::nil)
			y = y->leftChild;
		orignalColor = y->c;
		x = y->rightChild;
		if (y->father == dn)
			x->father = y;
		else
		{
			Transplant(y, y->rightChild);
			y->rightChild = dn->rightChild;
			y->rightChild->father = y;
		}
		Transplant(dn, y);
		y->leftChild = dn->leftChild;
		y->leftChild->father = y;
		y->c = dn->c;
	}
	delete dn;
	if (orignalColor == BLACK)
		DeleteFix(x);
	return 1;
}