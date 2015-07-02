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
    if(size==capacity)Expand();
    this->Data[size++]=*Data;
}

template <class T> void ArrayList<T>::Set(int index, T *Data){
    if(index<0 || index>=this->size) throw OutofBoundsException();
    this->Data[index]=*Data;
}

template <class T> T* ArrayList<T>::Get(int index){
    if(index<0 || index>=this->size) throw OutofBoundsException();
    else return &this->Data[index];
}

template<class T> void ArrayList<T>::Reset(){
    Clean();
    Init();
}

template<class T> int ArrayList<T>::Size(){
    return this->size;
}

template <class T> void ArrayList<T>::Expand(){
    T* Temp=new T[(int)(this->capacity*1.5)]();
    if(!Temp) throw ReallocException();
    capacity*=1.5;
    for (int i=0; i<this->size; i++) Temp[i]=this->Data[i];
    delete [] this->Data;
    this->Data=Temp;
}

template <class T> void ArrayList<T>::Init(){
    size=0,capacity=ARRAYLIST_INIT_CAP;
    this->Data=new T[ARRAYLIST_INIT_CAP]();
}

template <class T> void ArrayList<T>::Clean(){
    delete [] this->Data;
    this->Data=NULL;this->size=this->capacity=0;
}

/*
    ArrayList_Ext
    An ArrayList with Extended functions
 */

template <class T> void ArrayList_Ext<T>::RemoveLast(){
    if(--this->size < this->capacity*0.45)Collapse();
}
 
template<class T> int ArrayList_Ext<T>::Find(T* Data){
    for (int i=0; i<this->size; i++) if(this->Data==this->Get(i))return i;
    throw UncaughtException();
}

template<class T> void ArrayList_Ext<T>::ShrinkToFit(){
    T* Temp=new T[(int)(this->size)]();
    if(!Temp) throw ReallocException();
    this->capacity=this->size;
    for (int i=0; i<this->size; i++) Temp[i]=this->Data[i];
    delete [] this->Data;
    this->Data=Temp;
}
 
template <class T> void ArrayList_Ext<T>::Collapse(){
    T* Temp=new T[(int)(this->capacity/1.5)]();
    if(!Temp) throw ReallocException();
    this->capacity/=1.5;
    for (int i=0; i<this->size; i++) Temp[i]=this->Data[i];
    delete [] this->Data;
    this->Data=Temp;
}
