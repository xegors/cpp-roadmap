#include <iostream>
#include <string>
#include <vector>

enum class ECategory { Food, Bike, Tech, Book };

struct TProduct {
    std::string Name;
    double Price = 0.0;
    int Qty = 0;
    ECategory Cat;
};

TProduct* FindByName(std::vector<TProduct>& catalog, const std::string& name) {
    for (auto& p : catalog) {
        if (name == p.Name)
            return &p;
    }

    return nullptr;
}
const TProduct* FindByNameConst(const std::vector<TProduct>& catalog, const std::string& name) {
    for (const auto& p : catalog) {
        if (name == p.Name)
            return &p;
    }

    return nullptr;
}
// const TProduct* - нельзя менять товар, можно менять указатель; TProduct* const - наоборот.

int main() {
    std::vector<TProduct> catalog = {
        {"Local Chicken Breast", 499.9, 15, ECategory::Food},
        {.Name = "Olympus OM-D E-M1 Mark III", .Price = 10990.0, .Qty = 2, .Cat = ECategory::Tech},
        {"Some Old Soviet Bike", 4990.0, 1, ECategory::Bike},
        {"Flush by Virginia Woolf", 700.0, 70, ECategory::Book}};

    auto p1 = FindByName(catalog, "Local Chicken Breast");
    if (p1 != nullptr) {
        std::cout << p1->Name << " | " << p1->Price << '\n';
    } else {
        std::cout << "not found!" << '\n';
    }

    auto p2 = FindByName(catalog, "My Dog");
    if (p2 != nullptr) {
        std::cout << p2->Name << " | " << p2->Price << '\n';
    } else {
        std::cout << "not found!" << '\n';
    }

    auto p3 = FindByNameConst(catalog, "Local Chicken Breast");
    if (p3 != nullptr) {
        std::cout << (*p3).Name << " | " << (*p3).Price << '\n';
    } else {
        std::cout << "not found!" << '\n';
    }
}