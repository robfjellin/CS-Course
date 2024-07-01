//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iomanip>

using namespace std;

// Structure to hold course information
struct Course {
    string courseCode;
    string title;
    vector<string> prerequisites;
};

// Vector to store all courses
vector<Course> courses;

// Function to load data from file
void loadDataFromFile(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cout << "Error opening file." << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        Course course;
        istringstream iss(line);

        // Assuming the file format is: CourseCode,Title,Prereq1,Prereq2,...
        getline(iss, course.courseCode, ',');
        getline(iss, course.title, ',');

        string prereq;
        while (getline(iss, prereq, ',')) {
            if (!prereq.empty()) {
                course.prerequisites.push_back(prereq);
            }
        }

        courses.push_back(course);
    }

    cout << "Data loaded successfully. " << courses.size() << " courses loaded." << endl;
    file.close();
}

// Function to print all Computer Science courses
void printCSCourses() {
    vector<string> csCourses;
    for (const auto& course : courses) {
        if (course.courseCode.substr(0, 3) == "CSC") {
            csCourses.push_back(course.courseCode + " - " + course.title);
        }
    }

    if (csCourses.empty()) {
        cout << "No Computer Science courses found." << endl;
        return;
    }

    sort(csCourses.begin(), csCourses.end());

    cout << "Computer Science Courses:" << endl;
    for (const auto& course : csCourses) {
        cout << course << endl;
    }
}

// Function to print course details
void printCourseDetails() {
    string courseCode;
    cout << "Enter the course code: ";
    cin >> courseCode;

    for (const auto& course : courses) {
        if (course.courseCode == courseCode) {
            cout << "Course: " << course.courseCode << " - " << course.title << endl;
            cout << "Prerequisites: ";
            if (course.prerequisites.empty()) {
                cout << "None";
            }
            else {
                for (size_t i = 0; i < course.prerequisites.size(); ++i) {
                    cout << course.prerequisites[i];
                    if (i < course.prerequisites.size() - 1) {
                        cout << ", ";
                    }
                }
            }
            cout << endl;
            return;
        }
    }

    cout << "Course not found." << endl;
}

void displayMenu() {
    int userChoice;
    bool isTrue = true;

    while (isTrue) {
        cout << "Option 1: Load the file data into the data structure" << endl;
        cout << "Option 2: Print an alphanumeric list of all the courses in the Computer Science department" << endl;
        cout << "Option 3: Print the course title and the prerequisites for any individual course" << endl;
        cout << "Option 9: Exit the program" << endl;

        cin >> userChoice;

        switch (userChoice) {
         case 1:
            {
                string filename;
                cout << "Enter the filename to load: ";
                cin >> filename;
                loadDataFromFile(filename);
            }
            break;
         case 2:
             printCSCourses();
             break;
         case 3:
             printCourseDetails();
             break;
         case 9:
             cout << "Goodbye." << endl;
             isTrue = false;
             break;
         default:
             cout << "Please enter a valid input... 1, 2, 3 or 9" << endl << endl;
        }
    }
}


int main()
{
    displayMenu();
}

