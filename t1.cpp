#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

// Forward declaration
class Course;

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

class Course {
private:
    string courseName;
    Teacher* teacher;
    vector<Student*> studentsEnrolled;
    const int maxCapacity = 10; // Max number of students allowed in the course
public:
    Course(string name, Teacher* t) : courseName(name), teacher(t) {}

    string getCourseName() const { return courseName; }

    bool addStudent(Student* student) {
        if (studentsEnrolled.size() < maxCapacity) {
            studentsEnrolled.push_back(student);
            return true;
        } else {
            return false;
        }
    }

    void removeStudent(Student* student) {
        auto it = find(studentsEnrolled.begin(), studentsEnrolled.end(), student);
        if (it != studentsEnrolled.end()) {
            studentsEnrolled.erase(it);
        }
    }
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
    // Remove the course from the enrolled courses list
    auto it = find(coursesEnrolled.begin(), coursesEnrolled.end(), course);
    if (it != coursesEnrolled.end()) {
        coursesEnrolled.erase(it);
        // Remove the student from the course
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

    return 0;
}
