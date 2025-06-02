#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <string>

class Grade {
protected:
    std::vector<std::string> subjectName = {"Math", "Science", "English", "History"};
    std::vector<double> gradeValue;
public:
    Grade(const std::vector<double>& g) : gradeValue(g) {}

    double getTotal() const {
        double total = 0.0;
        for (double grade : gradeValue) {
            total += grade;
        }
        return total;
    }

    double getAverage() const {
        if (gradeValue.empty()) {
            throw std::out_of_range("Grade cannot be negative or empty!");
        }
        return getTotal() / gradeValue.size();
    }

    void displayGrade() const {
        double total = getTotal();
        double average = getAverage();
        for (size_t i = 0; i < gradeValue.size(); ++i) {
            std::cout << subjectName[i] << ": " << gradeValue[i] << std::endl;
        }
        std::cout << "Total: " << total << std::endl;
        std::cout << "Average: " << average << std::endl;
        std::cout << "Status: " << (average >= 75 ? "Passed" : "Failed") << std::endl;
    }
};

class Student : public Grade {
protected:
    std::string name;
    std::string studentID;
    static std::vector<Student> studentRecords;

public:
    Student(const std::string& n, const std::string& id, const std::vector<double>& g)
        : Grade(g), name(n), studentID(id) {}

    static int binarySearch(const std::string& targetID) {
        int left = 0, right = studentRecords.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (studentRecords[mid].studentID == targetID) return mid;
            else if (studentRecords[mid].studentID < targetID) left = mid + 1;
            else right = mid - 1;
        }
        return -1;
    }

    static void displayStudentInfo() {
        std::cout << "Students" << std::endl;
        for (const auto& student : studentRecords) {
            std::cout << "\t|-Student Name: " << student.name << std::endl;
            std::cout << "\t|-Student ID: " << student.studentID << std::endl;
            student.displayGrade();
        }
    }

    static void pushStudent() {
        std::string name, id;
        std::vector<double> grades(4);
        std::cout << "Enter Student Name: ";
        std::getline(std::cin >> std::ws, name);

        std::cout << "Enter Student ID: ";
        std::cin >> id;

        std::cout << "Enter grades for Math, Science, English, History:\n";
        for (auto& grade : grades) {
            std::cin >> grade;
        }

        studentRecords.emplace_back(name, id, grades);
        std::cout << "Student record created successfully!" << std::endl;
    }

    static void removeStudent(const std::string& id) {
        auto it = std::remove_if(studentRecords.begin(), studentRecords.end(), [&](const Student& s) {
            return s.studentID == id;
        });
        if (it != studentRecords.end()) {
            studentRecords.erase(it, studentRecords.end());
            std::cout << "Student removed." << std::endl;
        }
    }

    static void updateStudentInfo(const std::string& id) {
        int idx = binarySearch(id);
        if (idx == -1) return;

        std::string newName, newID;
        double newGrade;
        std::cout << "Enter new name (or press enter to skip): ";
        std::getline(std::cin >> std::ws, newName);
        if (!newName.empty()) studentRecords[idx].name = newName;

        std::cout << "Enter new ID (or press enter to skip): ";
        std::getline(std::cin >> std::ws, newID);
        if (!newID.empty()) studentRecords[idx].studentID = newID;

        std::vector<std::string> subjectNames = {"Math", "Science", "English", "History"};
        for (size_t i = 0; i < subjectNames.size(); ++i) {
            std::cout << "New grade for " << subjectNames[i] << " (or skip): ";
            std::string input;
            std::getline(std::cin >> std::ws, input);
            if (!input.empty()) {
                try {
                    newGrade = std::stod(input);
                    studentRecords[idx].gradeValue[i] = newGrade;
                } catch (...) {}
            }
        }
    }
};

std::vector<Student> Student::studentRecords;

class Enroll {
    int enrollmentID;
    std::string enrollerName;
    static std::vector<Enroll> enrollmentQueue;

public:
    Enroll(int id, const std::string& name) : enrollmentID(id), enrollerName(name) {}

    static void enqueueEnroll() {
        int id;
        std::string name;
        std::cout << "Enter Enrollment ID: ";
        std::cin >> id;
        std::cout << "Enter Enroller Name: ";
        std::getline(std::cin >> std::ws, name);
        enrollmentQueue.emplace_back(id, name);
        std::cout << "Enrollment added." << std::endl;
    }

    static void dequeueEnroll() {
        if (!enrollmentQueue.empty()) {
            enrollmentQueue.erase(enrollmentQueue.begin());
            std::cout << "Enrollment processed." << std::endl;
        }
    }

    static void displayEnrollmentQueue() {
        for (size_t i = 0; i < enrollmentQueue.size(); ++i) {
            std::cout << i + 1 << ". ID: " << enrollmentQueue[i].enrollmentID << " | Name: " << enrollmentQueue[i].enrollerName << std::endl;
        }
    }
};

std::vector<Enroll> Enroll::enrollmentQueue;

int main() {
    std::string choice;
    while (true) {
        std::cout << "\n>>> ";
        std::cin >> choice;

        std::transform(choice.begin(), choice.end(), choice.begin(), ::tolower);

        if (choice == "help") {
            std::cout << "1. Add\n2. Remove\n3. Update\n4. View\n5. Enroll\n6. Process\n7. Help\n8. Exit" << std::endl;
        } else if (choice == "1") {
            Student::pushStudent();
        } else if (choice == "2") {
            std::string id;
            std::cout << "Enter ID to remove: ";
            std::cin >> id;
            Student::removeStudent(id);
        } else if (choice == "3") {
            std::string id;
            std::cout << "Enter ID to update: ";
            std::cin >> id;
            Student::updateStudentInfo(id);
        } else if (choice == "4") {
            Student::displayStudentInfo();
        } else if (choice == "5") {
            Enroll::enqueueEnroll();
        } else if (choice == "6") {
            Enroll::dequeueEnroll();
        } else if (choice == "7") {
            std::cout << "1. Add\n2. Remove\n3. Update\n4. View\n5. Enroll\n6. Process\n7. Help\n8. Exit" << std::endl;
        } else if (choice == "8") {
            break;
        } else {
            std::cout << "Invalid input." << std::endl;
        }
    }
    return 0;
}