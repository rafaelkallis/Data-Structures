# Data Structure Library for C++

These Structures have various algorithmic and database related appliances.

##### Structures Included:

* [Stack](https://github.com/rafaelkallis/Data-Structures/blob/master/README.md#stack)
* [Queue](https://github.com/rafaelkallis/Data-Structures/blob/master/README.md#queue)
* [Heap (Min & Max)](https://github.com/rafaelkallis/Data-Structures/blob/master/README.md#heap)
* [PriorityQueue (Min & Max)](https://github.com/rafaelkallis/Data-Structures/blob/master/README.md#priorityqueue)
* Tree (Binary Search Tree)
* TreeMap (BST Dictionary)
* [ArrayList, ArrayList-Ext](https://github.com/rafaelkallis/Data-Structures/blob/master/README.md#arraylist) (Similar to Java's ArrayList, uses amortized dynamic memory allocation based on size)
* Nodes and Containers used in different data structures

##### Work In Progress: Red Black Trees, Hash Tables / Functions.

***

## Stack

A `Stack` is a basic LIFO based data structured, useful in many appliances such as Topological Sort, Undo/Redo operations, Virtual machines (e.g JVM).

`Stack` is found in `adt.h` and respective member functions in `adt.cpp`

###### Constructor:

```C++
Stack<Type> *myStack=new Stack<Type>();
```

###### Member Functions:

```C++
Stack<Type>{
    Type*   Top();
    void    Pop();
    void    Push(Type *Data);
    int     Size();
}
```

***

```C++
myStack->Push(new int(3));
```
* Inserts Data into the Stack.

```C++
int *Temp=Stack->Top()
```
* Returns the Last Inserted Data without removing it from the Stack.

```C++
myStack->Pop();
```
* Removes the Last Inserted Data from the Stack.

```C++
int Temp=myStack->Size();
```
* Returns the total number of elements inside the Stack.

## Queue
 
A `Queue` is a basic FIFO based data structured, useful in many appliances such as Web Server response management, or a Process Queue for the CPU.

`Queue` is found in `adt.h` and member functions in `adr.cpp`

###### Constructor:

```C++
Queue<Type> *myQueue=new Queue<Type>();
```

###### Member Functions:

```C++
Queue<Type>{
    Type*   Top();
    void    Pop();
    void    Push(Type *Data);
    int     Size();
}
```

***

```C++
myQueue->Push(new int(3))
```
* Inserts Data into the Queue.

```C++
int *Temp=myQueue->Top();
```
* Returns the First Inserted Data without removing it from the Stack.

```C++
myQueue->Pop();
```
* Removes the First Inserted Data from the Stack.

```C++
int Temp=myQueue->Size()
```
* Returns the total number of elements inside the Stack.

## ArrayList

The `ArrayList` is a dynamic memory (de)allocating Array based structure, useful in many appliances such as Heaps and any other Database which needs Constant Insertion and Retrieval Complexity. 

`ArrayList` is found in `arrays.h` and member functions in `arrays.cpp`

The Array Expands when it's filled up. It grows by a 1.5 factor, which close to the Golden Ration (φ = 1.61803398.. ) as it's proven to be very efficient and the Java API ArrayList also uses the same factor.

`ArrayList_Ext` is a derived `ArrayList` class which provides extended functions. Collapses when its used capacity is 45% of the available capacity. I have chosen this factor as after private research I concluded it's efficient enough. (Minimises repeatedly shrinking and growing of array so it keeps the amortised costs as low as possible).

For more info, there is a [Wikipedia Article](https://en.wikipedia.org/wiki/Dynamic_array).

###### Constructor:
```C++
ArrayList<Type> *myArrayList=new ArrayList<Type>();
ArrayList_Ext<Type> *myArrayList=new ArrayList_Ext<Type>();
```
###### Member Functions:
```C++
ArrayList<Type>{
    void    Insert(Type *Data);
    Type*   Get(int index);
    void    Set(int index,Type *Data);
    void    Reset();
    int     Size();
    /* Member Functions below are only in ArrayList_Ext<Type> */
    void    RemoveLast();
    int     Find(Type *Data);
    void    ShrinkToFit();
}
```

***

```C++
myArrayList->Insert(new int(3));
```
* Inserts Data into the ArrayList.

```C++
int *Temp=myArrayList->Get(1);
```
* Returns the Data inside position of index. If index is not valid it throws an OutofBoundsException.

```C++
myArrayList->Set(1,new int(2));
```
* Changes the Data of position index with the new Data provided.

```C++
myArrayList->Reset();
```
* Deletes All Data inside the ArrayList and Initialises it in its original capacity (2).

```C++
int Temp=myStack->Size();
```
* Returns the total number of occupied positions inside the ArrayList.

##### Only in `ArrayList_Ext`

```C++
myArrayList_Ext->RemoveLast();
```
* Deletes the last occupied position's Data. Useful for Heaps and Priority Queues.

```C++
int Temp=myArrayList_Ext->Find(new char'R');
```
* Performs Linear Search and returns index of Object's position.

```C++
myArrayList_Ext->ShrinkToFit();
```
* Shrinks Array to last occupied space.

## Heap

A Heap is an essential Data Structure, used to guarantee O(log n) Retrieval and Insertion Time Complexity of the Biggest/Smallest Element in the Structure. Very usable for various Sorting Algorithms which rely on Operation with biggest/smallest element (Selection Sort).

`Minheap` and `MaxHeap` can be found in `adt.h` and their member functions in `adt.cpp`

###### Constructor:
```C++
MinHeap<Type> *myMinHeap=new MinHeap<Type>();
MaxHeap<Type> *myMaxHeap=new MaxHeap<Type>();
```
###### Member Fucntions:
```C++
MinHeap<Comparable>{
    void        Insert(Comparable *Data);
    Comparable* Extract();
    Comparable* Peek();
}
```

***

```C++
myMinHeap->Insert(new int(3));
```
* Inserts Data into the MinHeap.

```C++
Comparable *Temp=myMinHeap->Extract();
```
* Returns the lowest/biggest Data and Removes it from Heap.

```C++
Comparable *Temp=myMinHeap->Peek();
```
* Returns the lowest/highest Data without removing it from Heap.

## PriorityQueue

A Priority Queue is quite as essential as the Heap, and performs almost likewise. It has equal properties to a Heap, yet its applications differ. The main difference is that a Priority Queue acts like a Map. While inserting Data, you also assign a priority value to the Data. The Data with smallest/biggest priority gets Extracted first.

Famous applications for Priority Queues include Dijkstras Shortest Path Algorithm, Prim-Jarnik Minimum Spanning Tree Algorithm etc.

`MinPriorityQueue` and `MaxPriorityQueue` are included in `adt.h` and their respective member functions in `adt.cpp`

###### Constructor:
```C++
MinPriorityQueue<Comparable,Type> *myMinPQ=new MinPriorityQueue<Comparable,Type>();
MaxPriorityQueue<Comparable,Type> *myMaxPQ=new MaxPriorityQueue<Comparable,Type>();
```

###### Member Functions:
```C++
MinPriorityQueue<Comparable, Type>{
    void    Insert(Comparable* Priority, Type* Data);
    Type*   Extract();
    Type*   Peek();
}
```

***

```C++
myMinPQ->Insert(new int(100),new char('R'));
```
* Inserts 'R' into the PQ with Priority 100.

```C++
char* Temp=myMinPQ->Extract();
```
* Returns the char with lowest/highest priority and removes it from PQ.

```C++
char* Temp=myMinPQ->Peek();
```
* Returns the char with lowest/highest priority without removing it from PQ. 
