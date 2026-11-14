#include "DonationListing.hpp"
#include <sstream>
#include <vector>
#include <cmath>

namespace annadatu {
static std::vector<std::string> split(const std::string& s) {
    std::vector<std::string> v; std::stringstream ss(s); std::string x;
    while (std::getline(ss, x, '|')) { v.push_back(x); }
    return v;
}
DonationListing::DonationListing() : status(ListingStatus::Available) {}
DonationListing::DonationListing(const std::string& i, const std::string& d, const FoodItem& f,
 const std::string& c, ListingStatus s) : id(i), donorId(d), createdAt(c), food(f), status(s) {}
const std::string& DonationListing::getId() const { return id; }
const std::string& DonationListing::getDonorId() const { return donorId; }
const std::string& DonationListing::getCreatedAt() const { return createdAt; }
const FoodItem& DonationListing::getFood() const { return food; }
ListingStatus DonationListing::getStatus() const { return status; }
void DonationListing::setStatus(ListingStatus s) { status = s; }
double DonationListing::urgencyScore() const {
    double h = food.getSafeHours();
    return h <= 2.0 ? 60.0 : std::max(0.0, 60.0 - h * 2.0);
}
std::string DonationListing::serialize() const {
    return id + "|" + donorId + "|" + food.serialize() + "|" + createdAt + "|" + toString(status);
}
DonationListing DonationListing::deserialize(const std::string& line) {
    auto v = split(line); if (v.size() < 11) throw AnnadatuException("Invalid donation record.");
    FoodItem f = FoodItem::deserialize(v[2],v[3],v[4],v[5],v[6],v[7],v[8]);
    return DonationListing(v[0],v[1],f,v[9],listingStatusFromString(v[10]));
}
}
