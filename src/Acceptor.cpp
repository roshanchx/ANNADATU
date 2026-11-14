#include "Acceptor.hpp"
#include "Common.hpp"
namespace annadatu {
Role Acceptor::getRole() const { return Role::Acceptor; }
std::string Acceptor::getRoleName() const { return "Acceptor"; }
std::string Acceptor::serialize() const {
    return id + "|Acceptor|" + name + "|" + email + "|" + phone + "|" + location.serialize() + "|" + category;
}
}
