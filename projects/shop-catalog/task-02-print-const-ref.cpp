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

int main() {
    std::vector<TProduct> catalog = {
        {"Local Chicken Breast", 499.9, 15, ECategory::Food},
        {.Name = "Olympus OM-D E-M1 Mark III", .Price = 10990.0, .Qty = 2, .Cat = ECategory::Tech},
        {"Some Old Soviet Bike", 4990.0, 1, ECategory::Bike},
        {"Flush by Virginia Woolf", 700.0, 70, ECategory::Book}};

    for (const auto& p : catalog) {
        std::cout << p.Name << " | " << p.Price << " | " << p.Qty << " | "
                  << static_cast<int>(p.Cat) << '\n';
    }

    catalog[1].Price = 9990.0;

    std::cout << "--- after update ---\n";
    for (const auto& p : catalog) {
        std::cout << p.Name << " | " << p.Price << " | " << p.Qty << " | "
                  << static_cast<int>(p.Cat) << '\n';
    }
}
