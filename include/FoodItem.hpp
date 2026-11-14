#pragma once
#include "Common.hpp"
#include <string>

namespace annadatu {
class FoodItem {
private:
    std::string name;
    PreparationType preparation;
    DietaryType dietary;
    double quantityKg;
    int servings;
    double safeHours;
    std::string instructions;
public:
    FoodItem();
    FoodItem(const std::string& name, PreparationType preparation, DietaryType dietary,
             double quantityKg, int servings, double safeHours, const std::string& instructions);
    const std::string& getName() const;
    PreparationType getPreparation() const;
    DietaryType getDietary() const;
    double getQuantityKg() const;
    int getServings() const;
    double getSafeHours() const;
    const std::string& getInstructions() const;
    std::string serialize() const;
    static FoodItem deserialize(const std::string& name, const std::string& preparation,
        const std::string& dietary, const std::string& quantity, const std::string& servings,
        const std::string& safeHours, const std::string& instructions);
};
}
