#pragma once
#include <string>

namespace annadatu {
namespace UI {
void banner();
void pause();
int readInt(const std::string& prompt, int minimum, int maximum);
double readDouble(const std::string& prompt, double minimum, double maximum);
std::string readLine(const std::string& prompt);
void message(const std::string& text);
}
}
