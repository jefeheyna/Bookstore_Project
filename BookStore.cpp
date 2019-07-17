//
//  BookStore.cpp
//  Final Project
//
//  Created by Jeff Hejna on 12/7/15.
//  Last updated: 12/11/15
//  Copyright © 2015 Jeff Hejna. All rights reserved.
//
//  This implements the BookStore.h file and uses an Inventory to store the information provided by the user.

#include "Inventory.h"
#include "Book.hpp"
#include "BookStore.h"
#include <stdio.h>
#include <ctype.h>
#include <fstream>
#include <sstream>
#include <vector>

BookStore::BookStore(){
    inventory = new Inventory;
}

BookStore::~BookStore(){
    //calls inventory destructor to deal with arrays
    delete inventory;
}

// reads file into inventory
BookStore :: BookStore(std::string filename){
    filename ="BookstoreInventory.txt";
    std::ifstream infile(filename);
    std::string title, haveStr, wantStr, wlStr;
    int have, want;
    
    //creates new inventory
    inventory = new Inventory;
    
    if (infile) {
        while (infile) {
            std::string line;
            getline(infile, line);
            
            //splitting up the file
            std::stringstream splitter2 (line);
            getline(splitter2, title, ':');
            getline(splitter2, haveStr, ':');
            getline(splitter2, wantStr, ':');
            getline(splitter2, wlStr, ':');
            
            //convert to int
            std::stringstream(haveStr) >> have;
            std::stringstream(wantStr) >> want;
            
            //create new book
            Book* temp = new Book(title,want);
            temp->setHave(have);
            
            //make waitlist, if it's not empty
            std::string prefix2 = "No wait list";
            if(wlStr.substr(0, prefix2.size()) != prefix2) {
                std::stringstream ss(wlStr);
                std::vector<std::string> result;
                
                while( ss.good() )
                {
                    std::string substr;
                    getline( ss, substr, ',' );
                    result.push_back( substr );
                }
                ss.clear();
                
                for (int i=0;i<result.size();i++){
                    temp->addToWaitlist(result[i]);
                }
            }
            
            //if book is valid, add it to the inventory
            if (temp->getTitle()!=""){
                inventory -> addBook(temp);
            }
        }
    }
    else {
        throw FileNotFoundException();
    }
}

int BookStore::read_input(){
    int input = -1;
    bool valid= false;
    do
    {
        std::cout << "Enter the number of copies you want: " << std::flush;
        std::cin >> input;
        if (std::cin.good())
        {
            //everything went well, we'll get out of the loop and return the value
            valid = true;
        }
        else
        {
            //something went wrong, we reset the buffer's state to good
            std::cin.clear();
            //and empty it
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            std::cout << "Invalid input; please re-enter." << std::endl;
        }
    } while (!valid);
    
    return (input);
}


void BookStore::returnInvoice(std::string fileName){
    fileName = fileName + ".txt";
    std::ofstream outf(fileName);
    outf << "See file "+fileName+".txt for a list of books to return. \n";
    for (int i = 0; i < inventory->getSize(); i++) {
        if (inventory->getBook(i)->getHave() > inventory->getBook(i)->getWant()) {
            outf << inventory->getBook(i)->getTitle() + ":";
            outf << inventory->getBook(i)->getHave();
            outf << ":";
            outf << inventory->getBook(i)->getWant();
            outf << "\n";
            inventory->getBook(i)->setHave(inventory->getBook(i)->getWant());
        }
    }
}

bool BookStore::canPurchaseOrder() {
    for (int i = 0; i < inventory->getSize(); i++) {
        if (inventory->getBook(i)->getHave() < inventory->getBook(i)->getWant()) {
            return true;
        }
    }
    return false;
}

bool BookStore::canReturnInvoice() {
    for (int i = 0; i < inventory->getSize(); i++) {
        if (inventory->getBook(i)->getHave() > inventory->getBook(i)->getWant()) {
            return true;
        }
    }
    return false;
}

void BookStore::printInventory(){
    std::cout << inventory->toString() << std::endl;
}


void BookStore::getDelivery(std::string fileName){
    //opens file
    std::ifstream infile(fileName);
    
    if (infile) {
        while (infile) {
            //split lines
            std::string line;
            getline(infile, line);
            std::stringstream splitter (line);
            std::string title, newHave;
            getline(splitter, title, ':');
            getline(splitter, newHave, ':');
            
            //convert to int
            int have;
            std::stringstream(newHave) >> have;
            
            //searches to see if book exists
            bool exists = inventory->boolSearch(title);
            
            //if it does exist, add books, remove waitlist names if there are any
            if (exists){
                Book* temp = inventory->search(title);
                int len = temp->getWaitListLength();
                
                //if there is no waitlist, no need to print anything
                if (len == 0){
                    temp->increaseHave(have);
                }
                
                //if we're getting more books than are on the waitlist
                //then remove everybody from waitlist, add remaining books from order
                else if (have >= len){
                    std::cout << "Put copies of "+title+" on hold for:" << std::endl;
                    for (int i=0; i<len; i++) {
                        std::cout<<temp->deleteFromWaitList()<<std::endl;
                    }
                    temp->increaseHave(have);
                }
                
                //if there are more names on the waitlist than in the delivery
                else if (len > have){
                    std::cout << "Put copies of "+title+" on hold for:" << std::endl;
                    for (int i=0; i<have; i++) {
                        std::cout<<temp->deleteFromWaitList()<<std::endl;
                    }
                    temp->increaseHave(have);
                }
            }
            else{
                //if it doesn't exist, make a new book
                if (title!=""){
                    std::cout<<"For the book:"+title+", ";
                    int num = read_input();
                    
                    
                    Book* newBook = new Book(title,num);
                    newBook->setHave(have);
                    if (newBook->getTitle()!=""){
                        inventory->addBook(newBook);
                    }
                }
            }
        }
        //close delivery file
        infile.close();
            
    }
    else {
        throw FileNotFoundException();
    }
}

void BookStore::Menu(){
    std::cout<<"Welcome to the Bookstore!"<<std::endl;
    std::cout<<""<<std::endl;
    while (true){
        std::cout<<"Please input a command or press 'H' for summary of commands: ";
        char selection;
        std::cin>>selection;
        
        //Help command
        //Displays the commands available to the user.
        if (selection == 'H' || selection == 'h') {
            std::cout<<""<<std::endl;
            std::cout<<"Here is the list of commands"<<std::endl;
            std::cout<<"------------------------------"<<std::endl;
            std::cout<<"I : Display information for a specified title."<<std::endl;
            std::cout<<""<<std::endl;
            std::cout<<"L : Lists the information of the entire inventory in aplhabetical order"<<std::endl;
            std::cout<<""<<std::endl;
            std::cout<<"A : Add a book to the inventory"<<std::endl;
            std::cout<<""<<std::endl;
            std::cout<<"M : Modify the 'want' value for a specified title"<<std::endl;
            std::cout<<""<<std::endl;
            std::cout<<"O : Create a purchase order for additional books"<<std::endl;
            std::cout<<""<<std::endl;
            std::cout<<"D : Take information from a delivery shipment"<<std::endl;
            std::cout<<""<<std::endl;
            std::cout<<"R : Write a return invoice"<<std::endl;
            std::cout<<""<<std::endl;
            std::cout<<"S : Sell a book"<<std::endl;
            std::cout<<""<<std::endl;
            std::cout<<"Q : Quit (inventory will be saved)"<<std::endl;
            std::cout<<""<<std::endl;
        }
        
        //Quit command.
        //Saves the inventory to a BookstoreInventory.txt file
        else if(selection == 'Q' || selection =='q'){
            std::cout<<""<<std::endl;
            std::cout<<"Goodbye!"<<std::endl;
            inventory->saveInv();
            break;
        }
        
        //Add a book command
        //Adds a book or alerts the user if the book already exists.
        else if (selection == 'A' || selection == 'a'){
            std::cout<<""<<std::endl;
            std::cout<<"Enter the title of the book you would like to add to the inventory: ";
            std::string title;
            std::cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(std::cin,title);
            if (inventory->boolSearch(title)) {
                std::cout<<""<<std::endl;
                std::cout<<"Sorry, that title already exists!"<<std::endl;
                std::cout<<""<<std::endl;
            }
            else{
                std::cout<<""<<std::endl;
                
                int num = read_input();
                
                std::cout<<""<<std::endl;
                Book* myBook = new Book(title, num);
                inventory->addBook(myBook);
                std::cout<<"Your book has successfully been added!"<<std::endl;
                std::cout<<""<<std::endl;
                
            }
        }
        //Inquire Command
        //finds the specified book or allows the user to add the book if it isn't in the inventory.
        else if (selection == 'I' || selection == 'i'){
            std::cout<<""<<std::endl;
            std::cout<<"Enter the title you want info about: ";
            std::string title;
            std::cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(std::cin,title);
            std::cout<<""<<std::endl;
            if (inventory->boolSearch(title)) {
                std::cout<<inventory->search(title)->toString()<<std::endl;
            }
            else{
                std::cout<<"We couldn't find that book in the inventory. Would you like to add this book? (Y/N): ";
                while (true) {
                    char choice;
                    std::cin>>choice;
                    if (choice == 'Y' || choice == 'y') {
                        std::cout<<""<<std::endl;
                        
                        int num = read_input();
                        
                        std::cout<<""<<std::endl;
                        Book* newBook = new Book(title, num);
                        inventory->addBook(newBook);
                        std::cout<<"Your book has successfully been added!"<<std::endl;
                        std::cout<<""<<std::endl;
                        break;
                    }
                    else if (choice == 'N' || choice == 'n'){
                        std::cout<<""<<std::endl;
                        std::cout<<"OK, the book was not added."<<std::endl;
                        break;
                    }
                    else{
                        std::cout<<"Invalid:  Choose Y or N: ";
                    }
                }
            }
        }
        //Sell command
        //adds users to waitlist if the book is not in stock
        else if (selection == 'S' || selection == 's'){
            std::cout<<""<<std::endl;
            std::cout<<"Enter the title you want to sell: ";
            std::string title;
            std::cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(std::cin,title);
            std::cout<<""<<std::endl;
            
            
            if(inventory->boolSearch(title)){
                Book* book = inventory->search(title);
                book->decreaseHaveByOne();
                if (inventory->search(title)->getHave()<0) {
                    std::cout<<"Sorry, that title is sold out. We will add you to the waitlist. Input your name: ";
                    std::string name;
                    //std::cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
                    std::getline(std::cin,name);
                    book->addToWaitlist(name);
                    std::cout<<"Ok you have been added to the waitlist!"<<std::endl;
                }
                else{
                    std::cout<<"Thank you for your purchase!"<<std::endl;
                }
                
                book = nullptr;
                delete book;
            }
            
            else{
                std::cout<<"We couldn't find that book in the inventory. Would you like to add this book? (Y/N): ";
                while (true) {
                    char choice;
                    std::cin>>choice;
                    if (choice == 'Y' || choice == 'y') {
                        std::cout<<""<<std::endl;
                        
                        int num = read_input();
                        
                        std::cout<<""<<std::endl;
                        Book* newBook = new Book(title, num);
                        inventory->addBook(newBook);
                        std::cout<<"Your book has successfully been added!"<<std::endl;
                        std::cout<<""<<std::endl;
                        break;
                    }
                    else if (choice == 'N' || choice == 'n'){
                        std::cout<<""<<std::endl;
                        std::cout<<"OK, the book was not added."<<std::endl;
                        break;
                    }
                    else{
                        std::cout<<"Invalid:  Choose Y or N: ";
                    }
                }
            }
        }
        //modify the want value of a book
        else if (selection == 'M' || selection =='m'){
            std::cout<<""<<std::endl;
            std::cout<<"Enter the title you want to modify: ";
            std::string title;
            std::cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(std::cin,title);
            std::cout<<""<<std::endl;
            
            
            if(inventory->boolSearch(title)){
                Book* book = inventory->search(title);
                std::cout<<"Here is the number of copies you want for this title: " + book->getTitle() + ": ";
                std::cout<<book->getWant();
                std::cout<<""<<std::endl;
                int num = read_input();
                book->setWant(num);
                std::cout<<""<<std::endl;
                std::cout<<"Ok, you now want ";
                std::cout<< book->getWant();
                std::cout<<" number of copies for this title: " + book->getTitle()<<std::endl;
                std::cout<<""<<std::endl;
             
                
            }
         
            else{
                std::cout<<"We couldn't find that book in the inventory. Would you like to add this book? (Y/N): ";
                while (true) {
                    char choice;
                    std::cin>>choice;
                    if (choice == 'Y' || choice == 'y') {
                        std::cout<<""<<std::endl;
                        
                        int num = read_input();
                    
                        std::cout<<""<<std::endl;
                        Book* newBook = new Book(title, num);
                        inventory->addBook(newBook);
                        std::cout<<"Your book has successfully been added!"<<std::endl;
                        std::cout<<""<<std::endl;
                        break;
                    }
                    else if (choice == 'N' || choice == 'n'){
                        std::cout<<""<<std::endl;
                        std::cout<<"OK, the book was not added."<<std::endl;
                        break;
                    }
                    else{
                        std::cout<<"Invalid:  Choose Y or N: ";
                    }
                }

            }
    
        }
        
        //create a purchase order
        else if (selection == 'O' || selection == 'o') {
            std::cout << "Enter purchase order filename (without extension): ";
            std::string filename;
            std::cin >> filename;
            std::cout << "Creating purchase order..." << std::endl;
            std::cout <<std::endl;
            
            std::ofstream outf(filename+".txt");
            if (canPurchaseOrder() == true) {
                for (int i=0;i<inventory->getSize();i++){
                    Book* temp = inventory->getBook(i);
                    //if we want more books than we have
                    if (temp->getWant() > temp->getHave()){
                        //convert difference to string
                        std::string difference;
                        std::ostringstream convert;
                        convert << temp->getWant()-temp->getHave();
                        difference = convert.str();
                        
                        //print to screen
                        std::cout << temp->getTitle();
                        std::cout << ":"+difference << std::endl;
                        
                        //write to file
                        outf << temp->getTitle();
                        outf << ":"+difference << std::endl;
                    }
                }
            }
            outf.close();
        }
        
        
        else if (selection == 'R' || selection == 'r'){
            std::cout<<""<<std::endl;
            if (canReturnInvoice() == true) {
                std::cout<<"Enter the filename (without an extension) where the return invoice will be saved: ";
                std::string fileName;
                std::cin>>fileName;
                std::cout<<""<<std::endl;
                try {
                    returnInvoice(fileName);
                    std::cout<<"The return invoice has been successfully written to " << fileName << " !" << std::endl;
                    
                } catch (std::exception) {
                    while (true) {
                        std::cout << "An error occured while writing to that file.  Please enter a new filename (without an extension: " << std::endl;
                        std::cin>>fileName;
                        try {
                            returnInvoice(fileName);
                            std::cout<<"The return invoice has been successfully written to " << fileName << " !" << std::endl;
                            break;
                        } catch(std::exception) {
                            continue;
                        }
                    }
                }
                std::cout<<""<<std::endl;
            }
            else {
                std::cout << "There are no books available to return." << std::endl;
            }
        }
        
        //Delivery command
        //read a delivery file and add shipment to inventory
        else if (selection == 'D' || selection == 'd'){
            std::cout << "Enter the filename of delivery summary to read (without extension): ";
            std::string filename;
            std::cin >> filename;
            std::cout << "Adding delivered books to inventory..." << std::endl;
            std::cout << std::endl;
            
            getDelivery(filename+".txt");
        }
        //List command
        //lists all the information about the books in the inventory.
        else if (selection == 'L' || selection == 'l'){
            printInventory();
        }
        
        //if the user doesn't input a valid command key
        else{
            std::cout<<"Invalid Option"<<std::endl;
            std::cout<<""<<std::endl;
            std::cin.clear();
        }


    }
}