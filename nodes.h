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


template<class T> class TreeNode{
public:
	TreeNode(T *Key,TreeNode *Left,TreeNode *Right)
		:Key(Key),Left(Left),Right(Right){}
	~TreeNode(){Left=Right=NULL,delete Key;}
	
	T *Key;
	TreeNode *Left,*Right;
};

template<class T> class TreeNodeWParent{
public:
	TreeNodeWParent(T *Key,TreeNodeWParent *Left,TreeNodeWParent *Right,TreeNodeWParent *Parent)
		:Key(Key),Left(Left),Right(Right),Parent(Parent){}
	~TreeNodeWParent(){delete Key,Left=Right=Parent=NULL;}
	
	T *Key;
	TreeNodeWParent *Left,*Right,*Parent;
};

template<class Comparable,class T> class TreeMapNode{
    
};

template<class Comparable,class T> class TreeMapNodeWParent{
    
};

#include "nodes.cpp"
#endif /* NODES_H */