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

int main() {
    std::vector<Product> catalog = {
        {
            "Local Chicken Breast",
            499.9,
            15,
            Category::Food
        },
        {
            .name = "Olympus OM-D E-M1 Mark i",
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

    for (const auto& p : catalog) {
        std::cout << p.name << " | " << p.price << " | " << p.qty << " | "
                  << static_cast<int>(p.cat) << '\n';
    }

    catalog[1].price = 9990.0;

    std::cout << "--- after update ---\n";
    for (const auto& p : catalog) {
        std::cout << p.name << " | " << p.price << " | " << p.qty << " | "
                  << static_cast<int>(p.cat) << '\n';
    }
}
