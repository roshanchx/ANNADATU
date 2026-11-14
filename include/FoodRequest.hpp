#pragma once
#include "Common.hpp"
#include <string>

namespace annadatu {
class FoodRequest {
private:
    std::string id, acceptorId, donationId, createdAt;
    int servings;
    RequestStatus status;
public:
    FoodRequest();
    FoodRequest(const std::string& id, const std::string& acceptorId, const std::string& donationId,
                int servings, const std::string& createdAt, RequestStatus status = RequestStatus::Pending);
    const std::string& getId() const;
    const std::string& getAcceptorId() const;
    const std::string& getDonationId() const;
    const std::string& getCreatedAt() const;
    int getServings() const;
    RequestStatus getStatus() const;
    void setStatus(RequestStatus status);
    std::string serialize() const;
    static FoodRequest deserialize(const std::string& line);
};
}
