#include "UIHelper.hpp"
#include <iostream>
#include <limits>
#include <sstream>

namespace annadatu { namespace UI {
void banner() {
    std::cout << "\n============================================\n"
                 "       ANNADATU - FOOD RESCUE PLATFORM\n"
                 "============================================\n";
}
void pause() { std::cout << "\nPress Enter to continue..."; std::string s; std::getline(std::cin,s); }
int readInt(const std::string& prompt, int min, int max) {
    while(true) { std::cout << prompt; std::string s; std::getline(std::cin,s); std::stringstream ss(s); int n; char c;
        if(ss >> n && !(ss >> c) && n>=min && n<=max) return n;
        std::cout << "Enter a number between " << min << " and " << max << ".\n";
    }
}
double readDouble(const std::string& prompt, double min, double max) {
    while(true) { std::cout << prompt; std::string s; std::getline(std::cin,s); std::stringstream ss(s); double n; char c;
        if(ss >> n && !(ss >> c) && n>=min && n<=max) return n;
        std::cout << "Enter a value between " << min << " and " << max << ".\n";
    }
}
std::string readLine(const std::string& prompt) { std::cout << prompt; std::string s; std::getline(std::cin,s); return s; }
void message(const std::string& text) { std::cout << "\n" << text << "\n"; }
} }
