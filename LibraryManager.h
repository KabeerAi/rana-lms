#ifndef LIBRARYMANAGER_H
#define LIBRARYMANAGER_H
#include <iostream>
#include <string>
#include <vector>

#include "Book.h"
#include "User.h"
#include "BorrowRecord.h"


using namespace std;

class LibraryManager
{
private:
    vector<Book> books;
    vector<User*> users;
    vector<BorrowRecord> borrowHistory;

    static LibraryManager* instance;
    LibraryManager() {}

public:
    static LibraryManager* getInstance(){
        if (instance == nullptr){
            instance = new LibraryManager();
        }
        return instance;
    }

    ~LibraryManager() {
        for (User* u : users) {
            delete u;
        }
    }

    void addBook(const Book& b){
        books.push_back(b);
    }

    bool removeBook(const string& isbn){
        for (auto it = books.begin(); it != books.end(); ++it) {
            if (it->getISBN() == isbn) {
                books.erase(it);
                return true;
            }
        }
        return false;
    }

    void addUser(User* u){
        users.push_back(u);
    }

    bool findUserByUsername(const string& uname){
        for (User* u : users) {
            if (u->getUsername() == uname) {
                return true; // User found
            }
        }
        return false; // User not found
    }

    bool removeUser(const string& uname){
        for (auto it = users.begin(); it!= users.end(); ++it) {
            if ((*it)->getUsername() == uname) {
                users.erase(it);
                return true;
            }
        }
        return false;
    }

    User* login(const string& uname, const string& pwd){
        for (User* u : users) {
            if (u->getUsername() == uname && u->getPassword() == pwd) {
                return u; // Return the user if login is successful
            }
        }
        return nullptr; // Return nullptr if login fails
    }

    Book* findBookByISBN(const string& isbn) {
        for (Book& b : books) {
            if (b.getISBN() == isbn) {
                return &b; // Return the book if found
            }
        }
        return nullptr; // Return nullptr if the book is not found
    }

    Book* findBookByTitle(const string& title) {
        for (Book& b : books) {
            if (b.getTitle() == title) {
                return &b; // Return the book if found
            }
        }
        return nullptr; // Return nullptr if the book is not found
    }

    void displayBookDetails(const string& title) const {
        for (const Book& b : books) {
            if (b.getTitle() == title) {
                cout << "Title: " << b.getTitle()
                     << ", Author: " << b.getAuthor()
                     << ", ISBN: " << b.getISBN()
                     << ", Genre: " << b.getGenre()
                     << ", Available: " << b.getAvailableCopies()
                     << "/" << b.getTotalCopies() << endl;
            }
        }
    }

    void displayAllBooks() const {
        cout << "\nAvailable Books:\n" << endl;
        cout << "+--------------------------------+---------------------------+------------------+------------------+----------------+" << endl;
        cout << "| Title                          | Author                    | ISBN             | Genre            | Available      |" << endl;
        cout << "+--------------------------------+---------------------------+------------------+------------------+----------------+" << endl;
        
        for (const Book& b : books) {
            string title = b.getTitle();
            string author = b.getAuthor();
            string isbn = b.getISBN();
            string genre = b.getGenre();
            string available = to_string(b.getAvailableCopies()) + "/" + to_string(b.getTotalCopies());
            
            cout << "| " << left << setw(30) << title 
                 << " | " << setw(25) << author
                 << " | " << setw(16) << isbn
                 << " | " << setw(16) << genre
                 << " | " << setw(15) << available << "|" << endl;
        }
        
        cout << "+--------------------------------+---------------------------+------------------+------------------+----------------+" << endl;
    }

    void addBorrowRecord(const BorrowRecord& br){
        borrowHistory.push_back(br);
    }

    const vector<BorrowRecord>& getAllRecords() const {
        return borrowHistory;
    }

    void displayBorrowHistory() const {
        cout << "\nBorrow History:\n" << endl;
        cout << "+----------------+----------------+----------------+----------------+----------+----------------+------------+" << endl;
        cout << "| Username       | Book Title     | Borrow Date    | Due Date       | Returned | Return Date    | Fine (Rs)  |" << endl;
        cout << "+----------------+----------------+----------------+----------------+----------+----------------+------------+" << endl;
        
        for (const BorrowRecord& br : borrowHistory) {
            string username = br.getUsername();
            string title = br.getTitle().substr(0, 10) + "...";
            string borrowDate = br.getBorrowDate();
            string dueDate = br.getDueDate();
            string returned = br.isReturned() ? "Yes" : "No";
            string returnDate = br.isReturned() ? br.getReturnDate() : "-";
            string fine = br.isReturned() ? to_string(br.getFine()) : "-";
            
            cout << "| " << left << setw(14) << username 
                 << " | " << setw(14) << title
                 << " | " << setw(14) << borrowDate
                 << " | " << setw(14) << dueDate
                 << " | " << setw(8) << returned
                 << " | " << setw(14) << returnDate
                 << " | " << setw(10) << fine << " |" << endl;
        }
        
        cout << "+----------------+----------------+----------------+----------------+----------+----------------+------------+" << endl;
    }

    vector<BorrowRecord>& getMutableBorrowHistory() {
        return borrowHistory;
    }

    // float checkUserFine(const string& uname){
    //     float totalFine = 0.0;
    //     for (const BorrowRecord& br : borrowHistory) {
    //         if (br.getUsername() == uname && br.isReturned()) {
    //             totalFine += br.calculateFine();
    //         }
    //     }
    //     return totalFine;
    // }
};
#endif