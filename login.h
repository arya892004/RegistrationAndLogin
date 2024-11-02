// Title: A Login and Registration System Programmed in C++
// PROJECT FOR C/C++ PROGRAMMING TUTORIAL


#pragma once
//#include<iostream>
#include <string>
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
};L

enum Status {
    SUCCESS,
    FAILURE,
    USER_NOT_FOUND,
    NOT_VERIFIED
};

class User {
private:
    string username;           
    string hashedPassword;       
    string securityQuestion;   
    string email;               
    int isVerified;             

   
    static string hashPassword(const string& password);

public:
  
    User(const string& uname, const string& password, const string& secQuestion, const string& mail);

    
    Status verifyPassword(const string& password);

   
    string getUsername() const;

   
    string getEmail() const;

    
    int getVerificationStatus() const;

   
    void setVerified();

    
    string getSecurityQuestion() const;
};
