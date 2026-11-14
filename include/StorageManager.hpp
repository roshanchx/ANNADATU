#pragma once
#include "User.hpp"
#include "DonationListing.hpp"
#include "FoodRequest.hpp"
#include <memory>
#include <string>
#include <vector>

namespace annadatu {
class StorageManager {
private:
    std::string dataDirectory;
public:
    explicit StorageManager(const std::string& dataDirectory = "data");
    void ensureFiles() const;
    std::vector<std::shared_ptr<User>> loadUsers() const;
    std::vector<DonationListing> loadDonations() const;
    std::vector<FoodRequest> loadRequests() const;
    void saveUsers(const std::vector<std::shared_ptr<User>>& users) const;
    void saveDonations(const std::vector<DonationListing>& donations) const;
    void saveRequests(const std::vector<FoodRequest>& requests) const;
};
}
