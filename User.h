#ifndef USER_H
#define USER_H
#include <iostream>
using namespace std;

class User
{
private:
    string username, password, role;

public:
    User() {}
    User(string usn, string pass, string rle) : username(usn), password(pass), role(rle) {}
    virtual ~User() {}
    string getUsername() const { return username; }
    string getPassword() const { return password; }
    string getRole() const { return role; }
    void setPassword(string newPassword)
    {
        password = newPassword;
    }
    virtual void displayMenu() = 0;
    bool authenticate(string uname, string pwd)
    {
        return (uname == username && pwd == password);
    }
};

#endif