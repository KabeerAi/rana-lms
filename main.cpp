#include <iostream>
#include <iomanip>
#include "LibraryManager.h"
#include "UserFactory.h"
#include "SystemInitializer.h"

using namespace std;

LibraryManager* LibraryManager::instance = nullptr;
int main() {
    SystemInitializer::initializeSystem();
    while (true) {
        system("cls"); // Clear screen for cleaner display
        cout << endl;
        cout << "+----------------------------------+\n";
        cout << "|     RANA'S LIBRARY MANAGEMENT    |\n";
        cout << "+----------------------------------+\n\n";
        
        cout << "+-------------- MENU --------------+\n";
        cout << "|                                  |\n";
        cout << "|   [1] Login to Your Account      |\n";
        cout << "|   [2] Browse as Guest            |\n";
        cout << "|   [3] Exit Application           |\n";
        cout << "|                                  |\n";
        cout << "+----------------------------------+\n\n";
        
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            system("cls");
            cout << "\n+----------- LOGIN ------------+\n\n";
            
            string uname, pwd;
            cout << "  Username: ";
            getline(cin, uname);
            cout << "  Password: ";
            getline(cin, pwd);

            User* user = LibraryManager::getInstance()->login(uname, pwd);
            if (user) {
                cout << "\n* Login successful! Welcome, " << user->getRole() << "!\n";
                system("pause");
                user->displayMenu();
            } else {
                cout << "\nX Invalid credentials. Please try again.\n";
                system("pause");
            }

        } else if (choice == 2) {
            cout << "\n-> Continuing as Guest...\n";
            User* guest = UserFactory::createUser("Guest");
            system("pause");
            system("cls");
            guest->displayMenu();
            delete guest;

        } else if (choice == 3) {
            cout << "\n+--------------------------------+\n";
            cout << "|  Thank you for using our library! |\n";
            cout << "+--------------------------------+\n";
            break;

        } else {
            cout << "\nX Invalid choice. Please try again.\n";
            system("pause");
        }
    }

    return 0;
}