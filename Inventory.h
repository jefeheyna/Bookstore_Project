//
//  Inventory.h
//  Final Project
//
//  Created by Joe Menduni on 11/19/15.
//  Last updated: 12/11/15
//  Copyright (c) 2015 JoeMenduni. All rights reserved.
//
//  This is the Inventory class interface.

#ifndef __Bookstore_Project__Inventory__
#define __Bookstore_Project__Inventory__

#include <stdio.h>
#include "Book.hpp"

class Inventory{
    
private:
    //an array of pointers to Book objects
    Book** inventoryArray;
    
    //number of titles in the array
    int numTitles;
    
    //max number of titles allowed
    int maxTitles;
    
public:
    
    //default constructor
    Inventory();
    
    //constructor for when reading in an inventory text file
    Inventory(int numTitlesIn);
    
    // destructor
    ~Inventory();
    
    //returns size of inventory array
    int getSize();
    
    //returns a book at a specfic index
    Book* getBook(int index);
    
    // search inventory and returns book
    Book* search(std::string titleIn);
    
    //searchs for a book and returns true if it is in the inventory.
    bool boolSearch(std::string titleIn);
    
    // adds book, keeping array sorted
    void addBook(Book* bookIn);
    
    // sorts array
    void sortArray();
    
    // to string
    std::string toString();
    
    // saves inventory to file
    void saveInv();
    
};
#endif /* defined(__Bookstore_Project__Inventory__) */
