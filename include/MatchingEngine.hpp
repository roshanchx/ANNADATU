#pragma once
#include "DonationListing.hpp"
#include <vector>

namespace annadatu {
class IMatchingStrategy {
public:
    virtual ~IMatchingStrategy() = default;
    virtual double score(const DonationListing& listing, int requestedServings) const = 0;
};
class UrgencyAwareMatchingStrategy : public IMatchingStrategy {
public:
    double score(const DonationListing& listing, int requestedServings) const override;
};
class MatchingEngine {
private:
    const IMatchingStrategy& strategy;
public:
    explicit MatchingEngine(const IMatchingStrategy& strategy);
    std::vector<DonationListing> rank(std::vector<DonationListing> listings, int requestedServings) const;
};
}
