// Title: A Login and Registration System Programmed in C++
// PROJECT FOR C/C++ PROGRAMMING TUTORIAL


#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <functional>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "login.h"
using namespace std;

// User class functions
string User::hashPassword(const string& password) {
    string hashedPassword;
    for (char c : password) {
        hashedPassword += to_string(static_cast<int>(c) + 1);
    }
    return hashedPassword;
}

string User::generateVerificationCode() {
    srand(static_cast<unsigned int>(time(0)));
    string code;
    for (int i = 0; i < 6; ++i) {
        code += to_string(rand() % 10);
    }
    return code;
}

User::User(const string& uname, const string& password, const string& secQuestion, const string& mail)
    : username(uname), hashedPassword(hashPassword(password)), securityQuestion(secQuestion), email(mail), isVerified(0) {
    verificationCode = generateVerificationCode();
}

Status User::verifyPassword(const string& password) {
    if (hashedPassword == hashPassword(password)) {
        return isVerified ? SUCCESS : NOT_VERIFIED;
    }
    return FAILURE;
}

string User::getUsername() const {
    return username;
}

string User::getEmail() const {
    return email;
}

int User::getVerificationStatus() const {
    return isVerified;
}

void User::setVerified() {
    isVerified = 1;
}

string User::getSecurityQuestion() const {
    return securityQuestion;
}

void User::sendVerificationEmail() {
    cout << "Sending verification email to " << email << " with code: " << verificationCode << endl;
}

Status User::verifyEmail(const string& code) {
    if (code == verificationCode) {
        setVerified();
        return SUCCESS;
    }
    return FAILURE;
}

void User::setPassword(const string& newPassword) {
    hashedPassword = hashPassword(newPassword);
}

//login class functions
void login::Login() {
    string username, password;
    system("clear");
    cout << "\n\t\t\t Please enter the username and password: " << endl;
    cout << "\t\t\t USERNAME: ";
    cin >> username;
    cout << "\t\t\t PASSWORD: ";
    cin >> password;

    for (auto& user : users) {
        if (user.getUsername() == username) {
            Status status = user.verifyPassword(password);
            if (status == SUCCESS) {
                cout << "\nLogin successful!\n";
                return;
            } else if (status == NOT_VERIFIED) {
                cout << "\nEmail not verified. Please verify your email first.\n";
                return;
            }
        }
    }
    cout << "\nInvalid username or password.\n";
}

void login::Registration() {
    string regUser, regPassword, regEmail, securityQuestion;
    system("clear");
    cout << "\n\t\t\t Enter Username: ";
    cin >> regUser;
    cout << "\t\t\t Enter Password: ";
    cin >> regPassword;
    cout << "\t\t\t Security Question: What was your favorite childhood movie?: ";
    cin.ignore();
    getline(cin, securityQuestion);
    cout << "\t\t\t Enter Email: ";
    cin >> regEmail;

    User newUser(regUser, regPassword, securityQuestion, regEmail);
    newUser.sendVerificationEmail(); 
    users.push_back(newUser);
    ofstream f1("data.txt", ios::app);
    f1 << regUser << ' ' << newUser.getEmail() << ' ' << newUser.getSecurityQuestion() << endl;
    system("clear");
    cout << "\n\t\t\t Registration successful!\n";
}

void login::VerifyEmail() {
    string username, code;
    cout << "\nEnter your username: ";
    cin >> username;
    cout << "Enter the verification code sent to your email: ";
    cin >> code;

    for (auto& user : users) {
        if (user.getUsername() == username) {
            Status status = user.verifyEmail(code);
            if (status == SUCCESS) {
                cout << "Email verified successfully!\n";
                return;
            } else {
                cout << "Invalid verification code.\n";
                return;
            }
        }
    }
    cout << "User not found.\n";
}

void login::ForgotPassword() {
    string username, answer, newPassword;
    system("clear");
    
    cout << "\n\t\t\tForgot Password\n";
    cout << "\t\t\tEnter your username: ";
    cin >> username;

    for (auto& user : users) {
        if (user.getUsername() == username) {
            cout << "\t\t\tSecurity Question: " << user.getSecurityQuestion() << endl;
            cout << "\t\t\tYour answer: ";
            cin.ignore(); 
            getline(cin, answer);

            
            if (answer == "correct_answer") { 
                cout << "\t\t\tEnter your new password: ";
                cin >> newPassword;
                user.setPassword(newPassword);
                cout << "\n\t\t\tPassword has been updated successfully!\n";
                return;
            } else {
                cout << "\t\t\tIncorrect answer to the security question.\n";
                return;
            }
        }
    }
    cout << "\t\t\tUser not found.\n";
}


void login::DeleteLine(string userDelete) {
    string line;
    ifstream myFile("data.txt");
    ofstream temp("temp.txt");
    while (getline(myFile, line)) {
        if (line.substr(0, userDelete.size()) != userDelete) {
            temp << line << endl;
        }
    }
    myFile.close();
    temp.close();
    remove("data.txt");
    rename("temp.txt", "data.txt");
}
