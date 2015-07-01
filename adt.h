/*
	adt.h
    Created by Rafael Kallis
    Copyright (c) 2015 Rafael Kallis. All rights reserved.
*/

/*
 Stack<T>
 Queue<T>
 SimpleHeap<T>
 PriorityQueue<T>
 */
#ifndef ADT_H
#define ADT_H
#include "nodes.h"
#include "exceptions.h"
#include "arrays.h"
#include <stdio.h>

/*
    Stack
    Implements a simple LinkedList for dynamic memory allocation.
    Top(),Pop(),Push(),Size(): Worst Case - O(1)
 */

template<class T> class Stack{
public:
    Stack(){Head=NULL,size=0;}
	~Stack(){try{ while(1)Pop();}catch(EmptyADTException e){ Head=NULL;}}
	
	T Top();
	void Pop();
	void Push(T key);
	int Size();
	
protected:
    /*
     GenericSingleListNode is a Node consisting of:
     1) Key (of class T).
     2) Pointer to next Node.
     GenericSingleListNode<T> definition found in nodes.h
     */
	GenericSingleListNode<T> *Head;
	int size;	
};

/*
    Queue
    Implements a simple LinkedList for dynamic memory allocation.
    Top(),Pop(),Push(),Size(): Worst Case - O(1)
 */

template<class T> class Queue{
public:
    Queue(){Head=Tail=NULL,size=0;}
    ~Queue(){try{ while(1)Pop();}catch(EmptyADTException e){ Head=NULL;}}
    
    T Top();
    void Pop();
    void Push(T key);
    int Size();
protected:
    /*
        GenericSingleListNode is a Node consisting of:
        1) Key (of class T).
        2) Pointer to next Node.
        GenericSingleListNode<T> definition found in nodes.h
     */
    GenericSingleListNode<T> *Head,*Tail;
    int size;
};

/*
    MinHeap Abstract Class
 
    T: the Data type. NodeType: Node(Container) used for implementation
 
    Insert(),Extract(): Worst Case - O(lg n)
 */

template<class Comparable,class NodeType> class ABCHeap{
public:
    
    /* 
     Adds a Node(Container) of Object (of class Comparable) into Heap.
     Must be Overloaded in derived class.
     See adt.cpp for Details
     */
    virtual void Insert();
    
    /*
     Returns Object (of class Comparable) without the Container.
     Must be Overloaded in derived class.
     See adt.cpp for Details
     */
    void Extract();

protected:
    /*
     Array Used for storing Heap Data.
     ArrayList is a self-expanding and collapsing dynamic array.
     ArrayList can be found in arrays.h
     */
    ArrayList<NodeType> *Data;
    
    /* Returns Key of Node, depending on use this is used different. */
    virtual Comparable* GetNodeKey(int index)=0;
    
    /* Functions used by Insert() and Extract() */
    void Swap(int i, int j);
    void Perc_Up(int index);
    void Perc_Down(int index);
    int Left(int index){return (2*index)+1;}
    int Right(int index){return (2*index)+2;}
    int Parent(int index){return (index-1)/2;}
};

/*
    SimpleHeap
    Uses GenericNode<T>, a simple Node containing only a T* pointer.
*/

template<class Comparable> class SimpleHeap: public ABCHeap<Comparable,GenericNode<Comparable>>{
public:
    
    SimpleHeap(){ABCHeap<Comparable,GenericNode<Comparable>>::Data=new ArrayList<GenericNode<Comparable>>;}
    ~SimpleHeap(){delete ABCHeap<Comparable,GenericNode<Comparable>>::Data;}
    
    void Insert(Comparable *Data);
    Comparable* Extract();
    
protected:
    
    Comparable* GetNodeKey(int index){
        return ABCHeap<Comparable,GenericNode<Comparable>>::Data->Get(index)->key;}
};

/*
    PriorityQueue
    Uses ArrayList of DoubleGenericNode<int,T>, each node consisting of:
    1) int* key1, used as the Priority key for comparison.
    2) T* key2, the actual Data.
*/

template<class T> class PriorityQueue:public ABCHeap<int,DoubleGenericNode<int, T>>{
public:
    
    PriorityQueue(){
        ABCHeap<int,DoubleGenericNode<int,T>>::Data=new ArrayList<DoubleGenericNode<int,T>>();
    }
    ~PriorityQueue(){delete ABCHeap<int,DoubleGenericNode<int,T>>::Data;}

    /*
     Pretty straight-forward, Inserts a Node with Data and the Data's priority.
     
     Insert(new int(3),new char('R'));
     => Inserts a new node of char value 'R' and priority 3. <=
     */
    void Insert(int* priority, T* Data);
    
    /* Returns the Object with smallest Priority. */
    T* Extract();
    
protected:
    
    /* Returns key1 used for priority comparison */
    int* GetNodeKey(int index){
        return ABCHeap<int,DoubleGenericNode<int, T>>::Data->Get(index)->key1;}
    
};


/*
    Abstract Tree Class
 
    *Root is the Root Node of NodeType Class
 
    Insert: O(lg n) - Average
            O(n) - Worst Case
    Delete: O(lg n) - Average
            O(n) - Worst Case
    Reset:  O(n) - Average & Worst Case
 */


template<class Comparable,class NodeType> class ABCtree{
public:
    
    /* Basic Functions */
    void Insert(Comparable *Key);
    void Delete(Comparable *Key);
    void Reset();
    
    /* Useful for Debugging */
    void PrintInOrder();
    void PrintGraph();
    
protected:
    
    /* Overloaded Functions using Tree Traversal */
    void Reset(NodeType *Root);
    void PrintInOrder(NodeType *Root);
    void PrintGraph(NodeType *Root);
    
    /*  */
    NodeType *Smallest(NodeType *Root);
    NodeType *Search(Comparable *Key);
    bool isLeftChild(NodeType *Root);
    
    /* To be Defined in Derived Classes */
    virtual void Swap(NodeType *Node1, NodeType *Node2)=0;
    
    /* Node Accessors, To be Defined in Derived Classes */
    virtual Comparable *GetNodeKey(NodeType *Node)=0;
    virtual NodeType *GetLeftChild(NodeType *Node)=0;
    virtual void SetLeftChild(NodeType *Node,NodeType *Child)=0;
    virtual NodeType *GetRightChild(NodeType *Node)=0;
    virtual void SetRightChild(NodeType *Node,NodeType *Child)=0;
    virtual NodeType *GetParent(NodeType *Node)=0;
    virtual void SetParent(NodeType *Node,NodeType *Parent)=0;
    
    NodeType *Root;
};

/*
    Binary Search Tree
    Node has a Comparable Object and 3 Pointers(Parent, Left Child, Right Child)
 */

template<class Comparable> class Tree: public ABCtree<Comparable, TreeNodeWParent<Comparable>>{
public:
    
    Tree(){this->Root=NULL;}
    ~Tree(){this->Reset();}
    
protected:
    
    void Swap(TreeNodeWParent<Comparable> *Node1,TreeNodeWParent<Comparable> *Node2);
    Comparable *GetNodeKey(TreeNodeWParent<Comparable> *Node);
    TreeNodeWParent<Comparable> *GetLeftChild(TreeNodeWParent<Comparable> *Node);
    void SetLeftChild(TreeNodeWParent<Comparable> *Node,TreeNodeWParent<Comparable> *Child);
    TreeNodeWParent<Comparable> *GetRightChild(TreeNodeWParent<Comparable> *Node);
    void SetRightChild(TreeNodeWParent<Comparable> *Node,TreeNodeWParent<Comparable> *Child);
    TreeNodeWParent<Comparable> *GetParent(TreeNodeWParent<Comparable> *Node);
    void SetParent(TreeNodeWParent<Comparable> *Node,TreeNodeWParent<Comparable> *Parent);
};

#include "adt.cpp"
#endif /* ADT_H */
