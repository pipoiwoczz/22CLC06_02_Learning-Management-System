﻿#include "guiView.h"
#include <iostream>
#include "viewStudentScoreboard.h"
using namespace std;

void viewSchoolYear(string username) {
	system("cls");
	wstring temp = L"█▓▒░░AVAILABLE SCHOOL YEAR░░▒▓█";
	printCenterCharacters(temp, Color::light_red, Color::bright_white, 2, My_Windows);
	ifstream ifs("SY.txt");
	if (!ifs.is_open() || ifs.eof()) {
		ifs.close();
		printCenterCharacters(L"NO SCHOOL YEAR AVAILABLE", Color::black, Color::bright_white, 3, My_Windows);
		printCenterCharacters(L"Press any key to return to main menu", Color::black, Color::bright_white, 0, My_Windows);
		getKey();
		return ProfileMenuPage(username);
	}
	else {
		string temp;
		int i = 4;
		while (!ifs.eof()) {
			getline(ifs, temp);
			if (temp == "") {
				break;
			}
			printCenterCharacters(wstring(temp.begin(), temp.end()), Color::black, Color::bright_white, i, My_Windows);
			i += 2;
		}

		printCenterCharacters(L"Press any key to back to previous menu", Color::purple, Color::bright_white, 0, My_Windows);
		getKey();
		return ProfileMenuPage(username);
		ifs.close();
	}
}

void chooseSchoolYear(string username) {
	system("cls");
	wstring temp = L"█▓▒░░CHOOSE SCHOOL YEAR░░▒▓█";
	printCenterCharacters(temp, Color::light_red, Color::bright_white, 2, My_Windows);
	printCenterCharacters(L"All Available School Year", Color::light_red, Color::bright_white, 4, My_Windows);
	ifstream ifs("SY.txt");
	if (!ifs.is_open() || ifs.eof()) {
		ifs.close();
		printCenterCharacters(L"NO SCHOOL YEAR AVAILABLE", Color::black, Color::bright_white, 6, My_Windows);
		printCenterCharacters(L"Press any key to return to previous menu", Color::black, Color::bright_white, 0, My_Windows);
		getKey();
		return ProfileMenuPage(username);
	}
	else {
		string temp;
		int i = 6;
		while (!ifs.eof()) {
			getline(ifs, temp);
			if (temp == "") {
				break;
			}
			printCenterCharacters(wstring(temp.begin(), temp.end()), Color::black, Color::bright_white, i, My_Windows);
			i += 2;
		}
		printCharacter(L"Press ESC to return to main menu", { 0, 0 }, Color::black, Color::bright_white);
		printCharacter(L"Press F1 to back to previous menu", { short(My_Windows.Right - 34) , 0 }, Color::black, Color::bright_white);
		ifs.close();

		printCharacter(L"Input schoolyear here", { 45, short(i + 2) }, Color::blue, Color::bright_white);
		drawBox(i + 3);
		gotoxy(46, i + 4);
		string input;
		input = getMenuString();
		if (input == "ESC") {
			return mainmenuOpt();
		}
		if (input == "F1") {
			return ProfileMenuPage(username);
		}
		ifs.open("SY.txt");
		while (getline(ifs, temp)) {
			if (temp == input) {
				ifs.close();
				printCenterCharacters(L"School year is available", Color::green, Color::bright_white, i + 7, My_Windows);
				printCenterCharacters(L"Press any key to continue...", Color::green, Color::bright_white, 0, My_Windows);
				_getch();
				return SYMenuPage(username, input);
			}
		}
		ifs.close();
		printCenterCharacters(L"School year is not available", Color::red, Color::bright_white, i + 7, My_Windows);
		printCenterCharacters(L"Press any key to enter again...", Color::green, Color::bright_white, 0, My_Windows);
		printCharacter(L"Press F1 to return to previous menu", { short(My_Windows.Right - 32), 0 }, Color::black, Color::bright_white);
		int key = _getch();
		if (key == 59) {
			return ProfileMenuPage(username);
		}
		if (key == 27)
			return mainmenuOpt();

		return chooseSchoolYear(username);
	}
}

void viewAndChooseSemesterPage(string username, string SY) {
	system("cls");
	wstring temp = L"█▓▒░░CHOOSE SEMESTER░░▒▓█";
	printCenterCharacters(temp, Color::light_red, Color::bright_white, 2, My_Windows);


	short idx = 6;
	short line = 0;
	bool Se[3] = { false, false, false };
	bool flag = false;
	string filename = SY + "//";
	ifstream ifs;
	ifs.open(SY + "/1/info.txt");
	if (ifs.is_open() && !ifs.eof()) {
		flag = true;
		printCenterCharacters(L"Spring", Color::black, Color::bright_white, idx, My_Windows);
		idx += 2;
		Se[0] = true;
		line++;
	}
	ifs.close();
	ifs.open(SY + "/2/info.txt");
	if (ifs.is_open() && !ifs.eof()) {
		flag = true;
		printCenterCharacters(L"Summer", Color::black, Color::bright_white, idx, My_Windows);
		idx += 2;
		Se[1] = true;
		line++;
	}
	ifs.close();
	ifs.open(SY + "/3/info.txt");
	if (ifs.is_open() && !ifs.eof()) {
		flag = true;
		printCenterCharacters(L"Autumn", Color::black, Color::bright_white, idx, My_Windows);
		idx += 2;
		Se[2] = true;
		line++;
	}
	ifs.close();

	if (!flag) {
		printCenterCharacters(L"NO SEMESTER AVAILABLE", Color::red, Color::bright_white, 4, My_Windows);
		printCenterCharacters(L"PLEASE CREATE A SEMESTER FIRST", Color::red, Color::bright_white, 6, My_Windows);
		printCenterCharacters(L"Press any key to return to previous menu", Color::black, Color::bright_white, 0, My_Windows);
		int key = getKey();
		if (key == 27)
			return mainmenuOpt();
		return SYMenuPage(username, SY);
	}

	printCenterCharacters(L"All Available Semester", Color::light_red, Color::bright_white, 4, My_Windows);
	printCharacter(L"Press ESC to return to main menu", { 0, 0 }, Color::black, Color::bright_white);
	printCharacter(L"Press F1 to return to previous menu", { short(My_Windows.Right - 36), 0 }, Color::black, Color::bright_white);

	printCharacter(L"Enter your choice here", { 45, short(idx + 2) }, Color::blue, Color::bright_white);
	gotoxy(45 + 23, idx + 2);

	string input = getMenuString();
	if (input == "ESC")
		return mainmenuOpt();
	if (input == "F1")
		return SYMenuPage(username, SY);
	if (input == "Spring" && Se[0]) {
		//ofstream ofs("curTime.txt");
		//ofs << SY << endl << 1;
		//ofs.close();
		return SemesterMenuPage(username, SY, short(1));
	}
	if (input == "Summer" && Se[1]) {
		//ofstream ofs("curTime.txt");
		//ofs << SY << endl << 2;
		//ofs.close();
		return SemesterMenuPage(username, SY, short(2));
	}
	if (input == "Autumn" && Se[2]) {
		//ofstream ofs("curTime.txt");
		//ofs << SY << endl << 3;
		//ofs.close();
		return SemesterMenuPage(username, SY, short(3));
	}
	else {
		printCenterCharacters(L"Semester is not available", Color::red, Color::bright_white, idx + 4, My_Windows);
		printCenterCharacters(L"Press any key to enter again...", Color::green, Color::bright_white, 0, My_Windows);
		int key = getKey();
		if (key == 59) {
			return SYMenuPage(username, SY);
		}
		if (key == 27)
			return mainmenuOpt();
		return viewAndChooseSemesterPage(username, SY);
	}
}

void viewAndChooseClassPage(string username, string SY) {
	system("cls");
	wstring temp = L"█▓▒░░CHOOSE CLASS░░▒▓█";
	printCenterCharacters(temp, Color::light_red, Color::bright_white, 2, My_Windows);
	string curSY, curSeason;
	ifstream ifs("SY.txt");
	ifs >> curSY;
	ifs.close();
	// CASE NO CLASS AVAILABLE
	ifs.open(curSY + "/class.txt");
	if (!ifs.is_open() || ifs.eof()) {
		printCharacter(L"Press ESC to return to main menu", { 0, 0 }, Color::black, Color::bright_white);
		printCenterCharacters(L"NO CLASS AVAILABLE", Color::red, Color::bright_white, 4, My_Windows);
		printCenterCharacters(L"PLEASE CREATE A CLASS FIRST", Color::red, Color::bright_white, 6, My_Windows);
		printCenterCharacters(L"Press any key to return to previous menu", Color::green, Color::bright_white, 0, My_Windows);
		int key = getKey();
		if (key == 27)
			return mainmenuOpt();
		return SYMenuPage(username, SY);
	}
	else { 	// CASE CLASS AVAILABLE
		string tmp;
		short idx = 6;
		printCenterCharacters(L"ALL AVAILABLE CLASS", Color::light_red, Color::bright_white, 4, My_Windows);
		printCharacter(L"Press ESC to return to main menu", { 0, 0 }, Color::black, Color::bright_white);
		printCharacter(L"Press F1 to return to previous menu", { short(My_Windows.Right - 36), 0 }, Color::black, Color::bright_white);
		while (!ifs.eof()) {
			getline(ifs, tmp);
			if (tmp == "") break;
			printCenterCharacters(wstring(tmp.begin(), tmp.end()), Color::black, Color::bright_white, idx, My_Windows);
			idx += 2;
		}
		ifs.close();

		printCharacter(L"Enter your choice here: ", { 45, short(idx + 2) }, Color::blue, Color::bright_white);
		gotoxy(45 + 23 + 1, idx + 2);
		string input = getStringInput();
		if (input == "ESC")
			return mainmenuOpt();
		ifstream ifs;
		ifs.open(curSY + "/class.txt");
		while (getline(ifs, tmp)) {
			if (tmp == input) {
				printCenterCharacters(L"Class is available", Color::green, Color::bright_white, idx + 4, My_Windows);
				printCenterCharacters(L"Press any key to enter class menu...", Color::purple, Color::bright_white, 0, My_Windows);
				getKey();
				return ClassMenuPage(username, SY, input);
			}
		}
		ifs.close();
		printCenterCharacters(L"Class is not available", Color::red, Color::bright_white, idx + 4, My_Windows);
		printCenterCharacters(L"Press any key to enter again...", Color::purple, Color::bright_white, 0, My_Windows);

		int key = getKey();
		if (key == 59) {
			return SYMenuPage(username, SY);
		}
		if (key == 27)
			return mainmenuOpt();
		return viewAndChooseClassPage(username, SY);
	}
}

struct courseInThisSem {
	string ID;
	courseInThisSem* next = nullptr;
};

bool checkExist(courseInThisSem* head, string value) {
	while (head) {
		if (head->ID == value) return true;
		head = head->next;
	}
	return false;
}

void insertCourseAtBegin(courseInThisSem*& head, string value) {
	courseInThisSem* temp = new courseInThisSem;
	temp->ID = value;
	temp->next = head;
	head = temp;
}

void deleteCourseLL(courseInThisSem*& head) {
	courseInThisSem* temp = head;
	while (head) {
		head = head->next;
		delete temp;
		temp = head;
	}
}

void viewScoreboard(string username, string SY, string className) {
	system("cls");
	wstring temp[3];
	temp[0] = L"▒█▀▀▀█ ▒█▀▀█ ▒█▀▀▀█ ▒█▀▀█ ▒█▀▀▀ ▒█▀▀█ ▒█▀▀▀█ ░█▀▀█ ▒█▀▀█ ▒█▀▀▄";
	temp[1] = L"░▀▀▀▄▄ ▒█░░░ ▒█░░▒█ ▒█▄▄▀ ▒█▀▀▀ ▒█▀▀▄ ▒█░░▒█ ▒█▄▄█ ▒█▄▄▀ ▒█░▒█";
	temp[2] = L"▒█▄▄▄█ ▒█▄▄█ ▒█▄▄▄█ ▒█░▒█ ▒█▄▄▄ ▒█▄▄█ ▒█▄▄▄█ ▒█░▒█ ▒█░▒█ ▒█▄▄▀";
	for (int i = 0; i < 3; i++)
	{
		printCenterCharacters(temp[i], Color::light_green, Color::bright_white, i + 2, My_Windows);
		Sleep(100);
	}
	printCharacter(L"Press ESC to back to main menu", { 0, 0 }, Color::black, Color::bright_white);
	Sleep(100);
	

	string sy;
	ifstream syfile("./SY.txt");
	getline(syfile, sy);
	syfile.close(); 

	string title1, title2;
	ifstream ti("curTime.txt");
	ti >> title1 >> title2;
	ti.close();

	printCenterCharacters(wstring(className.begin(), className.end()) + L", School Year: " + wstring(title1.begin(), title1.end()) + L", Semester: " + wstring(title2.begin(), title2.end()), Color::light_green, Color::bright_white, 5, My_Windows);
	Sleep(200);

	ifstream ifs, student;
	string course, ID, name, total, final, GPA, curSem, curSY;

	ifs.open("./" + sy + "/" + className + "/student.txt");
	// Check if this file have nothing or does not exist
	if (ifs.eof() || !ifs.is_open()) {
		printCenterCharacters(L"THIS CLASS HAS NO STUDENT NOW", Color::red, Color::bright_white, 7, My_Windows);
		printCenterCharacters(L"Press any key to back to previous menu.", Color::purple, Color::bright_white, 9, My_Windows);
		int key = getKey();
		if (key == 27)
			return mainmenuOpt();
		return ClassMenuPage(username, SY, className);
	}
	ifs.close();

	short curLine = 7;

	ifs.open("./curTime.txt");
	getline(ifs, curSY); // Current year
	getline(ifs, curSem); // Current Semester
	ifs.close();

	courseInThisSem* head = nullptr; // This linked list is used to 
	// Open the file contain list of student's ID in a class
	ifs.open("./" + sy + "/" + className + "/student.txt");
	while (!ifs.eof()) {
		getline(ifs, ID); // Student's ID
		// Open the file saving courses that a student will learn in this semester
		student.open("./" + sy + "/" + className + "/" + ID + "/" + curSem + "_" + curSY + ".txt"); // <sem>_<SY>.txt
		if (student.is_open()) { // if this student does not learn in this sem -> do not do this code segment
			getline(student, course); // GPA in this semester -> no need here
			getline(student, course); // credit -> no need either
			while (!student.eof()) {
				getline(student, course, ','); // get a course's ID
				if (!checkExist(head, course)) insertCourseAtBegin(head, course);
				getline(student, course); // class of the course -> no need here
			}
		}
		student.close();
	}
	ifs.close();

	// Now we have the linked list of courses
	// Print out first line to the screen
	gotoxy(35, curLine + 2);
	short i = 0;
	cout << left << setw(34) << "Name"; // the name of the column that represents student's name
	courseInThisSem* cur = head; // A temp pointer used to traverse
	while (cur) {
		gotoxy(35 + 34 + i * 10, curLine + 2);
		cout << setw(10) << cur->ID; // course ID
		cur = cur->next;
		i++;
	}
	cout << setw(8) << "GPA" << setw(12) << "Overall GPA" << endl;
	curLine++;

	// 2nd, 3rd, 4th, ... line
	ifs.open("./" + sy + "/" + className + "/student.txt");
	// Check if this file have nothing or does not exist
	while (!ifs.eof()) {
		gotoxy(35, curLine + 2);
		getline(ifs, ID); // Student's ID
		student.open("./profile/" + ID + ".txt");
		string fName, lName;
		for (int i = 0; i < 4; i++)
			getline(student, fName);

		getline(student, fName, ',');
		getline(student, lName, '\n');
		name = lName + " " + fName;
		cout << left << setw(34) << name; // Prints out student name
		student.close();

		cur = head; // refresh the "cur" variable
		while (cur) {
			student.open("./" + sy + "/" + className + "/" + ID + "/" + cur->ID + ".txt");
			// If this student does not enroll in this course, print out x
			if (!student.is_open()) cout << setw(10) << "x";
			else {
				getline(student, total, ',');
				getline(student, final, ',');
				cout << setw(10) << total; // Total mark
			}
			student.close();

			cur = cur->next;
		}

		student.open("./" + sy + "/" + className + "/" + ID + "/" + curSem + "_" + curSY + ".txt");
		getline(student, GPA);
		if (!student.is_open()) cout << setw(8) << 0;
		else cout << setw(8) << GPA; // GPA in this sem
		student.close();

		student.open("./" + sy + "/" + className + "/" + ID + "/total.txt");
		getline(student, GPA);
		if (!student.is_open()) cout << setw(12) << 0 << endl;
		else cout << setw(12) << GPA << endl; // OVerall GPA
		student.close();
		curLine++;
	}
	ifs.close();

	
	deleteCourseLL(head); // Delete linked list
	printCenterCharacters(L"--------------------------------------------------", Color::purple, Color::bright_white, curLine + 3, My_Windows);
	printCenterCharacters(L"Press any key to back to previous menu.", Color::green, Color::bright_white, curLine + 4, My_Windows);
	printCenterCharacters(L"Press F1 to choose a Semester view scoreboard.", Color::green, Color::bright_white, curLine + 5, My_Windows);

	int key = getKey();
	if (key == 27)
		return mainmenuOpt();
	if (key == 59) {
		string schoolyear, semester;
		gotoxy(45, curLine + 7);
		cout << "Enter School Year: "; 
		schoolyear = getStringInput();
		if (schoolyear == "ESC")
			return mainmenuOpt();
		gotoxy(45, curLine + 8);
		cout << "Enter Semester(1, 2 or 3): ";
		semester = getStringInput();
		if (semester == "ESC")
			return mainmenuOpt();
		ifs.open(sy + "/" + className + "/student.txt");
		string id;
		getline(ifs, id);
		ifs.close();
		ifs.open(sy + "/" + className + "/" + id + "/" + semester + "_" + schoolyear + ".txt");
		if (!ifs.is_open()) {
			printCenterCharacters(L"THIS SEMESTER DOESN'T HAVE SCOREBOARD.", Color::red, Color::bright_white, curLine + 10, My_Windows);
			getKey();
			return viewScoreboard(username, SY, className);
		}
		ifs.close();

		return viewScoreboardClassChooseSem(username, SY, className, schoolyear, semester);
	}
	return ClassMenuPage(username, SY, className);
}


void viewListOfStudentsInClass(string username, string SY, string classID) {
	system("cls");
	printCharacter(L"Press ESC to back to main menu", { 0, 0 }, Color::black, Color::bright_white);
	printCenterCharacters(L"<<<< CLASS " + wstring(classID.begin(), classID.end()) + L" >>>>", Color::light_green, Color::bright_white, 2, My_Windows);

	string sy;
	ifstream syFile("./SY.txt");
	getline(syFile, sy);
	syFile.close();

	string path = sy + "//" + classID + "//" + "student.txt";
	string tmp;
	int no = 1;

	ifstream ifs((path).c_str());
	short line = 8;
	if (!ifs.is_open()) {
		printCenterCharacters(L"----------------------THIS CLASS HAS NO STUDENT------------------------", Color::purple, Color::bright_white, 4, My_Windows);
		printCenterCharacters(L"Press any key to back to previous menu", Color::green, Color::bright_white, 0, My_Windows);
		int key = getKey();
		if (key == 27)
			return mainmenuOpt();
		return ClassMenuPage(username, SY, classID);
	}
	else {
		printCenterCharacters(L"----------------------List of Students------------------------", Color::purple, Color::bright_white, 4, My_Windows);
		gotoxy(28, 6);
		std::cout << left << setw(3) << "No" << setw(10) << "MSSV" << setw(34) << "Full Name" << setw(9) << "Gender" << setw(13) << "DoB" << setw(14) << "Social ID" << endl << endl;
		string mssv;
		while (getline(ifs, mssv)) {
			gotoxy(28, line);
			line++;
			std::cout << setw(3) << no;
			++no;
			ifstream fin(("profile//" + mssv + ".txt").c_str());
			if (fin.is_open()) {
				string tmp;
				getline(fin, tmp);
				std::cout << left << setw(10) << tmp;
				getline(fin, tmp);
				getline(fin, tmp);
				getline(fin, tmp);
				getline(fin, tmp, ',');
				string tmp2;
				getline(fin, tmp2);
				tmp2 = tmp2 + " " + tmp;
				std::cout << setw(34) << tmp2;
				getline(fin, tmp);
				std::cout << setw(9) << tmp;
				getline(fin, tmp);
				std::cout << setw(13) << tmp;
				getline(fin, tmp);
				std::cout << setw(14) << tmp << endl;
			}
			fin.close();
		}
	}
	ifs.close();
	std::cout << endl << endl;
	printCenterCharacters(L"Press any key to back to previous menu", Color::green, Color::bright_white, line + 2, My_Windows);
	int key = getKey();
	if (key == 27)
		return mainmenuOpt();
	return ClassMenuPage(username, SY, classID);

}

void viewAndChooseCourse(string username, string SY, int season) {
	system("cls");
	printCharacter(L"Press ESC to back to main menu", { 0, 0 }, Color::black, Color::bright_white);
	printCharacter(L"Press F1 to back to previous menu", { short(My_Windows.Right - 34), 0 }, Color::black, Color::bright_white);
	printCenterCharacters(L"█▓▒░░CHOOSE COURSE░░▒▓█", Color::light_red, Color::bright_white, 2, My_Windows);
	if (season == 1)
		printCenterCharacters(L"<<<<SPRING>>>>", Color::light_blue, Color::bright_white, 3, My_Windows);
	if (season == 2)
		printCenterCharacters(L"<<<<SUMMER>>>>", Color::light_blue, Color::bright_white, 3, My_Windows);
	if (season == 3)
		printCenterCharacters(L"<<<<AUTUMN>>>>", Color::light_blue, Color::bright_white, 3, My_Windows);
	string path = SY + "//" + to_string(season) + "/" + "course.txt";
	string tmp;
	int no = 1;
	ifstream ifs((path).c_str());
	short line = 8;
	if (!ifs.is_open() || ifs.eof()) {
		ifs.close();
		printCenterCharacters(L"----------------------THIS SEMESTER HAS NO COURSE------------------------", Color::purple, Color::bright_white, 5, My_Windows);
		printCenterCharacters(L"Press any key to back to previous menu", Color::green, Color::bright_white, 0, My_Windows);
		int key = getKey();
		if (key == 27)
			return mainmenuOpt();
		return SemesterMenuPage(username, SY, season);
	}
	else {
		printCenterCharacters(L"----------------------List of Courses------------------------", Color::purple, Color::bright_white, 5, My_Windows);
		while (getline(ifs, tmp)) {
			if (tmp != "" && tmp != "\n")
			{
				printCenterCharacters(wstring(tmp.begin(), tmp.end()), Color::purple, Color::bright_white, line, My_Windows);
				line += 2;
			}
		}

		ifs.close();
		printCharacter(L"Enter your choice here: ", { 45, short(line + 3) }, Color::blue, Color::bright_white);
		gotoxy(45 + 25, line + 3);
		string course = getMenuString();
		if (course == "ESC")
			return mainmenuOpt();
		if (course == "F1")
			return SemesterMenuPage(username, SY, season);
		bool flag = false;
		ifs.open(path);
		while (getline(ifs, tmp)) {
			if (tmp == course) {
				flag = true;
				break;
			}
		}
		ifs.close();
		if (!flag) {
			printCenterCharacters(L"THE COURSE YOU CHOOSED IS NOT AVAILABLE", Color::red, Color::bright_white, line + 5, My_Windows);
			printCenterCharacters(L"Press any key to enter again or press F1 to back to previous menu", Color::red, Color::bright_white, line + 7, My_Windows);
			int key = getKey();
			if (key == 27)
				return mainmenuOpt();
			if (key == 59)
				return SemesterMenuPage(username, SY, season);
			return viewAndChooseCourse(username, SY, season);
		}
		else {
			printCenterCharacters(L"YOUR CHOICE IS AVAILABLE", Color::green, Color::bright_white, line + 7, My_Windows);
			printCenterCharacters(L"Press any key to continue with Course Management or press F1 to back to previous menu", Color::green, Color::bright_white, line + 7, My_Windows);
			int key = getKey();
			if (key == 27)
				return mainmenuOpt();
			if (key == 59)
				return SemesterMenuPage(username, SY, season);
			return CourseMenuPage(username, SY, season, course);
		}
	}
}

void viewCourseInformation(string username, string SY, int season, string courseID) {
	system("cls");
	printCharacter(L"Press ESC to back to main menu", { 0, 0 }, Color::black, Color::bright_white);
	printCenterCharacters(L"COURSE INFORMATION", Color::aqua, Color::bright_white, 2, My_Windows);
	printCenterCharacters(wstring(courseID.begin(), courseID.end()), Color::light_aqua, Color::bright_white, 3, My_Windows);

	// get Course info
	string courseName, courseCre;
	ifstream ifs(SY + "/" + to_string(season) + "/" + courseID + "/info.txt");
	getline(ifs, courseName);
	getline(ifs, courseName);
	getline(ifs, courseCre);
	ifs.close();

	printCharacter(L"Course ID: ", { 45, 6 }, Color::blue, Color::bright_white);
	printCharacter(wstring(courseID.begin(), courseID.end()), { 45 + 12, 6 }, Color::blue, Color::bright_white);
	printCharacter(L"Course Name: ", { 45, 8 }, Color::blue, Color::bright_white);
	printCharacter(wstring(courseName.begin(), courseName.end()), { 45 + 14, 8 }, Color::blue, Color::bright_white);
	printCharacter(L"Course Credit: ", { 45, 10 }, Color::blue, Color::bright_white);
	printCharacter(wstring(courseCre.begin(), courseCre.end()), { 45 + 16, 10 }, Color::blue, Color::bright_white);

	// print all course classes info
	ifs.open(SY + "/" + to_string(season) + "/" + courseID + "/class.txt");
	if (!ifs.is_open() || ifs.eof()) {
		ifs.close();
		printCenterCharacters(L"NO COURSE CLASS NOW", Color::green, Color::bright_white, 13, My_Windows);
		printCenterCharacters(L"Press any key to back to previous menu", Color::green, Color::bright_white, 0, My_Windows);
		int key = getKey();
		if (key == 27)
			return mainmenuOpt();
		return CourseMenuPage(username, SY, season, courseID);
	}
	else {
		short idx = 15;
		printCenterCharacters(L"ALL COURSE CLASS INFORMATION", Color::green, Color::bright_white, 13, My_Windows);
		string className, teacherName, dayOfWeek, session, numberOfStudent;
		while (getline(ifs, className)) {
			if (className != "" && className != "\n")
			{
				string path = SY + "/" + to_string(season) + "/" + courseID + "/" + className + "/info.txt";
				ifstream fin(path);
				getline(fin, teacherName); // courseID
				getline(fin, teacherName); // course Name
				getline(fin, teacherName); // className
				getline(fin, teacherName); // teacher Name
				getline(fin, courseCre); // course Cre
				getline(fin, numberOfStudent); // number of students
				getline(fin, dayOfWeek); // day of week
				getline(fin, session); // session
				fin.close();

				printCharacter(L"Class Name: ", { 60, ++idx }, Color::blue, Color::bright_white);
				printCharacter(wstring(className.begin(), className.end()), { 60 + 13, idx }, Color::black, Color::bright_white);
				printCharacter(L"Teacher Name: ", { 45, ++idx }, Color::blue, Color::bright_white);
				printCharacter(wstring(teacherName.begin(), teacherName.end()), { 45 + 15, idx }, Color::black, Color::bright_white);
				printCharacter(L"Number Of Students: ", { 45, ++idx }, Color::blue, Color::bright_white);
				printCharacter(wstring(numberOfStudent.begin(), numberOfStudent.end()), { 45 + 21, idx }, Color::black, Color::bright_white);
				printCharacter(L"Day of Week: ", { 45, ++idx }, Color::blue, Color::bright_white);
				printCharacter(wstring(dayOfWeek.begin(), dayOfWeek.end()), { 45 + 14, idx }, Color::black, Color::bright_white);
				printCharacter(L"Session: ", { 45, ++idx }, Color::blue, Color::bright_white);
				printCharacter(wstring(session.begin(), session.end()), { 45 + 10, idx }, Color::black, Color::bright_white);
				idx += 2;
			}
		}
		printCenterCharacters(L"Press any key to back to previous menu", Color::green, Color::bright_white, 0, My_Windows);
		int key = getKey();
		if (key == 27)
			return mainmenuOpt();
		return CourseMenuPage(username, SY, season, courseID);
	}
}


void viewListOfStudentInACourse(string username, string SY, short season, string courseID) {
	system("cls");
	printCharacter(L"Press ESC to back to main menu", { 0, 0 }, Color::black, Color::bright_white);
	printCenterCharacters(L"<<<< COURSE " + wstring(courseID.begin(), courseID.end()) + L" >>>>", Color::light_green, Color::bright_white, 2, My_Windows);

	string path = SY + "//" + to_string(season) + "//" + courseID + "/class.txt";
	string tmp;
	short no = 1;

	ifstream ifs(path);
	short line = 8;

	if (!ifs.is_open()) {
		printCenterCharacters(L"----------------------THIS CLASS HAS NO STUDENT------------------------", Color::purple, Color::bright_white, 4, My_Windows);
		printCenterCharacters(L"Press any key to back to previous menu", Color::green, Color::bright_white, 0, My_Windows);
		int key = getKey();
		if (key == 27)
			return mainmenuOpt();
		return CourseMenuPage(username, SY, season, courseID);
	}
	else {
		printCenterCharacters(L"----------------------List of Students------------------------", Color::purple, Color::bright_white, 4, My_Windows);
		gotoxy(40, 6);
		std::cout << left << setw(4) << "NO" << setw(11) << "MSSV" << setw(34) << "Full Name" << "Course Class" << endl;
		while (getline(ifs, tmp)) {
			if (tmp != "\n" && tmp != "") {
				string classPath = SY + "/" + to_string(season) + "/" + courseID + "/" + tmp + "/listStud.txt";
				string stID, stName;
				ifstream fin(classPath);
				if (fin.is_open() && !fin.eof()) {
					getline(fin, stID, ',');
					getline(fin, stName);
					while (getline(fin, stID, ',') && getline(fin, stName)) {
						gotoxy(40, line);
						std::cout << left << setw(4) << no << setw(11) << stID << setw(34) << stName << tmp << endl;
						line++;
						no++;
					}
					fin.close();
				}
			}
		}
		ifs.close();
		printCenterCharacters(L"Press any key to back to previous menu", Color::green, Color::bright_white, line + 2, My_Windows);
		int key = getKey();
		if (key == 27)
			return mainmenuOpt();
		return CourseMenuPage(username, SY, season, courseID);
	}
}


void viewScoreboardOfACourse(string username, string SY, short season, string courseID) {
	system("cls");
	wstring temp[3];
	temp[0] = L"▒█▀▀█ ▒█▀▀▀█ ▒█░▒█ ▒█▀▀█ ▒█▀▀▀█ ▒█▀▀▀    ▒█▀▀▀█ ▒█▀▀█ ▒█▀▀▀█ ▒█▀▀█ ▒█▀▀▀ ▒█▀▀█ ▒█▀▀▀█ ░█▀▀█ ▒█▀▀█ ▒█▀▀▄";
	temp[1] = L"▒█░░░ ▒█░░▒█ ▒█░▒█ ▒█▄▄▀ ░▀▀▀▄▄ ▒█▀▀▀    ░▀▀▀▄▄ ▒█░░░ ▒█░░▒█ ▒█▄▄▀ ▒█▀▀▀ ▒█▀▀▄ ▒█░░▒█ ▒█▄▄█ ▒█▄▄▀ ▒█░▒█";
	temp[2] = L"▒█▄▄█ ▒█▄▄▄█ ░▀▄▄▀ ▒█░▒█ ▒█▄▄▄█ ▒█▄▄▄    ▒█▄▄▄█ ▒█▄▄█ ▒█▄▄▄█ ▒█░▒█ ▒█▄▄▄ ▒█▄▄█ ▒█▄▄▄█ ▒█░▒█ ▒█░▒█ ▒█▄▄▀";
	for (int i = 0; i < 3; i++)
	{
		printCenterCharacters(temp[i], Color::light_green, Color::bright_white, i + 2, My_Windows);
		Sleep(100);
	}
	printCharacter(L"Press ESC to back to main menu", { 0, 0 }, Color::black, Color::bright_white);
	Sleep(100);
	printCenterCharacters(wstring(courseID.begin(), courseID.end()), Color::light_green, Color::bright_white, 5, My_Windows);
	Sleep(200);
	string path;
	ifstream courseClass;

	path = "./" + SY + "/" + to_string(season) + "/" + courseID + "/class.txt";

	// View list of classes in a course
	string cClass, chosenClass;
	short line = 7;
	courseClass.open(path);
	while (!courseClass.eof()) {
		getline(courseClass, cClass);
		printCenterCharacters(L"Class " + wstring(cClass.begin(), cClass.end()), Color::green, Color::bright_white, line, My_Windows);
		line++;
		ifstream ifs;
		ifs.open("./" + SY + "/" + to_string(season) + "/" + courseID + "/" + cClass + "/scoreboard.txt");
		if (ifs.is_open()) {
			gotoxy(35, line);
			std::cout << left << setw(5) << "No" << setw(10) << "ID";
			std::cout << left << setw(22) << "Last name" << setw(12) << "First Name";
			std::cout << left << setw(8) << "Total" << setw(8) << "Final" << setw(8) << "Midterm" << setw(8) << "Other" << endl;
			line++;
			while (!ifs.eof()) {
				string tmp;
				gotoxy(35, line);
				getline(ifs, tmp, ','); // Ordinal number
				std::cout << left << setw(5) << tmp;
				getline(ifs, tmp, ','); // ID
				std::cout << left << setw(10) << tmp;
				getline(ifs, tmp, ','); // Last Name
				std::cout << left << setw(22) << tmp;
				getline(ifs, tmp, ','); // First Name
				std::cout << left << setw(12) << tmp;
				getline(ifs, tmp, ','); // Total
				std::cout << left << setw(8) << tmp;
				getline(ifs, tmp, ','); // Final 
				std::cout << left << setw(8) << tmp;
				getline(ifs, tmp, ','); // Midterm
				std::cout << left << setw(8) << tmp;
				getline(ifs, tmp); // Other
				std::cout << left << setw(8) << tmp << endl;
				line++;
			}
			line++;
			ifs.close();
			line++;
		}
		else {
			printCenterCharacters(L"THIS COURSE CLASS HAS NO SCOREBOARD", Color::red, Color::bright_white, line, My_Windows);
			line++;
			line++;
		}

	}
	courseClass.close();
	printCenterCharacters(L"Press any key to back to previous menu", Color::green, Color::bright_white, line + 2, My_Windows);
	int key = getKey();

	if (key == 27)
		return mainmenuOpt();
	return CourseMenuPage(username, SY, season, courseID);
}

void viewAndChooseCourseClass(string username, string SY, short season, string courseID) {
	system("cls");
	printCenterCharacters(L"CHOOSE COURSE CLASS PAGE", Color::light_green, Color::bright_white, 2, My_Windows);
	printCenterCharacters(L"AVAILABLE COURSE CLASSES", Color::light_green, Color::bright_white, 4, My_Windows);
	printCharacter(L"Press ESC to back to main menu", { 0, 0 }, Color::black, Color::bright_white);
	printCharacter(L"Press F1 to back to previous menu", { short(My_Windows.Right - 34), 0 }, Color::black, Color::bright_white);
	printCenterCharacters(wstring(courseID.begin(), courseID.end()), Color::light_aqua, Color::bright_white, 5, My_Windows);
	string classPath = SY + "/" + to_string(season) + "/" + courseID + "/class.txt";
	ifstream ifs;
	ifs.open(classPath);
	if (!ifs.is_open() || ifs.eof()) {
		printCenterCharacters(L"THERE IS NO COURSE CLASSES IN THIS COURSE", Color::red, Color::bright_white, 8, My_Windows);
		printCenterCharacters(L"Press any key to back to previous menu", Color::light_green, Color::bright_white, 2, My_Windows);
		int key = getKey();
		if (key == 27)
			return mainmenuOpt();
		return CourseMenuPage(username, SY, season, courseID);
	}
	else {
		string cClass;
		short line = 7;
		while (!ifs.eof()) {
			getline(ifs, cClass);
			printCenterCharacters(wstring(cClass.begin(), cClass.end()), Color::purple, Color::bright_white, line, My_Windows);
			line++;
		}
		ifs.close();
		printCharacter(L"Enter your choice: ", { 45, short(line + 3) }, Color::blue, Color::bright_white);
		gotoxy(45 + 20, line + 3);
		string chosenClass = getMenuString();
		if (chosenClass == "ESC")
			return mainmenuOpt();
		if (chosenClass == "F1")
			return CourseMenuPage(username, SY, season, courseID);
		ifs.open(classPath);
		while (!ifs.eof()) {
			getline(ifs, cClass);
			if (cClass == chosenClass) {
				ifs.close();
				printCenterCharacters(L"YOUR CHOICE IS AVAILABLE", Color::green, Color::bright_white, line + 5, My_Windows);
				printCenterCharacters(L"Press any key to continue", Color::light_green, Color::bright_white, line + 7, My_Windows);
				int key = getKey();
				if (key == 27)
					return mainmenuOpt();
				return CourseClassMenuPage(username, SY, season, courseID, chosenClass);
			}
		}
		ifs.close();
		printCenterCharacters(L"YOUR CHOICE IS NOT AVAILABLE", Color::red, Color::bright_white, line + 5, My_Windows);
		printCenterCharacters(L"Press any key enetr again or Press F1 to back to previous menu", Color::light_green, Color::bright_white, line + 7, My_Windows);
		int key = getKey();
		if (key == 27)
			return mainmenuOpt();
		if (key == 59)
			return CourseMenuPage(username, SY, season, courseID);
		return viewAndChooseCourseClass(username, SY, season, courseID);
	}
}

void viewScoreboardOfACourseClass(string username, string SY, short season, string courseID, string className) {
	system("cls");
	wstring temp[3];
	temp[0] = L"▒█▀▀█ ▒█▀▀▀█ ▒█░▒█ ▒█▀▀█ ▒█▀▀▀█ ▒█▀▀▀    ▒█▀▀▀█ ▒█▀▀█ ▒█▀▀▀█ ▒█▀▀█ ▒█▀▀▀ ▒█▀▀█ ▒█▀▀▀█ ░█▀▀█ ▒█▀▀█ ▒█▀▀▄";
	temp[1] = L"▒█░░░ ▒█░░▒█ ▒█░▒█ ▒█▄▄▀ ░▀▀▀▄▄ ▒█▀▀▀    ░▀▀▀▄▄ ▒█░░░ ▒█░░▒█ ▒█▄▄▀ ▒█▀▀▀ ▒█▀▀▄ ▒█░░▒█ ▒█▄▄█ ▒█▄▄▀ ▒█░▒█";
	temp[2] = L"▒█▄▄█ ▒█▄▄▄█ ░▀▄▄▀ ▒█░▒█ ▒█▄▄▄█ ▒█▄▄▄    ▒█▄▄▄█ ▒█▄▄█ ▒█▄▄▄█ ▒█░▒█ ▒█▄▄▄ ▒█▄▄█ ▒█▄▄▄█ ▒█░▒█ ▒█░▒█ ▒█▄▄▀";
	for (int i = 0; i < 3; i++)
	{
		printCenterCharacters(temp[i], Color::light_green, Color::bright_white, i + 2, My_Windows);
		Sleep(100);
	}
	printCharacter(L"Press ESC to back to main menu", { 0, 0 }, Color::black, Color::bright_white);
	Sleep(100);
	printCenterCharacters(wstring(courseID.begin(), courseID.end()), Color::light_green, Color::bright_white, 5, My_Windows);
	Sleep(200);
	string path;

	// View list of classes in a course
	short line = 7;
	printCenterCharacters(L"Class " + wstring(className.begin(), className.end()), Color::green, Color::bright_white, line, My_Windows);
	line++;

	ifstream ifs;
	ifs.open("./" + SY + "/" + to_string(season) + "/" + courseID + "/" + className + "/scoreboard.txt");
	if (ifs.is_open()) {
		gotoxy(35, line);
		std::cout << left << setw(5) << "No" << setw(10) << "ID";
		std::cout << left << setw(22) << "Last name" << setw(12) << "First Name";
		std::cout << left << setw(8) << "Total" << setw(8) << "Final" << setw(8) << "Midterm" << setw(8) << "Other" << endl;
		line++;
		while (!ifs.eof()) {
			string tmp;
			gotoxy(35, line);
			getline(ifs, tmp, ','); // Ordinal number
			std::cout << left << setw(5) << tmp;
			getline(ifs, tmp, ','); // ID
			std::cout << left << setw(10) << tmp;
			getline(ifs, tmp, ','); // Last Name
			std::cout << left << setw(22) << tmp;
			getline(ifs, tmp, ','); // First Name
			std::cout << left << setw(12) << tmp;
			getline(ifs, tmp, ','); // Total
			std::cout << left << setw(8) << tmp;
			getline(ifs, tmp, ','); // Final 
			std::cout << left << setw(8) << tmp;
			getline(ifs, tmp, ','); // Midterm
			std::cout << left << setw(8) << tmp;
			getline(ifs, tmp); // Other
			std::cout << left << setw(8) << tmp << endl;
			line++;

		}
		ifs.close();
	}
	else {
		printCenterCharacters(L"THIS COURSE CLASS HAS NO SCOREBOARD", Color::red, Color::bright_white, line, My_Windows);
	}


	printCenterCharacters(L"Press any key to back to previous menu", Color::green, Color::bright_white, line + 2, My_Windows);
	int key = getKey();
	if (key == 27)
		return mainmenuOpt();
	return CourseClassMenuPage(username, SY, season, courseID, className);
}

void viewStudentProfile(string username) {
	system("cls");
	wstring tmp[3];
	tmp[0] = L"░█▀▀█ ░█▀▀█ ░█▀▀▀█ ░█▀▀▀ ▀█▀ ░█─── ░█▀▀▀";
	tmp[1] = L"░█▄▄█ ░█▄▄▀ ░█──░█ ░█▀▀▀ ░█─ ░█─── ░█▀▀▀";
	tmp[2] = L"░█─── ░█─░█ ░█▄▄▄█ ░█─── ▄█▄ ░█▄▄█ ░█▄▄▄";
	for (int i = 0; i < 3; i++)
	{
		printCenterCharacters(tmp[i], Color::light_green, Color::bright_white, i + 2, My_Windows);
		Sleep(100);
	}
	printCharacter(L"Press ESC to back to main menu", { 0, 0 }, Color::black, Color::bright_white);
	Sleep(100);
	printCenterCharacters(wstring(username.begin(), username.end()), Color::light_green, Color::bright_white, 6, My_Windows);
	Sleep(200);

	string pathProfile = "./profile/" + username + ".txt";
	string stID;
	string temp;
	ifstream ifs(pathProfile);
	if (!ifs.is_open()) {
		std::cout << "Something went wrong. Please try again.\n\n\n";
		system("pause");
		return;
	}

	getline(ifs, stID);
	short len = stID.length() + 11;
	short center = (135 - len) / 2;
	printCharacter(L"Username: ", { center, 8 }, Color::black, Color::bright_white);
	printCharacter(wstring(stID.begin(), stID.end()), { short(center + 11), 8 }, Color::blue, Color::bright_white);

	getline(ifs, temp);
	len = temp.length() + 11;
	center = (135 - len) / 2;
	printCharacter(L"Password: ", { center, 10 }, Color::black, Color::bright_white);
	printCharacter(wstring(temp.begin(), temp.end()), { short(center + 11), 10 }, Color::blue, Color::bright_white);

	getline(ifs, temp);
	len = temp.length() + 22;
	center = (135 - len) / 2;
	printCharacter(L"Current school year: ", { center, 12 }, Color::black, Color::bright_white);
	printCharacter(wstring(temp.begin(), temp.end()), { short(center + 22), 12 }, Color::blue, Color::bright_white);

	getline(ifs, temp);
	len = temp.length() + 8;
	center = (135 - len) / 2;
	printCharacter(L"Class: ", { center, 14 }, Color::black, Color::bright_white);
	printCharacter(wstring(temp.begin(), temp.end()), { short(center + 8), 14 }, Color::blue, Color::bright_white);

	len = username.length() + 8;
	center = (135 - len) / 2;
	printCharacter(L"Student ID: ", { center, 16 }, Color::black, Color::bright_white);
	printCharacter(wstring(username.begin(), username.end()), { short(center + 13), 16 }, Color::blue, Color::bright_white);

	getline(ifs, temp, ',');
	len = temp.length() + 13;
	center = (135 - len) / 2;
	printCharacter(L"First name: ", { center, 18 }, Color::black, Color::bright_white);
	printCharacter(wstring(temp.begin(), temp.end()), { short(center + 13), 18 }, Color::blue, Color::bright_white);

	getline(ifs, temp);
	len = temp.length() + 12;
	center = (135 - len) / 2;
	printCharacter(L"Last name: ", { center, 20 }, Color::black, Color::bright_white);
	printCharacter(wstring(temp.begin(), temp.end()), { short(center + 12), 20 }, Color::blue, Color::bright_white);

	getline(ifs, temp);
	len = temp.length() + 9;
	center = (135 - len) / 2;
	printCharacter(L"Gender: ", { center, 22 }, Color::black, Color::bright_white);
	printCharacter(wstring(temp.begin(), temp.end()), { short(center + 9), 22 }, Color::blue, Color::bright_white);


	getline(ifs, temp);
	len = temp.length() + 16;
	center = (135 - len) / 2;
	printCharacter(L"Date of birth: ", { center, 24 }, Color::black, Color::bright_white);
	printCharacter(wstring(temp.begin(), temp.end()), { short(center + 16), 24 }, Color::blue, Color::bright_white);

	getline(ifs, temp);
	len = temp.length() + 12;
	center = (135 - len) / 2;
	printCharacter(L"Social ID: ", { center, 26 }, Color::black, Color::bright_white);
	printCharacter(wstring(temp.begin(), temp.end()), { short(center + 12), 26 }, Color::blue, Color::bright_white);

	ifs.close();
	printCenterCharacters(L"PRESS ANY KEY TO CONTINUE...", Color::black, Color::bright_white, 29, My_Windows);
	int key = getKey();
	if (key == 27)
		return mainmenuOpt();
	return studentMenuPage(username);
}

void changeStudentInfo(string username) {
	system("cls");
	wstring title[2];
	title[0] = L"█▀▀ █░█ ▄▀█ █▄░█ █▀▀ █▀▀   █▀█ █▀█ █▀█ █▀▀ █ █░░ █▀▀";
	title[1] = L"█▄▄ █▀█ █▀█ █░▀█ █▄█ ██▄   █▀▀ █▀▄ █▄█ █▀░ █ █▄▄ ██▄";
	for (int i = 0; i < 2; i++)
	{
		printCenterCharacters(title[i], Color::light_green, Color::bright_white, i + 2, My_Windows);
		Sleep(100);
	}
	printCharacter(L"Press ESC to back to main menu", { 0, 0 }, Color::black, Color::bright_white);
	Sleep(100);
	printCenterCharacters(wstring(username.begin(), username.end()), Color::light_green, Color::bright_white, 5, My_Windows);
	Sleep(200);

	string username1, password1, firstname1, lastname1, gender1, dateofbirth1, socialid1, sy, className;
	ifstream fin("profile\\" + username + ".txt");
	if (fin.is_open()) {
		getline(fin, username1);
		getline(fin, password1);
		getline(fin, sy);
		getline(fin, className);
		getline(fin, firstname1, ',');
		getline(fin, lastname1);
		getline(fin, gender1);
		getline(fin, dateofbirth1);
		getline(fin, socialid1);
		fin.close();
	}

	printCharacter(L"Password: ", { 45, 7 }, Color::blue, Color::bright_white);
	printCharacter(L"" + wstring(password1.begin(), password1.end()), { 45 + 11, 7 }, Color::gray, Color::bright_white);
	drawBox(8);
	printCharacter(L"First Name: ", { 45, 11 }, Color::blue, Color::bright_white);
	printCharacter(L"" + wstring(firstname1.begin(), firstname1.end()), { 45 + 13, 11 }, Color::gray, Color::bright_white);
	drawBox(12);
	printCharacter(L"Last Name: ", { 45, 15 }, Color::blue, Color::bright_white);
	printCharacter(L"" + wstring(lastname1.begin(), lastname1.end()), { 45 + 12, 15 }, Color::gray, Color::bright_white);
	drawBox(16);
	printCharacter(L"Gender: ", { 45, 19 }, Color::blue, Color::bright_white);
	printCharacter(L"" + wstring(gender1.begin(), gender1.end()), { 45 + 9, 19 }, Color::gray, Color::bright_white);
	drawBox(20);
	printCharacter(L"Date Of Birth: ", { 45, 23 }, Color::blue, Color::bright_white);
	printCharacter(L"" + wstring(dateofbirth1.begin(), dateofbirth1.end()), { 45 + 16, 23 }, Color::gray, Color::bright_white);
	drawBox(24);
	printCharacter(L"Social ID: ", { 45, 27 }, Color::blue, Color::bright_white);
	printCharacter(L"" + wstring(socialid1.begin(), socialid1.end()), { 45 + 12, 27 }, Color::gray, Color::bright_white);
	drawBox(28);
	printCenterCharacters(L"Press ESC to back to main menu", Color::red, Color::bright_white, 36, My_Windows);

	gotoxy(46, 9);
	password1 = getStringInput();
	if (password1 == "ESC")
		return mainmenuOpt();
	gotoxy(46, 13);
	firstname1 = getStringInput();
	if (firstname1 == "ESC")
		return mainmenuOpt();
	gotoxy(46, 17);
	lastname1 = getStringInput();
	if (lastname1 == "ESC")
		return mainmenuOpt();
	gotoxy(46, 21);
	gender1 = getStringInput();
	if (gender1 == "ESC")
		return mainmenuOpt();
	gotoxy(46, 25);
	dateofbirth1 = getStringInput();
	if (dateofbirth1 == "ESC")
		return mainmenuOpt();
	gotoxy(46, 29);
	socialid1 = getStringInput();
	if (socialid1 == "ESC")
		return mainmenuOpt();

	string filename = "profile\\" + username + ".txt";
	ofstream ofs;
	ifstream ifs;
	ifs.open(filename);
	string tmp;
	getline(ifs, tmp); // username
	getline(ifs, tmp); // password
	if (password1 == "") {
		password1 = tmp;
	}
	getline(ifs, tmp); // SY
	getline(ifs, tmp); // class

	getline(ifs, tmp, ',');
	if (firstname1 == "") {
		firstname1 = tmp;
	}
	getline(ifs, tmp);
	if (lastname1 == "") {
		lastname1 = tmp;
	}
	getline(ifs, tmp);
	if (gender1 == "") {
		gender1 = tmp;
	}
	getline(ifs, tmp);
	if (dateofbirth1 == "") {
		dateofbirth1 = tmp;
	}
	getline(ifs, tmp);
	if (socialid1 == "") {
		socialid1 = tmp;
	}
	ifs.close();
	ofs.open(filename);
	ofs << username << endl;
	ofs << password1 << endl;
	ofs << sy << endl << className << endl;
	ofs << firstname1 << ",";
	ofs << lastname1 << endl;
	ofs << gender1 << endl;
	ofs << dateofbirth1 << endl;
	ofs << socialid1 << endl;
	ofs.close();

	gotoxy(0, 0);
	printCenterCharacters(L"Update Successfully", Color::green, Color::bright_white, 31, My_Windows);
	printCenterCharacters(L"Press any key to continue...", Color::green, Color::bright_white, 33, My_Windows);
	int key = getKey();
	if (key == 27)
		return mainmenuOpt();
	return studentMenuPage(username);
}

void viewStudentScoreboard(string username) {
	system("cls");
	wstring tmp[3];
	tmp[0] = L"▒█░░▒█ ▀█▀ ▒█▀▀▀ ▒█░░▒█    ▒█▀▀▀█ ▒█▀▀█ ▒█▀▀▀█ ▒█▀▀█ ▒█▀▀▀ ▒█▀▀█ ▒█▀▀▀█ ░█▀▀█ ▒█▀▀█ ▒█▀▀▄";
	tmp[1] = L"░▒█▒█░ ▒█░ ▒█▀▀▀ ▒█▒█▒█    ░▀▀▀▄▄ ▒█░░░ ▒█░░▒█ ▒█▄▄▀ ▒█▀▀▀ ▒█▀▀▄ ▒█░░▒█ ▒█▄▄█ ▒█▄▄▀ ▒█░▒█";
	tmp[2] = L"░░▀▄▀░ ▄█▄ ▒█▄▄▄ ▒█▄▀▄█    ▒█▄▄▄█ ▒█▄▄█ ▒█▄▄▄█ ▒█░▒█ ▒█▄▄▄ ▒█▄▄█ ▒█▄▄▄█ ▒█░▒█ ▒█░▒█ ▒█▄▄▀";
	for (int i = 0; i < 3; i++)
	{
		printCenterCharacters(tmp[i], Color::light_green, Color::bright_white, i + 2, My_Windows);
		Sleep(100);
	}
	printCharacter(L"Press ESC to back to main menu", { 0, 0 }, Color::black, Color::bright_white);
	Sleep(100);
	printCenterCharacters(wstring(username.begin(), username.end()), Color::light_green, Color::bright_white, 5, My_Windows);
	Sleep(200);

	string SY, Class;
	ifstream ifs;
	ifs.open("./profile/" + username + ".txt");
	for (int i = 0; i < 3; i++) getline(ifs, SY);
	getline(ifs, Class);
	ifs.close();

	string path, line, curSY, Semester, GPA, courseClass;
	path = "./profile/" + username + ".txt"; // get info to open files
	ifs.open(path);
	getline(ifs, SY); // Username
	getline(ifs, SY); // Password
	getline(ifs, SY); // School year
	getline(ifs, Class); // Class
	ifs.close();

	ifs.open("./curTime.txt");
	getline(ifs, curSY); // current school year
	getline(ifs, Semester); // Semester
	ifs.close();

	// school year saving data of student
	path = "./" + SY + "/" + Class + "/" + username + "/" + Semester + "_" + curSY + ".txt";
	// Open file saving list of courses in current semester
	ifs.open(path);

	getline(ifs, GPA); // GPA in this semester
	printCenterCharacters(L"YOUR SCOREBOARD IN THIS SEMESTER", Color::black, Color::bright_white, 7, My_Windows);
	printCenterCharacters(L"-----------------------------------------", Color::purple, Color::bright_white, 8, My_Windows);
	printCenterCharacters(L"GPA: " + wstring(GPA.begin(), GPA.end()), Color::black, Color::bright_white, 9, My_Windows);
	printCenterCharacters(L"-----------------------", Color::purple, Color::bright_white, 10, My_Windows);
	gotoxy(25, 12);
	std::cout << left << setw(12) << "Course ID" << setw(30) << "Course name" << setw(8) << "Class" << setw(8) << "Credits" << setw(6) << "Total" << setw(6) << "Final" << setw(8) << "Midterm" << setw(6) << "Other" << endl;
	getline(ifs, line); // number of credits -> no use here

	short curLine = 12;

	while (!ifs.eof()) {
		gotoxy(25, curLine + 2);
		getline(ifs, line, ','); // Get a course's ID
		getline(ifs, courseClass); // Get class name of the course
		ifstream course;
		// open file info of a course
		path = "./" + curSY + "/" + Semester + "/" + line + "/" + courseClass + "/info.txt";
		course.open(path);
		string courseName, className, numCredits;
		std::cout << left << setw(12) << line; // courseId is also the value of variable "line"
		getline(course, courseName); // course's ID -> don't need this information because we've already had it
		getline(course, courseName);
		std::cout << setw(30) << courseName; // name of course
		getline(course, className);
		std::cout << setw(8) << className; // name of class of the course
		getline(course, numCredits); // Get teacher's name -> don't need here
		getline(course, numCredits);
		std::cout << setw(8) << numCredits; // number of credits of the course
		course.close();

		// open file score of a student
		path = "./" + SY + "/" + Class + "/" + username + "/" + line + ".txt";
		course.open(path);
		getline(course, line, ',');
		std::cout << setw(6) << line; // Total mark
		getline(course, line, ',');
		std::cout << setw(6) << line; // Final mark
		getline(course, line, ',');
		std::cout << setw(8) << line; // Midterm mark
		getline(course, line);
		std::cout << setw(6) << line << endl; // Other mark
		course.close();

		curLine++;
	}
	ifs.close();
	printCenterCharacters(L"---------------------------------------", Color::purple, Color::bright_white, curLine + 3, My_Windows);
	printCenterCharacters(L"PRESS F1 to View Scoreboard Of All Course", Color::purple, Color::bright_white, curLine + 5, My_Windows);
	printCenterCharacters(L"PRESS F2 to View Scoreboard Of A Semester", Color::purple, Color::bright_white, curLine + 7, My_Windows);
	printCenterCharacters(L"PRESS any key else to back to previous menu", Color::purple, Color::bright_white, curLine + 9, My_Windows);
	curLine += 9;

	int key = getKey();
	if (key == 27)
		return mainmenuOpt();
	if (key == 59) {
		return viewStudentScoreboardAllCourses(username);
	}
	if (key == 60)
		return viewStudentScoreboardChooseSem(username);
	return studentMenuPage(username);

}

void viewListCousres(string username) {
	system("cls");
	wstring tmp[3];
	tmp[0] = L"░█──░█ ▀█▀ ░█▀▀▀ ░█──░█   ░█▀▀█ ░█▀▀▀█ ░█─░█ ░█▀▀█ ░█▀▀▀█ ░█▀▀▀ ░█▀▀▀█";
	tmp[1] = L"─░█░█─ ░█─ ░█▀▀▀ ░█░█░█   ░█─── ░█──░█ ░█─░█ ░█▄▄▀ ─▀▀▀▄▄ ░█▀▀▀ ─▀▀▀▄▄";
	tmp[2] = L"──▀▄▀─ ▄█▄ ░█▄▄▄ ░█▄▀▄█   ░█▄▄█ ░█▄▄▄█ ─▀▄▄▀ ░█─░█ ░█▄▄▄█ ░█▄▄▄ ░█▄▄▄█";
	for (int i = 0; i < 3; i++)
	{
		printCenterCharacters(tmp[i], Color::light_green, Color::bright_white, i + 2, My_Windows);
		Sleep(100);
	}
	printCharacter(L"Press ESC to back to main menu", { 0, 0 }, Color::black, Color::bright_white);
	Sleep(100);
	printCenterCharacters(wstring(username.begin(), username.end()), Color::light_green, Color::bright_white, 6, My_Windows);
	Sleep(200);


	string path, line, SY, Class, courseClass, Sem, curSY;
	// Path leads to the file student info in folder profile
	path = "./profile/" + username + ".txt"; // Get SY and Class
	ifstream ifs, Course;
	ifs.open(path);
	getline(ifs, SY); // username
	getline(ifs, SY); // password
	getline(ifs, SY); // school year
	getline(ifs, Class); // class name
	ifs.close();
	ifs.open("./curTime.txt");
	getline(ifs, curSY); // get the current year
	getline(ifs, Sem); // get the current semester
	ifs.close();

	path = "./" + SY + "/" + Class + "/" + username + "/" + "courses.txt"; // Get info of courses leaning in this sem
	ifs.open(path);
	if (!ifs.is_open()) {
		ifs.close();
		printCenterCharacters(L"THIS SEMESTER HAS NO COURSES NOW", Color::red, Color::bright_white, 8, My_Windows);
		printCenterCharacters(L"PRESS any key to back to previous menu", Color::green, Color::bright_white, 10, My_Windows);
		int key = getKey();
		if (key == 27)
			return mainmenuOpt();
		return studentMenuPage(username);
	}


	printCenterCharacters(L"ALL COURSE IN THIS SEMESTER", Color::blue, Color::bright_white, 8, My_Windows);
	printCenterCharacters(L"-------------------------------------------", Color::purple, Color::bright_white, 9, My_Windows);
	getline(ifs, line); // semester -> no need here
	getline(ifs, line); // SY -> no need either
	short curLine = 11;

	int i = 1; // This variable is used to represent ordinal number, add up to 1 when there's a new member printing out
	string CourseID, CourseName, CourseClass, Teacher, Credit, DayOfWeek, Session;
	gotoxy(20, curLine);
	cout << left << setw(5) << "No." << setw(12) << "Course ID" << setw(30) << "Course name" << setw(8) << "Credit" << setw(10) << "Class" << setw(14) << "Session" << "   " << "Teacher" << endl;
	while (!ifs.eof()) {
		gotoxy(20, curLine + 2);
		getline(ifs, line, ','); // Read courseID
		getline(ifs, courseClass); // Read class name in the course
		Course.open("./" + curSY + "/" + Sem + "/" + line + "/" + courseClass + "/info.txt");
		getline(Course, CourseID);
		getline(Course, CourseName);
		getline(Course, CourseClass);
		getline(Course, Teacher);
		getline(Course, Credit);
		getline(Course, DayOfWeek); // max student -> no need either
		getline(Course, DayOfWeek);
		getline(Course, Session);
		Course.close();
		cout << left << setw(5) << i << setw(12) << CourseID << setw(30) << CourseName << setw(8) << Credit << setw(10) << CourseClass << setw(4) << DayOfWeek << setw(10) << Session << "   " << Teacher << endl;
		i++;
		curLine++;
	}
	printCenterCharacters(L"------------------------------------------------", Color::purple, Color::bright_white, curLine + 4, My_Windows);
	ifs.close();

	printCenterCharacters(L"PRESS any key else to back to previous menu", Color::green, Color::bright_white, curLine + 6, My_Windows);
	int key = getKey();
	if (key == 27)
		return mainmenuOpt();
	return studentMenuPage(username);
}

void exportListStudentToFile(string username, string SY, short season, string courseID) {
	printCharacter(L"Input the path to export CSV file here", { 45, 25 }, Color::blue, Color::bright_white);
	printCharacter(L"Press F1 to back to previous menu", { short(My_Windows.Right - 34), 0}, Color::black, Color::bright_white);
	drawBox(26);
	gotoxy(46, 27);

	string outputPath;
	outputPath = getMenuString();

	if (outputPath == "ESC")
		return mainmenuOpt();
	if (outputPath == "F1")
		return CourseMenuPage(username, SY, season, courseID);

	ofstream ofs;

	ofs.open(outputPath);

	if (ofs.is_open()) {
		string path = "./" + SY + "/" + to_string(season) + "/" + courseID + "/class.txt";
		ifstream ifs;

		ifs.open(path);
		if (ifs.is_open())	{
			while (!ifs.eof()) {
				string cClass;
				getline(ifs, cClass);
				ofs << courseID << " class " << cClass << endl;
				ofs << "No" << "," << "ID" << ",";
				ofs << "Last name" << "," << "First name" << ",";
				ofs << "Total" << "," << "Final" << "," << "Midterm" << "," << "Other" << endl;

				ifstream Class;
				Class.open("./" + SY + "/" + to_string(season) + "/" + courseID + "/" + cClass + "/scoreboard.txt");
				if (Class.is_open())	{
					while (!Class.eof()) {
						string tmp;
						getline(Class, tmp, ','); // Ordinal number
						ofs << tmp << ",";
						getline(Class, tmp, ','); // ID
						ofs << tmp << ",";
						getline(Class, tmp, ','); // Last Name
						ofs << tmp << ",";
						getline(Class, tmp, ','); // First Name
						ofs << tmp << ",";
						getline(Class, tmp, ','); // Total
						ofs << tmp << ",";
						getline(Class, tmp, ','); // Final 
						ofs << tmp << ",";
						getline(Class, tmp, ','); // Midterm
						ofs << tmp << ",";
						getline(Class, tmp); // Other
						ofs << tmp << endl;
					}
					ofs << endl;
				}
				else	{
					ofs << "Haven't imported scoreboard for this course class." << endl;
					ofs << "Please import scoreboard first." << endl;
					ofs << endl;
				}
				Class.close();
			}
		}
		
		ifs.close();
		ofs.close();
		printCenterCharacters(L"EXPORT SUCCESSFULLY", Color::green, Color::bright_white, 30, My_Windows);
		printCenterCharacters(L"PRESS any key to back to previous menu", Color::green, Color::bright_white, 32, My_Windows);
		int key = getKey();
		if (key == 27)
			return mainmenuOpt();
		return CourseMenuPage(username, SY, season, courseID);
	}
	else {
		ofs.close();
		printCenterCharacters(L"SOME THING WRONG WHEN EXPORTING FILE", Color::red, Color::bright_white, 30, My_Windows);
		printCenterCharacters(L"PRESS any key to back to previous menu", Color::green, Color::bright_white, 32, My_Windows);
		int key = getKey();
		if (key == 27)
			return mainmenuOpt();
		return CourseMenuPage(username, SY, season, courseID);
	}
}

void viewStudentInACourseClass(string username, string SY, short season, string courseID, string courseClassID) {
	system("cls");
	printCharacter(L"Press ESC to back to main menu", { 0, 0 }, Color::black, Color::bright_white);
	printCenterCharacters(L"<<<< COURSE " + wstring(courseID.begin(), courseID.end()) + L" >>>>", Color::light_green, Color::bright_white, 2, My_Windows);
	printCenterCharacters(L"~~~ Class " + wstring(courseID.begin(), courseID.end()) + L" ~~~" ,Color::light_blue, Color::bright_white, 3, My_Windows);

	string path = SY + "//" + to_string(season) + "//" + courseID + "/" + courseClassID + "/listStud.txt";
	string tmp;
	short no = 1;

	ifstream ifs(path);
	short line = 8;

	if (!ifs.is_open()) {
		printCenterCharacters(L"----------------------THIS CLASS HAS NO STUDENT------------------------", Color::purple, Color::bright_white, 4, My_Windows);
		printCenterCharacters(L"Press any key to back to previous menu", Color::green, Color::bright_white, 0, My_Windows);
		int key = getKey();
		if (key == 27)
			return mainmenuOpt();
		return CourseMenuPage(username, SY, season, courseID);
	}
	else {
		printCenterCharacters(L"----------------------List of Students------------------------", Color::purple, Color::bright_white, 4, My_Windows);
		gotoxy(40, 6);
		std::cout << left << setw(4) << "NO" << setw(11) << "MSSV" << setw(34) << "Full Name" << "Class" << endl;
		string stID, stName;
		if (ifs.is_open() && !ifs.eof()) {
			while (getline(ifs, stID, ',') && getline(ifs, stName)) {
				ifstream student("./profile//" + stID + ".txt");
				string StClass;
				for (int i = 0; i < 4; i++)
					getline(student, StClass);
				student.close();
				gotoxy(40, line);
				std::cout << left << setw(4) << no << setw(11) << stID << setw(34) << stName << StClass << endl;
				line++;
				no++;
			}
		}
		ifs.close();
		printCenterCharacters(L"Press any key to back to previous menu", Color::green, Color::bright_white, line + 2, My_Windows);
		int key = getKey();
		if (key == 27)
			return mainmenuOpt();
		return CourseClassMenuPage(username, SY, season, courseID, courseClassID);
	}
}


void viewScoreboardClassChooseSem(string username, string SY, string className, string chosenSY, string chosenSem) {
	system("cls");
	wstring temp[3];
	temp[0] = L"▒█▀▀▀█ ▒█▀▀█ ▒█▀▀▀█ ▒█▀▀█ ▒█▀▀▀ ▒█▀▀█ ▒█▀▀▀█ ░█▀▀█ ▒█▀▀█ ▒█▀▀▄";
	temp[1] = L"░▀▀▀▄▄ ▒█░░░ ▒█░░▒█ ▒█▄▄▀ ▒█▀▀▀ ▒█▀▀▄ ▒█░░▒█ ▒█▄▄█ ▒█▄▄▀ ▒█░▒█";
	temp[2] = L"▒█▄▄▄█ ▒█▄▄█ ▒█▄▄▄█ ▒█░▒█ ▒█▄▄▄ ▒█▄▄█ ▒█▄▄▄█ ▒█░▒█ ▒█░▒█ ▒█▄▄▀";
	for (int i = 0; i < 3; i++)
	{
		printCenterCharacters(temp[i], Color::light_green, Color::bright_white, i + 2, My_Windows);
		Sleep(100);
	}
	printCharacter(L"Press ESC to back to main menu", { 0, 0 }, Color::black, Color::bright_white);
	Sleep(100);


	string sy;
	ifstream syfile("./SY.txt");
	getline(syfile, sy);
	syfile.close();

	printCenterCharacters(wstring(className.begin(), className.end()) + L", School Year: " + wstring(chosenSY.begin(), chosenSY.end()) + L", Semester: " + wstring(chosenSem.begin(), chosenSem.end()), Color::light_green, Color::bright_white, 5, My_Windows);
	Sleep(200);

	ifstream ifs, student;
	string course, ID, name, total, final, GPA, curSem, curSY;

	short curLine = 7;



	courseInThisSem* head = nullptr; // This linked list is used to 
	// Open the file contain list of student's ID in a class
	ifs.open("./" + sy + "/" + className + "/student.txt");
	while (!ifs.eof()) {
		getline(ifs, ID); // Student's ID
		// Open the file saving courses that a student will learn in this semester
		student.open("./" + sy + "/" + className + "/" + ID + "/" + chosenSem + "_" + chosenSY + ".txt"); // <sem>_<SY>.txt
		if (student.is_open()) { // if this student does not learn in this sem -> do not do this code segment
			getline(student, course); // GPA in this semester -> no need here
			getline(student, course); // credit -> no need either
			while (!student.eof()) {
				getline(student, course, ','); // get a course's ID
				if (!checkExist(head, course)) insertCourseAtBegin(head, course);
				getline(student, course); // class of the course -> no need here
			}
		}
		student.close();
	}
	ifs.close();

	// Now we have the linked list of courses
	// Print out first line to the screen
	gotoxy(35, curLine + 2);
	short i = 0;
	cout << left << setw(34) << "Name"; // the name of the column that represents student's name
	courseInThisSem* cur = head; // A temp pointer used to traverse
	while (cur) {
		gotoxy(35 + 34 + i * 10, curLine + 2);
		cout << setw(10) << cur->ID; // course ID
		cur = cur->next;
		i++;
	}
	cout << setw(8) << "GPA" << setw(12) << "Overall GPA" << endl;
	curLine++;

	// 2nd, 3rd, 4th, ... line
	ifs.open("./" + sy + "/" + className + "/student.txt");
	// Check if this file have nothing or does not exist
	while (!ifs.eof()) {
		gotoxy(35, curLine + 2);
		getline(ifs, ID); // Student's ID
		student.open("./profile/" + ID + ".txt");
		string fName, lName;
		for (int i = 0; i < 4; i++)
			getline(student, fName);

		getline(student, fName, ',');
		getline(student, lName, '\n');
		name = lName + " " + fName;
		cout << left << setw(34) << name; // Prints out student name
		student.close();

		cur = head; // refresh the "cur" variable
		while (cur) {
			student.open("./" + sy + "/" + className + "/" + ID + "/" + cur->ID + ".txt");
			// If this student does not enroll in this course, print out x
			if (!student.is_open()) cout << setw(10) << "x";
			else {
				getline(student, total, ',');
				getline(student, final, ',');
				cout << setw(10) << total; // Total mark
			}
			student.close();

			cur = cur->next;
		}

		student.open("./" + sy + "/" + className + "/" + ID + "/" + chosenSem + "_" + chosenSY + ".txt");
		getline(student, GPA);
		if (!student.is_open()) cout << setw(8) << 0;
		else cout << setw(8) << GPA; // GPA in this sem
		student.close();

		student.open("./" + sy + "/" + className + "/" + ID + "/total.txt");
		getline(student, GPA);
		if (!student.is_open()) cout << setw(12) << 0 << endl;
		else cout << setw(12) << GPA << endl; // OVerall GPA
		student.close();
		curLine++;
	}
	ifs.close();


	deleteCourseLL(head); // Delete linked list
	printCenterCharacters(L"--------------------------------------------------", Color::purple, Color::bright_white, curLine + 3, My_Windows);
	printCenterCharacters(L"Press any key to back to previous menu.", Color::green, Color::bright_white, curLine + 4, My_Windows);
	printCenterCharacters(L"Press F1 view Scoreboard of Newest Semester", Color::green, Color::bright_white, curLine + 5, My_Windows);

	int key = getKey();
	if (key == 27)
		return mainmenuOpt();
	if (key == 59) {
		return viewScoreboard(username, SY, className);
	}
	return ClassMenuPage(username, SY, className);
}