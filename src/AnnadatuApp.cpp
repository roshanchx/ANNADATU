#include "AnnadatuApp.hpp"
#include "Donor.hpp"
#include "Acceptor.hpp"
#include "UIHelper.hpp"
#include "Common.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <limits>

namespace annadatu {
AnnadatuApp::AnnadatuApp() { storage.ensureFiles(); loadData(); seedSampleData(); }
void AnnadatuApp::loadData() { users=storage.loadUsers(); donations=storage.loadDonations(); requests=storage.loadRequests(); }
void AnnadatuApp::saveData() const { storage.saveUsers(users); storage.saveDonations(donations); storage.saveRequests(requests); }
void AnnadatuApp::seedSampleData() {
    if (!users.empty() || !donations.empty()) return;
    users.push_back(std::make_shared<Donor>("DONOR-DEMO","Haldirams CP Flagship","demo-donor@example.com","9999000001",Location("Connaught Place, New Delhi"),"Restaurant"));
    users.push_back(std::make_shared<Donor>("DONOR-MESS","IIT Delhi Mess Committee","mess@example.com","9999000002",Location("Hauz Khas, New Delhi"),"Hostel Mess"));
    users.push_back(std::make_shared<Acceptor>("ACCEPTOR-DEMO","Robin Hood Army Delhi","demo-ngo@example.com","9999000003",Location("Connaught Place, New Delhi"),"Registered NGO"));
    donations.emplace_back("FOOD-DEMO-1","DONOR-DEMO",FoodItem("Fresh Idli and Sandwich Combo",PreparationType::Cooked,DietaryType::PureVeg,8.0,32,4.0,"Keep covered; collect promptly."),currentTimestamp());
    donations.emplace_back("FOOD-DEMO-2","DONOR-MESS",FoodItem("Rajma Chawal",PreparationType::Cooked,DietaryType::PureVeg,12.0,40,2.0,"Packed in food-grade containers."),currentTimestamp());
    saveData();
}
std::shared_ptr<User> AnnadatuApp::selectOrCreateUser(Role role) {
    std::cout << "\n" << (role==Role::Donor ? "DONOR" : "ACCEPTOR") << " ACCOUNTS\n";
    for(const auto& u:users) if(u->getRole()==role)
        std::cout << u->getId() << " | " << u->getName() << " | " << u->getCategory() << " | " << u->getLocation().getAddress() << '\n';
    std::cout << "\n1. Continue with an existing account\n2. Create a new account\n0. Back\n";
    int c=UI::readInt("Choose: ",0,2); if(c==0) return nullptr;
    if(c==2) { registerUser(role); return users.back(); }
    std::string id=UI::readLine("Enter account ID: ");
    for(auto& u:users) if(u->getRole()==role && u->getId()==id) return u;
    UI::message("Account ID not found."); return nullptr;
}
void AnnadatuApp::registerUser(Role role) {
    std::string name=UI::readLine("Name / organization: ");
    std::string category=UI::readLine("Category (e.g. Restaurant, Home, NGO, Shelter): ");
    std::string email=UI::readLine("Email: ");
    std::string phone=UI::readLine("Phone: ");
    std::string address=UI::readLine("Full address (entered manually): ");
    std::string id=makeId(role==Role::Donor?"DON-":"ACC-");
    if(role==Role::Donor) users.push_back(std::make_shared<Donor>(id,name,email,phone,Location(address),category));
    else users.push_back(std::make_shared<Acceptor>(id,name,email,phone,Location(address),category));
    saveData(); UI::message("Account created. Your account ID is: "+id);
}
void AnnadatuApp::printDonation(const DonationListing& d) const {
    auto donor=std::find_if(users.begin(),users.end(),[&](const auto& u){return u->getId()==d.getDonorId();});
    std::cout << "\n[" << d.getId() << "] " << d.getFood().getName()
      << "\nDonor: " << (donor!=users.end()?(*donor)->getName():d.getDonorId())
      << "\nPickup address: " << (donor!=users.end()?(*donor)->getLocation().getAddress():"Not available")
      << "\nPreparation: " << toString(d.getFood().getPreparation())
      << " | Diet: " << toString(d.getFood().getDietary())
      << "\nQuantity: " << d.getFood().getQuantityKg() << " kg | Servings: " << d.getFood().getServings()
      << "\nSafe-consumption window: " << d.getFood().getSafeHours() << " hours"
      << "\nInstructions: " << d.getFood().getInstructions()
      << "\nStatus: " << toString(d.getStatus()) << "\n";
}
void AnnadatuApp::createDonation(const std::shared_ptr<User>& donor) {
    std::string name=UI::readLine("Food item name: ");
    int p=UI::readInt("Preparation (1 Cooked, 2 Raw): ",1,2);
    int d=UI::readInt("Diet (1 Pure Veg, 2 Non-Veg, 3 Eggetarian): ",1,3);
    double kg=UI::readDouble("Quantity in kg: ",0.01,100000);
    int servings=UI::readInt("Estimated servings: ",1,1000000);
    double hours=UI::readDouble("Safe-consumption window in hours: ",0.1,1000);
    std::string instructions=UI::readLine("Handling / pickup instructions: ");
    FoodItem food(name,p==1?PreparationType::Cooked:PreparationType::Raw,
      d==1?DietaryType::PureVeg:(d==2?DietaryType::NonVeg:DietaryType::Eggetarian),kg,servings,hours,instructions);
    donations.emplace_back(makeId("FOOD-"),donor->getId(),food,currentTimestamp());
    saveData(); UI::message("Donation listed successfully.");
}
void AnnadatuApp::reviewRequests(const std::shared_ptr<User>& donor) {
    bool found=false;
    for(auto& r:requests) {
        if(r.getStatus()!=RequestStatus::Pending) continue;
        auto a=std::find_if(users.begin(),users.end(),[&](const auto& u){return u->getId()==r.getAcceptorId();});
        if(r.getDonationId().rfind("NEED: ",0)==0) {
            found=true;
            std::cout << "\nFood requirement " << r.getId()
              << "\nRequirement: " << r.getDonationId().substr(6)
              << "\nAcceptor: " << (a!=users.end()?(*a)->getName():r.getAcceptorId())
              << "\nAcceptor address: " << (a!=users.end()?(*a)->getLocation().getAddress():"Not available")
              << "\nRequested servings: " << r.getServings() << "\n";
            int choice=UI::readInt("1 Acknowledge, 2 Reject, 0 Skip: ",0,2);
            if(choice==1) r.setStatus(RequestStatus::Approved);
            else if(choice==2) r.setStatus(RequestStatus::Rejected);
            continue;
        }
        auto listing=std::find_if(donations.begin(),donations.end(),[&](const auto& d){return d.getId()==r.getDonationId() && d.getDonorId()==donor->getId();});
        if(listing==donations.end()) continue;
        found=true;
        std::cout << "\nRequest " << r.getId() << " for " << listing->getFood().getName()
          << "\nAcceptor: " << (a!=users.end()?(*a)->getName():r.getAcceptorId())
          << "\nAcceptor address: " << (a!=users.end()?(*a)->getLocation().getAddress():"Not available")
          << "\nRequested servings: " << r.getServings() << "\n";
        int choice=UI::readInt("1 Approve, 2 Reject, 0 Skip: ",0,2);
        if(choice==1 && listing->getStatus()==ListingStatus::Available) {
            r.setStatus(RequestStatus::Approved);
            listing->setStatus(ListingStatus::Reserved);
        } else if(choice==2) {
            r.setStatus(RequestStatus::Rejected);
        } else if(choice==1) {
            UI::message("This donation is no longer available.");
        }
    }
    if(!found) UI::message("No pending requests.");
    saveData();
}
void AnnadatuApp::donorMenu(const std::shared_ptr<User>& user) {
    while(true) {
        std::cout << "\nDONOR DASHBOARD - " << user->getName() << "\n1. Add food donation\n2. View my listings\n3. Review incoming requests\n4. Environmental impact summary\n0. Sign out\n";
        int c=UI::readInt("Choose: ",0,4);
        if(c==0) break;
        if(c==1) createDonation(user);
        if(c==2) { for(const auto& d:donations) if(d.getDonorId()==user->getId()) printDonation(d); }
        if(c==3) reviewRequests(user);
        if(c==4) showImpact();
        UI::pause();
    }
}
void AnnadatuApp::browseDonations(const std::shared_ptr<User>& acceptor) {
    int needed=UI::readInt("How many servings do you need? ",1,1000000);
    int diet=UI::readInt("Diet filter (1 All, 2 Pure Veg, 3 Non-Veg, 4 Eggetarian): ",1,4);
    std::vector<DonationListing> available;
    for(const auto& d:donations) {
        bool matchesDiet = diet==1 || (diet==2 && d.getFood().getDietary()==DietaryType::PureVeg)
            || (diet==3 && d.getFood().getDietary()==DietaryType::NonVeg)
            || (diet==4 && d.getFood().getDietary()==DietaryType::Eggetarian);
        if(d.getStatus()==ListingStatus::Available && d.getFood().getServings()>0 && matchesDiet) available.push_back(d);
    }
    UrgencyAwareMatchingStrategy strategy; MatchingEngine engine(strategy);
    available=engine.rank(available,needed);
    if(available.empty()) { UI::message("No available donations at the moment."); return; }
    for(const auto& d:available) printDonation(d);
    std::string id=UI::readLine("\nEnter donation ID to request (or leave blank to cancel): ");
    if(id.empty()) return;
    auto it=std::find_if(donations.begin(),donations.end(),[&](const auto& d){return d.getId()==id && d.getStatus()==ListingStatus::Available;});
    if(it==donations.end()) { UI::message("Donation not found or no longer available."); return; }
    int servings=UI::readInt("Servings requested (1-" + std::to_string(it->getFood().getServings()) + "): ",1,it->getFood().getServings());
    requests.emplace_back(makeId("REQ-"),acceptor->getId(),id,servings,currentTimestamp());
    saveData(); UI::message("Request submitted. The donor must approve it before pickup.");
}
void AnnadatuApp::raiseFoodRequest(const std::shared_ptr<User>& acceptor) {
    std::string description=UI::readLine("Describe the food requirement: ");
    int servings=UI::readInt("Required servings: ",1,1000000);
    requests.emplace_back(makeId("NEED-"),acceptor->getId(),"NEED: "+cleanField(description),servings,currentTimestamp());
    saveData();
    UI::message("Your food requirement has been saved and can be reviewed by donors.");
}
void AnnadatuApp::acceptorMenu(const std::shared_ptr<User>& user) {
    while(true) {
        std::cout << "\nACCEPTOR DASHBOARD - " << user->getName() << "\n1. Browse and request donations\n2. View my requests / confirm receipt\n3. Raise a food requirement\n4. Environmental impact summary\n0. Sign out\n";
        int c=UI::readInt("Choose: ",0,4); if(c==0) break;
        if(c==1) browseDonations(user);
        if(c==2) {
            for(auto& r:requests) if(r.getAcceptorId()==user->getId()) {
                std::cout << "\nRequest " << r.getId() << " | " << r.getDonationId()
                  << " | Servings " << r.getServings() << " | " << toString(r.getStatus()) << '\n';
                if(r.getStatus()==RequestStatus::Approved && r.getDonationId().rfind("NEED: ",0)!=0) {
                    int confirm=UI::readInt("Confirm food received? (1 Yes, 0 No): ",0,1);
                    if(confirm==1) {
                        r.setStatus(RequestStatus::Completed);
                        auto d=std::find_if(donations.begin(),donations.end(),[&](const auto& x){return x.getId()==r.getDonationId();});
                        if(d!=donations.end()) d->setStatus(ListingStatus::Completed);
                    }
                }
            }
            saveData();
        }
        if(c==3) raiseFoodRequest(user);
        if(c==4) showImpact();
        UI::pause();
    }
}
void AnnadatuApp::showImpact() const {
    double kg=0;
    for(const auto& d:donations) if(d.getStatus()==ListingStatus::Completed) kg+=d.getFood().getQuantityKg();
    std::cout << "\nENVIRONMENTAL IMPACT (completed donations)\n"
      << "Food rescued: " << std::fixed << std::setprecision(2) << kg << " kg\n"
      << "Estimated CO2e emissions averted: " << kg*2.5 << " kg CO2e\n"
      << "Estimated virtual water saved: " << kg*800 << " litres\n";
}
void AnnadatuApp::run() {
    while(true) {
        UI::banner();
        std::cout << "1. Donor\n2. Acceptor\n3. Environmental impact summary\n0. Exit\n";
        int c=UI::readInt("Choose: ",0,3); if(c==0) { saveData(); break; }
        if(c==3) { showImpact(); UI::pause(); continue; }
        auto user=selectOrCreateUser(c==1?Role::Donor:Role::Acceptor);
        if(!user) { UI::pause(); continue; }
        if(user->getRole()==Role::Donor) donorMenu(user); else acceptorMenu(user);
    }
}
}
