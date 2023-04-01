#include "importScoreboard.h"
// #include <format>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

void importScoreBoard(Course* pCourse)
{
	string pathOfScoreboard;
	ifstream fin;
	cout << "Enter the path of the scoreboard: ";
	cin >> pathOfScoreboard;
	fin.open(pathOfScoreboard);

	while (!fin.eof()) {
		string temp, No;
		getline(fin, No, ',');
		getline(fin, temp, ',');
		string path = "./profile/" + temp + ".txt";
		string schoolYear;
		string stClass;
		ifstream profileSt(path);
		getline(profileSt, schoolYear);
		getline(profileSt, schoolYear);
		getline(profileSt, schoolYear);
		getline(profileSt, stClass);
		profileSt.close();

        string path2 = schoolYear + "//" + stClass + "//" + temp + "//" + char(pCourse -> courseID + 48) + ".txt";
        ofstream fout(path2);

		// ofstream fout(format("./{}/{}/{}/{}.txt", schoolYear, stClass, temp, pCourse->courseID));
		fout << No << "," << temp << ",";
		getline(fin, temp, ',');
		fout << temp << ",";
		getline(fin, temp, ',');
		fout << temp << ",";
		getline(fin, temp, ',');
		fout << temp << ",";
		getline(fin, temp, ',');
		fout << temp << ",";
		getline(fin, temp);
		fout << temp;
		fout.close();
	}
	fin.close();
}