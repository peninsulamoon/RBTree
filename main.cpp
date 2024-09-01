#include<iostream>
#include"RBTree.h"
#include"RBTree.cpp"

int main()
{
	RBTree<float> t;
	for (int i = 0; i < 10000; i++)
	{
		t.InsertNode(i);
	}
	t.Print();
	for (int i = 0; i < 10000; i++)  
	{
		t.DeleteNode(i);
	}   
	t.Print();
	return 0;     
}