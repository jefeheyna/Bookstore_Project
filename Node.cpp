//
//  Node.cpp
//  220-19-Nodes
//
//  Created by Toby Dragon on 10/8/15.
//  Copyright (c) 2015 Toby Dragon. All rights reserved.
//
//  Node implementation

#include "Node.h"

Node::Node(ItemType itemIn){
    item = itemIn;
    next = nullptr;
}

ItemType Node::getData(){
    return item;
}

Node* Node::getNext(){
    return next;
}
void Node::setNext(Node* nextIn){
    next = nextIn;
}