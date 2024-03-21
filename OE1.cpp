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


