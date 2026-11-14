#pragma once
#include <string>

namespace annadatu {
class Location {
private:
    std::string address;
public:
    Location() = default;
    explicit Location(const std::string& address);
    const std::string& getAddress() const;
    void setAddress(const std::string& address);
    std::string serialize() const;
};
}
