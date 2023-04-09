#include "main.h"
#include "studentInAClass.h"
#include "removeAStudent.h"
#include "Add1StToClass.h"
#include "viewScoreboardOfClass.h"
#include "SYmenu.h"
#include "profile.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

void classMenu(string username, schoolYear * headSY, schoolYear * curSY, string nameClass)
{
    Class *curClass = curSY -> Classes;

    while (curClass -> name != nameClass) {
        curClass = curClass -> next;
    }
        system("cls");
        int move; 
        ifstream fin;

        cout << "\tClass Menu: " << curClass -> name << endl;
        cout << "1. Add students of class (by importing file)\n";
        cout << "2. View students in class\n";
        cout << "3. Add 1 student\n";
        cout << "4. Remove 1 student\n";
        cout << "5. View Scoreboard of this class\n";
        cout << "0. Return to previous menu\n";
        cout << "=========================\n";
        
        do {
            cout << "Pls enter your move: ";
            cin >> move;      
            switch (move)
            {
                case 1:
                    inputStudentsToClass(curSY, curClass);             
                    break;
                case 2: 
                    displayListOfStudents(curSY -> name, curClass -> name);
                    break;
                case 3:
                    add1StToClass(curClass -> Students, curSY, curClass);
                    break;
                case 4:
                    removeAStudent(curSY, curClass);
                    break;
                case 5:
                    viewClassScoreboard(curSY, curClass);
                    break;
                case 0:
                    return SYMenu(username, headSY, curSY);
                    break;
                default:
                    cout << "You've entered wrong move\n";
                    cout << "Pls enter your move again: \n";
                    break;
            }  
            system("pause");
            classMenu(username, headSY, curSY, nameClass);            
        } while (move < 0 || move > 5);
}