#include "Donor.hpp"
#include "Common.hpp"
namespace annadatu {
Role Donor::getRole() const { return Role::Donor; }
std::string Donor::getRoleName() const { return "Donor"; }
std::string Donor::serialize() const {
    return id + "|Donor|" + name + "|" + email + "|" + phone + "|" + location.serialize() + "|" + category;
}
}
