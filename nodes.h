/*
	nodes.h

*/
#ifndef NODES_H
#define NODES_H
#include <stdio.h>

template <class T> class GenericNode{
public:
    GenericNode(){key=NULL;}
	GenericNode(T* key):key(key){}
    ~GenericNode(){delete key;}
	T* key;
};

/* Priority Queues (key1(priority), key2(ptr_to_object)) */
template <class T1, class T2> class DoubleGenericNode{
public:
    DoubleGenericNode(){key1=NULL;key2=NULL;}
	DoubleGenericNode(T1* key1,T2* key2):key1(key1),key2(key2){}
    ~DoubleGenericNode(){delete key1;delete key2;}
	T1* key1; // used as priority
	T2* key2; // used as Data
}; 

class SingleListNode{
public:
    SingleListNode(){Next=NULL;key=NULL;}
	SingleListNode(int* key, SingleListNode *Next)
		:key(key),Next(Next){}
    ~SingleListNode(){delete key;Next=NULL;}
	
	int *key;
	SingleListNode *Next;
};

template<class T> class GenericSingleListNode{
public:
    GenericSingleListNode(){key=NULL;Next=NULL;}
	GenericSingleListNode(T *key, GenericSingleListNode *Next)
		:key(key),Next(Next){}
    ~GenericSingleListNode(){delete key;Next=NULL;}
	
	T* key;
	GenericSingleListNode<T> *Next;
};


template<class Comparable> class TreeNode{
public:
    TreeNode(){Key=NULL;Left=Right=NULL;}
	TreeNode(Comparable *Key,TreeNode *Left,TreeNode *Right)
		:Key(Key),Left(Left),Right(Right){}
	~TreeNode(){Left=Right=NULL,delete Key;}
	
	Comparable *Key;
	TreeNode *Left,*Right;
};

/* Used by Binary Search Tree */
template<class Comparable> class TreeNodeWParent{
public:
    TreeNodeWParent(){Key=NULL;Left=Right=Parent=NULL;}
	TreeNodeWParent(Comparable *Key,TreeNodeWParent *Left,TreeNodeWParent *Right,TreeNodeWParent *Parent)
		:Key(Key),Left(Left),Right(Right),Parent(Parent){}
    TreeNodeWParent(Comparable *Key):Key(Key){Left=Right=Parent=NULL;}
	~TreeNodeWParent(){delete Key,Left=Right=Parent=NULL;}
	
	Comparable *Key;
	TreeNodeWParent *Left,*Right,*Parent;
};

template<class Comparable,class T> class TreeMapNode{
public:
    TreeMapNode(){Key=NULL;Data=NULL;Left=Right=NULL;}
    TreeMapNode(Comparable *Key,T *Data,TreeMapNode *Left,TreeMapNode *Right)
    :Key(Key),Data(Data),Left(Left),Right(Right){}
    ~TreeMapNode(){Left=Right=NULL,delete Key;delete Data;}
    
    Comparable *Key;
    T *Data;
    TreeMapNode *Left,*Right;
};

/* Used by Binary Search Tree Map(Dictionary) */
template<class Comparable,class T> class TreeMapNodeWParent{
public:
    TreeMapNodeWParent(){Key=NULL;Data=NULL;Left=Right=Parent=NULL;}
    TreeMapNodeWParent(Comparable *Key,T *Data,TreeMapNodeWParent *Left,TreeMapNodeWParent *Right,TreeMapNodeWParent *Parent)
    :Key(Key),Data(Data),Left(Left),Right(Right),Parent(Parent){}
    TreeMapNodeWParent(Comparable *Key,T *Data):Key(Key),Data(Data){Left=Right=Parent=NULL;}
    ~TreeMapNodeWParent(){delete Key,Left=Right=Parent=NULL;}
    
    Comparable *Key;
    T *Data;
    TreeMapNodeWParent *Left,*Right,*Parent;
};

#include "nodes.cpp"
#endif /* NODES_H */