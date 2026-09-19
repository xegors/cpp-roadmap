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

bool Buy(std::vector<TProduct>& catalog, const std::string& name, int n) {
    TProduct* p = FindByName(catalog, name);
    if (p == nullptr || p->Qty < n || n <= 0)
        return false;

    p->Qty -= n;
    return true;
}

void Discount(std::vector<TProduct>& catalog, double pct) {
    for (auto& p : catalog) {
        p.Price *= (1 - pct / 100.0);
    }
}

bool RemoveByName(std::vector<TProduct>& catalog, const std::string& name) {
    for (size_t i = 0; i != catalog.size(); ++i) {
        if (catalog[i].Name == name) {
            catalog.erase(catalog.begin() + i);
            return true;
        }
    }
    return false;
}

int main() {
    std::vector<TProduct> catalog = {
        {"Local Chicken Breast", 499.9, 15, ECategory::Food},
        {.Name = "Olympus OM-D E-M1 Mark III", .Price = 10990.0, .Qty = 2, .Cat = ECategory::Tech},
        {"Some Old Soviet Bike", 4990.0, 1, ECategory::Bike},
        {"Flush by Virginia Woolf", 700.0, 70, ECategory::Book}};

    std::cout << "Trying to buy Flush: "
              << (Buy(catalog, "Flush by Virginia Woolf", 30) ? "All good!\n" : "Nah!\n");
    std::cout << "Trying to buy bike: "
              << (Buy(catalog, "Some Old Soviet Bike", 30) ? "All good!\n" : "Nah!\n");
    std::cout << "Trying to buy drone: "
              << (Buy(catalog, "Basic Drone", 1) ? "All good!\n" : "Nah!\n");
    std::cout << '\n';

    std::cout << "Before discount: " << catalog[1].Price << '\n';
    Discount(catalog, 10);
    std::cout << "After discount: " << catalog[1].Price << '\n';

    std::cout << "Before removal: " << catalog.size() << '\n';
    std::cout << "Trying to remove: "
              << (RemoveByName(catalog, "Local Chicken Breast") ? "Yeah, removed!"
                                                                : "No, cannot remove")
              << '\n';
    std::cout << "After removal: " << catalog.size() << '\n';
    /*
        After erase/push_back a previously taken TProduct* is invalidated
        (vector shifts elements or reallocates storage),
        so the pointer must be obtained again via FindByName.
    */

    std::cout << "\n----- All Goods -----\n";
    for (const auto& p : catalog) {
        std::cout << p.Name << " | " << p.Price << " | " << p.Qty << " | "
                  << static_cast<int>(p.Cat) << '\n';
    }
}