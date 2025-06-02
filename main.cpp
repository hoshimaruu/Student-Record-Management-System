/*
    Tasks for Student Record Management System Project

    1. Create Data Structures:
        - Use vector to store student records dynamically. <vector>----------------------- implement vector (STL) /
        - Use queue to manage enrollment requests in order. ------------------------------ implement queue (no STL)

    2. Implement Sorting:
        - Write insertion sort to sort student records by name or grades. ---------------- implement insertion sort (no STL)
                                                                          ---------------- Sort in decending order (grade then name)

    3. Implement Searching:
        - Write linear search to find a student in unsorted records. ---------------------- implement linear search

    4. Add CRUD Operations:
        - Add new student records.
        - Remove existing student records.
        - View or list student records.

    5. Manage Enrollment Requests:
        - Add enrollment requests to a queue.
        - Process enrollment requests FIFO.

    6. Implement Undo Feature:
        - Track changes (add, remove) using a stack.
        - Allow undoing the last action.

    7. Create User Interface:
    - Console menu to allow users to perform the above operations.

    Subjects:  (use inheritance)
        - Math
        - Science
        - English
        - History
        formula for average: x = ∑n
                             m = x / 4
*/

#include <iostream>
#include <vector>
#include <algorithm> // for text
#include <cctype> // for std::tolower

class Grade {
    protected:
        std::vector<std::string> subjectName = {"Math", "Science", "English", "History"};
        std::vector<double> gradeValue;
    public:
        Grade(const std::vector<double>& g) : gradeValue(g) {};
        double getTotal() {
            double total = 0.0;
            for (double grades : gradeValue) {
                total += grades;
            }
            return total;
        }
        
        double getAverage() {
            for (int grades : gradeValue) {
                if (gradeValue.empty()) {
                    throw std::out_of_range("Grade cannot be negative or empty!");
                }
            }
            return getTotal() / gradeValue.size();
        }

        // print all grades w subject names 
        void displayGrade(){
            double total = getTotal();
            double average = getAverage();
            for (int i = 0; i < gradeValue.size(); ++i) {
                std::cout << subjectName[i] << ": " << gradeValue[i] << std::endl;
            }
            std::cout << "Total: " << total << std::endl;
            std::cout << "Average: " << average << std::endl;
            if (average >= 75) {
                std::cout << "Status: Passed" << std::endl;
            } else {
                std::cout << "Status: Failed" << std::endl;
            }
        }
};

class Student : public Grade {
    protected:
        std::string name;
        std::string studentID;

    private:
        std::vector<Student> studentRecords;

    public:
        Student(const std::string& n, const std::string& id, const std::vector<double>& g) 
            : Grade(g), name(n), studentID(id) {};

        // ------------ Search ID using binary search -------------
        int binarySearch(std::vector<Student> student, const std::string& targetID) {
            int left = 0;
            int right = student.size() - 1;
            while (left <= right) {
                int mid = left + (right - left) / 2;

                if (student[mid].studentID == targetID) {
                    return mid;
                } else if (student[mid].studentID < targetID) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
            return -1;
        }

        //------------------------ Create / Remove / Update / Read --------------------------
        void displayStudentInfo() {
            std::cout << "Students" << std::endl;
            for (const auto& student : studentRecords) {
                std::cout << "\t|-Student Name: " << student.name << std::endl;
                std::cout << "\t|-Student ID: " << student.studentID << std::endl;
                displayGrade();
            }
        }

        void pushStudent() {
            // Example grades for Math, Science, English, History
            double readGrade;
            std::string readName;
            std::string studentID;
            std::vector<std::string> subjectNames = {"Math", "Science", "English", "History"};
            std::vector<double> grades;

            try {
                std::cout << "Enter Student Name: ";
                std::getline(std::cin >> std::ws, readName);
                if (readName.length() <= 0) {
                    throw std::out_of_range("Student Name cannot be empty!");
                }

                std::cout << "Enter Student ID: ";
                std::cin >> studentID;
                if (studentID.empty() || (studentID.length() < 5 && studentID.length() > 5)) {
                    throw std::out_of_range("Student ID must be at least 5 characters long!");
                }

                std::cout << "Enter grades for: \n";
                for (const auto& subject : subjectNames) {
                    std::cout << "\t" << subject << ": ";
                    std::cin >> readGrade;
                    if (readGrade < 0 || readGrade > 100) {
                        throw std::out_of_range("Grade must be between 0 and 100!");
                    }
                    grades.push_back(readGrade);
                }
                studentRecords.push_back(Student(readName, studentID, grades));

                std::cout << "Student record created successfully!" << std::endl;
            } catch (const std::out_of_range& e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        }

        void removeStudent(const std::string& id) {
            for (std::vector<Student>::iterator it = studentRecords.begin(); it != studentRecords.end(); ++it) {
                if (it->studentID == id) {
                    studentRecords.erase(it);
                    break;
                }
            }
        }

        void updateStudentInfo(const std::string& id) {
            int idx = binarySearch(studentRecords, id);


            for (size_t i = 0; i < studentRecords.size(); ++i) {
                if (static_cast<int>(i) == idx) {
                    /*
                        update:
                            -name
                            -id
                            -grades per subject 
                    */
                    double readGrade;
                    std::string readName;
                    std::vector<std::string> subjectNames = {"Math", "Science", "English", "History"};
                    std::vector<double> grades;

                    //update name
                    std::cout << "Enter new name (Press enter if you want to skip): ";
                    std::getline(std::cin >> std::ws, readName);
                    if (!readName.empty()) {
                        studentRecords[i].name = readName;
                    }

                    // update id
                    std::string newID;
                    std::cout << "Enter new ID (Press enter if you want to skip): ";
                    std::getline(std::cin >> std::ws, newID);
                    if (!newID.empty()) {
                        studentRecords[i].studentID = newID;
                    }
                    
                    // update grade per subj
                    std::cout << "Enter new grade for (Press enter if you want to skip): " << std::endl;
                    for (size_t j = 0; j < subjectNames.size(); ++j) {
                        std::cout << "\t|--" << subjectNames[j] << ": ";
                        std::string input;
                        std::getline(std::cin >> std::ws, input);
                        if (!input.empty()) {
                            try {
                                readGrade = std::stod(input);
                                if (readGrade >= 0 && readGrade <= 100) {
                                    studentRecords[i].gradeValue[j] = readGrade;
                                }
                            } catch (...) {
                                // Ignore invalid input
                            }
                        }
                    }
                }
            }
        }
};


class Enroll {
    protected:
        int enrollmentID;
        std::string enrollerName;
    private:
        std::vector<Enroll> enrollmentQueue;
    public:
        Enroll(const int& eI, const std::string& eN) 
            : enrollmentID(eI), enrollerName(eN) {};

        void enqueueEnroll() {
            int id;
            std::string name;
            std::cout << "Enter Enrollment ID (5 integers): ";
            std::cin >> id;
            if(std::to_string(id).length() != 5) {
                throw std::out_of_range("Enrollment ID must be exactly 5 characters long!");
            };
            std::cout << "Enter Enroller Name: ";
            std::getline(std::cin >> std::ws, name);
            if (name.empty()) {
                throw std::out_of_range("Enroller Name cannot be empty!");
            }
            enrollmentQueue.push_back(Enroll(id, name));
            std::cout << "Enrollment request added successfully!" << std::endl;
        }

        void dequeueEnroll() {
            if (!enrollmentQueue.empty()) {
                enrollmentQueue.erase(enrollmentQueue.begin());
                std::cout << "Enrollment request processed successfully!" << std::endl;
            } else {
                throw std::out_of_range("Enrollment queue is empty!");
            }
        }

        void displayEnrollmentQueue() {
            if (enrollmentQueue.empty()) {
                std::cout << "Enrollment queue is empty!" << std::endl;
                return;
            }
            std::cout << "Enrollment Queue:" << std::endl;
            for (const auto& enroll : enrollmentQueue) {
                for (int i = 0; i < enroll.enrollmentQueue.size(); ++i) {
                    std::cout << "Index: " << i + 1 << "\n\tEnrollment ID: " 
                                    << enroll.enrollmentID << "\n\tEnroller Name: " << enroll.enrollerName << std::endl;
                }
            }
        }

        void dequeueAndPushback() {
            if (!enrollmentQueue.empty()) {
                Enroll front = enrollmentQueue.front();
                enrollmentQueue.erase(enrollmentQueue.begin());
                enrollmentQueue.push_back(front);
                std::cout << "Moved front enrollment request to the back of the queue." << std::endl;
                Student pushStudent();
            } else {
                throw std::out_of_range("Enrollment queue is empty!");
            }
        }

};

bool isInteger(const std::string& str) 
{
    try {
        size_t pos;
        std::stoi(str, &pos);
        return pos == str.length();
    } catch (...) {
        return false;
    }
}

int main() {
    std::cout << "Student Record Management System" << std::endl;
    

    while (true) {
        
        std::cout << "\n>>> ";

        std::string choice;
        std::cin >> choice;

        // string commands
        std::string lowerChoice(choice.size(), '\0');
        std::transform(choice.begin(), choice.end(), lowerChoice.begin(),
            [](unsigned char c) { return std::tolower(c); });

        if (lowerChoice == "help") {
            std::cout << "1. Add Student Record" << std::endl;
            std::cout << "2. Remove Student Record" << std::endl;
            std::cout << "3. Update Student Record" << std::endl;
            std::cout << "4. View Student Records" << std::endl;
            std::cout << "5. Add Enrollment Request" << std::endl;
            std::cout << "6. Process Enrollment Request" << std::endl;
            std::cout << "7. Help" << std::endl;
            std::cout << "8. Exit" << std::endl;
            continue; // Skip the rest of the loop
        } else if (lowerChoice == "exit") {
            return 0; // exit the program
        } else if (lowerChoice == "add student") {

        }

        // integer commands
        switch (isInteger(choice)) {
            case 1: {
                Student student("", "", {});
                student.pushStudent();
                break;
            }
            case 2: {
                // Implement remove student logic
                break;
            }
            case 3: {
                // Implement update student logic
                break;
            }
            case 4: {
                // Implement view student records logic
                break;
            }
            case 5: {
                Enroll enqueueEnroll();
                break;
            }
            case 6: {
                Enroll dequeueEnroll();
                break;
            }
            case 7: {
                std::cout << "1. Add Student Record" << std::endl;
                std::cout << "2. Remove Student Record" << std::endl;
                std::cout << "3. Update Student Record" << std::endl;
                std::cout << "4. View Student Records" << std::endl;
                std::cout << "5. Add Enrollment Request" << std::endl;
                std::cout << "6. Process Enrollment Request" << std::endl;
                std::cout << "7. Help" << std::endl;
                std::cout << "8. Exit" << std::endl;
            }
            case 8:
                return 0; // Exit the program
            default:
                std::cout << "Invalid choice, please try again." << std::endl;
        }
    }
}