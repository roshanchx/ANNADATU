#pragma once
#include "User.hpp"

namespace annadatu {
class Donor : public User {
public:
    using User::User;
    Role getRole() const override;
    std::string getRoleName() const override;
    std::string serialize() const override;
};
}
