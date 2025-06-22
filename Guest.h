#ifndef GUEST_H
#define GUEST_H

#include "User.h"
#include "LibraryManager.h"
#include <iostream>

class Guest : public User {
public:
    Guest() : User("Guest", "", "Guest") {}

    void displayMenu() override {
        int choice;
        do {
            system("cls");
            cout << "\n+-------------------------------+";
            cout << "\n|          GUEST MENU           |";
            cout << "\n+-------------------------------+";
            cout << "\n|                               |";
            cout << "\n|   [1] Search Book             |";
            cout << "\n|   [2] View All Books          |";
            cout << "\n|   [3] Exit Guest Mode         |";
            cout << "\n|                               |";
            cout << "\n+-------------------------------+";
            cout << "\n\nEnter your choice: ";

            cin >> choice;
            cin.ignore();

            switch (choice) {
                case 1: 
                    system("cls");
                    searchBook(); 
                    break;
                case 2: 
                    system("cls");
                    viewAllBooks(); 
                    break;
                case 3: 
                    cout << "\n+-------------------------------+";
                    cout << "\n|  Exiting guest mode...         |";
                    cout << "\n+-------------------------------+";
                    break;
                default: 
                    cout << "\nX Invalid option. Please try again.\n";
                    system("pause");
            }
        } while (choice != 3);
    }

    void searchBook() {
        string title;
        cout << "Enter book title to search: ";
        getline(cin, title);

        Book* book = LibraryManager::getInstance()->findBookByTitle(title);
        if (book) {
            LibraryManager::getInstance()->displayBookDetails(title);
            system("pause");
        } else {
            cout << "No book found with the title '" << title << "'.\n";
            system("pause");
        }
    }

    void viewAllBooks() {
        LibraryManager::getInstance()->displayAllBooks();
        system("pause");
    }
};

#endif