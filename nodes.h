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


template<class Comparable> class TreeNode{
public:
	TreeNode(Comparable *Key,TreeNode *Left,TreeNode *Right)
		:Key(Key),Left(Left),Right(Right){}
	~TreeNode(){Left=Right=NULL,delete Key;}
	
	Comparable *Key;
	TreeNode *Left,*Right;
};

template<class Comparable> class TreeNodeWParent{
public:
	TreeNodeWParent(Comparable *Key,TreeNodeWParent *Left,TreeNodeWParent *Right,TreeNodeWParent *Parent)
		:Key(Key),Left(Left),Right(Right),Parent(Parent){}
    TreeNodeWParent(Comparable *Key):Key(Key){Left=Right=Parent=NULL;}
	~TreeNodeWParent(){delete Key,Left=Right=Parent=NULL;}
	
	Comparable *Key;
	TreeNodeWParent *Left,*Right,*Parent;
};

template<class Comparable,class T> class TreeMapNode{
    TreeMapNode(Comparable *Key,T *Data,TreeMapNode *Left,TreeMapNode *Right)
    :Key(Key),Data(Data),Left(Left),Right(Right){}
    ~TreeMapNode(){Left=Right=NULL,delete Key;delete Data;}
    
    Comparable *Key;
    T *Data;
    TreeMapNode *Left,*Right;
};

template<class Comparable,class T> class TreeMapNodeWParent{
    TreeMapNodeWParent(Comparable *Key,T *Data,TreeMapNodeWParent *Left,TreeMapNodeWParent *Right,TreeMapNodeWParent *Parent)
    :Key(Key),Data(Data),Left(Left),Right(Right),Parent(Parent){}
    ~TreeMapNodeWParent(){delete Key,Left=Right=Parent=NULL;}
    
    Comparable *Key;
    T *Data;
    TreeMapNodeWParent *Left,*Right,*Parent;
};

#include "nodes.cpp"
#endif /* NODES_H */