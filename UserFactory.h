#ifndef USERFACTORY_H
#define USERFACTORY_H

#include "User.h"
#include "Member.h"
#include "Librarian.h"
#include "Admin.h"
#include "Guest.h"

class UserFactory {
public:
    static User* createUser(const string& role, const string& uname, const string& pwd) {
        if (role == "Member") {
            return new Member(uname, pwd);
        }
        else if (role == "Librarian") {
            return new Librarian(uname, pwd);
        }
        else if (role == "Admin") {
            return new Admin(uname, pwd);
        }
        else {
            return nullptr;
        }
    }

    static User* createUser(const string& role) {
        if (role == "Guest") return new Guest();
        return nullptr;
    }
};

#endif