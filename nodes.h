/*
	nodes.h

*/
#ifndef NODES_H
#define NODES_H
#include <stdio.h>

template <class T> class GenericNode{
public:
	GenericNode(T* key):key(key){}
	~GenericNode(){}
	T* key;
};

// Priority Queues (key1(priority), key2(ptr_to_object))
template <class T1, class T2> class DoubleGenericNode{
public:
	DoubleGenericNode(T1* key1,T2* key2):key1(key1),key2(key2){}
	~DoubleGenericNode(){}
	T1* key1; // used as priority
	T2* key2; // used as Data
}; 

class SingleListNode{
public:
	SingleListNode(int key, SingleListNode *Next)
		:key(key),Next(Next){}
	~SingleListNode(){Next=NULL;}
	
	int key;
	SingleListNode *Next;
};

template<class T> class GenericSingleListNode{
public:
	GenericSingleListNode(T key, GenericSingleListNode *Next)
		:key(key),Next(Next){}
	~GenericSingleListNode(){Next=NULL;}
	
	T key;
	GenericSingleListNode<T> *Next;
};

class TreeNode{
public:
	TreeNode(int key,TreeNode *Left,TreeNode *Right)
		:key(key),Left(Left),Right(Right){}
	~TreeNode(){Left=Right=NULL;}
	
	int key;
	TreeNode *Left,*Right;
};

class TreeNodeParent{
public:
	TreeNodeParent(int key,TreeNodeParent *Left,TreeNodeParent *Right,TreeNodeParent *Parent)
		:key(key),Left(Left),Right(Right),Parent(Parent){}
	~TreeNodeParent(){Left=Right=Parent=NULL;}
	
	int key;
	TreeNodeParent *Left,*Right,*Parent;
};

template<class T> class DataTreeNode{
public:
	DataTreeNode(int key, T *Data,DataTreeNode *Left,DataTreeNode *Right)
		:key(key),Data(Data),Left(Left),Right(Right){}
	~DataTreeNode(){Data=Left=Right=NULL;}
	
	T *Data;
	int key;
	DataTreeNode *Left,*Right;
};

template<class T> class DataTreeNodeParent{
public:
	DataTreeNodeParent(int key, T *Data,DataTreeNodeParent *Left,DataTreeNodeParent *Right,DataTreeNodeParent *Parent)
		:key(key),Data(Data),Left(Left),Right(Right),Parent(Parent){}
	~DataTreeNodeParent(){Data=Left=Right=Parent=NULL;}
	
	T *Data;
	int key;
	DataTreeNodeParent *Left,*Right,*Parent;
};

#include "nodes.cpp"
#endif /* NODES_H */