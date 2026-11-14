#pragma once
#include <string>
#include <stdexcept>

namespace annadatu {
enum class Role { Donor, Acceptor };
enum class PreparationType { Cooked, Raw };
enum class DietaryType { PureVeg, NonVeg, Eggetarian };
enum class ListingStatus { Available, Reserved, Completed };
enum class RequestStatus { Pending, Approved, Rejected, Completed };

class AnnadatuException : public std::runtime_error {
public:
    explicit AnnadatuException(const std::string& message) : std::runtime_error(message) {}
};
using ValidationException = AnnadatuException;

std::string toString(Role value);
std::string toString(PreparationType value);
std::string toString(DietaryType value);
std::string toString(ListingStatus value);
std::string toString(RequestStatus value);
Role roleFromString(const std::string& value);
PreparationType preparationFromString(const std::string& value);
DietaryType dietaryFromString(const std::string& value);
ListingStatus listingStatusFromString(const std::string& value);
RequestStatus requestStatusFromString(const std::string& value);
std::string makeId(const std::string& prefix);
std::string currentTimestamp();
std::string cleanField(std::string value);
}
