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

struct UA1 {
    int questno;
    char answer;
};



vector<User> readUserData(const string& filename) {
    vector<User> userBIGMAN ;
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Error in opening file: " << filename << endl;
        exit(1);
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string username, password;

        getline(ss, username, ',');
        getline(ss, password, ',');

        userBIGMAN.push_back({username, password});
    }

    file.close();
    return userBIGMAN;
}

bool login(const vector<User>& userBIGMAN) {
    string enteredusername, enteredpassword;

    cout << "Enter your username: ";
    cin >> enteredusername;
    cout << "Enter your password: ";
    cin >> enteredpassword;

    for (const auto& user : userBIGMAN) {
        if (user.username == enteredusername && user.password == enteredpassword) {
            cout << "Login successful, Read and Attempt all questions,   " << enteredusername << "!" << endl << endl;
            return true;
        }
    }

    cout << "Incorrect username or password. Please try again." << endl;
    return false;
}

int main() {
    string userDataFile = "C:\\Users\\Chib\\Desktop\\admitted_students.csv";
    vector<User> userBIGMAN = readUserData(userDataFile);
    while (!login(userBIGMAN )) {
    }

    string filename = "C:\\Users\\Chib\\Desktop\\questions.txt";
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Error opening file: " << filename << endl;
        return 1;
    }

    vector<UA1> UA3; 
    for (int questno = 1; questno <= 10; ++ questno) {

        vector<string> questionData;
        string line;

        for (int i = 0; i < 6; ++i) {
            getline(file, line);
            questionData.push_back(line);
        }

        cout << "Question " << questno << ":" << endl;
        for (const auto& data : questionData) {
            cout << data << endl;
        }
        char UA2;
        bool answered = false;

        for (auto& answer : UA3) {
            if (answer.questno == questno) {
                UA2 = answer.answer;
                answered = true;
                break;
            }
        }
        do {
            cout << "Input your answer (A-D), or S to skip: ";
            cin >> UA2;

            UA2 = toupper(UA2);

            if (UA2 == 'S') {
                break;
            } else if (UA2 < 'A' || UA2 > 'D') {
                cout << "Invalid option. Please enter A, B, C, D, or S to skip." << endl;
            }
        } while (UA2 < 'A' || UA2 > 'D');

        if (!answered && UA2 != 'S') {
            UA3.push_back({questno, UA2});
        }
        questionData.clear();
    }

  char revisitChoice;
do {
    cout << "Do you want to revisit a question? (Y/N): ";
    cin >> revisitChoice;
    revisitChoice = toupper(revisitChoice);

    if (revisitChoice == 'Y') {
        int revisitquestnoR;
        cout << "Enter the question number you want to revisit (1-10): ";
        cin >> revisitquestnoR;

        bool found = false;
        for (auto& answer : UA3) {
            if (answer.questno == revisitquestnoR) {
                cout << "Your previous answer for Question " << revisitquestnoR
                     << " was: " << answer.answer << endl;

                char newUA1;
                do {
                    cout << "Enter a new answer (A-D), or S to skip: ";
                    cin >> newUA1;
                    newUA1 = toupper(newUA1);

                    if (newUA1 == 'S') {
                        break;
                    } else if (newUA1 < 'A' || newUA1 > 'D') {
                        cout << "Invalid option. Please enter A, B, C, D, or S to skip." << endl;
                    }
                } while (newUA1 < 'A' || newUA1 > 'D');

                if (newUA1 != 'S') {
                    answer.answer = newUA1;
                } else {
                    UA3.erase(remove_if(UA3.begin(), UA3.end(),
                                                [revisitquestnoR](const UA1& ua) {
                                                    return ua.questno == revisitquestnoR;
                                                }),
                                      UA3.end());
                }

                found = true;
                break;
            }
        }

        if (!found) {
            char newUA1;
            do {
                cout << "Enter a new answer (A-D), or S to skip: ";
                cin >> newUA1;
                newUA1 = toupper(newUA1);

                if (newUA1 == 'S') {
                    break;
                } else if (newUA1 < 'A' || newUA1 > 'D') {
                    cout << "Invalid option. Please enter A, B, C, D, or S to skip." << endl;
                }
            } while (newUA1 < 'A' || newUA1 > 'D');

            if (newUA1 != 'S') {
                UA3.push_back({revisitquestnoR, newUA1});
            }
        }
    }
} while (revisitChoice == 'Y');

 string answersFile = "C:\\Users\\Chib\\Desktop\\answers.txt";
ifstream answersFileStream(answersFile);

if (!answersFileStream.is_open()) {
    cout << "Error opening file: " << answersFile << endl;
    return 1;
}

vector<char> correctAnswers;

char correctAnswer;
while (answersFileStream >> correctAnswer) {
    correctAnswers.push_back(correctAnswer);
}

answersFileStream.close();

cout << "Answer Sheet: " <<endl; 
for (char answer : correctAnswers) {
    cout << answer << " ";
}
cout << endl;
    int score = 0;
    for (const auto& UA2 : UA3) {
        int questno = UA2.questno - 1;

        if (questno >= 0 && questno < correctAnswers.size()) {
            char correctAnswer = correctAnswers[questno];

            cout << "Question " << UA2.questno << ": Your answer - "
                 << UA2.answer << ", Correct answer - " << correctAnswer << endl;

            if (UA2.answer == correctAnswer) {
                ++score;
            }
        }
    }

    cout <<endl; 
    cout << "Your Final Score is " << score << "/" << correctAnswers.size() << " . Thank you for taking the test!" << endl;
    cout <<endl;

    file.close();
    return 0;
}
