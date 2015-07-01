/*
	adt.cpp
    Created by Rafael Kallis
    Copyright (c) 2015 Rafael Kallis. All rights reserved.
*/
#include "adt.h"
#include <iostream>

template<class T> T Stack<T>::Top(){
    if(!Head)throw EmptyADTException();
    return Head->key;
}

template<class T> void Stack<T>::Pop(){
    if(!Head)throw EmptyADTException();
    GenericSingleListNode<T> *toDelete=Head;
    Head=Head->Next,size--;
    delete toDelete;
}

template<class T> void Stack<T>::Push(T key){
    Head=new GenericSingleListNode<T>(key,Head);size++;
}

template<class T>int Stack<T>::Size(){
    return size;
}

template<class T> T Queue<T>::Top(){
    if(!Head)throw EmptyADTException();
    return Head->key;
}

template<class T> void Queue<T>::Pop(){
    if(!Head)throw EmptyADTException();
    GenericSingleListNode<T> *toDelete=Head;
    Head=Head->Next,size--;
    delete toDelete;
}

template<class T> void Queue<T>::Push(T key){
    if(!Head)Head=Tail=new GenericSingleListNode<T>(key,NULL);
    else Tail->Next=new GenericSingleListNode<T>(key,NULL),Tail=Tail->Next;
    size++;
}

template<class T>int Queue<T>::Size(){
    return size;
}

/*
 MinHeap Abstract Class
 T: the Data type. NodeType: Node used for implementation
*/


/*
 ABCHeap<T,NodeType>::Insert() 
 Should be included in all Derived Insert() Functions
*/

template<class Comparable,class NodeType>
void ABCHeap<Comparable,NodeType>::Insert(){
    // ArrayList Insertion functions in Derived classes should be called here
    Perc_Up(this->Data->Size()-1);
}

template<class Comparable,class NodeType>
void ABCHeap<Comparable,NodeType>::Extract(){
    Swap(0,this->Data->Size()-1);
    this->Data->RemoveLast();
    Perc_Down(0);
}

template<class Comparable,class NodeType>
void ABCHeap<Comparable,NodeType>::Swap(int i, int j){
    NodeType *temp=new NodeType(*this->Data->Get(i));
    this->Data->Set(i,this->Data->Get(j));
    this->Data->Set(j,temp);
}

template<class Comparable,class NodeType>
void ABCHeap<Comparable,NodeType>::Perc_Up(int index){
    if(index > 0 && *GetNodeKey(index) < *GetNodeKey(Parent(index)))
       Swap(index,Parent(index)),Perc_Up(Parent(index));
}

template<class Comparable,class NodeType>
void ABCHeap<Comparable,NodeType>::Perc_Down(int index){
    int m=index,l=this->Left(index),r=this->Right(index);
    if (l < this->Data->Size() && *GetNodeKey(l) < *GetNodeKey(m)) m=l;
    if (r < this->Data->Size() && *GetNodeKey(r) < *GetNodeKey(m)) m=r;
    if(index!=m) Swap(index,m),Perc_Down(m);
}

/*
 SimpleHeap
 */

template<class Comparable>void SimpleHeap<Comparable>::Insert(Comparable *Data){
    this->Data->Insert(new GenericNode<Comparable>(Data));
    ABCHeap<Comparable, GenericNode<Comparable>>::Insert();
}

template<class Comparable> Comparable* SimpleHeap<Comparable>::Extract(){
    Comparable* temp= new Comparable(*this->Data->Get(0)->key);
    ABCHeap<Comparable, GenericNode<Comparable>>::Extract();
    return temp;
}

/*
 PriorityQueue
 */

template<class T> void PriorityQueue<T>::Insert(int* priority, T* Data){
    this->Data->Insert(new DoubleGenericNode<int, T>(priority,Data));
    ABCHeap<int, DoubleGenericNode<int,T>>::Insert();
}

template<class T> T* PriorityQueue<T>::Extract(){
    T* temp=new T(*this->Data->Get(0)->key2);
    ABCHeap<int, DoubleGenericNode<int,T>>::Extract();
    return temp;
}

/*
    Binary Search Tree Abstract Class
 */

template<class Comparable,class NodeType>
void ABCtree<Comparable,NodeType>::Insert(NodeType *NewNode){
    if(!this->Root)this->Root=NewNode;
    else{
        NodeType *Temp,*Follow;Temp=Follow=this->Root;
        while(Temp){
            Follow=Temp;
            if(*GetNodeKey(NewNode) < *GetNodeKey(Temp))Temp=GetLeftChild(Temp);
            else Temp=GetRightChild(Temp);
        }
        if(*GetNodeKey(NewNode) < *GetNodeKey(Follow))
            SetLeftChild(Follow,NewNode);
        else SetRightChild(Follow,NewNode);
        SetParent(NewNode, Follow);
    }
    
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

template<class Comparable> void Tree<Comparable>::Insert(Comparable *Key){
    ABCtree<Comparable, TreeNodeWParent<Comparable>>::
    Insert(new TreeNodeWParent<Comparable>(Key,NULL,NULL,NULL));
}

template<class Comparable> void Tree<Comparable>::
Swap(TreeNodeWParent<Comparable> *Node1,TreeNodeWParent<Comparable> *Node2){
    if(!Node1 || !Node2) throw UncaughtException();
    Comparable *Temp=Node1->Key;
    Node1->Key=Node2->Key;
    Node2->Key=Temp;
}
template<class Comparable> Comparable* Tree<Comparable>::
GetNodeKey(TreeNodeWParent<Comparable> *Node){
    if(!Node)throw UncaughtException();
    return Node->Key;
}

template<class Comparable> TreeNodeWParent<Comparable>* Tree<Comparable>::
GetLeftChild(TreeNodeWParent<Comparable> *Node){
    if(!Node)throw UncaughtException();
    return Node->Left;
}

template<class Comparable> void Tree<Comparable>::
SetLeftChild(TreeNodeWParent<Comparable>*Node,TreeNodeWParent<Comparable>*Child){
    if(!Node)throw UncaughtException();
    Node->Left=Child;
}

template<class Comparable> TreeNodeWParent<Comparable>* Tree<Comparable>::
GetRightChild(TreeNodeWParent<Comparable> *Node){
    if(!Node)throw UncaughtException();
    return Node->Right;
}

template<class Comparable> void Tree<Comparable>::
SetRightChild(TreeNodeWParent<Comparable>*Node,TreeNodeWParent<Comparable>*Child){
    if(!Node)throw UncaughtException();
    Node->Right=Child;
}

template<class Comparable> TreeNodeWParent<Comparable>* Tree<Comparable>::
GetParent(TreeNodeWParent<Comparable> *Node){
    if(!Node)throw UncaughtException();
    return Node->Parent;
}

template<class Comparable> void Tree<Comparable>::
SetParent(TreeNodeWParent<Comparable> *Node,TreeNodeWParent<Comparable> *Parent){
    if(!Node)throw UncaughtException();
    Node->Parent=Parent;
}