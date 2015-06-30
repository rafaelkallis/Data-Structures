/*
    arrays.cpp
    Created by Rafael Kallis on 24/06/15.
    Copyright (c) 2015 Rafael Kallis. All rights reserved.
 */

#include "arrays.h"

/*
 ArrayList<T>
 */

template <class T> void ArrayList<T>::Insert(T *Data){
    if(this->size==this->capacity)Expand();
    this->Data[size++]=*Data;
}

template <class T> void ArrayList<T>::RemoveLast(){
    size--;
    if(this->size < this->capacity*0.45)Collapse();
}

template <class T> void ArrayList<T>::Set(int index, T *Data){
    if(index>=this->size) throw OutofBoundsException();
    else this->Data[index]=*Data;
}

template <class T> T* ArrayList<T>::Get(int index){
    if(index<0 || index>=this->size) throw OutofBoundsException();
    else return this->Data+index;
}

template<class T> void ArrayList<T>::Reset(){
    Clean();
    Init();
}

template<class T> int ArrayList<T>::Size(){
    return this->size;
}

template <class T> void ArrayList<T>::Expand(){
    T *temp=this->Data;
    temp=(T*)realloc(temp,sizeof(T)*this->capacity*1.5);
    if(!temp)throw ReallocException();
    this->Data=temp,capacity*=1.5;
}

template <class T> void ArrayList<T>::Collapse(){
    T *temp=this->Data;
    temp=(T*)realloc(temp,sizeof(T)*this->capacity/1.5);
    if(!temp)throw ReallocException();
    this->Data=temp,capacity/=1.5;
}

template <class T> void ArrayList<T>::Init(){
    size=0,capacity=ARRAYLIST_INIT_CAP;
    this->Data=(T*)malloc(sizeof(T)*ARRAYLIST_INIT_CAP);
}

template <class T> void ArrayList<T>::Clean(){
    while(--size>0)delete (this->Data+size);
    free(this->Data);
}