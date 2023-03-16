#include "main.h"

void viewListCourses(Semester *semester) {
    cout << "List of courses: " << endl;
    while (semester) {
        Course *course = semester -> Courses;
        while (course) {
            cout << course -> courseName << endl;
            course = course -> next;
        }
        semester = semester -> next;
    }
}