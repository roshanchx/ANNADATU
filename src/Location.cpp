#include "Location.hpp"
#include "Common.hpp"

namespace annadatu {
Location::Location(const std::string& value) { setAddress(value); }
const std::string& Location::getAddress() const { return address; }
void Location::setAddress(const std::string& value) { address = cleanField(value); }
std::string Location::serialize() const { return address; }
}
