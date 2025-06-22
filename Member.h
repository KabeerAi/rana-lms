#ifndef MEMBER_H
#define MEMBER_H
#include <iostream>
#include <string>
#include "User.h"
#include "LibraryManager.h"

class Member : public User {
public:
    Member(string uname, string pwd) : User(uname, pwd, "Member") {}
    void displayMenu() override {
        int choice;
        do {
            system("cls");
            cout << endl;
            cout << "+----------------------------------+\n";
            cout << "|         MEMBER PANEL             |\n";
            cout << "+----------------------------------+\n\n";
            
            cout << "+-------------- MENU --------------+\n";
            cout << "|                                  |\n";
            cout << "|   [1] Search Book                |\n";
            cout << "|   [2] Borrow Books               |\n";
            cout << "|   [3] Return Books               |\n";
            cout << "|   [4] View Borrow History        |\n";
            cout << "|   [5] Check Fine                 |\n";
            cout << "|   [6] Logout                     |\n";
            cout << "|                                  |\n";
            cout << "+----------------------------------+\n\n";
            
            cout << " Enter your choice: ";
            cin >> choice;
            cin.ignore();

            system("cls");
            switch (choice) {
                case 1:
                    system("cls");
                    searchBook();
                    system("pause");
                    break;
                case 2:
                    system("cls");
                    borrowBooks();
                    system("pause");
                    break;
                case 3:
                    system("cls");
                    returnBooks();
                    system("pause");
                    break;
                case 4:
                    system("cls");
                    viewBorrowHistory();
                    system("pause");
                    break;
                case 5:
                    system("cls");
                    checkFine();
                    system("pause");
                    break;
                case 6:
                    cout << "Logging out...\n";
                    system("pause");
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n";
                    system("pause");
            }
        } while (choice != 6);
    }

    void searchBook() {
        cout << endl;
        cout << "+----------------------------------+\n";
        cout << "|         SEARCH BOOK              |\n";
        cout << "+----------------------------------+\n\n";

        string title;
        cout << "  Enter book title: ";
        getline(cin, title);
        cout << endl;

        cout << "Search Results for '" << title << "':\n\n";
        LibraryManager::getInstance()->displayBookDetails(title);
        if (LibraryManager::getInstance()->findBookByTitle(title) == nullptr) {
            cout << "* No book found with the title '" << title << "'.\n";
        }
    }

    void borrowBooks() {
        cout << endl;
        cout << "+----------------------------------+\n";
        cout << "|         BORROW BOOK              |\n";
        cout << "+----------------------------------+\n\n";

        string title;
        cout << "  Enter book title: ";
        getline(cin, title);
        cout << endl;
    
        Book* book = LibraryManager::getInstance()->findBookByTitle(title);
        if (book == nullptr) {
            cout << "* No book found with the title '" << title << "'.\n";
            return;
        }
    
        if (book->getAvailableCopies() <= 0) {
            cout << "* Sorry, no copies available for this book.\n";
            return;
        }
    
        string borrowDate, dueDate;
        cout << "  Enter borrow date (dd/mm/yyyy): ";
        getline(cin, borrowDate);
        cout << endl;

        int borrowDay, borrowMonth, borrowYear;
        int dueDay, dueMonth, dueYear;

        if(sscanf(borrowDate.c_str(), "%d/%d/%d", &borrowDay, &borrowMonth, &borrowYear) != 3) {
            cout << "* Invalid date format. Please enter date in dd/mm/yyyy format.\n";
            return;
        }

        dueDay = borrowDay + 14;
        dueMonth = borrowMonth;
        dueYear = borrowYear;
        if (dueDay > 30) {
            dueDay -= 30;
            dueMonth++;
        }
        if (dueMonth > 12) {
            dueMonth -= 12;
            dueYear++;
        }
        dueDate = to_string(dueDay) + "/" + to_string(dueMonth) + "/" + to_string(dueYear);

        book->borrow();
        BorrowRecord br(this->getUsername(), book->getTitle(), book->getISBN(), borrowDate, dueDate);
        LibraryManager::getInstance()->addBorrowRecord(br);
    
        cout << "* Book '" << title << "' borrowed successfully!\n";
        cout << "* Due date: " << dueDate << endl;
        cout << "* Borrowed book ISBN: " << book->getISBN() << endl;
        cout << "* Available copies: " << book->getAvailableCopies() << endl;
    }

    void returnBooks() {
        cout << endl;
        cout << "+----------------------------------+\n";
        cout << "|         RETURN BOOK              |\n";
        cout << "+----------------------------------+\n\n";

        vector<BorrowRecord> allRecords = LibraryManager::getInstance()->getAllRecords();
        bool hasBorrowed = false;

        cout << "Your borrowed books:\n\n";
        for (const BorrowRecord& br : allRecords) {
            if (br.getUsername() == this->getUsername() && !br.isReturned()) {
                cout << "  Title: " << br.getTitle() << endl
                     << "  ISBN: " << br.getISBN() << endl
                     << "  Borrowed on: " << br.getBorrowDate() << endl
                     << "  Due on: " << br.getDueDate() << endl << endl;
                hasBorrowed = true;
            }
        }

        if (!hasBorrowed) {
            cout << "* You don't have any borrowed books currently.\n";
            return;
        }

        string isbn;
        cout << "  Enter book ISBN to return: ";
        getline(cin, isbn);
        cout << endl;

        Book* book = LibraryManager::getInstance()->findBookByISBN(isbn);
        if (book == nullptr) {
            cout << "* No book found with the ISBN '" << isbn << "'.\n";
            return;
        }

        string returnDate;
        cout << "  Enter return date (dd/mm/yyyy): ";
        getline(cin, returnDate);
        cout << endl;

        bool found = false;
        vector<BorrowRecord>& records = LibraryManager::getInstance()->getMutableBorrowHistory();
        for (BorrowRecord& br : records) {
            if (br.getUsername() == this->getUsername() && br.getISBN() == isbn && !br.isReturned()) {
                br.setReturnDate(returnDate);
                br.calculateFine();
                found = true;

                cout << "* Book returned successfully!\n";
                book->returnBook();
                cout << "* Return date: " << returnDate << endl;
                cout << "* Fine: Rs. " << br.getFine() << endl;
                cout << "* Available copies: " << book->getAvailableCopies() << endl;
                break;
            }
        }

        if (!found) {
            cout << "* You haven't borrowed a book with the ISBN '" << isbn << "'.\n";
        }
    }

    void viewBorrowHistory() {
        cout << endl;
        cout << "+----------------------------------+\n";
        cout << "|         BORROW HISTORY           |\n";
        cout << "+----------------------------------+\n\n";

        vector<BorrowRecord> allRecords = LibraryManager::getInstance()->getAllRecords();
        bool hasBorrowed = false;

        for (const BorrowRecord& br : allRecords) {
            if (br.getUsername() == this->getUsername()) {
                cout << "  Title: " << br.getTitle() << endl
                     << "  ISBN: " << br.getISBN() << endl
                     << "  Borrowed on: " << br.getBorrowDate() << endl
                     << "  Due on: " << br.getDueDate() << endl
                     << "  Returned on: " << (br.isReturned() ? br.getReturnDate() : "Not returned yet") << endl
                     << "  Fine: Rs. " << br.getFine() << endl << endl;
                hasBorrowed = true;
            }
        }
        if (!hasBorrowed) {
            cout << "* You don't have any borrow history.\n";
        }
    }

    void checkFine() {
        cout << endl;
        cout << "+----------------------------------+\n";
        cout << "|         CHECK FINE               |\n";
        cout << "+----------------------------------+\n\n";

        vector<BorrowRecord> allRecords = LibraryManager::getInstance()->getAllRecords();
        float totalFine = 0.0f;

        for (const BorrowRecord& br : allRecords) {
            if (br.getUsername() == this->getUsername()) {
                totalFine += br.getFine();
            }
        }
        cout << "* Total fine: Rs. " << totalFine << endl;
    }
};

#endif
