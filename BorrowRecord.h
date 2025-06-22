#ifndef BORROWRECORD_H
#define BORROWRECORD_H
#include <iostream>
#include "Fine.h"
using namespace std;

class BorrowRecord {
private:
    string username;       // Who borrowed the book
    string ISBN;           // Book’s identifier
    string title;
    string borrowDate;
    string dueDate;
    string returnDate;     // Empty if not returned yet
    float fineAmount;      // 0 if returned on time

public:
    // Constructors
    BorrowRecord() {}
    BorrowRecord(string user, string ttle, string isbn, string borrow, string due) : username(user), title(ttle), ISBN(isbn), borrowDate(borrow), dueDate(due), returnDate(""), fineAmount(0.0) {}

    // Destructor
    ~BorrowRecord() {}

    void setReturnDate(string date) {
        returnDate = date;
        calculateFine();
    }

    float calculateFine() {
        // checking if return date is empty
        if (returnDate.empty()) {
            return 0.0f;
        }

        Fine fineCalc(100);
        fineCalc.calculateFine(dueDate, returnDate);
        fineAmount = fineCalc.getFineAmount();
        return fineAmount;

    }

    float getFine() const {
        return fineAmount;
    }

    string getTitle() const {
        return title;
    }

    string getBorrowDate() const {
        return borrowDate;
    }

    string getReturnDate() const {
        return returnDate;
    }

    bool isReturned() const {
        return returnDate != "";
    }

    string getISBN() const {
        return ISBN;
    }

    string getUsername() const {
        return username;
    }

    string getDueDate() const {
        return dueDate;
    }

    bool isOverdue() const {
        // checking if return date is empty
        if (returnDate.empty()) {
            return false;
        }
        int returnDay, returnMonth, returnYear;
        int dueDay, dueMonth, dueYear;

        sscanf(returnDate.c_str(), "%d/%d/%d", &returnDay, &returnMonth, &returnYear);
        sscanf(dueDate.c_str(), "%d/%d/%d", &dueDay, &dueMonth, &dueYear);

        // Calculate fine based on the difference in days
        int daysLate = (returnYear - dueYear) * 365 + (returnMonth - dueMonth) * 30 + (returnDay - dueDay);

        return daysLate > 0; // Return true if daysLate is positive, indicating overdue
    }



};

#endif