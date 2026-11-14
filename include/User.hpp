#pragma once
#include "Common.hpp"
#include "Location.hpp"
#include <memory>
#include <string>

namespace annadatu {
class User {
protected:
    std::string id, name, email, phone;
    Location location;
    std::string category;
public:
    User(const std::string& id, const std::string& name, const std::string& email,
         const std::string& phone, const Location& location, const std::string& category);
    virtual ~User() = default;
    const std::string& getId() const;
    const std::string& getName() const;
    const std::string& getEmail() const;
    const std::string& getPhone() const;
    const Location& getLocation() const;
    const std::string& getCategory() const;
    virtual Role getRole() const = 0;
    virtual std::string getRoleName() const = 0;
    virtual std::string serialize() const = 0;
    virtual void displayProfile() const;
};
}
