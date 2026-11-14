#include "User.hpp"
#include <iostream>

namespace annadatu {
User::User(const std::string& i, const std::string& n, const std::string& e, const std::string& p,
           const Location& l, const std::string& c)
    : id(cleanField(i)), name(cleanField(n)), email(cleanField(e)), phone(cleanField(p)), location(l), category(cleanField(c)) {}
const std::string& User::getId() const { return id; }
const std::string& User::getName() const { return name; }
const std::string& User::getEmail() const { return email; }
const std::string& User::getPhone() const { return phone; }
const Location& User::getLocation() const { return location; }
const std::string& User::getCategory() const { return category; }
void User::displayProfile() const {
    std::cout << "\nID: " << id << "\nName: " << name << "\nCategory: " << category
              << "\nPhone: " << phone << "\nAddress: " << location.getAddress() << "\n";
}
}
