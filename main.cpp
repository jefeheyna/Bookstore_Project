//
//  main.cpp
//  Final Project
//
//  Created by Emily Conklin, Jeffrey Hejna, and Joe Menduni on 12/11/15.
//  Last updated: 12/11/15
//  Copyright © 2015 Emily Conklin. All rights reserved.
//
//  This is the main file that creates a Bookstore and starts the menu

#include <iostream>
#include "Book.hpp"
#include "Inventory.h"
#include "BookStore.h"

int main(int argc, const char * argv[]) {
    
    
    std::cout<<"Do you have an inventory file that you would like to use? (Y/N): ";
    
    while (true) {
        char choice;
        std::cin>>choice;
        
    
        if (choice=='Y' || choice=='y') {
            std::cout<<""<<std::endl;
            BookStore* bookstore = new BookStore("BookstoreInventory.txt");
            std::cout<<""<<std::endl;
            bookstore->Menu();
            break;
        }
    
        else if(choice=='N' || choice=='n'){
            std::cout<<""<<std::endl;
            BookStore* bookstore = new BookStore;
            bookstore->Menu();
            break;
        }
        else{
            std::cout<<""<<std::endl;
            std::cout<<"Invalid entry. Choose (Y/N)"<<std::endl;
            std::cin.clear();
            
        }

    }

    
}
