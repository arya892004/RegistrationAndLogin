// Title: A Login and Registration System Programmed in C++
// PROJECT FOR C/C++ PROGRAMMING TUTORIAL


#pragma once
//#include<iostream>
#include <string>
using namespace std;
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

enum Status { SUCCESS, FAILURE, NOT_VERIFIED };

class User {
private:
    string username;
    string hashedPassword;
    string securityQuestion;
    string email;
    int isVerified;
    string verificationCode;

    string hashPassword(const string& password);
    string generateVerificationCode();

public:
    User(const string& uname, const string& password, const string& secQuestion, const string& mail);
    Status verifyPassword(const string& password);
    string getUsername() const;
    string getEmail() const;
    int getVerificationStatus() const;
    void setVerified();
    string getSecurityQuestion() const;
    void sendVerificationEmail();
    Status verifyEmail(const string& code);
    void setPassword(const string& newPassword);
};

class login {
private:
    void DrunkGame();
    void DeleteLine(string username);
    vector<User> users;

public:
    void Login();
    void Registration();
    void VerifyEmail();
    void ForgotPassword();
};

