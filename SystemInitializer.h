#ifndef SYSTEMINITIALIZER_H
#define SYSTEMINITIALIZER_H
#include "LibraryManager.h"
#include "UserFactory.h"
#include "Book.h"

class SystemInitializer {
public:
    static void initializeSystem() {
        User* defaultAdmin = UserFactory::createUser("Admin", "admin", "admin");
        LibraryManager::getInstance()->addUser(defaultAdmin);

        // Add some Programming books to the library
        Book book1("The C++ Programming", "Bjarne Stroustrup", "978-0321563842", "Programming", 5);
        Book book2("C++ Primer", "Stanley B. Lippman", "978-0321563840", "Programming", 3);
        Book book3("Effective C++", "Scott Meyers", "978-0321334876", "Programming", 4);
        Book book4("C++ Cookbook", "Anthony Williams", "978-0321563847", "Programming", 2);

        LibraryManager::getInstance()->addBook(book1);
        LibraryManager::getInstance()->addBook(book2);
        LibraryManager::getInstance()->addBook(book3);
        LibraryManager::getInstance()->addBook(book4);
    }
};

#endif 