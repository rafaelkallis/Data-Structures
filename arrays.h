/*
    arrays.h
    Created by Rafael Kallis on 24/06/15.
    Copyright (c) 2015 Rafael Kallis. All rights reserved.
*/

#ifndef __ADT__arrays__
#define __ADT__arrays__
#include "exceptions.h"
#include <stdio.h>
#include <stdlib.h>
#define ARRAYLIST_INIT_CAP 2


template <class T> class ArrayList{
public:
    ArrayList(){Init();}
    ~ArrayList(){Clean();}
    void    Insert(T *data);
    void    RemoveLast();
    void    Set(int index,T *data);
    T*      Get(int index);
    void    Reset();
    int     Size();
    
protected:
    int     size,capacity;
    T*      Data;
    
    void    Expand();
    void    Collapse();
    void    Init();
    void    Clean();
};

/*
    ArrayList_Ext
    An ArrayList with Extended functions
 */

/*template <class T> class ArrayList_Ext: public ArrayList<T>{
public:
    void RemoveLast();
    int  Find(T* Data);
    void ShrinkToFit();
protected:
    void Collapse();
    
};*/

#include "arrays.cpp"
#endif /* defined(__ADT__arrays__) */
