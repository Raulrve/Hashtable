#include <iostream>
#include <string>
#include <cctype>
#include <utility>
#include "passserver.h"
#include "hashtable.h"

using namespace std;
void Menu();


int main() {
    char choice;

    size_t capacity;
    string username, password, newpassword, loadfilename;

    cout<<"Enter the preferred hash table capacity: ";
    cin>> capacity;


    PassServer server(capacity);
    do{
        Menu();
        cin>>choice;
        if(choice == 'l')
        {
            cout<< "Enter password file name to load from: ";
            cin>>loadfilename;
            if (server.load(loadfilename.c_str()))
                break;
            else
                cout<< "Error: cannot open file: "<<loadfilename<<endl;
        }
        else if(choice == 'a')
        {
            cout<<"Enter username: ";
            cin>>username;
            cout<<"Enter password: ";
            cin>>password;

            if(server.addUser(make_pair(username, password)))
                cout<<"User "<< username<<" added.\n";
            else
                cout<<"*****Error: User already existys. Could not add user.\n";
        }
        else if(choice == 'r')
        {
            cout << "Enter username: ";
            cin >> username;
            if (server.removeUser(username))
                cout << "User " << username << " deleted.";
            else
                cout << "ERROR: User not found.  Could not remove user.";
        }
        else if(choice == 'c')
        {
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;
            cout << "\nEnter new password: ";
            cin >> newpassword;
            if (server.changePassword(make_pair(username, password), newpassword))
                cout << "\nPassword changed for user " << username; break;
            cout << "Error: Could not change user password";
        }
        else if(choice == 'f')
        {
            cout << "Enter username: ";
            cin >> username;
            if (server.find(username))
                cout << "\nUser '" << username << "' found."; break;
            cout << "\nUser '" << username << "' not found.";
        }
        else if(choice == 'd')
        {
            server.dump();
        }
        else if(choice == 's')
        {
            cout << "Size of hashtable: " << server.size();
        }
        else if(choice == 'w')
        {
            cout << "Enter password file name to write to: ";
            cin >> loadfilename;
            server.write_to_file(loadfilename.c_str());
        }
        else
            cout << "Incorrect choice. Please try again \n";


    }while (choice != 'x');


    return 0;
}

void Menu()
{
    cout << "\n\n";
    cout << "l - Load From File" << endl;
    cout << "a - Add User" << endl;
    cout << "r - Remove User" << endl;
    cout << "c - Change User Password" << endl;
    cout << "f - Find User" << endl;
    cout << "d - Dump HashTable" << endl;
    cout << "s - HashTable Size" << endl;
    cout << "w - Write to Password File" << endl;
    cout << "x - Exit program" << endl;
    cout << "\nEnter choice : ";
}
