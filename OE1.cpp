#include <iostream>
#include <vector>
#include <string>

using namespace std;



class Student {
private:
    int studentID;
    string name;
    vector<Course*> coursesEnrolled;
public:
    Student(int id, string n) : studentID(id), name(n) {}

    void enrollCourse(Course* course);
    void dropCourse(Course* course);
    void viewCourses();
};
class Teacher {
private:
    int teacherID;
    string name;
    vector<Course*> coursesTaught;
public:
    Teacher(int id, string n) : teacherID(id), name(n) {}

    void assignCourse(Course* course);
    void removeCourse(Course* course);
    void viewCourses();
};


