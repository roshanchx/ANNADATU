#include "Common.hpp"
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <cctype>

namespace annadatu {
std::string toString(Role v) { return v == Role::Donor ? "Donor" : "Acceptor"; }
std::string toString(PreparationType v) { return v == PreparationType::Cooked ? "Cooked" : "Raw"; }
std::string toString(DietaryType v) {
    switch (v) { case DietaryType::PureVeg: return "PureVeg"; case DietaryType::NonVeg: return "NonVeg"; default: return "Eggetarian"; }
}
std::string toString(ListingStatus v) {
    switch (v) { case ListingStatus::Available: return "Available"; case ListingStatus::Reserved: return "Reserved"; default: return "Completed"; }
}
std::string toString(RequestStatus v) {
    switch (v) { case RequestStatus::Pending: return "Pending"; case RequestStatus::Approved: return "Approved"; case RequestStatus::Rejected: return "Rejected"; default: return "Completed"; }
}
Role roleFromString(const std::string& v) { return v == "Donor" ? Role::Donor : Role::Acceptor; }
PreparationType preparationFromString(const std::string& v) { return v == "Cooked" ? PreparationType::Cooked : PreparationType::Raw; }
DietaryType dietaryFromString(const std::string& v) {
    if (v == "NonVeg") return DietaryType::NonVeg;
    if (v == "Eggetarian") return DietaryType::Eggetarian;
    return DietaryType::PureVeg;
}
ListingStatus listingStatusFromString(const std::string& v) {
    if (v == "Reserved") return ListingStatus::Reserved;
    if (v == "Completed") return ListingStatus::Completed;
    return ListingStatus::Available;
}
RequestStatus requestStatusFromString(const std::string& v) {
    if (v == "Approved") return RequestStatus::Approved;
    if (v == "Rejected") return RequestStatus::Rejected;
    if (v == "Completed") return RequestStatus::Completed;
    return RequestStatus::Pending;
}
std::string makeId(const std::string& prefix) {
    static unsigned long long counter = 0;
    auto now = std::chrono::steady_clock::now().time_since_epoch().count();
    std::ostringstream out; out << prefix << now << ++counter; return out.str();
}
std::string currentTimestamp() {
    auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::ostringstream out; out << now; return out.str();
}
std::string cleanField(std::string value) {
    std::replace(value.begin(), value.end(), '|', '/');
    std::replace(value.begin(), value.end(), '\n', ' ');
    std::replace(value.begin(), value.end(), '\r', ' ');
    return value;
}
}
