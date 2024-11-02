// Title: A Login and Registration System Programmed in C++
// PROJECT FOR C/C++ PROGRAMMING TUTORIAL


#pragma once
//#include<iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

class login
{
private:
    void DrunkGame();
    void DeleteLine(string username);

public:
    void Login();
    void Registration();
    void ForgotPassword();
};

enum Status {
    SUCCESS,
    FAILURE,
    USER_NOT_FOUND,
    NOT_VERIFIED
};

class User {
private:
    string username;             // User's username
    string hashedPassword;       // Hashed password
    string securityQuestion;     // Security question for recovery
    string email;                // User's email
    int isVerified;              // Verification status (0: not verified, 1: verified)
    string verificationCode;     // Verification code for email verification

    static string hashPassword(const string& password);

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
};
