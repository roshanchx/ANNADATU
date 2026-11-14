#include "MatchingEngine.hpp"
#include <algorithm>

namespace annadatu {
double UrgencyAwareMatchingStrategy::score(const DonationListing& listing, int requestedServings) const {
    double urgency = listing.urgencyScore();
    int available = listing.getFood().getServings();
    double portionFit = available >= requestedServings ? 10.0 :
        (requestedServings > 0 ? 10.0 * available / requestedServings : 0.0);
    return urgency + portionFit;
}
MatchingEngine::MatchingEngine(const IMatchingStrategy& s) : strategy(s) {}
std::vector<DonationListing> MatchingEngine::rank(std::vector<DonationListing> listings, int requestedServings) const {
    std::stable_sort(listings.begin(), listings.end(), [&](const auto& a, const auto& b) {
        return strategy.score(a, requestedServings) > strategy.score(b, requestedServings);
    });
    return listings;
}
}
