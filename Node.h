//
//  Node.h
//  220-19-Nodes
//
//  Created by Toby Dragon on 10/8/15.
//  Copyright (c) 2015 Toby Dragon. All rights reserved.
//
//  Node interface

#ifndef ___20_19_Nodes__Node__
#define ___20_19_Nodes__Node__

#include "GenericItemType.h"

class Node{
private:
    //item in node
    ItemType item;
    
    //pointer to next node
    Node* next;
    
public:
    //creates a node
    Node(ItemType itemIn);
    
    //gets the data from a node
    ItemType getData();
    
    //returns the next node
    Node* getNext();
    
    //sets the next node
    void setNext(Node* nextIn);
};

#endif /* defined(___20_19_Nodes__Node__) */
