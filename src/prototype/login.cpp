#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

const string ADMIN_USERNAME = "admin";
const string ADMIN_PASSWORD = "admin123";

const string CUSTOMER_USERNAME = "user";
const string CUSTOMER_PASSWORD = "user123";

bool login(bool &isAdmin) 
{
    int role;
    string validity, username, password;
    cout << "===== LOGIN =====\n";
    cout << "1. Admin\n";
    cout << "2. Customer\n";
    cout << "0. Exit\n";

    do {
    cout << "Choose role: ";
    cin >> role;
    if (role < 0 || role > 2)
        cout << "Invalid role choice. Please try again.\n";
    } while (role < 0 || role > 2);

    if (role == 0) {
        return false; // Exit application
    }

    cin.ignore();

    if (role == 1)
    {
            cout << "Admin login selected.\n";
            for ( int i = 0; i < 3; i++ ) 
            {
                cout << "Username: ";
                getline(cin, username);
                cout << "Password: ";
                getline(cin, password);

                if (username == ADMIN_USERNAME && password == ADMIN_PASSWORD) {
                    cout << "Admin login successful.\n";
                    validity = "valid";
                    isAdmin = true;
                    return true;
                    break;
                } else {
                    cout << "Invalid admin credentials. Please try again.\n";
                    validity = "invalid";
                }
            }
            if (validity == "invalid") {
                cout << "Too many failed attempts.\n";
                return false;
            }
    } else if (role == 2)
    {
            cout << "Customer login selected.\n";
            for ( int i = 0; i < 3; i++ ) 
            {
                cout << "Username: ";
                getline(cin, username);
                cout << "Password: ";
                getline(cin, password);

                if (username == CUSTOMER_USERNAME && password == CUSTOMER_PASSWORD) {
                    cout << "Customer login successful.\n";
                    validity = "valid";
                    return true;
                    break;
                } else {
                    cout << "Invalid customer credentials. Please try again.\n";
                    validity = "invalid";
                }
            }
            if (validity == "invalid") {
                cout << "Too many failed attempts.\n";
                return false;
            }
    }
}

int main() 
{
    bool isAdmin = false;
    char again;

    //arrayProducts();

    while (true) 
    {
        if (!login(isAdmin)) {
            cout << "\nGoodbye.\n";
            break;
        }

        if (isAdmin) {
            cout << "Your admin lol\n";
            //adminMenu();
        } else {
            cout << "Your customer lol\n";
            //customerMenu();
        }

        cout << "\nDo you want to login again? (y/n): ";
        cin >> again;
        
        if (again == 'n' || again == 'N')
            cout << "Exiting system. Goodbye.\n";
    }

    return 0;
}