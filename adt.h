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

template<class T,class NodeType> class ABCHeap{
public:
    
    /* 
     Adds a Node(Container) of Object (of class T) into Heap.
     Must be Overloaded in derived class.
     See adt.cpp for Details
     */
    virtual void Insert();
    
    /*
     Returns Object (of Class T) without the Container.
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
    virtual T* GetNodeKey(int index)=0;
    
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

template<class T> class SimpleHeap: public ABCHeap<T,GenericNode<T>>{
public:
    
    SimpleHeap(){ABCHeap<T,GenericNode<T>>::Data=new ArrayList<GenericNode<T>>;}
    ~SimpleHeap(){delete ABCHeap<T,GenericNode<T>>::Data;}
    
    void Insert(T *Data);
    T* Extract();
    
protected:
    
    T* GetNodeKey(int index){
        return ABCHeap<T,GenericNode<T>>::Data->Get(index)->key;}
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

#include "adt.cpp"
#endif /* ADT_H */