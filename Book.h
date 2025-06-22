#ifndef BOOK_H
#define BOOK_H
#include <iostream>
using namespace std;

class Book
{
private:
    string title, author, ISBN, genre;
    int totalCopies, availableCopies;

public:
    // Constructors
    Book() {}
    Book(string t, string auth, string isbn, string gnre, int total_copies) : title(t), author(auth), ISBN(isbn), genre(gnre), totalCopies(total_copies), availableCopies(total_copies) {}

    // Destructor
    ~Book() {}

    // Getters
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    string getISBN() const { return ISBN; }
    string getGenre() const { return genre; }
    int getTotalCopies() const { return totalCopies; }
    int getAvailableCopies() const { return availableCopies; }

    // Setters
    void setTitle(string t) { title = t; }
    void setAuthor(string a) { author = a; }
    void setGenre(string g) { genre = g; }
    void setTotalCopies(int t) { totalCopies = t; }

    // Availability control
    bool borrow()
    {
        if (availableCopies > 0)
        {
            availableCopies--;
            return true;
        }
        else
        {
            return false;
        }
    }

    void returnBook()
    {
        if (availableCopies < totalCopies)
        {
            availableCopies++;
        }
        else
        {
            cout << "Invalid Return Request!" << endl;
        }
    }
};

#endif