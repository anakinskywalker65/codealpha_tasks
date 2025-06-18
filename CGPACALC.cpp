#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

struct Course {
    string name;
    float grade;
    int credit;
};

int main() {
    int numCourses;
    float totalGradePoints = 0;
    int totalCredits = 0;

    cout << "Enter the number of courses: ";
    cin >> numCourses;

    vector<Course> courses(numCourses);

    for (int i = 0; i < numCourses; i++) {
        cout << "\nCourse " << i + 1 << ":\n";
        cout << "Enter course name: ";
        cin >> ws; // to consume any leftover whitespace
        getline(cin, courses[i].name);

        cout << "Enter grade (number value): ";
        cin >> courses[i].grade;

        cout << "Enter credit hours: ";
        cin >> courses[i].credit;

        totalGradePoints += courses[i].grade * courses[i].credit;
        totalCredits += courses[i].credit;
    }

    float CGPA = totalGradePoints / totalCredits;

    cout << fixed << setprecision(2);
    cout << "\nCourse Details:\n";
    for (int i = 0; i < numCourses; i++) {
        cout << "Course: " << courses[i].name 
             << ", Grade: " << courses[i].grade 
             << ", Credits: " << courses[i].credit << endl;
    }

    cout << "\nTotal Credits: " << totalCredits << endl;
    cout << "CGPA: " << CGPA << endl;

    return 0;
}