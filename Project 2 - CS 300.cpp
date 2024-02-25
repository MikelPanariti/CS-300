// MIKEL PANARITI
//CS - 300
//PROJECT 2
//FERUARY 25, 2024





#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

// Define a class for Course
class Course {
private:
    string file_name;
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;

public:
    // Default constructor
    Course() {}

    // Constructor
    Course(string number, string title, vector<string> prereqs) : courseNumber(number), courseTitle(title), prerequisites(prereqs) {}

    // Getters
    string getCourseNumber() const {
        return courseNumber;
    }

    string getCourseTitle() const {
        return courseTitle;
    }

    vector<string> getPrerequisites() const {
        return prerequisites;
    }
};

// Function prototypes
void loadDataStructure(unordered_map<string, Course>& courses, const string& filename);
void printCourseList(const unordered_map<string, Course>& courses);
void printCourseInformation(const unordered_map<string, Course>& courses, const string& courseNumber);

int main() {
    unordered_map<string, Course> courses; // Data structure to hold course objects

    // Load data from file
    //loadDataStructure(courses, "course_data.txt");

    // Menu loop
    int choice;
    string courseNumber;
    string file_name;

    cout << "Welcome to the course planner." << endl;

    do {
        // Display menu options
        cout << "1. Load Data Structure.\n"
            << "2. Print Course List.\n"
            << "3. Print Course.\n"
            << "4. Exit\n"
            << "What would you like to do? ";
        cin >> choice;

        switch (choice) {
        case 1: 
            //Load the data
            cout << "Please enter the file name: ";
            cin >> file_name;
            loadDataStructure(courses, file_name);
        case 2:
            // Print course list
            printCourseList(courses);
            break;
        case 3:
            // Prompt user for course number and print course information
            cout << "What course do you want to know about? ";
            cin >> courseNumber;
            printCourseInformation(courses, courseNumber);
            break;
        case 4:
            cout << "Thank you for using the course planner!" << endl;
            break;
        default:
            cout << "Invalid choice. Please enter a number between 1 and 4." << endl;
        }
    } while (choice != 4);

    return 0;
}

// Function to load data from file into data structure
void loadDataStructure(unordered_map<string, Course>& courses, const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string courseNumber, courseTitle, prerequisite;
            getline(ss, courseNumber, ',');
            getline(ss, courseTitle, ',');
            vector<string> prerequisites;
            while (getline(ss, prerequisite, ',')) {
                prerequisites.push_back(prerequisite);
            }
            courses[courseNumber] = Course(courseNumber, courseTitle, prerequisites);
        }
        file.close();
        cout << "Data loaded successfully." << endl;
    }
    else {
        cout << "Error: Unable to open file." << endl;
    }
}

// Function to print course list in alphanumeric order
void printCourseList(const unordered_map<string, Course>& courses) {
    cout << "Here is a sample schedule:" << endl;
    for (const auto& course : courses) {
        cout << course.second.getCourseNumber() << ", " << course.second.getCourseTitle() << endl;
    }
}

// Function to print course information
void printCourseInformation(const unordered_map<string, Course>& courses, const string& courseNumber) {
    auto it = courses.find(courseNumber);
    if (it != courses.end()) {
        cout << it->second.getCourseNumber() << ", " << it->second.getCourseTitle() << endl;
        cout << "Prerequisites:";
        for (const auto& prereq : it->second.getPrerequisites()) {
            cout << " " << prereq;
        }
        cout << endl;
    }
    else {
        cout << "Course not found." << endl;
    }
}
