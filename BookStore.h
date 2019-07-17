//
//  BookStore.h
//  Final Project
//
//  Created by Jeff Hejna on 12/7/15.
//  Last updated: 12/11/15
//  Copyright © 2015 Jeff Hejna. All rights reserved.
//
//  This is the interface for the BookStore class.

#ifndef BookStore_h
#define BookStore_h
#include "Inventory.h"

class FileNotFoundException : std::exception {};

class BookStore{
private:
    //pointer to an Inventory object
    Inventory* inventory;
    
public:
    //default constructor
    BookStore();
    
    //constructor when reading in an existing BookstoreInventory file
    BookStore(std::string filename);
    
    //destructor
    ~BookStore();
    
    //The menu that the user interacts with
    void Menu();
    
    //creates an Invoice and writes that to a file
    void returnInvoice(std::string fileName);
    
    //returns true if it can create a purchase order
    bool canPurchaseOrder();
    
    //returns true if there are books that need to be returned
    bool canReturnInvoice();
    
    //reads in a file from a delivery and updates the have values for the books
    void getDelivery(std::string filename);
    
    //prints the entire inventory
    void printInventory();
    
    //takes user input and makes sure it is a valid integer. Returns the integer
    int read_input();
    
};

#endif /* BookStore_h */
