#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"
#include "LibraryManager.h"

class Admin : public User {
public:
    Admin(string uname, string pwd) : User(uname, pwd, "Admin") {}
    void displayMenu() override {
        int choice;
        do {
            system("cls");
            cout << endl;
            cout << "+----------------------------------+\n";
            cout << "|           ADMIN PANEL            |\n";
            cout << "+----------------------------------+\n\n";
            
            cout << "+-------------- MENU --------------+\n";
            cout << "|                                  |\n";
            cout << "|   [1] Add Book                   |\n";
            cout << "|   [2] Remove Book                |\n";
            cout << "|   [3] Add User                   |\n";
            cout << "|   [4] Remove User                |\n";
            cout << "|   [5] Display All Books          |\n";
            cout << "|   [6] Display Borrow History     |\n";
            cout << "|   [7] Logout                     |\n";
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
                    addUser();
                    system("pause");
                    break;
                case 4:
                    system("cls");
                    removeUser();
                    system("pause");
                    break;
                case 5:
                    system("cls");
                    displayAllBooks();
                    system("pause");
                    break;
                case 6:
                    system("cls");
                    displayBorrowHistory();
                    system("pause");
                    break;
                case 7:
                    cout << "Logging out...\n";
                    system("pause");
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n";
                    system("pause");
            }
        }while (choice != 7);
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

    void addUser() {
        string username, password, role;
        
        cout << endl;
        cout << "+----------------------------------+\n";
        cout << "|         ADD NEW USER             |\n";
        cout << "+----------------------------------+\n\n";

        cout << "  Username: ";
        getline(cin, username);

        // Checking if the username already exists
        if (LibraryManager::getInstance()->findUserByUsername(username)) {
            cout << "* Username already exists. Please choose a different username.\n";
            return;
        }

        cout << "  Password: ";
        getline(cin, password);

        cout << "  Role (Member/Librarian/Admin): ";
        getline(cin, role);
        cout << endl;

        User* newUser = nullptr;

        if (role == "Member") {
            newUser = new Member(username, password);
        }
        else if (role == "Librarian") {
            newUser = new Librarian(username, password);
        }
        else if (role == "Admin") {
            newUser = new Admin(username, password);
        }
        else {
            cout << "* Invalid role. User not added.\n";
            return;
        }
        LibraryManager::getInstance()->addUser(newUser);
        cout << "* " << role << " added successfully!\n";
    }

    void removeUser() {
        string username;
        
        cout << endl;
        cout << "+----------------------------------+\n";
        cout << "|         REMOVE USER              |\n";
        cout << "+----------------------------------+\n\n";

        cout << "  Username: ";
        getline(cin, username);
        cout << endl;

        if (LibraryManager::getInstance()->removeUser(username)) {
            cout << "* User removed successfully!\n";
        }
        else {
            cout << "* User not found or not available for removal.\n";
        }
    }

    void displayAllBooks() {
        LibraryManager::getInstance()->displayAllBooks();
    }

    void displayBorrowHistory() {
        LibraryManager::getInstance()->displayBorrowHistory();
    }
};

#endif