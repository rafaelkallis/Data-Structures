/*
	nodes.h

*/
#ifndef NODES_H
#define NODES_H
#include <stdio.h>
/* Node */
template <class T> class Node{
public:
    Node(){key=NULL;}
	Node(T* key):key(key){}
    ~Node(){delete key;}
	T* key;
};

/* MapNode */
/* Priority Queues (key1(priority), key2(ptr_to_object)) */
template <class T1, class T2> class MapNode{
public:
    MapNode(){key1=NULL;key2=NULL;}
	MapNode(T1* key1,T2* key2):key1(key1),key2(key2){}
    ~MapNode(){delete key1;delete key2;}
	T1* key1; // used as priority
	T2* key2; // used as Data
};

/* SingleListNode */
template<class T> class SingleListNode{
public:
    SingleListNode(){key=NULL;Next=NULL;}
	SingleListNode(T *key, SingleListNode *Next)
		:key(key),Next(Next){}
    ~SingleListNode(){delete key;Next=NULL;}
	
	T* key;
	SingleListNode<T> *Next;
};

/* Used by Binary Search Tree */
template<class Comparable> class TreeNode{
public:
    TreeNode(){Key=NULL;Left=Right=Parent=NULL;}
	TreeNode(Comparable *Key,TreeNode *Left,TreeNode *Right,TreeNode *Parent)
		:Key(Key),Left(Left),Right(Right),Parent(Parent){}
    TreeNode(Comparable *Key):Key(Key){Left=Right=Parent=NULL;}
	~TreeNode(){delete Key,Left=Right=Parent=NULL;}
	
	Comparable *Key;
	TreeNode *Left,*Right,*Parent;
};

/* Used by Binary Search Tree Map(Dictionary) */
template<class Comparable,class T> class TreeMapNode{
public:
    TreeMapNode(){Key=NULL;Data=NULL;Left=Right=Parent=NULL;}
    TreeMapNode(Comparable *Key,T *Data,TreeMapNode *Left,TreeMapNode *Right,TreeMapNode *Parent)
    :Key(Key),Data(Data),Left(Left),Right(Right),Parent(Parent){}
    TreeMapNode(Comparable *Key,T *Data):Key(Key),Data(Data){Left=Right=Parent=NULL;}
    ~TreeMapNode(){delete Key,Left=Right=Parent=NULL;}
    
    Comparable *Key;
    T *Data;
    TreeMapNode *Left,*Right,*Parent;
};

#include "nodes.cpp"
#endif /* NODES_H */