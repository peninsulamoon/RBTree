#pragma once
enum color{
	RED = 0, BLACK = 1
};

template<class T>
struct RBTNode {
	struct RBTNode* leftChild;
	struct RBTNode* rightChild;
	struct RBTNode* father;
	T val;
	color c;

	RBTNode(T val);

	RBTNode(color c);
	~RBTNode();

	static  RBTNode nil;
};