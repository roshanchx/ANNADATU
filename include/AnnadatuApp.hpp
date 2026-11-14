#pragma once
#include "StorageManager.hpp"
#include "MatchingEngine.hpp"
#include <memory>
#include <vector>

namespace annadatu {
class AnnadatuApp {
private:
    StorageManager storage;
    std::vector<std::shared_ptr<User>> users;
    std::vector<DonationListing> donations;
    std::vector<FoodRequest> requests;
    void loadData();
    void saveData() const;
    void seedSampleData();
    std::shared_ptr<User> selectOrCreateUser(Role role);
    void registerUser(Role role);
    void donorMenu(const std::shared_ptr<User>& user);
    void acceptorMenu(const std::shared_ptr<User>& user);
    void createDonation(const std::shared_ptr<User>& donor);
    void reviewRequests(const std::shared_ptr<User>& donor);
    void browseDonations(const std::shared_ptr<User>& acceptor);
    void raiseFoodRequest(const std::shared_ptr<User>& acceptor);
    void showImpact() const;
    void printDonation(const DonationListing& listing) const;
public:
    AnnadatuApp();
    void run();
};
}
