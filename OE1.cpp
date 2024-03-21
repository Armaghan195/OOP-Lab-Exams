#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

#include"course.h"

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

    void saveToFile(const string& filename) {
        ofstream file(filename);
        if (file.is_open()) {
            file << studentID << "," << name << ",";
            for (const Course* course : coursesEnrolled) {
                file << course->getCourseName() << ",";
            }
            file.close();
            cout << "Student data saved to " << filename << endl;
        } else {
            cout << "Error: Unable to open file for writing." << endl;
        }
    }

    void loadFromFile(const string& filename, vector<Course*>& allCourses) {
        ifstream file(filename);
        if (file.is_open()) {
            string line;
            if (getline(file, line)) {
                stringstream ss(line);
                string token;
                getline(ss, token, ',');
                studentID = stoi(token);
                getline(ss, name, ',');
                coursesEnrolled.clear();
                while (getline(ss, token, ',')) {
                    for (Course* course : allCourses) {
                        if (course->getCourseName() == token) {
                            coursesEnrolled.push_back(course);
                            break;
                        }
                    }
                }
                cout << "Student data loaded from " << filename << endl;
            }
            file.close();
        } else {
            cout << "Error: Unable to open file for reading." << endl;
        }
    }
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

    void saveToFile(const string& filename) {
        ofstream file(filename);
        if (file.is_open()) {
            file << teacherID << "," << name << ",";
            for (const Course* course : coursesTaught) {
                file << course->getCourseName() << ",";
            }
            file.close();
            cout << "Teacher data saved to " << filename << endl;
        } else {
            cout << "Error: Unable to open file for writing." << endl;
        }
    }

    void loadFromFile(const string& filename, vector<Course*>& allCourses) {
        ifstream file(filename);
        if (file.is_open()) {
            string line;
            if (getline(file, line)) {
                stringstream ss(line);
                string token;
                getline(ss, token, ',');
                teacherID = stoi(token);
                getline(ss, name, ',');
                coursesTaught.clear();
                while (getline(ss, token, ',')) {
                    for (Course* course : allCourses) {
                        if (course->getCourseName() == token) {
                            coursesTaught.push_back(course);
                            break;
                        }
                    }
                }
                cout << "Teacher data loaded from " << filename << endl;
            }
            file.close();
        } else {
            cout << "Error: Unable to open file for reading." << endl;
        }
    }
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



void Student::enrollCourse(Course* course) {
    if (course->addStudent(this)) {
        coursesEnrolled.push_back(course);
        cout << name << " enrolled in " << course->getCourseName() << endl;
    } else {
        cout << "Failed to enroll in course: " << course->getCourseName() << ". Course is full." << endl;
    }
}

void Student::dropCourse(Course* course) {
    auto it = find(coursesEnrolled.begin(), coursesEnrolled.end(), course);
    if (it != coursesEnrolled.end()) {
        coursesEnrolled.erase(it);
        course->removeStudent(this);
        cout << "Dropped course: " << course->getCourseName() << endl;
    } else {
        cout << "You are not enrolled in course: " << course->getCourseName() << endl;
    }
}

void Student::viewCourses() {
    cout << name << "'s courses:" << endl;
    for (Course* course : coursesEnrolled) {
        cout << "- " << course->getCourseName() << endl;
    }
}

void Teacher::assignCourse(Course* course) {
    coursesTaught.push_back(course);
    cout << name << " assigned to teach " << course->getCourseName() << endl;
}

void Teacher::removeCourse(Course* course) {
    auto it = find(coursesTaught.begin(), coursesTaught.end(), course);
    if (it != coursesTaught.end()) {
        coursesTaught.erase(it);
        cout << "Removed course: " << course->getCourseName() << endl;
    } else {
        cout << "Course not found: " << course->getCourseName() << endl;
    }
}

void Teacher::viewCourses() {
    cout << name << "'s courses:" << endl;
    for (Course* course : coursesTaught) {
        cout << "- " << course->getCourseName() << endl;
    }
}

int main() {
    // Create teachers
    Teacher teacher1(101, "Mr. Smith");
    Teacher teacher2(102, "Ms. Johnson");

    // Create students
    Student student1(1001, "Alice");
    Student student2(1002, "Bob");

    // Create courses
    Course course1("Programming 101", &teacher1);
    Course course2("Mathematics 101", &teacher2);

    // Assign courses to teachers
    teacher1.assignCourse(&course1);
    teacher2.assignCourse(&course2);

    // Enroll students in courses
    student1.enrollCourse(&course1);
    student2.enrollCourse(&course2);

    // View courses
        student1.viewCourses();
    student2.viewCourses();
    teacher1.viewCourses();
    teacher2.viewCourses();

    // Save data to files
    vector<Course*> allCourses = {&course1, &course2};
    student1.saveToFile("student1.txt");
    student2.saveToFile("student2.txt");
    teacher1.saveToFile("teacher1.txt");
    teacher2.saveToFile("teacher2.txt");

    // Load data from files
    student1.loadFromFile("student1.txt", allCourses);
    student2.loadFromFile("student2.txt", allCourses);
    teacher1.loadFromFile("teacher1.txt", allCourses);
    teacher2.loadFromFile("teacher2.txt", allCourses);

    return 0;
}

