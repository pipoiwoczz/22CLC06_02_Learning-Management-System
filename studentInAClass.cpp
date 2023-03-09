#include "studentInAClass.h"
#include "main.h"
#include <fstream>

void addAStudent(Student*& pCurr, ifstream& fin)
{
	string temp;
	getline(fin, temp, ',');
	pCurr->No = stoi(temp);
	getline(fin, temp, ',');
	pCurr->studentId = stoi(temp);
	getline(fin, temp, ',');
	pCurr->firstName = temp;
	getline(fin, temp, ',');
	pCurr->lastName = temp;
	getline(fin, temp, ',');
	pCurr->gender = temp;
	getline(fin, temp, ',');
	pCurr->dateOfBirth = temp;
	getline(fin, temp);
	pCurr->socialId = temp;
}

void inputStudentsToClass(Student*& pHead)
{
	ifstream fin;
	string path, temp;
	cout << "Enter the path of a CSV file containing students: ";
	cin >> path;
	fin.open(path);

	if (!fin.is_open()) {
		cout << "The file doesn't exist.";
		return;
	}

	Student* curr;
	while (!fin.eof()) {
		if (!pHead) {
			pHead = new Student;
			curr = pHead;
		}
		else {
			curr->next = new Student;
			curr = curr->next;
		}
		addAStudent(curr, fin);
		curr->next = nullptr;
	}
	fin.close();
}

void displayListOfStudents(Student* pHead)
{
	Student* temp = pHead;
	while (temp) {
		cout << temp->No;
		if (temp->No >= 10)
			cout << " ";
		cout << "  ";
		cout << temp->studentId << "  ";
		cout << temp->firstName << " " << temp->lastName << "  ";
		cout << temp->gender << "  ";
		cout << temp->dateOfBirth << "  ";
		cout << temp->socialId << endl;
		temp = temp->next;
	}
}