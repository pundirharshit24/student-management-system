#include <iostream>
#include <fstream>
#include <cstring>
#include <conio.h>
using namespace std;

// ?? Login with 3 Attempts + Hidden Password
void login() {
    string user;
    char ch;
    char pass[20];

    int attempts = 0;

    while (attempts < 3) {
        int i = 0;

        cout << "\n===== Admin Login =====\n";
        cout << "Enter Username: ";
        cin >> user;

        cout << "Enter Password: ";

        while (true) {
            ch = getch();

            if (ch == 13) {
                pass[i] = '\0';
                break;
            } 
            else if (ch == 8) {
                if (i > 0) {
                    i--;
                    cout << "\b \b";
                }
            } 
            else {
                pass[i++] = ch;
                cout << "*";
            }
        }

        if (user == "admin" && strcmp(pass, "1234") == 0) {
            cout << "\nLogin Successful!\n";
            return;
        } else {
            attempts++;
            cout << "\nInvalid Login! Attempts left: " << (3 - attempts) << endl;
        }
    }

    cout << "\nToo many failed attempts! Program Exit.\n";
    exit(0);
}

class Student {
public:
    int roll;
    char name[50];
    char course[50];

    void addStudent() {
        cout << "Enter Roll Number: ";
        cin >> roll;

        ifstream file("students.txt");
        int r;
        char n[50], c[50];
        bool exists = false;

        while (file >> r >> n >> c) {
            if (r == roll) {
                exists = true;
                break;
            }
        }
        file.close();

        if (exists) {
            cout << "This student information already exists!\n";
            return;
        }

        cout << "Enter Name: ";
        cin >> name;
        cout << "Enter Course: ";
        cin >> course;

        ofstream out("students.txt", ios::app);
        out << roll << " " << name << " " << course << endl;
        out.close();

        cout << "Student Added Successfully!\n";
    }

    void viewStudents() {
        ifstream file("students.txt");
        cout << "\n--- Student Records ---\n";

        while (file >> roll >> name >> course) {
            cout << "Roll: " << roll
                 << " | Name: " << name
                 << " | Course: " << course << endl;
        }

        file.close();
    }

    void searchStudent() {
        int r;
        cout << "Enter Roll Number: ";
        cin >> r;

        ifstream file("students.txt");
        bool found = false;

        while (file >> roll >> name >> course) {
            if (roll == r) {
                cout << "Found: " << roll << " " << name << " " << course << endl;
                found = true;
            }
        }

        if (!found)
            cout << "Student Not Found!\n";

        file.close();
    }

    // ?? Updated Selective Update Feature
    void updateStudent() {
        int r;
        cout << "Enter Roll Number to Update: ";
        cin >> r;

        ifstream file("students.txt");
        ofstream temp("temp.txt");

        bool found = false;
        int choice;

        while (file >> roll >> name >> course) {
            if (roll == r) {
                found = true;

                cout << "\nWhat do you want to update?\n";
                cout << "1. Name\n";
                cout << "2. Course\n";
                cout << "3. Roll Number\n";
                cout << "Enter choice: ";
                cin >> choice;

                if (choice == 1) {
                    cout << "Enter New Name: ";
                    cin >> name;
                }
                else if (choice == 2) {
                    cout << "Enter New Course: ";
                    cin >> course;
                }
                else if (choice == 3) {
                    int newRoll;
                    cout << "Enter New Roll Number: ";
                    cin >> newRoll;

                    ifstream checkFile("students.txt");
                    int cr;
                    char cn[50], cc[50];
                    bool exists = false;

                    while (checkFile >> cr >> cn >> cc) {
                        if (cr == newRoll) {
                            exists = true;
                            break;
                        }
                    }
                    checkFile.close();

                    if (exists) {
                        cout << "Roll number already exists! Update cancelled.\n";
                    } else {
                        roll = newRoll;
                    }
                }
                else {
                    cout << "Invalid choice! No changes made.\n";
                }
            }

            temp << roll << " " << name << " " << course << endl;
        }

        file.close();
        temp.close();

        remove("students.txt");
        rename("temp.txt", "students.txt");

        if (found)
            cout << "Record Updated Successfully!\n";
        else
            cout << "Student Not Found!\n";
    }

    void deleteStudent() {
        int r;
        cout << "Enter Roll Number to Delete: ";
        cin >> r;

        ifstream file("students.txt");
        ofstream temp("temp.txt");

        bool found = false;

        while (file >> roll >> name >> course) {
            if (roll != r) {
                temp << roll << " " << name << " " << course << endl;
            } else {
                found = true;
            }
        }

        file.close();
        temp.close();

        remove("students.txt");
        rename("temp.txt", "students.txt");

        if (found)
            cout << "Record Deleted Successfully!\n";
        else
            cout << "Student Not Found!\n";
    }
};

int main() {
    login();

    Student s;
    int choice;

    do {
        cout << "\n===== Student Management System =====\n";
        cout << "1. Add Student\n";
        cout << "2. View Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Exit\n";
        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            s.addStudent();
            break;
        case 2:
            s.viewStudents();
            break;
        case 3:
            s.searchStudent();
            break;
        case 4:
            s.updateStudent();
            break;
        case 5:
            s.deleteStudent();
            break;
        case 6:
            cout << "Program Ended\n";
            break;
        default:
            cout << "Invalid Choice!\n";
        }

    } while (choice != 6);

    return 0;
}
