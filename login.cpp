#include "logIn.h"
#include "mainMenu.h"
#include <iostream>
#include <cstring>
#include <string>
#include <conio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

void createFolder(char *name) {
    mkdir(name);
}

bool isValidUsername(char *username, bool check) {
    unsigned int le = strlen(username);

    if (le == 0) return false;
    
    if (check) {
        for (unsigned int i = 0; i < le; i++) {
            if (!((username[i] >= 'A' && username[i] <= 'Z') || (username[i] >= 'a' && username[i] <= 'z') || (username[i] >= '0' && username[i] <= '9'))) {
                cout << "Please enter a valid username!!\n";
                cout << "A valid user name cannt include special char or spacing\n";
                system("pause");
                return false;
            }
        }
    } else{
        for (unsigned int i = 0; i < le; i++) {
            if (!( (username[i] >= '0' && username[i] <= '9'))) {
                cout << "Please enter a valid username!!\n";
                cout << "A student user name only includes 8 numbers\n";
                system("pause");
                return false;
            }
        }
    }

    return true;
}

bool isStaff(int k) {
    string code;
    int x;

    while (true) {
            cout << "Enter teacher key code to prove you're a teacher!!\n";
            cin.ignore();
            getline (cin, code);
            if (code == "CS101") {
                cout << "You enter correct key!!\n";
                cout << "Now you can start your register\n\n";
                return true;
            } else {
                cout << "You enter wrong key!!\n";
                cout << "You can input 1 to enter again or 0 back to main menu\n";
                do {
                    cin >> x;
                    if (x == 0) {
                        mainMenu();
                        return false;
                    }
                    if (x == 1) break;
                } while (x > 1 || x < 0);
            }
    }

    return true;
}

void signUp(){
    system("cls");
    cin.ignore();
    char *username, *password;
    char tmp[1000] = {0}, sTmp[1000] = "User\\";


    int x;
    bool check;

    cout << "REGISTER PAGE!!\n\n";

    cout << "You can only sign up as a: \n";
    cout << "=================================\n";
    cout << "1. Teacher\n";
    cout << "=================================\n";

    cout << "Enter username: ";
    // cin.ignore();
    cin.getline(tmp, 100, '\n');

    unsigned le = strlen(tmp) + 1;
    username = new char[le];
    strcpy(username, tmp);

    strcat(sTmp, username);
    strcat(sTmp,  ".txt");

    cout << "Enter password: ";
    // cin.ignore();
    cin.getline(tmp, 1000, '\n');

    le = strlen(tmp) + 1;
    password = new char[le];
    strcpy(password, tmp);

    if (!isValidUsername(username, check)) {
        return mainMenu();
    }

    char name[] = "User";
    createFolder(name);

    FILE *fi, * fc;

    fc = fopen(sTmp, "r");
    if (fc == NULL) ;
    else {
        cout << "This user name has been already exist!\n";
        cout << "Please choose another username!!\n";
        system("pause");
        delete password;
        delete username;
        signUp();
        return;
    }

    // Them tai khoan vao folder luu tru

    fi = fopen(sTmp, "w");
    fprintf(fi, "%s\n", username);
    fprintf(fi, "%s\n", password);
    if (check) {
        fprintf(fi, "1\n");
    } else fprintf(fi, "0\n");
    fclose(fi);

    cout << "You signed in successfully!!\n";
    cout << "Now you can log in with your account\n";
    system("pause");

    fclose(fi);

    delete password;
    delete username;

    mainMenu();
}


void login() {
    system("cls");
    char username[1000], password[1000];

    cout << "LOG IN PAGE!!\n\n";

    cout << "Enter your username: "; 
    cin.ignore();
    cin.getline(username, 1000, '\n');
    cout << username << endl;

    cout << "Enter your password: ";
    // cin.ignore();
    cin.getline(password, 1000, '\n');
    cout << password << endl;

    char tmp[1000] = "User\\";
    strcat(tmp, username);
    strcat(tmp, ".txt");

    char passTmp[1000] = {0}, usernameTmp[1000] = {0};

    FILE *fi = fopen(tmp, "r");
    if (fi == NULL) {
        cout << "This account is not exist!!\n";
        cout << "What do you want to do now?\n";
        system("pause");
        return mainMenu();
    }

    fscanf(fi, "%s\n%s\n", usernameTmp, passTmp);

    if (strcmp(password, passTmp) != 0) {
        cout << "You entered wrong password!!\n";
        system("pause");
        cout << "What do you want to do now?\n";
        fclose(fi);
        return mainMenu();
    }

    fclose(fi);

    cout << "Log in successfully !!\n\n";
    cout << "Make a profile function here!!\n";
    system("pause");

}