/*
	adt.cpp
    Created by Rafael Kallis
    Copyright (c) 2015 Rafael Kallis. All rights reserved.
*/
#include "adt.h"

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
 ABCHeap<T,NodeType>::Insert() Should be included in all Derived Insert() Functions
*/

template<class T,class NodeType> void ABCHeap<T,NodeType>::Insert(){
    // ArrayList Insertion functions in Derived classes should be called here
    Perc_Up(this->Data->Size()-1);
}

template<class T,class NodeType> void ABCHeap<T,NodeType>::Extract(){
    Swap(0,this->Data->Size()-1);
    this->Data->RemoveLast();
    Perc_Down(0);
}

template<class T,class NodeType> void ABCHeap<T,NodeType>::Swap(int i, int j){
    NodeType *temp=new NodeType(*this->Data->Get(i));
    this->Data->Set(i,this->Data->Get(j));
    this->Data->Set(j,temp);
}

template<class T,class NodeType> void ABCHeap<T,NodeType>::Perc_Up(int index){
    if(index > 0 && *GetNodeKey(index) < *GetNodeKey(Parent(index)))
       Swap(index,Parent(index)),Perc_Up(Parent(index));
}

template<class T,class NodeType> void ABCHeap<T,NodeType>::Perc_Down(int index){
    int m=index,l=this->Left(index),r=this->Right(index);
    if (l < this->Data->Size() && *GetNodeKey(l) < *GetNodeKey(m)) m=l;
    if (r < this->Data->Size() && *GetNodeKey(r) < *GetNodeKey(m)) m=r;
    if(index!=m) Swap(index,m),Perc_Down(m);
}

/*
 SimpleHeap
 */

template<class T> void SimpleHeap<T>::Insert(T *Data){
    this->Data->Insert(new GenericNode<T>(Data));
    ABCHeap<T, GenericNode<T>>::Insert();
}

template<class T> T* SimpleHeap<T>::Extract(){
    T* temp= new T(*this->Data->Get(0)->key);
    ABCHeap<T, GenericNode<T>>::Extract();
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