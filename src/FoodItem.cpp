#include "FoodItem.hpp"
#include "Common.hpp"
#include <sstream>
#include <stdexcept>

namespace annadatu {
FoodItem::FoodItem() : preparation(PreparationType::Cooked), dietary(DietaryType::PureVeg), quantityKg(0), servings(0), safeHours(0) {}
FoodItem::FoodItem(const std::string& n, PreparationType p, DietaryType d, double kg, int s, double h, const std::string& i)
    : name(cleanField(n)), preparation(p), dietary(d), quantityKg(kg), servings(s), safeHours(h), instructions(cleanField(i)) {
    if (name.empty() || kg <= 0 || s <= 0 || h <= 0) throw ValidationException("Food name, quantity, servings and safe-consumption hours must be valid.");
}
const std::string& FoodItem::getName() const { return name; }
PreparationType FoodItem::getPreparation() const { return preparation; }
DietaryType FoodItem::getDietary() const { return dietary; }
double FoodItem::getQuantityKg() const { return quantityKg; }
int FoodItem::getServings() const { return servings; }
double FoodItem::getSafeHours() const { return safeHours; }
const std::string& FoodItem::getInstructions() const { return instructions; }
std::string FoodItem::serialize() const {
    std::ostringstream o; o << name << '|' << toString(preparation) << '|' << toString(dietary) << '|'
      << quantityKg << '|' << servings << '|' << safeHours << '|' << instructions; return o.str();
}
FoodItem FoodItem::deserialize(const std::string& n, const std::string& p, const std::string& d,
 const std::string& kg, const std::string& s, const std::string& h, const std::string& i) {
    return FoodItem(n, preparationFromString(p), dietaryFromString(d), std::stod(kg), std::stoi(s), std::stod(h), i);
}
}
