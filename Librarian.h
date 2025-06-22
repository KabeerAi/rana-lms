#ifndef LIBRARIAN_H
#define LIBRARIAN_H
#include "Book.h"
#include "LibraryManager.h"
#include <iostream>
#include <string>

using namespace std;

class Librarian : public User {
public:
    Librarian(string uname, string pwd) : User(uname, pwd, "Librarian") {}
    void displayMenu() override {
        int choice;
        do {
            system("cls");
            cout << endl;
            cout << "+----------------------------------+\n";
            cout << "|         LIBRARIAN PANEL          |\n";
            cout << "+----------------------------------+\n\n";
            
            cout << "+-------------- MENU --------------+\n";
            cout << "|                                  |\n";
            cout << "|   [1] Add Book                   |\n";
            cout << "|   [2] Remove Book                |\n";
            cout << "|   [3] View All Books             |\n";
            cout << "|   [4] View Borrow History        |\n";
            cout << "|   [5] Logout                     |\n";
            cout << "|                                  |\n";
            cout << "+----------------------------------+\n\n";
            
            cout << " Enter your choice: ";
            cin >> choice;
            cin.ignore();

            system("cls");
            switch (choice) {
                case 1:
                    system("cls");
                    addBook();
                    system("pause");
                    break;
                case 2:
                    system("cls");
                    removeBook();
                    system("pause");
                    break;
                case 3:
                    system("cls");
                    viewAllBooks();
                    system("pause");
                    break;
                case 4:
                    system("cls");
                    viewAllBorrowHistory();
                    system("pause");
                    break;
                case 5:
                    cout << "Logging out...\n";
                    system("pause");
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n";
                    system("pause");
            }
        } while (choice != 5);
    }

    void addBook() {
        string title, author, isbn, genre;
        int totalCopies;

        cout << endl;
        cout << "+----------------------------------+\n";
        cout << "|         ADD NEW BOOK             |\n";
        cout << "+----------------------------------+\n\n";
        
        cout << "  Title: ";
        getline(cin, title);
        cout << "  Author: ";
        getline(cin, author);
        cout << "  ISBN: ";
        getline(cin, isbn);
        cout << "  Genre: ";
        getline(cin, genre);
        cout << "  Total Copies: ";
        cin >> totalCopies;
        cout << endl;
        
        cin.ignore();

        Book newBook(title, author, isbn, genre, totalCopies);
        LibraryManager::getInstance()->addBook(newBook);

        cout << "* Book added successfully!\n";
    }

    void removeBook() {
        string isbn;
        
        cout << endl;
        cout << "+----------------------------------+\n";
        cout << "|         REMOVE BOOK              |\n";
        cout << "+----------------------------------+\n\n";

        cout << "  ISBN: ";
        getline(cin, isbn);
        cout << endl;

        if (LibraryManager::getInstance()->removeBook(isbn)) {
            cout << "* Book removed successfully!\n";
        } else {
            cout << "* Book not found or not available for removal.\n";
        }
    }

    void viewAllBooks() {
        LibraryManager::getInstance()->displayAllBooks();
    }

    void viewAllBorrowHistory() {
        LibraryManager::getInstance()->displayBorrowHistory();
    }
};

#endif