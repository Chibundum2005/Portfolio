#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

struct User {
    string username;
    string password;
};

struct Student {
    string username;
    string password;
    float ca1Score;
    float ca2Score;
    float examScore;
    float overallScore; 
};

void saveSearchRecord(const Student& student);
void displayAllRecords(const vector<Student>& students);

vector<Student> readStudentData(const string& filename) {
    vector<Student> students;
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Error in opening file: " << filename << endl;
        exit(1);
    }

    string line;
    getline(file, line);

    while (getline(file, line)) {
        stringstream ss(line);
        string username, password;
        float ca1, ca2, exam;

        getline(ss, username, ',');
        getline(ss, password, ',');
        ss >> ca1 >> ca2 >> exam;

        students.push_back({username, password, ca1, ca2, exam, 0.0});
    }

    file.close();
    return students;
}

bool login(const vector<Student>& students) {
    string enteredusername, enteredpassword;

    cout << "GROUP 6 MANAGEMENT SYSTEM\nGroup Members:\nUmeh Chibundum\nOkpara Clinton\nGbulie Chisom\nIbrahim Abdulaziz\nOsumili Chiamaka\nOlorundare Ayomide\n" <<endl;
    cout << "Enter your username: ";
    cin >> enteredusername;
    cout << "Enter your password: ";
    cin >> enteredpassword;

    for (const auto& student : students) {
        if (student.username == enteredusername && student.password == enteredpassword) {
            cout << "Login successful, Welcome to the Group 6 Result Management System!, " << enteredusername << "!" << endl << endl;
            return true;
        }
    }

    cout << "Incorrect username or password. Please try again." << endl;
    return false;
}

void inputScores(vector<Student>& students) {
    char continueInput;
    do {
        string studentUsername;
        cout << "Enter student username to input scores: ";
        cin >> studentUsername;

        auto it = find_if(students.begin(), students.end(), [studentUsername](const Student& s) {
            return s.username == studentUsername;
        });

        if (it != students.end()) {
            do {
                cout << "Enter CA1 score (0-100): ";
                cin >> it->ca1Score;
                if (it->ca1Score < 0 || it->ca1Score > 100) {
                    cout << "Score exceeds 100. Please try again.\n";
                }
            } while (it->ca1Score < 0 || it->ca1Score > 100);

            do {
                cout << "Enter CA2 score (0-100): ";
                cin >> it->ca2Score;
                if (it->ca2Score < 0 || it->ca2Score > 100) {
                    cout << "Score exceeds 100. Please try again.\n";
                }
            } while (it->ca2Score < 0 || it->ca2Score > 100);

            do {
                cout << "Enter Exam score (0-100): ";
                cin >> it->examScore;
                if (it->examScore < 0 || it->examScore > 100) {
                    cout << "Score exceeds 100. Please try again.\n";
                }
            } while (it->examScore < 0 || it->examScore > 100);

            it->overallScore = min((it->ca1Score + it->ca2Score + it->examScore) / 3.0, 100.0);

            cout << "Scores updated successfully." << endl;
        } else {
            cout << "Student not found." << endl;
        }

        cout << "Do you want to input scores for another student? (y/n): ";
        cin >> continueInput;
    } while (continueInput == 'y' || continueInput == 'Y');
}

void searchStudent(const vector<Student>& students) {
    string studentUsername;
    cout << "Enter student username to search: ";
    cin >> studentUsername;

    auto it = find_if(students.begin(), students.end(), [studentUsername](const Student& s) {
        return s.username == studentUsername;
    });

    if (it != students.end()) {
        cout << "Username: " << it->username << endl;
        cout << "CA1 Score: " << it->ca1Score << endl;
        cout << "CA2 Score: " << it->ca2Score << endl;
        cout << "Exam Score: " << it->examScore << endl;
        cout << "Overall Score: " << it->overallScore << endl;
        char saveChoice;
        cout << "Do you want to save this record to a new file? (y/n): ";
        cin >> saveChoice;

        if (saveChoice == 'y' || saveChoice == 'Y') {
            saveSearchRecord(*it);
        }
    } else {
        cout << "Student not found." << endl;
    }
}

void saveSearchRecord(const Student& student) {
    ofstream outFile("C:\\Users\\Chib\\Desktop\\Searched_Record.csv");
    outFile << "Username,CA1,CA2,Exam,Overall Score" << endl;
    outFile << student.username << "," << student.ca1Score << ","
            << student.ca2Score << "," << student.examScore << "," << student.overallScore << endl;
    outFile.close();

    cout << "Record saved successfully." << endl;
}

void saveAllRecords(const vector<Student>& students) {
    ofstream outFile("C:\\Users\\Chib\\Desktop\\All_Student_Records.csv");
    outFile << "Username,CA1,CA2,Exam,Overall Score" << endl;
    for (const auto& student : students) {
        outFile << student.username << "," << student.ca1Score << ","
                << student.ca2Score << "," << student.examScore << "," << student.overallScore << endl;
    }
    outFile.close();

    cout << "All student records saved successfully." << endl;
}

void displayAllRecords(const vector<Student>& students) {
    cout << "All Student Records:\n";
    cout << "Username\tCA1\tCA2\tExam\tOverall Score\n";
    cout << fixed;
    for (const auto& student : students) {
        cout << student.username << "\t\t" << student.ca1Score << "\t" << student.ca2Score
             << "\t" << student.examScore << "\t" << student.overallScore << endl;
    }
}

int main() {
    string studentDataFile = "C:\\Users\\Chib\\Desktop\\admitted_students.csv";
    vector<Student> students = readStudentData(studentDataFile);

    while (!login(students)) {
    }

    char choice;
    do {
        cout << "MAIN MENU\n";
        cout << "1. Input student record\n";
        cout << "2. Search a record\n";
        cout << "3. Save all student records to a CSV file\n";
        cout << "4. Display all student records\n";
        cout << "5. Quit\n";
        cout << "Enter your choice (1-5): ";
        cin >> choice;

        switch (choice) {
            case '1':
                inputScores(students);
                break;
            case '2':
                searchStudent(students);
                break;
            case '3':
                saveAllRecords(students);
                break;
            case '4':
                displayAllRecords(students);
                break;
            case '5':
                cout << "Quitting the program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 5.\n";
                break;
        }
    } while (choice != '5');

    return 0;
}