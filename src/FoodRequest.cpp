#include "FoodRequest.hpp"
#include <sstream>
#include <vector>

namespace annadatu {
static std::vector<std::string> splitRequest(const std::string& s) {
    std::vector<std::string> v; std::stringstream ss(s); std::string x;
    while (std::getline(ss, x, '|')) { v.push_back(x); }
    return v;
}
FoodRequest::FoodRequest() : servings(0), status(RequestStatus::Pending) {}
FoodRequest::FoodRequest(const std::string& i, const std::string& a, const std::string& d, int s,
 const std::string& c, RequestStatus st) : id(i), acceptorId(a), donationId(d), createdAt(c), servings(s), status(st) {}
const std::string& FoodRequest::getId() const { return id; }
const std::string& FoodRequest::getAcceptorId() const { return acceptorId; }
const std::string& FoodRequest::getDonationId() const { return donationId; }
const std::string& FoodRequest::getCreatedAt() const { return createdAt; }
int FoodRequest::getServings() const { return servings; }
RequestStatus FoodRequest::getStatus() const { return status; }
void FoodRequest::setStatus(RequestStatus s) { status = s; }
std::string FoodRequest::serialize() const {
    return id + "|" + acceptorId + "|" + donationId + "|" + std::to_string(servings) + "|" + createdAt + "|" + toString(status);
}
FoodRequest FoodRequest::deserialize(const std::string& line) {
    auto v = splitRequest(line); if (v.size() < 6) throw AnnadatuException("Invalid request record.");
    return FoodRequest(v[0],v[1],v[2],std::stoi(v[3]),v[4],requestStatusFromString(v[5]));
}
}
