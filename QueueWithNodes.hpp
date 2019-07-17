//
//  QueueWithNodes.hpp
//  Final Project
//
//  Created by Emily Conklin on 11/4/15.
//  Last updated: 12/11/15
//  Copyright © 2015 Emily Conklin. All rights reserved.
//
//  The interface for QueueWithNodes and inherits from QueueADT.

#ifndef QueueWithNodes_hpp
#define QueueWithNodes_hpp

#include <stdio.h>
#include "GenericItemType.h"
#include "QueueADT.h"
#include "Node.h"

class QueueWithNodes : public QueueADT{
    private:
        //the number of nodes
        int numNodes;
    
        //timer
        int timer;
    
        //first node in the queue
        Node* first;
    
        //last node in the queue
        Node* last;
    
    public:
        //Constructor: creates a new, empty Queue
        QueueWithNodes();
        //Copy Constructor: makes a new deep copy of the Queue parameter
        //QueueWithNodes(const QueueWithNodes& queueToCopy);
        //Destructor
        ~QueueWithNodes();
        //returns true if Queue has no items, false otherwise
        bool isEmpty();
        //adds one item to the back of the Queue
        void enqueue(ItemType newItem);
        //removes one item from the front of the Queue and returns it
        ItemType dequeue();
        std::string toString();
        //returns the total number of bytes of memory this object is using
        int calcMemUsage();
        //returns the total amount of time used by this object (number of lines of code executed)
        int getElapsedTime();
        int getNumNodes();
};

#endif /* QueueWithNodes_hpp */
