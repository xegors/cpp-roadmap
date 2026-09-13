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

bool buy(std::vector<Product>& catalog, const std::string& name, int n) {
    Product* p = findByName(catalog, name);
    if (p == nullptr || p->qty < n || n <= 0) return false;

    p->qty -= n;
    return true;
}

void discount(std::vector<Product>& catalog, double pct) {
    for (auto& p : catalog) {
        p.price *= (1 - pct / 100.0);
    }
}

bool removeByName(std::vector<Product>& catalog, const std::string& name) {
    for (size_t i = 0; i != catalog.size(); ++i) {
        if (catalog[i].name == name) {
            catalog.erase(catalog.begin() + i);
            return true;
        }
    }
    return false;
}

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

    std::cout << "Trying to buy Flush: " << (buy(catalog, "Flush by Virginia Woolf", 30) ? "All good!\n" : "Nah!\n");
    std::cout << "Trying to buy bike: " << (buy(catalog, "Some Old Soviet Bike", 30) ? "All good!\n" : "Nah!\n");
    std::cout << "Trying to buy drone: " << (buy(catalog, "Basic Drone", 1) ? "All good!\n" : "Nah!\n");
    std::cout << '\n';

    std::cout << "Before discount: " << catalog[1].price << '\n';
    discount(catalog, 10);
    std::cout << "After discount: " << catalog[1].price << '\n';

    std::cout << "Before removal: " << catalog.size() << '\n';
    std::cout << "Trying to remove: " << (removeByName(catalog, "Local Chicken Breast") ? "Yeah, removed!" : "No, cannot remove") << '\n';
    std::cout << "After removal: " << catalog.size() << '\n';
    /*
        After erase/push_back a previously taken Product* is invalidated
        (vector shifts elements or reallocates storage),
        so the pointer must be obtained again via findByName.
    */

    std::cout << "\n----- All Goods -----\n";
    for (const auto& p : catalog) {
        std::cout << p.name << " | " << p.price << " | " << p.qty << " | "
                  << static_cast<int>(p.cat) << '\n';
    }
}