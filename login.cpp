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



void login::Login() {
    string username, password;
    cout << "\nPlease enter your username: ";
    cin >> username;
    cout << "Please enter your password: ";
    cin >> password;

   
    for (const auto& user : users) {
        if (user.getUsername() == username) {
            Status status = user.verifyPassword(password);
            if (status == SUCCESS) {
                cout << "Login successful!\n";
                return;
            } else if (status == NOT_VERIFIED) {
                cout << "Email not verified. Please verify your email first.\n";
                return;
            } else {
                cout << "Invalid password.\n";
                return;
            }
        }
    }
    cout << "User not found.\n";
}

void login::Registration() {
    string regUser, regPassword, regEmail, securityQuestion;
    cout << "\nEnter Username: ";
    cin >> regUser;
    cout << "Enter Password: ";
    cin >> regPassword;
    cout << "Security Question (What was your favorite childhood movie?): ";
    cin.ignore();
    getline(cin, securityQuestion);
    cout << "Enter Email: ";
    cin >> regEmail;

   
    string hashedPassword = User::hashPassword(regPassword);

  
    ifstream input("data.txt");
    string regId, regPass, regSec, regMail;

    while (input >> regId >> regPass >> regSec >> regMail) {
        if (regUser == regId) {
            cout << "Username already taken. Please try a different one.\n";
            return;
        }
    }

    
    ofstream output("data.txt", ios::app);
    output << regUser << ' ' << hashedPassword << ' ' << securityQuestion << ' ' << regEmail << endl;

    cout << "Registration successful! Please check your email for a verification code.\n";

    
    User newUser(regUser, regPassword, securityQuestion, regEmail);
    newUser.sendVerificationEmail();

    
    users.push_back(newUser);
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

void login::DrunkGame() {
    srand(static_cast<unsigned int>(time(0)));
    const int size = 60;
    cout << "Enter a letter to begin: ";
    char x;
    cin >> x;
    int position = size / 2;
    while (true) {
        cout << "|START|";
        for (int i = 0; i < size; i++) {
            if (i == position)
                cout << x;
            else
                cout << " ";
        }
        cout << "|END|" << endl;
        int move = rand() % 3 - 1;
        position += move;
        if (position < 1) {
            cout << "Guess you were too drunk to make it to the end...\n";
            break;
        }
        if (position > size - 1) {
            cout << "You might be drunk, but you made it to the end!\n";
            break;
        }
        for (int sleep = 0; sleep < 1000000; ++sleep);
    }
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
