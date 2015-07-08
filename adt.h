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
	
	T*      Top();
	void    Pop();
	void    Push(T *Key);
	int     Size();
	
protected:
    /*
     GenericSingleListNode is a Node consisting of:
     1) Key (of class T).
     2) Pointer to next Node.
     GenericSingleListNode<T> definition found in nodes.h
     */
	SingleListNode<T>*  Head;
	int                 size;
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
    
    T*      Top();
    void    Pop();
    void    Push(T *Key);
    int     Size();
protected:
    /*
        GenericSingleListNode is a Node consisting of:
        1) Key (of class T).
        2) Pointer to next Node.
        GenericSingleListNode<T> definition found in nodes.h
     */
    SingleListNode<T> *Head,*Tail;
    int     size;
};

/*
    MinHeap Abstract Class
 
    Comparable: the Data type. NodeType: Node(Container) used for implementation
 
    Insert(),Extract(): Worst Case - O(lg n)
 */

template<class Comparable,class NodeType> class ABCHeap{
public:
    
    virtual             ~ABCHeap(){}
    
    /* 
     Adds a Node(Container) of Object (of class Comparable) into Heap.
     Must be Overloaded in derived class.
     See adt.cpp for Details
     */
    virtual void        Insert();
    
    /*
     Returns Object (of class Comparable) without the Container.
     Must be Overloaded in derived class.
     See adt.cpp for Details
     */
    void                Extract();

protected:
    /*
     Array Used for storing Heap Data.
     ArrayList is a self-expanding and collapsing dynamic array.
     ArrayList can be found in arrays.h
     */
    ArrayList_Ext<NodeType> *Data;
    
    /* Assign a value in the constructor of your derived class! */
    bool isMinHeap;
    
    /* Returns Key of Node, depending on use this is used different. */
    virtual Comparable* GetNodeKey(int index)=0;
    
    /* Functions used by Insert() and Extract() */
    bool                isSmaller(Comparable i,Comparable j);
    void                Swap(int i, int j);
    void                Perc_Up(int index);
    void                Perc_Down(int index);
    int                 Left(int index){return (2*index)+1;}
    int                 Right(int index){return (2*index)+2;}
    int                 Parent(int index){return (index-1)/2;}
};

/*
    Heap
    Uses GenericNode<T>, a simple Node containing only a T* pointer.
*/

template<class Comparable>
class MinHeap: public ABCHeap<Comparable,Node<Comparable>>{
public:
    
    MinHeap(){this->isMinHeap=true;ABCHeap<Comparable,Node<Comparable>>::Data=
        new ArrayList_Ext<Node<Comparable>>;
    }
    ~MinHeap(){delete ABCHeap<Comparable,Node<Comparable>>::Data;}
    
    void            Insert(Comparable *Data);
    Comparable*     Extract();
    
    /* Returns Value as in Extract without Removing it from the Heap */
    Comparable*     Peek();
    
protected:
    
    Comparable*     GetNodeKey(int index){
        return ABCHeap<Comparable,Node<Comparable>>::Data->Get(index)->key;
	}
};

/*
    MaxHeap
 */

template<class Comparable> class MaxHeap: public MinHeap<Comparable>{
public:
    MaxHeap():MinHeap<Comparable>(){this->isMinHeap=false;}
    ~MaxHeap(){};
};

/*
    MinPriorityQueue
    Uses ArrayList of MapNode<int,T>, each node consisting of:
    1) int* key1, used as the Priority key for comparison.
    2) T* key2, the actual Data.
*/

template<class Comparable,class T>
class MinPriorityQueue:public ABCHeap<int,MapNode<Comparable, T>>{
public:
    
    MinPriorityQueue(){this->isMinHeap=true;
        ABCHeap<Comparable,MapNode<Comparable,T>>::Data=
        new ArrayList_Ext<MapNode<Comparable,T>>();
    }
    ~MinPriorityQueue(){delete this->Data;this->Data=NULL;}

    /*
     Pretty straight-forward, Inserts a Node with Data and the Data's priority.
     
     Insert(new int(3),new char('R'));
     => Inserts a new node of char value 'R' and priority 3. <=
     */
    void            Insert(Comparable* priority, T* Data);
    
/*Returns the Object with smallest/biggest Priority and removes it from the PQ*/
    T*              Extract();
    
    /* Returns the Object with smallest/biggest Priority without removing it */
    T*              Peek();
    
protected:
    /* Returns key1 used for priority comparison */
    Comparable*     GetNodeKey(int index){
        return ABCHeap<int,MapNode<int, T>>::Data->Get(index)->key1;}
};

/*
    MaxPriorityQueue
 */

template<class Comparable,class T>
class MaxPriorityQueue:public MinPriorityQueue<Comparable,T>{
public:
    
    MaxPriorityQueue():MinPriorityQueue<Comparable,T>(){this->isMinHeap=false;}
    ~MaxPriorityQueue(){}

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
    
    virtual ~ABCtree(){}
    
    /* Basic Functions, can be Overloaded in Derived Classes */
    void                Insert(Comparable *Key);
    void                Delete(Comparable *Key);
    void                Reset();
    
    /* Useful for Debugging */
    void                PrintInOrder();
    void                PrintGraph();
    
protected:
    
    /* Can be Overloaded be Derived Classes */
    void                Insert(NodeType *Node);
    /* Overloaded Functions using Tree Traversal */
    void                Reset(NodeType *Root);
    void                PrintInOrder(NodeType *Root);
    virtual void        PrintGraph(NodeType *Root);
    
    /* */
    NodeType*           Smallest(NodeType *Root);
    NodeType*           Search(Comparable *Key);
    bool                isLeftChild(NodeType *Root);
    
    /* Following 3 functions only used in RBTs */
    virtual void        InsertFix(NodeType *toInsert,bool isInsertedLeftChild)=0;
    virtual void        DeleteFix(NodeType *Replacement,bool
                                  isReplacementLeftChild)=0;
    
    /* To be Defined in Derived Classes */
    virtual void        Swap(NodeType *Node1, NodeType *Node2)=0;
    
    /* Node Accessors, To be Defined in Derived Classes */
    virtual Comparable* GetNodeKey(NodeType *Node)=0;
    virtual NodeType*   GetLeftChild(NodeType *Node)=0;
    virtual void        SetLeftChild(NodeType *Node,NodeType *Child)=0;
    virtual NodeType*   GetRightChild(NodeType *Node)=0;
    virtual void        SetRightChild(NodeType *Node,NodeType *Child)=0;
    virtual NodeType*   GetParent(NodeType *Node)=0;
    virtual void        SetParent(NodeType *Node,NodeType *Parent)=0;
    
    NodeType *Root;
};

/*
    Binary Search Tree
    Node has a Comparable Object and 3 Pointers(Parent, Left Child, Right Child)
 */

template<class Comparable>
class Tree: public ABCtree<Comparable, TreeNode<Comparable>>{
public:
    
    Tree(){this->Root=NULL;}
    ~Tree(){this->Reset();}
    
protected:
    
/*             Avoid next 3 functions! They are only effectively used in RBT       */
/**/void                    InsertFix(TreeNode<Comparable> *toInserted,
/**/                                  bool isInsertedLeftChild){};
/**/                                                                             
/**/void                    DeleteFix(TreeNode<Comparable> *Replacement,
/**/                                  bool isReplacementLeftChild){};
/**/
/**/TreeNode<Comparable>*   Sentinel(TreeNode<Comparable>* Parent){return NULL;}
/*                                                                                 */
    
    void                    Swap(TreeNode<Comparable> *Node1,
                                 TreeNode<Comparable> *Node2);
    
    Comparable*             GetNodeKey(TreeNode<Comparable> *Node);
    
    TreeNode<Comparable>*   GetLeftChild(TreeNode<Comparable> *Node);
    
    void                    SetLeftChild(TreeNode<Comparable> *Node,
                                         TreeNode<Comparable> *Child);
    
    TreeNode<Comparable>*   GetRightChild(TreeNode<Comparable> *Node);
    
    void                    SetRightChild(TreeNode<Comparable> *Node,
                                          TreeNode<Comparable> *Child);
    
    TreeNode<Comparable>*   GetParent(TreeNode<Comparable> *Node);
    
    void                    SetParent(TreeNode<Comparable> *Node,
                                      TreeNode<Comparable> *Parent);
};

/*
    Binary Search Tree Map(Dictionary)
    Associates Keys with Data.
 */

template<class Comparable,class T>
class TreeMap: public ABCtree<Comparable, TreeMapNode<Comparable, T>>{
public:
    
    TreeMap(){this->Root=NULL;}
    ~TreeMap(){this->Reset();}
    
    /* Input Key with Linked Data */
    void                        Insert(Comparable *Key, T *Data);
    
    /* Maps to the Linked Data of Selected Key */
    T*                          Extract(Comparable *Key);
    
    /* Overrides Selected Key's Data with new Data */
    void                        Edit(Comparable *Key, T *Data);
    
protected:
    
/*          Avoid next 3 functions! They are only effectively used in RBT        */
/**/void                        InsertFix(TreeMapNode<Comparable, T> *Inserted,
/**/                                      bool isInsertedLeftChild){};
/**/
/**/void                        DeleteFix(TreeMapNode<Comparable, T> *Replacement,
/**/                                    bool isReplacementLeftChild){};
/**/
/**/TreeMapNode<Comparable, T>* Sentinel(TreeMapNode<Comparable, T> *Parent){
/**/                                                               return NULL;}
/*                                                                               */
    
    void                        Swap(TreeMapNode<Comparable, T> *Node1,
                                     TreeMapNode<Comparable, T> *Node2);
    
    Comparable*                 GetNodeKey(TreeMapNode<Comparable, T> *Node);
    
    TreeMapNode<Comparable, T>* GetLeftChild(TreeMapNode<Comparable, T> *Node);
    
    void                        SetLeftChild(TreeMapNode<Comparable, T> *Node,
                                             TreeMapNode<Comparable, T> *Child);
    
    TreeMapNode<Comparable, T>* GetRightChild(TreeMapNode<Comparable, T> *Node);
    
    void                        SetRightChild(TreeMapNode<Comparable,T> *Node,
                                              TreeMapNode<Comparable,T> *Child);
    
    TreeMapNode<Comparable, T>* GetParent(TreeMapNode<Comparable, T> *Node);
    
    void                        SetParent(TreeMapNode<Comparable, T> *Node,
                                          TreeMapNode<Comparable, T> *Parent);
};

/*
    Red Black Tree
 
    Guarantees that Tree is Balanced at all times.
 */

template<class Comparable>
class RBTree: public ABCtree<Comparable, RBTNode<Comparable>>{
public:
    RBTree(){this->Root=NULL;}
    ~RBTree(){this->Reset();}
    
protected:
    
    void                    InsertFix(RBTNode<Comparable> *Inserted,
                                      bool isInsertedLeftChild);
    
    void                    DeleteFix(RBTNode<Comparable> *Replacement,
                                      bool isReplacementLeftChild);
    
    void                    PrintGraph(RBTNode<Comparable> *Root);
    
    void                    Swap(RBTNode<Comparable> *Node1,
                                 RBTNode<Comparable> *Node2);
    
    Comparable*             GetNodeKey(RBTNode<Comparable> *Node);
    
    RBTNode<Comparable>*    GetLeftChild(RBTNode<Comparable> *Node);
    
    void                    SetLeftChild(RBTNode<Comparable> *Node,
                                         RBTNode<Comparable> *Child);
    
    RBTNode<Comparable>*    GetRightChild(RBTNode<Comparable> *Node);
    
    void                    SetRightChild(RBTNode<Comparable> *Node,
                                          RBTNode<Comparable> *Child);
    
    RBTNode<Comparable>*    GetParent(RBTNode<Comparable> *Node);
    
    void                    SetParent(RBTNode<Comparable> *Node,
                                      RBTNode<Comparable> *Parent);
    
    /* Node Rotations */
    void                    LeftRotate(RBTNode<Comparable> *Node);
    
    void                    RightRotate(RBTNode<Comparable> *Node);
    
    /* Insertion Cases */
    void                    InsertCase1(RBTNode<Comparable>     *Node,
                                        RBTNode<Comparable>     *Uncle);
    
    void                    InsertCase2(RBTNode<Comparable>     *Node,
                                        RBTNode<Comparable>     *Uncle);
    
    void                    InsertCase3(RBTNode<Comparable>     *Node,
                                        RBTNode<Comparable>     *Uncle);
    
    /* Insertion Mirror Cases */
    void                    InsertCase2m(RBTNode<Comparable>    *Node,
                                         RBTNode<Comparable>     *Uncle);
    
    void                    InsertCase3m(RBTNode<Comparable>    *Node,
                                         RBTNode<Comparable>     *Uncle);
    
    /* Deletion Cases */
    void                    DeleteCase1(RBTNode<Comparable>     *Node);
    
    void                    DeleteCase2(RBTNode<Comparable>     *Node);
    
    void                    DeleteCase3(RBTNode<Comparable>     *Node);
    
    void                    DeleteCase4(RBTNode<Comparable>     *Node);
    
    /* Deletion Mirror Cases */
    void                    DeleteCase1m(RBTNode<Comparable>    *Node);
    
    void                    DeleteCase2m(RBTNode<Comparable>    *Node);
    
    void                    DeleteCase3m(RBTNode<Comparable>    *Node);
    
    void                    DeleteCase4m(RBTNode<Comparable>    *Node);
    
};

/*
    Red Black Tree Dictionary
 
    Guarantees that Tree is Balanced at all times.
 //TODO: Add Edit method
 */

template<class Comparable, class T>
class RBTreeMap: public ABCtree<Comparable, RBTMapNode<Comparable, T>>{
public:
    RBTreeMap(){this->Root=NULL;}
    ~RBTreeMap(){this->Reset();}
    
    /* Input Key with Linked Data */
    void                        Insert(Comparable *Key, T *Data);
    
    /* Maps to the Linked Data of Selected Key */
    T*                          Extract(Comparable *Key);
    
    /* Overrides Selected Key's Data with new Data */
    void                        Edit(Comparable *Key, T *Data);
    
protected:
    
    void                    InsertFix(RBTMapNode<Comparable, T> *toInserted, bool isInsertedLeftChild);
    
    void                    DeleteFix(RBTMapNode<Comparable, T> *Replacement, bool isReplacementLeftChild);
    
    void                    PrintGraph(RBTMapNode<Comparable, T> *Root);
    
    void                    Swap(RBTMapNode<Comparable, T> *Node1,
                                 RBTMapNode<Comparable, T> *Node2);
    
    Comparable*             GetNodeKey(RBTMapNode<Comparable, T> *Node);
    
    RBTMapNode<Comparable, T>*   GetLeftChild(RBTMapNode<Comparable, T> *Node);
    
    void                    SetLeftChild(RBTMapNode<Comparable, T> *Node,
                                         RBTMapNode<Comparable, T> *Child);
    
    RBTMapNode<Comparable, T>*   GetRightChild(RBTMapNode<Comparable, T> *Node);
    
    void                    SetRightChild(RBTMapNode<Comparable, T> *Node,
                                          RBTMapNode<Comparable, T> *Child);
    
    RBTMapNode<Comparable, T>*   GetParent(RBTMapNode<Comparable, T> *Node);
    
    void                    SetParent(RBTMapNode<Comparable, T> *Node,
                                      RBTMapNode<Comparable, T> *Parent);
    
    /* Node Rotations */
    void                    LeftRotate(RBTMapNode<Comparable, T> *Node);
    
    void                    RightRotate(RBTMapNode<Comparable, T> *Node);
    
    /* Insertion Cases */
    void                    InsertCase1(RBTMapNode<Comparable, T>     *Node,
                                        RBTMapNode<Comparable, T>     *Uncle);
    
    void                    InsertCase2(RBTMapNode<Comparable, T>     *Node,
                                        RBTMapNode<Comparable, T>     *Uncle);
    
    void                    InsertCase3(RBTMapNode<Comparable, T>     *Node,
                                        RBTMapNode<Comparable, T>     *Uncle);
    
    /* Insertion Mirror Cases */
    void                    InsertCase2m(RBTMapNode<Comparable, T>    *Node,
                                         RBTMapNode<Comparable, T>     *Uncle);
    
    void                    InsertCase3m(RBTMapNode<Comparable, T>    *Node,
                                         RBTMapNode<Comparable, T>     *Uncle);
    
    /* Deletion Cases */
    void                    DeleteCase1(RBTMapNode<Comparable, T>     *Node);
    
    void                    DeleteCase2(RBTMapNode<Comparable, T>     *Node);
    
    void                    DeleteCase3(RBTMapNode<Comparable, T>     *Node);
    
    void                    DeleteCase4(RBTMapNode<Comparable, T>     *Node);
    
    /* Deletion Mirror Cases */
    void                    DeleteCase1m(RBTMapNode<Comparable, T>    *Node);
    
    void                    DeleteCase2m(RBTMapNode<Comparable, T>    *Node);
    
    void                    DeleteCase3m(RBTMapNode<Comparable, T>    *Node);
    
    void                    DeleteCase4m(RBTMapNode<Comparable, T>    *Node);
};

#include "adt.cpp"
#endif /* ADT_H */
