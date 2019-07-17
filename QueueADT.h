//
//  QueueADT.h
//  220-19-Nodes
//
//  Created by Toby Dragon on 10/19/15.
//  Copyright (c) 2015 Toby Dragon. All rights reserved.
//
//  Abstract Data Type for a Queue.

#ifndef _20_19_Nodes_QueueADT_h
#define _20_19_Nodes_QueueADT_h

#include "GenericItemType.h"

//exception for when you try to pop an empty stack
class DequeueFromEmptyException : std::exception {};

class QueueADT {
    
public:
    //returns true if stack has no items, false otherwise
    virtual bool isEmpty()=0;
    //adds one item to the top of the stack
    virtual void enqueue(ItemType newItem)=0;
    //removes one item from the top of the stack and returns it
    virtual ItemType dequeue()=0;
    //returns the total number of bytes of memory this object is using
    virtual int calcMemUsage()=0;
    //returns the total amount of time used by this object (number of lines of code executed)
    virtual int getElapsedTime()=0;
    //default destructor, declared virtual to ensure that child destructors are called
    virtual ~QueueADT(){};
    virtual int getNumNodes()=0;
    virtual std::string toString()=0;
};

#endif
