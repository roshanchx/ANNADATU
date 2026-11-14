#include "StorageManager.hpp"
#include "Donor.hpp"
#include "Acceptor.hpp"
#include <filesystem>
#include <fstream>
#include <sstream>

namespace annadatu {
static std::vector<std::string> fields(const std::string& line) {
    std::vector<std::string> out; std::stringstream ss(line); std::string part;
    while (std::getline(ss, part, '|')) { out.push_back(part); }
    return out;
}
StorageManager::StorageManager(const std::string& dir) : dataDirectory(dir) {}
void StorageManager::ensureFiles() const {
    std::filesystem::create_directories(dataDirectory);
    for (const auto& name : {"users.txt","donations.txt","requests.txt"}) {
        std::ofstream f(dataDirectory + "/" + name, std::ios::app);
    }
}
std::vector<std::shared_ptr<User>> StorageManager::loadUsers() const {
    std::vector<std::shared_ptr<User>> out; std::ifstream f(dataDirectory + "/users.txt"); std::string line;
    while (std::getline(f,line)) { if(line.empty()) continue; auto v=fields(line); if(v.size()<7) continue;
        Location loc(v[5]);
        if(v[1]=="Donor") out.push_back(std::make_shared<Donor>(v[0],v[2],v[3],v[4],loc,v[6]));
        else out.push_back(std::make_shared<Acceptor>(v[0],v[2],v[3],v[4],loc,v[6]));
    } return out;
}
std::vector<DonationListing> StorageManager::loadDonations() const {
    std::vector<DonationListing> out; std::ifstream f(dataDirectory + "/donations.txt"); std::string line;
    while(std::getline(f,line)) if(!line.empty()) { try { out.push_back(DonationListing::deserialize(line)); } catch(...) {} }
    return out;
}
std::vector<FoodRequest> StorageManager::loadRequests() const {
    std::vector<FoodRequest> out; std::ifstream f(dataDirectory + "/requests.txt"); std::string line;
    while(std::getline(f,line)) if(!line.empty()) { try { out.push_back(FoodRequest::deserialize(line)); } catch(...) {} }
    return out;
}
void StorageManager::saveUsers(const std::vector<std::shared_ptr<User>>& users) const {
    std::ofstream f(dataDirectory + "/users.txt"); for(const auto& u:users) f << u->serialize() << '\n';
}
void StorageManager::saveDonations(const std::vector<DonationListing>& items) const {
    std::ofstream f(dataDirectory + "/donations.txt"); for(const auto& d:items) f << d.serialize() << '\n';
}
void StorageManager::saveRequests(const std::vector<FoodRequest>& items) const {
    std::ofstream f(dataDirectory + "/requests.txt"); for(const auto& r:items) f << r.serialize() << '\n';
}
}
