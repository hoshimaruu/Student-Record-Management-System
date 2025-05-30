/*
    Tasks for Student Record Management System Project

    1. Create Data Structures:
        - Use vector to store student records dynamically. <vector>----------------------- implement vector (STL) /
        - Use stack to track recent actions for undo functionality. ---------------------- implement stack (no STL) 
        - Use queue to manage enrollment requests in order. ------------------------------ implement queue (no STL)

    2. Implement Sorting:
        - Write insertion sort to sort student records by name or grades. ---------------- implement insertion sort (no STL)
                                                                          ---------------- Sort in decending order (grade then name)

    3. Implement Searching:
        - Write linear search to find a student in unsorted records. ---------------------- implement linear search
        - Write binary search to find a student in sorted records. ------------------------ implement binary search (no STL)

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

class Grade {
    protected:
        std::vector<std::string> subjectName = {"Math", "Science", "English", "History"};
        std::vector<double> gradeValue;
    public:
        Grade(const std::vector<double>& g) : gradeValue(g) {};
        double getTotal() {
            double total = 0.0;
            for (int grades : gradeValue) {
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
        int binarySearch(std::vector<Student> student, double targetID) {
            int left = 0;
            int right = student.size() - 1;
            while (left <= right) {
                int mid = left + (right - left) / 2;

                for (std::vector<Student>::iterator it = studentRecords.begin(); it != studentRecords.end(); ++it) {
                    if (it->studentID[mid] == targetID) {
                        return mid;
                    } else if (it->studentID[mid] < targetID) {
                        left = mid + 1;
                    } else {
                        right = mid - 1;
                    }
                }
            }
        }

        //------------------------ Create / Remove / Update / Read --------------------------
        void displayStudentInfo() {
            std::cout << "Student Name: " << name << std::endl;
            std::cout << "Student ID: " << studentID << std::endl;
            displayGrade();
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
                }
                break;
            }
        }

        void updateStudentInfo(const std::string& id) {
            for (std::vector<Student>::iterator it = studentRecords.begin(); it != studentRecords.end(); ++it){
                if (it->studentID == id) {
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
                    if (readName.empty()) {
                        it->name = name;
                    }

                    // update id
                    std::cout << "Enter new ID (Press enter if you want to skip): ";

                    // update grade per subj
                    std::cout << "Enter new grade for (Press enter if you want to skip): ";
                    for (int i = 0; i < studentRecords.size(); ++i) {
                        std::cout << "\t|--" << subjectNames[i] << ": ";
                        std::cin >> readGrade;
                        if (readGrade == NULL || readGrade <= 0) readGrade = it->gradeValue[i];
                    }
                }
            }
        }
};

int main() {
    
    return 0;
}