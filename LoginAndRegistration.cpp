// Title: A Login and Registration System Programmed in C++

#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <functional>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "login.cpp"
using namespace std;


int main() {
    Login userLogin;
    std::string userChoice;

    while (true) {
        system("clear");
        std::cout << "\t\t\t_____________________________________________\n\n\n";
        std::cout << "\t\t\t         Welcome to the MR 2024 Login!       \n\n";
        std::cout << "\t\t\t_________           Menu           __________\n\n";
        std::cout << "\t | Press 1 to LOGIN                              |\n";
        std::cout << "\t | Press 2 to REGISTER                           |\n";
        std::cout << "\t | Press 3 verify your email                     |\n";
        std::cout << "\t | Press 4 if you forgot PASSWORD                |\n";
        std::cout << "\t | Press 5 to EXIT                               |\n";
        std::cout << "\n\t\t\t Please Enter your choice: ";
        std::cin >> userChoice;
        std::cout << std::endl;

        if (userChoice == "1") {
            userLogin.Login();
        } else if (userChoice == "2") {
            userLogin.Registration();
        } else if (userChoice == "3") {
            userLogin.VerifyEmail();
        } else if (userChoice == "4") {
            userLogin.ForgotPassword();
        } else if (userChoice == "5") {
            std::cout << "\t\t\t Goodbye! \n\n";
            break; 
        } else {
            std::cout << "\t\t\t Please select from the options above\n";
        }
    }
    return 0;
}

