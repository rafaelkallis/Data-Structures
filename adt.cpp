/*
	adt.cpp
    Created by Rafael Kallis
    Copyright (c) 2015 Rafael Kallis. All rights reserved.
*/
#include "adt.h"
#include <iostream>

template<class T> T* Stack<T>::Top(){
    if(!Head)throw EmptyADTException();
    return Head->Key;
}

template<class T> void Stack<T>::Pop(){
    if(!Head)throw EmptyADTException();
    SingleListNode<T> *toDelete=Head;
    Head=Head->Next,size--;
    delete toDelete;
}

template<class T> void Stack<T>::Push(T *Key){
    Head=new SingleListNode<T>(Key,Head);size++;
}

template<class T>int Stack<T>::Size(){
    return size;
}

template<class T> T* Queue<T>::Top(){
    if(!Head)throw EmptyADTException();
    return Head->key;
}

template<class T> void Queue<T>::Pop(){
    if(!Head)throw EmptyADTException();
    SingleListNode<T> *toDelete=Head;
    Head=Head->Next;
    size--;
    delete toDelete;
    if(!Head)Tail=NULL;
}

template<class T> void Queue<T>::Push(T *Key){
    if(!Head)Head=Tail=new SingleListNode<T>(Key,NULL);
    else Tail->Next=new SingleListNode<T>(Key,NULL),Tail=Tail->Next;
    size++;
}

template<class T>int Queue<T>::Size(){
    return size;
}

/*
    Heap Abstract Class
    T: the Data type. NodeType: Node used for implementation
*/


/*
    ABCHeap<T,NodeType>::Insert()
    Should be included in all Derived Insert() Functions
*/

template<class Comparable,class NodeType>
void ABCHeap<Comparable,NodeType>::Insert(){
    /* ArrayList Insertion functions in Derived classes should be called here */
    Perc_Up(this->Data->Size()-1);
}

template<class Comparable,class NodeType>
void ABCHeap<Comparable,NodeType>::Extract(){
    Swap(0,this->Data->Size()-1);
    this->Data->RemoveLast();
    Perc_Down(0);
}

template<class Comparable,class NodeType>
bool ABCHeap<Comparable, NodeType>::isSmaller(Comparable i,Comparable j){
    return i < j;
}

template<class Comparable,class NodeType>
void ABCHeap<Comparable,NodeType>::Swap(int i, int j){
    NodeType *temp=new NodeType(*this->Data->Get(i));
    this->Data->Set(i,this->Data->Get(j));
    this->Data->Set(j,temp);
}

template<class Comparable,class NodeType>
void ABCHeap<Comparable,NodeType>::Perc_Up(int index){
    if(index > 0 &&
       isMinHeap == isSmaller(*GetNodeKey(index), *GetNodeKey(Parent(index))))
        Swap(index,Parent(index)),Perc_Up(Parent(index));
}

template<class Comparable,class NodeType>
void ABCHeap<Comparable,NodeType>::Perc_Down(int index){
    int m=index,l=this->Left(index),r=this->Right(index);
    if (l < this->Data->Size() &&
        isMinHeap == isSmaller(*GetNodeKey(l), *GetNodeKey(m))) m=l;
    if (r < this->Data->Size() &&
        isMinHeap == isSmaller(*GetNodeKey(r), *GetNodeKey(m))) m=r;
    if(index!=m) Swap(index,m),Perc_Down(m);
}

/*
    Heap
 */

template<class Comparable>void MinHeap<Comparable>::Insert(Comparable *Data){
    this->Data->Insert(new Node<Comparable>(Data));
    ABCHeap<Comparable, Node<Comparable>>::Insert();
}

template<class Comparable> Comparable* MinHeap<Comparable>::Extract(){
    Comparable* Temp= new Comparable(*this->Data->Get(0)->key);
    ABCHeap<Comparable, Node<Comparable>>::Extract();
    return Temp;
}

template<class Comparable> Comparable* MinHeap<Comparable>::Peek(){
    return this->Data->Get(0)->key;
}

/*
    PriorityQueue
    Comparable is used as Priority
    T is used as Data Type
 */

template<class Comparable,class T>
void MinPriorityQueue<Comparable,T>::Insert(Comparable* priority, T* Data){
    this->Data->Insert(new MapNode<Comparable, T>(priority,Data));
    ABCHeap<Comparable, MapNode<Comparable,T>>::Insert();
}

template<class Comparable,class T> T* MinPriorityQueue<Comparable,T>::Extract(){
    T* Temp=new T(*this->Data->Get(0)->key2);
    ABCHeap<Comparable, MapNode<Comparable,T>>::Extract();
    return Temp;
}

template<class Comparable, class T> T* MinPriorityQueue<Comparable,T>::Peek(){
    return this->Data->Get(0)->key2;
}

/*
    Binary Search Tree Abstract Class
 */

template<class Comparable,class NodeType>
void ABCtree<Comparable,NodeType>::Insert(Comparable *Key){
    Insert(new NodeType(Key));
}

template<class Comparable,class NodeType>
void ABCtree<Comparable,NodeType>::Delete(Comparable *Key){
    /* Defining Temporary Pointers to Reduce Function Calling Overload*/
    NodeType *toDelete=this->Search(Key);
    NodeType *LeftChild=GetLeftChild(toDelete);
    NodeType *RightChild=GetRightChild(toDelete);
    NodeType *Parent=GetParent(toDelete);
    bool isaLeftChild=isLeftChild(toDelete);
    
    /* Doesn't Exist */
    if(!toDelete) return;
    
    /* Node is Root, has no Children */
    else if(!LeftChild && !RightChild && !Parent)
        this->Root=NULL;
    
    /* Node has no Children, is a Left Child */
    else if(!LeftChild && !RightChild && isaLeftChild)
        SetLeftChild(Parent,NULL);
    
    /* Node has no Children, is a Right Child */
    else if(!LeftChild && !RightChild && !isaLeftChild)
        SetRightChild(Parent,NULL);
    
    /* Node has only a Left Child, is a Left Child */
    else if(LeftChild && !RightChild && isaLeftChild){
        SetLeftChild(Parent, LeftChild);
        SetParent(LeftChild,Parent);
        
        /* Node has only a Right Child, is a Left Child */
    }else if(!LeftChild && RightChild && isaLeftChild){
        SetLeftChild(Parent, RightChild);
        SetParent(RightChild, Parent);
        
        /* Node has only a Left Child, is a Right Child */
    }else if(LeftChild && !RightChild && !isaLeftChild){
        SetRightChild(Parent, LeftChild);
        SetParent(LeftChild, Parent);
        
        /* Node has only a Right Child, is a Left Child */
    }else if(!LeftChild && RightChild && !isaLeftChild){
        SetRightChild(Parent, RightChild);
        SetParent(RightChild, Parent);
        
    }else{
        NodeType *Temp=Smallest(RightChild);
        
        this->Swap(toDelete,Temp);
        /* Node has 2 Children, is a Right Child */
        if(Temp==RightChild){
            SetRightChild(toDelete, GetRightChild(Temp));
            if(GetRightChild(Temp))
                SetParent(GetRightChild(Temp),GetParent(Temp));
        }else{
        /* Node has 2 Children, is a Left Child */
            SetLeftChild(GetParent(Temp), GetRightChild(Temp));
            if(GetRightChild(Temp))
                SetParent(GetRightChild(Temp), GetParent(Temp));
        }
        toDelete=Temp;
    }
    delete toDelete;
    toDelete=NULL;
}

template<class Comparable,class NodeType>
void ABCtree<Comparable,NodeType>::Reset(){
    this->Reset(this->Root);
    this->Root=NULL;
}

template<class Comparable,class NodeType>
void ABCtree<Comparable,NodeType>::PrintInOrder(){
    this->PrintInOrder(this->Root);
    printf("\n");
}

template<class Comparable,class NodeType>
void ABCtree<Comparable,NodeType>::PrintGraph(){
    this->PrintGraph(Root);
}

template<class Comparable,class NodeType>
void ABCtree<Comparable,NodeType>::Insert(NodeType *Node){
    if(!this->Root)this->Root=Node;
    else{
        NodeType *Temp,*Follow;Temp=Follow=this->Root;
        while(Temp){
            Follow=Temp;
            if(*GetNodeKey(Node) < *GetNodeKey(Temp))Temp=GetLeftChild(Temp);
            else Temp=GetRightChild(Temp);
        }
        if(*GetNodeKey(Node) < *GetNodeKey(Follow))
            SetLeftChild(Follow,Node);
        else SetRightChild(Follow,Node);
        SetParent(Node, Follow);
    }
}

template<class Comparable,class NodeType>
void ABCtree<Comparable,NodeType>::Reset(NodeType *Root){
    if (Root) {
        Reset(GetLeftChild(Root));
        Reset(GetRightChild(Root));
        delete Root;
    }
}

template<class Comparable,class NodeType>
void ABCtree<Comparable,NodeType>::PrintInOrder(NodeType *Root){
    if (Root) {
        PrintInOrder(GetLeftChild(Root));
        std::cout << *GetNodeKey(Root) << " ";
        PrintInOrder(GetRightChild(Root));
    }
}

template<class Comparable,class NodeType>
void ABCtree<Comparable,NodeType>::PrintGraph(NodeType *Root){
    if(Root){
        if(!GetLeftChild(Root))printf("X");
        else std::cout<<*GetNodeKey(GetLeftChild(Root));
        std::cout<<" <--- "<<*GetNodeKey(Root)<<" ---> ";
        if(!GetRightChild(Root))printf("X");
        else std::cout<<*GetNodeKey(GetRightChild(Root));
        printf("\n\n");
        PrintGraph(GetLeftChild(Root));
        PrintGraph(GetRightChild(Root));
    }
}
template<class Comparable,class NodeType>
NodeType* ABCtree<Comparable,NodeType>::Smallest(NodeType *Root){
    if(GetLeftChild(Root))return Smallest(GetLeftChild(Root));
    else return Root;
}

template<class Comparable,class NodeType>
NodeType* ABCtree<Comparable,NodeType>::Search(Comparable *Key){
    NodeType *Temp=this->Root;
    while(Temp){
        if(*GetNodeKey(Temp)==*Key)break;
        else if(* Key < *GetNodeKey(Temp))Temp=GetLeftChild(Temp);
        else Temp=GetRightChild(Temp);
    }
    return Temp;
}

template<class Comparable,class NodeType>
bool ABCtree<Comparable,NodeType>::isLeftChild(NodeType *Root){
    if(!Root || !GetParent(Root) || !GetLeftChild(GetParent(Root)))return false;
    else if(GetLeftChild(GetParent(Root)) == Root) return true;
    else return false;
}

/*
 Tree
 
 Tree with basic Node structure containing a Comparable Key
 */

template<class Comparable> void Tree<Comparable>::
Swap(TreeNode<Comparable> *Node1,TreeNode<Comparable> *Node2){
    if(!Node1 || !Node2) throw UncaughtException();
    Comparable *Temp=Node1->Key;
    Node1->Key=Node2->Key;
    Node2->Key=Temp;
}
template<class Comparable> Comparable* Tree<Comparable>::
GetNodeKey(TreeNode<Comparable> *Node){
    if(!Node)throw UncaughtException();
    return Node->Key;
}

template<class Comparable> TreeNode<Comparable>* Tree<Comparable>::
GetLeftChild(TreeNode<Comparable> *Node){
    if(!Node)throw UncaughtException();
    return Node->Left;
}

template<class Comparable> void Tree<Comparable>::
SetLeftChild(TreeNode<Comparable>*Node,TreeNode<Comparable>*Child){
    if(!Node)throw UncaughtException();
    Node->Left=Child;
}

template<class Comparable> TreeNode<Comparable>* Tree<Comparable>::
GetRightChild(TreeNode<Comparable> *Node){
    if(!Node)throw UncaughtException();
    return Node->Right;
}

template<class Comparable> void Tree<Comparable>::
SetRightChild(TreeNode<Comparable>*Node,TreeNode<Comparable>*Child){
    if(!Node)throw UncaughtException();
    Node->Right=Child;
}

template<class Comparable> TreeNode<Comparable>* Tree<Comparable>::
GetParent(TreeNode<Comparable> *Node){
    if(!Node)throw UncaughtException();
    return Node->Parent;
}

template<class Comparable> void Tree<Comparable>::
SetParent(TreeNode<Comparable> *Node,TreeNode<Comparable> *Parent){
    if(!Node)throw UncaughtException();
    Node->Parent=Parent;
}

/*
    Binary Search Tree Map(Dictionary)
 */

template<class Comparable,class T>
void TreeMap<Comparable,T>::Insert(Comparable *Key, T *Data){
    ABCtree<Comparable, TreeMapNode<Comparable, T>>::
    Insert(new TreeMapNode<Comparable, T>(Key,Data));
}

template<class Comparable,class T>
T* TreeMap<Comparable, T>::Extract(Comparable *Key){
    TreeMapNode<Comparable, T> *Temp=ABCtree<Comparable, TreeMapNode<Comparable, T>>::Search(Key);
    if(!Temp) return NULL;
    else return Temp->Data;
}

template<class Comparable,class T>
void TreeMap<Comparable, T>::Edit(Comparable *Key, T *Data){
    TreeMapNode<Comparable, T> *Temp=ABCtree<Comparable, TreeMapNode<Comparable, T>>::Search(Key);
    if(!Temp) return;
    else Temp->Data=Data;
}

template<class Comparable,class T>
void TreeMap<Comparable,T>::Swap(TreeMapNode<Comparable, T> *Node1, TreeMapNode<Comparable, T> *Node2){
    Comparable *TempKey=Node1->Key;
    T *TempData=Node2->Data;
    Node1->Key=Node2->Key,Node1->Data=Node2->Data;
    Node2->Key=TempKey,Node2->Data=TempData;
}

template<class Comparable,class T>
Comparable* TreeMap<Comparable,T>::GetNodeKey(TreeMapNode<Comparable, T> *Node){
    if(!Node) throw UncaughtException();
    return Node->Key;
}

template<class Comparable,class T>
TreeMapNode<Comparable, T>* TreeMap<Comparable,T>::GetLeftChild(TreeMapNode<Comparable, T> *Node){
    if(!Node)throw UncaughtException();
    return Node->Left;
}

template<class Comparable,class T>
void TreeMap<Comparable, T>::SetLeftChild(TreeMapNode<Comparable, T> *Node, TreeMapNode<Comparable, T> *Child){
    if(!Node)throw UncaughtException();
    Node->Left=Child;
}

template<class Comparable,class T>
TreeMapNode<Comparable, T>* TreeMap<Comparable, T>::GetRightChild(TreeMapNode<Comparable, T> *Node){
    if(!Node)throw UncaughtException();
    return Node->Right;
}

template<class Comparable,class T>
void TreeMap<Comparable, T>::SetRightChild(TreeMapNode<Comparable, T> *Node, TreeMapNode<Comparable, T> *Child){
    if(!Node)throw UncaughtException();
    Node->Right=Child;
}

template<class Comparable,class T>
TreeMapNode<Comparable, T>* TreeMap<Comparable, T>::GetParent(TreeMapNode<Comparable, T> *Node){
    if(!Node)throw UncaughtException();
    return Node->Parent;
}

template<class Comparable,class T>
void TreeMap<Comparable, T>::SetParent(TreeMapNode<Comparable, T> *Node, TreeMapNode<Comparable, T> *Parent){
    if(!Node)throw UncaughtException();
    Node->Parent=Parent;
}
