# Data Structure Library for C++

These Structures have various algorithmic and database related appliances.

Check out the [Wiki page](https://github.com/rafaelkallis/Data-Structures/wiki) for more details.

### Structures Included:

* Stack
* Queue
* Heap
* Priority Queue
* Tree (BST)
* TreeMap (BST Dictionary)
* Dynamic Array (Similar to Java's ArrayList, uses amortized dynamic memory allocation based on size)
* List of Nodes and Containers used in different data structures

***
## Stack

A Stack is a basic LIFO based data structured, useful in many appliances such as Topological Sort, Undo/Redo operations, Virtual machines (e.g JVM).

Stack is found in `adt.h` and respective member functions in `adt.cpp`

###### Constructor:

```C++
Stack<Type> *myStack=new Stack<Type>();
```

###### Public Functions:

```C++
void Push(Type *Data);
```
```C++
myStack->Push(new int(3));
```
Inserts Data into the Stack.
***
```C++
Type* Top();
```
```C++
int *Temp=Stack->Top()
```
Returns the Last Inserted Data without removing it from the Stack.
***
```C++
void Pop();
```
```C++
myStack->Pop();
```
Removes the Last Inserted Data from the Stack.
***
```C++
int Size();
```
```C++
int Temp=myStack->Size();
```
Returns the total number of elements inside the Stack.

## Queue
 
A Queue is a basic FIFO based data structured, useful in many appliances such as Web Server response management, or a Process Queue for the CPU.

The Queue is found in `adt.h` and member functions in `adr.cpp`

###### Constructor:

```C++
Queue<Type> *myQueue=new Queue<Type>();
```

###### Public Functions:

```C++
void Push(Type *Data);
```
```C++
myQueue->Push(new int(3))
```
Inserts Data into the Queue.
***
```C++
Type* Top();
```
```C++
int *Temp=myQueue->Top();
```
Returns the First Inserted Data without removing it from the Stack.
***
```C++
void Pop();
```
```C++
myQueue->Pop();
```
Removes the First Inserted Data from the Stack.
***
```C++
int Size();
```
```C++
int Temp=myQueue->Size()
```
Returns the total number of elements inside the Stack.

