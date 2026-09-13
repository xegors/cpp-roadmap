#include <iostream>
#include <string>
#include <vector>

enum class Category {
    Food,
    Bike,
    Tech,
    Book
};

struct Product {
    std::string name;
    double price = 0.0;
    int qty = 0;
    Category cat;
};

Product* findByName(std::vector<Product>& catalog, const std::string& name) {
    for (auto& p : catalog) {
        if (name == p.name) return &p;
    }

    return nullptr;
}
const Product* findByNameConst(const std::vector<Product>& catalog, const std::string& name) {
    for (const auto& p : catalog) {
        if (name == p.name) return &p;
    }

    return nullptr;
}
// const Product* - нельзя менять товар, можно менять указатель; Product* const - наоборот.

int main() {
    std::vector<Product> catalog = {
        {
            "Local Chicken Breast",
            499.9,
            15,
            Category::Food
        },
        {
            .name = "Olympus OM-D E-M1 Mark III",
            .price = 10990.0,
            .qty = 2,
            .cat = Category::Tech
        },
        {
            "Some Old Soviet Bike",
            4990.0,
            1,
            Category::Bike
        },
        {
            "Flush by Virginia Woolf",
            700.0,
            70,
            Category::Book
        }
    };

    auto p1 = findByName(catalog, "Local Chicken Breast");
    if (p1 != nullptr) {
        std::cout << p1->name << " | " << p1->price << '\n';
    } else {
        std::cout << "not found!" << '\n';
    }

    auto p2 = findByName(catalog, "My Dog");
    if (p2 != nullptr) {
        std::cout << p2->name << " | " << p2->price << '\n';
    } else {
        std::cout << "not found!" << '\n';
    }

    auto p3 = findByNameConst(catalog, "Local Chicken Breast");
    if (p3 != nullptr) {
        std::cout << (*p3).name << " | " << (*p3).price << '\n';
    } else {
        std::cout << "not found!" << '\n';
    }
}