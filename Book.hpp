//
//  Book.hpp
//  Final Project
//
//  Created by Emily Conklin on 11/15/15.
//  Last updated: 12/11/15
//  Copyright © 2015 Emily Conklin. All rights reserved.
//
//  This is the interface for the Book class.

#ifndef Book_hpp
#define Book_hpp

#include <stdio.h>
#include <iostream>
#include "QueueWithNodes.hpp"
#include "QueueADT.h"

class Book{
private:
    //title
    std::string title;
    
    //number of books in stock
    int have;
    
    //number of books wanted in store
    int want;
    
    //waitlist of names if book isn't in stock
    QueueADT* waitList;
    
    //length of waitlist
    int waitListLen;

public:
    //constructor
    Book(std::string titleIn, int wantIn);
    
    //destructor
    ~Book();
    //sets the Title
    void setTitle(std::string titleIn);
    
    //returns title
    std::string getTitle();
    
    //sets the number of books in stock
    void setHave(int haveIn);
    
    //returns number of books in stock
    int getHave();
    
    //increases have value by an amount
    void increaseHave(int incIn);
    
    //decreases have by one
    void decreaseHaveByOne();
    
    //sets the want value to another value
    void setWant(int wantIn);
    
    //returns want value
    int getWant();
    
    //adds a name to the waitlist
    void addToWaitlist(std::string nameIn);
    
    //removes a name from the waitlist
    std::string deleteFromWaitList();
    
    //returns the waitlist
    std::string getWaitList();
    
    //returns waitlist length
    int getWaitListLength();
    
    //toString method
    std::string toString();
    
};
#endif /* Book_hpp */
