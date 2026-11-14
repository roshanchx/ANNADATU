#pragma once
#include "FoodItem.hpp"
#include <string>

namespace annadatu {
class DonationListing {
private:
    std::string id, donorId, createdAt;
    FoodItem food;
    ListingStatus status;
public:
    DonationListing();
    DonationListing(const std::string& id, const std::string& donorId, const FoodItem& food,
                    const std::string& createdAt, ListingStatus status = ListingStatus::Available);
    const std::string& getId() const;
    const std::string& getDonorId() const;
    const std::string& getCreatedAt() const;
    const FoodItem& getFood() const;
    ListingStatus getStatus() const;
    void setStatus(ListingStatus status);
    double urgencyScore() const;
    std::string serialize() const;
    static DonationListing deserialize(const std::string& line);
};
}
