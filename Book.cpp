//
//  Book.cpp
//  Final Project
//
//  Created by Emily Conklin on 11/15/15.
//  Last updated: 12/11/15
//  Copyright © 2015 Emily Conklin. All rights reserved.
//
//  This is the .cpp file which implements the Book.h file and creates a Book object.

#include "Book.hpp"
#include <string>
#include <fstream>
#include <sstream>

Book::Book(std::string titleIn, int wantIn){
    title = titleIn;
    have = 0;
    want = wantIn;
    //using QueueWithNodes for the waitlist
    waitList = new QueueWithNodes;
    waitListLen = 0;
}

void Book::setTitle(std::string titleIn){
    title = titleIn;
}

std::string Book::getTitle(){
    return title;
}

void Book::setHave(int haveIn){
    have = haveIn;
}

int Book::getHave(){
    return have;
}

void Book::increaseHave(int incIn){
    have+=incIn;
}

void Book::decreaseHaveByOne(){
    have--;
}

void Book::setWant(int wantIn){
    want = wantIn;
}

int Book::getWant(){
    return want;
}

void Book::addToWaitlist(std::string nameIn){
    waitList->enqueue(nameIn);
    waitListLen++;
}

std::string Book::deleteFromWaitList(){
    std:: string person = waitList->dequeue();
    waitListLen--;
    return person;
}

int Book::getWaitListLength(){
    return waitList->getNumNodes();
}

std::string Book::getWaitList(){
    return waitList->toString();
}

std::string Book::toString(){
    //convert have to string
    std::string result;
    std::ostringstream convert;
    convert << have;
    result = convert.str();
    
    //convert want to string
    std::string result2;
    std::ostringstream convert2;
    convert2 << want;
    result2 = convert2.str();
    
    
    std::string out;
    out+="Title: " + title + "\n" + "Copies in inventory: " + result;
    out+="\nCopies desired: " + result2;
    out+="\nWaitlist: "+waitList->toString() +"\n";
    return out;
}

Book::~Book(){
    delete waitList;
    waitList = nullptr;
}