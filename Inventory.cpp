//
//  Inventory.cpp
//  Final Project
//
//  Created by Joe Menduni on 11/19/15.
//  Last updated: 12/11/15
//  Copyright (c) 2015 JoeMenduni. All rights reserved.
//
//  This is the implementation of the Inventory class. It is an array of pointers to Book objects.


#include "Inventory.h"
#include "Book.hpp"
#include <stdio.h>
#include <ctype.h>
#include <fstream>

// constructor
Inventory::Inventory() {
    //max number of titles allowed in the array
    maxTitles = 100;
    
    //an array of pointers to books
    inventoryArray = new Book*[maxTitles];
    
    //keeps track of the number of titles
    numTitles = 0;
    
}

Inventory::~Inventory() {
    for (int i=0;i<numTitles;i++){
        delete inventoryArray[i];
        inventoryArray[i] = nullptr;
    }
}

// get inventory size
int Inventory::getSize() {
    return numTitles;
}

// get book at index of array
Book* Inventory::getBook(int index) {
    return inventoryArray[index];
}

//sorts the array
void Inventory::sortArray() {
    for (int i = 0; i < numTitles; i++) {
        for (int k = 0; k < numTitles; k++) {
            const char *bookI = inventoryArray[i]->getTitle().c_str();
            const char *bookK = inventoryArray[k]->getTitle().c_str();
            if (std::strcmp(bookI, bookK) < 0) {
                Book* tmp = inventoryArray[i];
                inventoryArray[i] = inventoryArray[k];
                inventoryArray[k] = tmp;
            }
        }
    }
}

// adds book, keeping array sorted
void Inventory::addBook(Book* bookIn) {
    if (numTitles >= maxTitles) {                                         // if there is no more room in the array
        Book** inventoryArray2 = new Book*[maxTitles*2];                  // makes a new array of twice the length
        maxTitles = maxTitles*2;                                          // also doubles max titles
        for (int i = 0; i < numTitles; i ++) {
            inventoryArray2[i] = inventoryArray[i];                  // copies entries from old array into new array
        }
        delete inventoryArray;                                            // deletes old array
        inventoryArray = inventoryArray2;                                 // sets pointer to new array
        inventoryArray2 = nullptr;
    }
    inventoryArray[numTitles] = bookIn;                                   // adds to the book to the arrray
    numTitles++;                                                          // increases the amount of titles
    sortArray();                                                          // sorts the array
}

// searches for a specified title
Book* Inventory::search(std::string titleIn) {
    int first = 0;
    int last = numTitles - 1;
    int middle;
    int position = -1;
    bool found = false;     // this will say if the book has been found
    
    while (!found && first <= last) {                                           // while the book hasn't been found and the first and the last aren't equal
        middle = (first + last) / 2;                                            // sets the middle
        std::string theMid = inventoryArray[middle]->getTitle();                // the title string of the middle
        if (theMid == titleIn) {                                                // if the middle IS the book
            found = true;                                                       // it has been found
            position = middle;                                                  // sets the position to the current index in the array
        }
        else if (theMid > titleIn) {                                            // if the book is before the middle
            last = middle - 1;                                                  // last is now before the middle
        }
        else {                                                                  // if the book is after the middle
            first = middle + 1;                                                 // first is now after the middle
        }
    }
    if (position >= 0 && found==true) {                                         // if the book was found
        return inventoryArray[position];                                        // returns a pointer to the book at that index
    }
    else {                                                                      // if the book wasn't found
        return nullptr;                                                         // returns null pointer
    }
}

// searches for a specified title, returns boolean
bool Inventory::boolSearch(std::string titleIn) {
    int first = 0;
    int last = numTitles - 1;
    int middle;
    int position = -1;
    bool found = false;                   // this will say if the book has been found
    
    while (!found && first <= last) { // while the book hasn't been found and the first and the last aren't equal
        middle = (first + last) / 2;                                            // sets the middle
        std::string theMid = inventoryArray[middle]->getTitle();                // the title string of the middle
        if (theMid == titleIn) {                                                // if the middle IS the book
            found = true;                                                       // it has been found
            position = middle;                                                  // sets the position to the current index in the array
        }
        else if (theMid > titleIn) {                                            // if the book is before the middle
            last = middle - 1;                                                  // last is now before the middle
        }
        else {                                                                  // if the book is after the middle
            first = middle + 1;                                                 // first is now after the middle
        }
    }
    if (position >= 0 && found==true) {                                         // if the book was found
        return true;
    }
    else {                                                                      // if the book wasn't found
        return false;
    }
}


// saves inventory into file
void Inventory::saveInv(){
    std::ofstream outf("BookstoreInventory.txt");
    for (int i = 0; i < numTitles; i++){
        outf << inventoryArray[i]->getTitle() + ":";
        outf << inventoryArray[i]->getHave();
        outf << ":";
        outf << inventoryArray[i]->getWant();
        outf << ":" + inventoryArray[i]->getWaitList() +"\n";
    }
    outf.close();
}

// to string
std::string Inventory::toString() {
    std::string returnString = "";
    for (int i = 0; i < numTitles; i ++) {
        returnString += inventoryArray[i]->toString() + "\n\n";
    }
    return returnString;
}